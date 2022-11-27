#include "MGImport.h"

#include "AppConfig.h"
#include "ImageExtentions.h"
#include "TargetsList.h"
#include "CLogger.h"
#include "CSVDatabase.h"
#include "MetadataObject.h"
#include "ArchiveObject.h"
#include "MusicContainer.h"


using namespace simplearchive;

class FilesImport {
	int m_folderCount;
	int m_fileCount;
	std::shared_ptr<ImageSets> m_imageSets;
	std::shared_ptr<ImageSet> m_imageSet;
	std::string m_path;
public:
	FilesImport() noexcept {
		m_folderCount = 0;
		m_fileCount = 0;
		m_imageSets = nullptr;
		m_imageSet = nullptr;
	};
	bool add(const char* filePath) {
		CLogger& logger = CLogger::getLogger();
		if (m_imageSets == 0) {
			m_imageSets = std::make_shared<ImageSets>();
		}
		ImageExtentions& ie = ImageExtentions::get();
		std::string file = SAUtils::getFilename(filePath);
		std::string ext = SAUtils::getExtention(filePath);
		if (ie.isAllowed(ext.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::WARNING, "Not a valid file type \"%s\" rejecting ", file.c_str());
			return false;
		}
		std::string folder = SAUtils::getFolder(filePath);
		std::shared_ptr<ImageSet>imageSet = m_imageSets->find(folder.c_str());
		if (imageSet == nullptr) {
			imageSet = std::make_shared<ImageSet>(filePath);
			m_imageSets->insert(m_imageSets->end(), imageSet);
		}
		imageSet->insert(imageSet->end(), std::make_shared<ImageItem>(filePath));
		return true;
	}
	std::shared_ptr<ImageSets> getImageSets() { return m_imageSets; };
};

class ImportList : public std::vector<std::string> {
public:
	ImportList() {};
	virtual ~ImportList() {};
};

class ImportListReader {
public:
	std::unique_ptr<ImportList> Read(const char* filepath) {
		std::unique_ptr<ImportList> importFile = std::make_unique<ImportList>();
		std::string text;
		std::ifstream file(filepath);
		if (file.is_open() == false) {
			// empty?
			std::unique_ptr<ImportList> emply;
			return emply;
		}

		for (std::getline(file, text); file.good(); std::getline(file, text)) {
			importFile->push_back(text);
		}
		file.close();

		return importFile;
	}
};

class ImageProcessor {


	CSVMasterTable& m_csvDatabase;
	//std::unique_ptr<ImagePath> m_imagePath;
	MusicContainer* m_curImageSet;
	//std::unique_ptr<ArchiveDate> m_archiveDate;


	//PrimaryIndex& m_imageIndex;
	ArchiveObject& m_archiveObject;
public:

	ImageProcessor(MusicContainer* curImageSet, ArchiveObject& archiveObject) :

		m_curImageSet(curImageSet),

		m_archiveObject(archiveObject),
		m_csvDatabase(CSVMasterTable::get())

	{}

	bool Process() {
		CLogger& logger = CLogger::getLogger();
		m_csvDatabase = CSVMasterTable::get();

		if (m_curImageSet->getError() < 0) {
			logger.log(LOG_OK, CLogger::Level::ERR, "Not archiving image: \"%s\"", m_curImageSet->getName().c_str());
			return false;
		}
		m_curImageSet->PostProcess();

		/*
		m_archiveDate = std::make_unique<ArchiveDate>();
		if (m_archiveDate->process(*m_curImageSet) == false) {
			logger.log(LOG_OK, CLogger::Level::WARNING, "Image capture date, not found: \"%s\" using another date", m_curImageSet->getName().c_str());
		}

		// using another date
		ExifDate archiveDate = m_archiveDate->getArchiveDate();
		logger.log(LOG_OK, CLogger::Level::STATUS, "Image: \"%s\" is being archived under date: %s from this source: %s",
			m_curImageSet->getName().c_str(), archiveDate.toString().c_str(), m_archiveDate->getUsingDateString().c_str());
		m_curImageSet->setTime(archiveDate.getTime());
		m_imagePath = std::make_unique<ImagePath>(archiveDate.getTime());
		*/
		if (m_curImageSet->getError() < 0) {
			logger.log(LOG_OK, CLogger::Level::ERR, "Not archiving image: \"%s\"", m_curImageSet->getName().c_str());
			return false;
		}
		bool stop = false;

		/*
		logger.log(LOG_OK, CLogger::Level::INFO, "Image: %s set to archive date: \"%s\"", m_curImageSet->getName().c_str(), archiveDate.toString().c_str());
		if (m_curImageSet->getComment().empty() == true) {
			m_curImageSet->setComment("New Image");
		}
		*/

		/*
		std::string imageRootPath = m_curImageSet->getPath();
		logger.log(LOG_OK, CLogger::Level::INFO, "Image(s) source path: \"%s\"", imageRootPath.c_str());
		m_curImageSet->setImageRootPath(m_imagePath->getRelativePath());
		if (m_curImageSet->hasPictureFile()) {
			const BasicMetadata& BasicMetadata = m_curImageSet->getPictureId();
			const MetadataObject& metadataObject = *m_curImageSet->getPictureMetadata();
			//((MTRow)metadataObject).debugPrint();
			std::string picName = m_curImageSet->getPictureFile();
			std::string path = m_curImageSet->getPath();
			if (processImage(picName, path, metadataObject, BasicMetadata) == false) {
				return false;
			}

		}
		if (m_curImageSet->hasRawFile()) {
			const BasicMetadata& BasicMetadata = m_curImageSet->getRawId();
			const MetadataObject& metadataObject = *m_curImageSet->getRawMetadata();
			std::string picName = m_curImageSet->getRawFile();
			std::string path = m_curImageSet->getPath();
			if (processImage(picName, path, metadataObject, BasicMetadata) == false) {
				return false;
			}

		}
		*/
		return true;
	}

