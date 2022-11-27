/* **************************************************
**
**    III                DDD  KKK
**    III                DDD  KKK
**                       DDD  KKK
**    III   DDDDDDDDDDD  DDD  KKK            KKK
**    III  DDD           DDD  KKK            KKK
**    III  DDD           DDD  KKK           KKK
**    III  DDD           DDD  KKK        KKKKKK
**    III  DDD           DDD  KKK   KKKKKKKKK
**    III  DDD           DDD  KKK        KKKKKK
**    III  DDD           DDD  KKK           KKK
**    III  DDD           DDD  KKK            KKK
**    III   DDDDDDDDDDDDDDDD  KKK            KKK
**
**
**     SSS         FF
**    S           F   T
**     SSS   OO   FF  TTT W   W  AAA  R RR   EEE
**        S O  O  F   T   W W W  AAAA RR  R EEEEE
**    S   S O  O  F   T   W W W A   A R     E
**     SSS   OO  FFF   TT  W W   AAAA R      EEE
**
**    Copyright: (c) 2015 IDK Software Ltd
**
****************************************************
**
**	Filename	: FileInfo.cpp
**	Author		: I.Ferguson
**	Version		: 1.000
**	Date		: 26-05-2015
**
** #$$@@$$# */

#include "SIALib.h"
#include "AppConfig.h"
//#include "SMGAppOptions.h"
#include "SACmdArgs.h"
//#include "ArchiveDate.h"
#include "MGImport.h"
#include "StandardOut.h"
//#include "ArchiveRepository.h"
#include "ImageExtentions.h"
//#include "ExifObject.h"
#include "MetadataTemplateManager.h"
#include "MetadataObject.h"
#include "ImageFileReader.h"
#include "ImageIndex.h"
#include "SAUtils.h"
#include "CLogger.h"
//#include "ImageHistory.h"
#include "TargetsList.h"
#include "FileInfo.h"
//#include "BasicMetadataFactory.h"
#include "XMLWriter.h"
#include "ImagePath.h"
//#include "ArchiveObject.h"
#include "CSVDBFile.h"
#include "HistoryEvent.h"
#include "History.h"
#include "CSVDatabase.h"
#include "HookCmd.h"
//#include "ViewManager.h"
#include "SummaryFile.h"
#include "CIDKDate.h"
//#include "MirrorManager.h"
//#include "Database.h"
#include "CSVDatabase.h"
//#include "MakeMedia.h"
#include "UDPOut.h"
//#include "IntegrityManager.h"
#include "TerminalServer.h"
#include "ArchivePath.h"
//#include "CheckoutStatus.h"
#include "IndexVisitor.h"
#include "SystemHistory.h"
#include "RemoteServer.h"
#include <stdio.h>
#include <sstream>
#include "WorkspaceFiles.h"

//#include "UpdateConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

#define VERSION	"1.00"
#define BUILD	"040115.1749"

#undef FILECODE
#define FILECODE SIALIB_CPP

//int pythonmain();

namespace simplearchive {
	


	


/////////////////////////////////////////////////////////


	SIALib::SIALib() :
		m_mgImport(std::make_shared<MGImport>()),
		m_winsockRequired(false),
		m_socklibStarted(false),
		m_enableEvents(false) 
	{}


	SIALib::~SIALib()
	{
		if (m_socklibStarted) {
#ifdef _WIN32
			WSACleanup();
#endif
		}
	}


	void  SIALib::enableEvents(const char *address, int port) {
		m_udpPortNum = port;
		m_udpAddress = address;
		m_enableEvents = true;
		m_winsockRequired = true;
	}

	void  SIALib::enableServer(int port) {
		m_tcpPortNum = port;
		m_enableServer = true;
		m_winsockRequired = true;
	}

	const int SIALib::getLastCode() {
		return CLogger::getLastCode();
	}
	const char *SIALib::getLastMessage() {
		return CLogger::getLastMessage();
	}