	bool hashTagMetadata(const MetadataObject& metadataObject)
	{
		/* To be Added
		HashTagIndexRow hashTagIndexRow(
			metadataObject.columnAt(DB_SEQUENCEID).getUInt(),
			metadataObject.columnAt(DB_FILENAME).getString().c_str(),
			metadataObject.columnAt(DB_ORGINALNAME).getString().c_str(),
			metadataObject.columnAt(DB_FILEPATH).getString().c_str(),
			metadataObject.columnAt(DB_UUID).getString().c_str(),
			metadataObject.columnAt(DB_SHA).getString().c_str(),
			metadataObject.columnAt(DB_CRC).getUInt());

		const std::string piPath = ImgArchiveHome::getPrimaryPath();

		MTColumn& col = metadataObject.columnAt(DB_TAGS);
		std::string tags;
		if (!col.isNull()) {
			tags = col.getString();
		}
		col = metadataObject.columnAt(DB_KEYWORDS);
		std::string keywords;
		if (!col.isNull()) {
			keywords = col.getString();
		}

		HashTag hashTag(piPath.c_str());
		if (!tags.empty()) {
			hashTag.insert(tags.c_str(), hashTagIndexRow);
		}

		Keyword keyword(piPath.c_str());
		if (!keywords.empty()) {
			keyword.insert(tags.c_str(), hashTagIndexRow);
		}
		*/


		return true;
	}
};

MGImport::MGImport() {
	m_Error = false;
	
	m_doDryRun = false;
	m_folders = 0;
	m_imageFiles = 0;
	m_imageFilesRejected = 0;
	m_imageFilesCompleted = 0;
}

MGImport::~MGImport() {

}

bool MGImport::Init() {

	AppConfig config = AppConfig::get();
	m_Error = false;

	MasterPath masterPath = MasterPath::getObject();
	m_MasterPath = masterPath.getPath();
	if (m_MasterPath.empty()) {
		return false;
	}
	//m_indexPath = m_archiveObject.getPrimaryIndexObject().getPrimaryIndexPath().getImageIndexPath();
	//if (m_indexPath.empty()) {
	//	return false;
	//}

	/*
	if (WorkspacePath::autoViewOn()) {
		WorkspacePath& workspacePath = WorkspacePath::getObject();
		m_workspacePath = workspacePath.getPath();
		if (m_workspacePath.empty()) {
			return false;
		}
	}
	*/
	m_templatePath = config.getTemplatePath();
	if (m_templatePath.empty()) {
		return false;
	}
	CLogger& logger = CLogger::getLogger();

	std::string journalPath = config.getSystemPath();
	if (SAUtils::DirExists(journalPath.c_str()) == false) {
		logger.log(LOG_OK, CLogger::Level::FATAL, "System directory not accessable? \"%s\"", journalPath.c_str());
		m_Error = true;
	}

	ImportJournalManager::setJournalFilePath(journalPath.c_str());

	//ViewManager::GetInstance().initaliseMaster(config.getWorkspacePath(), config.getMasterCataloguePath());


	logger.log(LOG_OK, CLogger::Level::INFO, "Using Master folder: \"%s\"", m_MasterPath.c_str());
	if (SAUtils::DirExists(m_MasterPath.c_str()) == false) {
		logger.log(LOG_OK, CLogger::Level::FATAL, "Archive Repository directory not accessable? \"%s\"", m_MasterPath.c_str());
		m_Error = true;
	}
	logger.log(LOG_OK, CLogger::Level::INFO, "Found Archive Repository directory \"%s\"", m_MasterPath.c_str());


	if (SAUtils::DirExists(m_indexPath.c_str()) == false) {
		logger.log(LOG_OK, CLogger::Level::FATAL, "Archive Index directory not accessable? \"%s\"", m_indexPath.c_str());
		m_Error = true;
	}
	logger.log(LOG_OK, CLogger::Level::INFO, "Found Archive Index directory \"%s\"", m_indexPath.c_str());

	/*
	if (WorkspacePath::autoViewOn()) {
		logger.log(LOG_OK, CLogger::Level::INFO, "Using Workspace folder: \"%s\"", m_workspacePath.c_str());
		if (SAUtils::DirExists(m_workspacePath.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "Workspace directory not accessable? \"%s\"", m_workspacePath.c_str());
			m_Error = true;
		}
		logger.log(LOG_OK, CLogger::Level::INFO, "Found Workspace Archive Repository directory \"%s\"", m_workspacePath.c_str());
	}
	// Primary Index path
	PrimaryIndexObject& primaryIndexObject = m_archiveObject.getPrimaryIndexObject();
	ImageIndex& imageIndex = primaryIndexObject.getimageIndex();
	imageIndex.init(m_indexPath.c_str());
	*/


	//	CDCheckInOutManager &cd = CDCheckInOutManager::get();
	//	std::string repositoryPath = m_archiveObject.getDerivativesObject().getRepositoryPath().getRepositoryPath();
	//	cd.initalise(config.getWorkspacePath(), m_MasterPath.c_str(), repositoryPath.c_str());

	m_doDryRun = config.isDryRun();
	return (!m_Error);
}