	int SIALib::initalise(const char *appName) {
		
		AppConfig &config = AppConfig::get();
		ImagePath::initPaths();
		std::string appPerName = appName;
		appPerName += "-";
		CLogger::setAppName(appPerName);
		CLogger::setLogLevel(config.getLogLevel());
		CLogger::setConsoleLevel(config.getConsoleLevel());
		CLogger::setSilent(config.isSilent());
		CLogger::setLogPath(config.getLogPath());
		
		try {
			CLogger::startLogging();
		}
		catch (std::exception e) {
			printf("Failed to start logging");
			return -1;
		}
		

		CLogger &logger = CLogger::getLogger();

#ifdef _WIN32
		WSADATA wsa;
		if (m_winsockRequired) {
			//Initialise winsock
			if (m_socklibStarted == false) {
				
				if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
				{
					//printf("Failed. Error Code : %d", WSAGetLastError());
					return false;
				}
				
				m_socklibStarted = true;
			}
		}
#endif
		

		m_enableEvents = config.isEventsOn();
		if (m_enableEvents == true && m_socklibStarted == true) {
			m_udpPortNum = config.eventPort();
			m_udpAddress = config.eventAddress();
			if (UDPOut::enableUDPOutput(m_udpPortNum, m_udpAddress.c_str()) == false) {
				return false;
			}
		}


		m_enableServer = config.isServerOn();
		if (m_enableServer == true && m_socklibStarted == true) {
			if (UDPOut::enableUDPOutput(m_udpPortNum, m_udpAddress.c_str()) == false) {
				return false;
			}
		}


		//logger.log(LOG_STARTING, CLogger::Level::SUMMARY, "Application starting at %s", date.Print().c_str());
		logger.log(LOG_OK, CLogger::Level::FINE, "Home path is \"%s\"", config.getHomePath());

		if (ImageExtentions::setExtentionsFilePath(config.getConfigPath()) == false) {
			logger.log(LOG_OK, CLogger::Level::INFO, "Unable to find image extensions file path: \"%s\"", config.getConfigPath());
			return -1;
		}

		if (ImagePath::isWorkspaceOn()) {
			logger.log(LOG_INITALISATION, CLogger::Level::INFO, "Workspace is enabled: \"%s\"", ImagePath::getPathToWorkspace().c_str());
			if (ImagePath::checkWorkspace() == false) {
				logger.log(LOG_OK, CLogger::Level::FATAL, "Workspace folder not found at location: \"%s\"", ImagePath::getPathToWorkspace().c_str());
				return -1;
			}
		}
		else {
			logger.log(LOG_INITALISATION, CLogger::Level::INFO, "Workspace is NOT enabled");
		}

		if (ImagePath::isPictureOn()) {
			logger.log(LOG_INITALISATION, CLogger::Level::INFO, "Pictures is enabled: \"%s\"", ImagePath::getPathToPictures().c_str());
			if (ImagePath::checkPicture() == false) {
				logger.log(LOG_OK, CLogger::Level::FATAL, "Pictures folder not found at location: \"%s\"", ImagePath::getPathToPictures().c_str());
				return -1;
			}
		}
		else {
			logger.log(LOG_INITALISATION, CLogger::Level::INFO, "Pictures is NOT enabled");
		}
		
		if (ImagePath::isWWWImageOn()) {
			logger.log(LOG_INITALISATION, CLogger::Level::INFO, "WWW images is enabled: \"%s\"", ImagePath::getPathToWWWImages().c_str());
			if (ImagePath::checkWWWImage() == false) {
				logger.log(LOG_OK, CLogger::Level::FATAL, "WWW images folder not found at location: \"%s\"", ImagePath::getPathToWWWImages().c_str());
				return -1;
			}
		}
		else {
			logger.log(LOG_INITALISATION, CLogger::Level::INFO, "WWW images is NOT enabled");
		}
		/*
		std::string userMetadataPath = config.getUserMetadataPath();
		if (SAUtils::DirExists(userMetadataPath.c_str()) == false) {
			if (SAUtils::mkDir(userMetadataPath.c_str()) == false) {
				logger.log(LOG_INITALISATION, CLogger::Level::FATAL, "Cannot create Metadata path at location: \"%s\"", userMetadataPath.c_str());
				return -1;
			}
		}
		*/

		

		try {
			//auto &archiveObject = ArchiveObject::getInstance();
			//if (archiveObject.Initalise() == false) {
			//	return -1;
			//}
			
			logger.log(LOG_OK, CLogger::Level::FINE, "Log path \"%s\"", config.getLogPath());
			std::string temp = config.getHistoryPath();
			if (SAUtils::DirExists(temp.c_str()) == false) {
				logger.log(LOG_OK, CLogger::Level::INFO, "History folder not found at location: \"%s\"", temp.c_str());

				if (SAUtils::mkDir(temp.c_str()) == false) {
					logger.log(LOG_OK, CLogger::Level::FATAL, "Cannot create History folder at location: \"%s\"", temp.c_str());
					return -1;
				}
				logger.log(LOG_OK, CLogger::Level::INFO, "History folder created at location: \"%s\"", temp.c_str());
			}
			logger.log(LOG_OK, CLogger::Level::FINE, "System path \"system\"");
			temp = config.getSystemPath();
			if (SAUtils::DirExists(temp.c_str()) == false) {
				logger.log(LOG_OK, CLogger::Level::INFO, "System path not found at location: \"%s\"", temp.c_str());

				if (SAUtils::mkDir(temp.c_str()) == false) {
					logger.log(LOG_OK, CLogger::Level::FATAL, "Cannot create System path at location: \"%s\"", temp.c_str());
					return -1;
				}
				logger.log(LOG_OK, CLogger::Level::INFO, "System folder created at location: \"%s\"", temp.c_str());
			}
			
			/*
			temp = config.getIndexPath();
			if (SAUtils::DirExists(temp.c_str()) == false) {
				logger.log(LOG_OK, CLogger::Level::INFO, "Index folder not found at location: \"%s\"", temp.c_str());

				if (SAUtils::mkDir(temp.c_str()) == false) {
					logger.log(LOG_OK, CLogger::Level::FATAL, "Cannot create Index folder at location: \"%s\"", temp.c_str());
					return -1;
				}
				logger.log(LOG_OK, CLogger::Level::INFO, "Index folder created at location: \"%s\"", temp.c_str());
			}
			*/
			
			if (ImageExtentions::setExtentionsFilePath(config.getConfigPath()) == false) {
				return -1;
			}
			HookCmd::setHookPath(config.getHookPath());
//			m_ArchiveBuilder->setUseExternalExifTool(true);

//			if (m_ArchiveBuilder->Init() == false) {
//				return -1;
//			}
			
			if (config.isSQL()) {
				/*
				Database &db = Database::getInstance();
				std::string dbPath = config.getDatabasePath();
				dbPath += '/';
				dbPath += SQLITE3_DB;
				if (db.open(dbPath.c_str(), "", "") == false) {
					printf("database open returned %s", db.getError());
				}
				*/
			}
		}
		catch (SIAException e) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "Failed to complete initalisation %s\n", e.what());
			return -1;
		}
		logger.log(LOG_INITALISATION, CLogger::Level::INFO, "Initalisation complete");
		return 0;
	}




	void SIALib::start() {
		AppConfig& config = AppConfig::get();
		SummaryFile::setPath(config.getHistoryPath());
		SummaryFile& summaryFile = SummaryFile::getSummaryFile();
		CIDKDate date;
		date.Now();
		summaryFile.log(SummaryFile::SF_BRIEF, SummaryFile::SF_COMMENT, "Summary start %s", date.Print().c_str());
	}
	
	/*
	int SIALib::complete() {
		CLogger &logger = CLogger::getLogger();
		SummaryFile &summaryFile = SummaryFile::getSummaryFile();
		CIDKDate date;
		date.Now();
		logger.log(LOG_COMPLETED, CLogger::Level::SUMMARY, "Application completed successfully at %s", date.Print().c_str());
		//logger.log(LOG_SUMMARY, CLogger::Level::SUMMARY, "Completed Summary\n%s", completedSummary.getSummary());
		//logger.log(LOG_RESULT, CLogger::Level::SUMMARY, "Result: %s", completedSummary.getResult());
		summaryFile.log(SummaryFile::SF_BRIEF, SummaryFile::SF_COMMENT, "Summary start");
		return 0;
	}
	*/

	int SIALib::complete() {
		CLogger &logger = CLogger::getLogger();
		SummaryFile &summaryFile = SummaryFile::getSummaryFile();
		CIDKDate date;
		date.Now();
		logger.log(LOG_COMPLETED, CLogger::Level::SUMMARY, "Application completed successfully at %s\n", date.Print().c_str());
		summaryFile.log(SummaryFile::SF_BRIEF, SummaryFile::SF_COMMENT, "Summary start");
		return 0;
	}

	bool SIALib::scan(ResultsPresentation::FormatType& formatType, const char* file) {

		AppConfig& config = AppConfig::get();
	
		//if (m_ArchiveBuilder->scanForImages(config.getSourcePath(), formatType, file) == false) {
			//completedSummary.setResult("Failed to complete");
			//return false;
		//}
		//completedSummary.setResult("Completed Successfully");
		return true;
	}

	// using list of images in a file
	bool SIALib::ImportFile(const char *filePath, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList) {
		//if (m_ArchiveBuilder->ImportFile(filePath, optionList) == false) {
		//	return false;
		//}

		return true;
	}



	bool SIALib::Import(const char* filePath, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList) {
		AppConfig &config = AppConfig::get();
		
		
			if (m_mgImport->Import(filePath, optionList) == false) {
				return false;
			}
	
		
		return true;
	}

	bool SIALib::show() {
		
		const char* file1 = "D:/ia_test1/DSC01275_1_00001C.ARW";
		const char* file2 = "D:/ia_test1/DSC01275_1_00001C.jpg";

		OnViewRAWCmd onViewRAWCmd(file1, file2);;
		onViewRAWCmd.process();

		//completedSummary.setSummary(str.c_str());
		//completedSummary.setResult("Completed Successfully");
		return true;
	}




	bool SIALib::showVersions()
	{
		
		return true;
	}

	bool SIALib::exportImage(const char *distpath) {
		///if (ArchiveObject::getInstance().exportImages(distpath) == false) {
			//completedSummary.setResult("Failed to complete");
		//	return false;
		//}
		//completedSummary.setResult("Completed Successfully");
		return true;
	}

	bool SIALib::history(const char* scope, ResultsPresentation::FormatType& formatType, const char* file) {
		CLogger& logger = CLogger::getLogger();
		History& history = History::getHistory();
		
		if (history.systemHistoryLog(scope, formatType, file) == false) {
			logger.log(LOG_OK, CLogger::Level::ERR, "Cannot process system history");
			return false;
		}
		CLog(LOG_OK) << "Successfully processed system history" << CLogger::Level::INFO;
		return true;
	}

	bool SIALib::status(const char* scope, ResultsPresentation::FormatType& formatType, const char* file) {

		// completedSummary.setResult("Completed Successfully");
		return true;
	}

	bool SIALib::showCheckedOut(const char* scope, ResultsPresentation::FormatType& formatType, const char* file) {
		/*
		if (ArchiveObject::getInstance().showCheckedOut(scope, formatType, file) == false) {
			//completedSummary.setResult("Failed to complete");
			return false;
		}
		//completedSummary.setResult("Completed Successfully");
		*/
		return true;
	}

	

	bool SIALib::get(const char *scope, const char* version, const char *comment, bool force) {
		version = "1, 2, [4-@]";
		//if (ArchiveObject::getInstance().get(scope, version, comment, force) == false) {
		//	return false;
		//}

		return true;
	}



	

	

	bool SIALib::deleteImages(const char* scope, const char* comment, bool force) {
		//if (ArchiveObject::getInstance().uncheckout(scope, comment, force) == false) {
		//	return false;
		//}
		return true;
	}

	bool SIALib::undeleteImages(const char* scope, const char* comment) {
		//if (ArchiveObject::getInstance().uncheckout(scope, comment) == false) {
		//	return false;
		//}
		return true;
	}

	bool SIALib::log(const char* scope, const char* fromDate, const char* toDate, ResultsPresentation::FormatType& formatType, const char* filename) {
		CLogger& logger = CLogger::getLogger();
		History& history = History::getHistory();
		
		/*
		SystemHistory archiveHistory = SystemHistory::get();
		const char* scope = nullptr;
		if (archiveHistory.select(scope) == false) {
			logger.log(LOG_OK, CLogger::Level::ERR, "Cannot process archive history");
			return false;
		}
		std::shared_ptr<ResultsList> results = archiveHistory.getResults();
		if (results == nullptr) {
			logger.log(LOG_OK, CLogger::Level::WARNING, "No results for archive history");
			return false;
		}
		ArchiveHistoryResultsPresentation resultsPresentation(*results);
		resultsPresentation.writeHuman();
		
		History& History = History::getHistory();

		ImageHistory& imageHistory = ImageHistory::get();
		const char* scope = nullptr;
		if (SystemHistory.select(scope) == false) {
			logger.log(LOG_OK, CLogger::Level::ERR, "Cannot process archive history");
			return false;
		}
		std::shared_ptr<ResultsList> results = imageHistory.getResults();
		if (results == nullptr) {
			logger.log(LOG_OK, CLogger::Level::WARNING, "No results for archive history");
			return false;
		}
		ImageHistoryResultsPresentation resultsPresentation(*results);
		resultsPresentation.writeHuman();
		*/


		/*
		if (filepath == nullptr || filepath[0] == '\0') {  // System History log
			
			if (ArchiveObject::getInstance().systemHistory(fromDate, toDate, formatType, filename) == false) {
				return false;
			}

		}
		else { // Image History log 

			if (ArchiveObject::getInstance().imageHistory(filepath, formatType, filename) == false) {
				return false;
			}
		}
		*/
		return true;

	}

	
	bool SIALib::journal(const char* scope, const char* fromDate, const char* toDate, ResultsPresentation::FormatType& formatType, const char* filename) {
		CLogger& logger = CLogger::getLogger();
		History& history = History::getHistory();
		
		return true;

	}

	bool SIALib::listContents(const char *addressScope) {
	//	if (ArchiveObject::getInstance().listContents(addressScope) == false) {
	//		return false;
	//	}
		return true;
	}
#ifdef NOT_USED
	bool SIALib::view(const char *name) {
	
		/*
		if (name.compare("Master") == 0) {
		viewManager.initaliseMaster(config.getArchivePath(), config.getMasterCataloguePath());
		//if (viewManager.processMaster() == false) {
		//	return false;
		//}
		}
		else {
		*/
		ViewManager& viewManager = ViewManager::GetInstance();
		if (viewManager.process() == false) {
			return false;
		}
		return true;
	}
#endif
	
	bool SIALib::workspace(bool sync) {
		return true;
	}

	bool SIALib::metadataTemplate(bool repo, bool level, int args) {
		CLogger& logger = CLogger::getLogger();
		AppConfig& config = AppConfig::get();
		std::string templatePath = config.getTemplatePath();
		
		if (templatePath.empty()) {
			logger.log(LOG_OK, CLogger::Level::INFO, "Cannot find template path");
			return false;
		}
		bool current = (args <= 1);
		if (repo) {
			

			if (MetadataTemplateManager::readMaster(templatePath.c_str(), level, current) == false) {
				logger.log(LOG_OK, CLogger::Level::INFO, "Cannot read master template file \"%s\"", templatePath.c_str());
			}
			logger.log(LOG_OK, CLogger::Level::INFO, "Completed reading metadata template file \"%s\"", templatePath.c_str());
		}
		else {
			
			logger.log(LOG_OK, CLogger::Level::INFO, "Completed reading metadata template file \"%s\"", templatePath.c_str());
		}
		return true;
	}

	bool SIALib::metadata(const char *scope, const char* formatType, const char* filePath) {

		CSVMasterTable& masterDatabase = CSVMasterTable::get();
		if (masterDatabase.showMasterMetadata(scope, formatType, filePath) == false) {
			
			return false;
		}
		return true;
	}

	
	bool SIALib::mirror(const char *name) {
		
		AppConfig& config = AppConfig::get();
/*
		MirrorManager mirrorManager;
		
		mirrorManager.setPrimaryIndexPath(config.getIndexPath());

		if (mirrorManager.process() == false) {
			return false;
		}
*/
		/*
		
		if (mirrorManager.verifyMirror() == false) {
			return false;
		}
		*/
		return true;
	}

	bool SIALib::setProperty(const char* scope, const char* option, const char* value) {
		
		//if (ArchiveObject::getInstance().updateMasterMetadata(scope, option, value) == false) {
		//	return false;
		//}
		return true;

	}

	bool SIALib::setProperty(const char* scope, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList) {

		//if (ArchiveObject::getInstance().updateMasterMetadata(scope, optionList) == false) {
		//	return false;
		//}
		return true;
		
	}

	

	bool SIALib::checkDisk() {
	//	IntegrityManager &im = IntegrityManager::get();
	//	im.makeList();
		return true;
	}


	bool SIALib::configure(const char* configOptionBlock, const char* configOption, const char* configValue) {
		/*
		UpdateConfig updateConfig;
		if (updateConfig.update(configOptionBlock, configOption, configValue) == false) {
			return false;
		}
		*/
		return true;
	}
	
	bool SIALib::validate(Scope scope, bool main, VerifyBackups verifyBackups, bool repair) {
		CLogger &logger = CLogger::getLogger();
		/*
		IntegrityManager &im = IntegrityManager::get();
		IMCompletedSummary imCompletedSummary;
		IntegrityManager::VerifyBackups imVerifyBackups;
		switch (verifyBackups) {
		case SIALib::VerifyBackups::Backup_1: imVerifyBackups = IntegrityManager::VerifyBackups::Backup_1; break;
		case SIALib::VerifyBackups::Backup_2: imVerifyBackups = IntegrityManager::VerifyBackups::Backup_1; break;
		case SIALib::VerifyBackups::Both: imVerifyBackups = IntegrityManager::VerifyBackups::Backup_1; break;
		case SIALib::VerifyBackups::None: imVerifyBackups = IntegrityManager::VerifyBackups::Backup_1; break;
		}
		
		switch (scope) {
		case Scope::Workspace:
			if (im.validate(imCompletedSummary, IntegrityManager::Scope::Workspace, main, imVerifyBackups, repair) == false) {
				return false;
			}
			break;
		case Scope::Master:
			if (im.validate(imCompletedSummary, IntegrityManager::Scope::Master, main, imVerifyBackups, repair) == false) {
				return false;
			}
			break;
		case Scope::Derivative:
			if (im.validate(imCompletedSummary, IntegrityManager::Scope::Derivative, main, imVerifyBackups, repair) == false) {
				return false;
			}
			break;
		case Scope::All:
			if (im.validate(imCompletedSummary, IntegrityManager::Scope::All, main, imVerifyBackups, repair) == false) {
				return false;
			}
			break;
		case Scope::Main:
			if (im.validate(imCompletedSummary, IntegrityManager::Scope::Main, main, imVerifyBackups, repair) == false) {
				return false;
			}
			break;
		default:
			if (im.validate(imCompletedSummary, IntegrityManager::Scope::All, main, imVerifyBackups, repair) == false) {
				return false;
			}
		}
		CompletedSummary completedSummary;
		completedSummary.setSummary(imCompletedSummary.getSummary());
		completedSummary.setResult(imCompletedSummary.getResult());
		return true;
		*/
		/*
		else {
			switch (scope) {
			case Workspace:
				logger.log(LOG_COMMAND, CLogger::Level::SUMMARY, "Validating Workspace");
				try {
					if (im.validate(imCompletedSummary, true, false) == false) {
						return false;
					}
				}
				catch (std::exception& e) {
					logger.log(LOG_COMMAND, CLogger::Level::FATAL, e.what());
					return false;
				}
				break;
			case Master:
				logger.log(LOG_COMMAND, CLogger::Level::SUMMARY, "Validating Master");
				if (im.validate(imCompletedSummary, false, true) == false) {
					return false;
				}
				break;
			default:
				logger.log(LOG_COMMAND, CLogger::Level::SUMMARY, "Validating Both Master and Workspace");
				if (im.validate(imCompletedSummary, true, true) == false) {
					return false;
				}
			}
			//completedSummary.setSummary(imCompletedSummary.getSummary());
			//completedSummary.setResult(imCompletedSummary.getResult());
			return true;
		}
		*/
		return true;
	}

	bool SIALib::sync(MainArchives mainArchives, Backups Backups)
	{
		CLogger& logger = CLogger::getLogger();
		/*
		IntegrityManager::MainArchives imArchives;
		IntegrityManager::Backups imBackups;

		bool master = false;
		bool derivative = false;
		switch (mainArchives) {
		case SIALib::MainArchives::Derivative: 
			imArchives = IntegrityManager::MainArchives::Derivative;
			logger.log(LOG_COMPLETED, CLogger::Level::SUMMARY, "Syncing Derivative archive");
			derivative = true;
			break;
		case SIALib::MainArchives::Master:
			logger.log(LOG_COMPLETED, CLogger::Level::SUMMARY, "Syncing Master archive");
			imArchives = IntegrityManager::MainArchives::Master;
			master = true;
			break;
		case SIALib::MainArchives::Both:
			logger.log(LOG_COMPLETED, CLogger::Level::SUMMARY, "Syncing Both Master and Derivative archives");
			imArchives = IntegrityManager::MainArchives::Both;
			master = true;
			derivative = true;
			break;
		}

		
		IntegrityManager& im = IntegrityManager::get();

		switch (Backups) {
		case SIALib::Backups::Backup_1:
			imBackups = IntegrityManager::Backups::Backup_1;
			logger.log(LOG_COMPLETED, CLogger::Level::SUMMARY, "Syncing archive with Backup 1");
			if ((master && !im.isMasterBackup1enabled()) || (derivative && !im.isDerivativeBackup1enabled())) {
				logger.log(LOG_COMPLETED, CLogger::Level::ERR, "Backup 1 not enabled cannot continue;");
					return false;
			}
			break;
		case SIALib::Backups::Backup_2:
			imBackups = IntegrityManager::Backups::Backup_2;
			logger.log(LOG_COMPLETED, CLogger::Level::SUMMARY, "Syncing archive with Backup 2");
			if ((master && !im.isMasterBackup2enabled()) || (derivative && !im.isDerivativeBackup2enabled())) {
				logger.log(LOG_COMPLETED, CLogger::Level::ERR, "Backup 2 not enabled cannot continue;");
					return false;
			}
			break;
		case SIALib::Backups::Both:
			imBackups = IntegrityManager::Backups::Both;
			logger.log(LOG_COMPLETED, CLogger::Level::SUMMARY, "Syncing archive with Both Backups");
			if ((master && !im.isMasterBackup1enabled()) || (derivative && !im.isDerivativeBackup1enabled())) {
				logger.log(LOG_COMPLETED, CLogger::Level::ERR, "Backup 1 not enabled cannot continue;");
					return false;
			}
			if ((master && !im.isMasterBackup2enabled()) || (derivative && !im.isDerivativeBackup2enabled())) {
				logger.log(LOG_COMPLETED, CLogger::Level::ERR, "Backup 2 not enabled cannot continue;");
					return false;
			}
			break;
		default:
			return false;
		}
		

		bool ret = im.sync(imArchives, imBackups);

		
		int imagesUpdated = im.imagesUpdated();
		if (imagesUpdated) {
			logger.log(LOG_COMPLETED, CLogger::Level::SUMMARY, "Sync: updated %d images", imagesUpdated);
		}
		else {
			logger.log(LOG_COMPLETED, CLogger::Level::SUMMARY, "Sync: no images updated, backup was found to be up-to-date");
		}
		*/
		return true;
	}
	

	bool SIALib::remoteServer() {
		RemoteServer remoteServer;
		remoteServer.Connect(22);
		remoteServer.Run();
		/*
		CTerminalServer terminalServer;
		terminalServer.Init(22);
		terminalServer.Run();
		*/
		return true;
	}

	bool SIALib::purge() {
		return true;
	}

	
} // simplearchive