bool MGImport::Import(const char* sourcePath, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList, bool peekImport)
{
	CLogger& logger = CLogger::getLogger();
	if (SAUtils::DirExists(sourcePath) == false) {
		logger.log(LOG_OK, CLogger::Level::ERR, "Source path \"%s\" not Found", sourcePath);
		return false;
	}
	// imageSets are no longer required so can be deleted.
	ImportJournal& importJournal = ImportJournalManager::GetJournal();
	std::shared_ptr<ImageSets> imageSets = nullptr;
	if ((imageSets = processFiles(sourcePath)) == nullptr) {
		return false;
	}

	imageSets->processImportJournal(importJournal);


	if (ImportJournalManager::save()) {
		logger.log(LOG_OK, CLogger::Level::INFO, "Journal log file path \"%s\"", importJournal.getCurJournalLogFilepath());
		logger.log(LOG_OK, CLogger::Level::INFO, "Journal xml file path \"%s\"", importJournal.getCurJournalXMLFilepath());
	}
	else {
		logger.log(LOG_OK, CLogger::Level::ERR, "Journal files not saved");
	}

	if (peekImport == true) {
		return true;
	}
	if (processImageGroupSets(imageSets, importJournal, optionList) == false) {
		return false;
	}
	TargetsList::destroy();
	//if (imageSets != nullptr) {
	//	delete imageSets;
	//}
	//ArchiveObject& archiveObject = ArchiveObject::getInstance();
	//if (archiveObject.OnCompletion() == false) {
	//	return false;
	//}

	return true;
}


bool MGImport::ImportFile(const char* sourcePath, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList) {
	ImportListReader importListReader;

	std::unique_ptr<ImportList> list = importListReader.Read(sourcePath);

	for (auto i = list->begin(); i != list->end(); i++) {
		std::string fileItem = *i;
		if (SAUtils::IsFile(fileItem.c_str())) {
			continue;
		}
		else {
			if (Import(fileItem.c_str(), optionList) == false) {
				return false;
			}
		}
	}
	return true;
}

std::shared_ptr<ImageSets> MGImport::processFiles(const char* sourcePath) {

	CLogger& logger = CLogger::getLogger();

	//
	// ==== Step 1 ====
	// Read files into folder sets (ImageSets)
	//
	logger.log(LOG_ANALISING, CLogger::Level::SUMMARY, "Stage 1: Reading Image files to be processes");

	TargetsList targetsList;
	targetsList.process(sourcePath);
	m_folders = TargetsList::getFolderCount();
	m_folders++;
	m_imageFiles = TargetsList::getFileCount();
	logger.log(LOG_INITIAL_SUMMARY, CLogger::Level::SUMMARY, "Completed Stage 1: Found %d image files to be processed in %d Folder(s)", m_imageFiles, m_folders);
	std::shared_ptr<ImageSets> imageSets = nullptr;
	if ((imageSets = targetsList.getImageSets()) == nullptr) {
		// No images to process
		return nullptr;
	}

	return imageSets;
}

bool MGImport::processImageGroupSets(std::shared_ptr<ImageSets> imageSets, ImportJournal& importJournal, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList)
{
	return false;
}
