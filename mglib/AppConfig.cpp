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
**	Filename	: CRegString.cpp
**	Author		: I.Ferguson
**	Version		: 1.000
**	Date		: 26-05-2015
**
** #$$@@$$# */

#include <sstream>
#include <iomanip>
#include "AppConfig.h"
#include "SAUtils.h"
#include "ArchivePath.h"
#include "CLogger.h"
#include "HomePaths.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

#undef FILECODE
#define FILECODE APPCONFIG_CPP

#ifdef WIN32
#define STRICMP _stricmp
#else
#include <strings.h>
#define STRICMP strcasecmp
#endif

namespace simplearchive {

	std::unique_ptr<AppConfig> m_this = nullptr;
	
	bool AppConfig::m_verbose = false;
	bool AppConfig::m_quiet = true;
	bool AppConfig::m_silent = false;
	std::string AppConfig::m_logLevel = "SUMMARY";
	std::string AppConfig::m_consoleLevel;
	bool AppConfig::m_dry_run = false;
	bool AppConfig::m_sql_on = true;
	bool AppConfig::m_lightroom = false;
	bool AppConfig::m_serverMode = false;
	bool AppConfig::m_file_cat_on = false;
	bool AppConfig::m_www_cat_on = false;
	bool AppConfig::m_workspaceEnabled = false;			// Workspace Enabled
	bool AppConfig::m_exifToolEnabled = false;	// External Exif Tool Enabled
			
	bool AppConfig::m_masterViewEnabled = false;
	bool AppConfig::m_masterViewFullSizeOn = false;
	bool AppConfig::m_masterViewPreview1On = false; // Previews Enabled
	bool AppConfig::m_masterViewThumbnailOn = false;

	bool AppConfig::m_masterBackup1Enabled = false;
	bool AppConfig::m_masterBackup2Enabled = false;
	bool AppConfig::m_derivativeBackup1Enabled = false;
	bool AppConfig::m_derivativeBackup2Enabled = false;

	bool AppConfig::m_eventsOn = false; // UDP events
	bool AppConfig::m_serverOn = false;

	int AppConfig::m_tcpPortNum = 1626;
	int AppConfig::m_udpPortNum = 560;
	std::string AppConfig::m_udpAddress = "127.0.0.1";

	std::string AppConfig::m_hookPath;
	std::string AppConfig::m_toolsPath;
	std::string AppConfig::m_workspacePath;
	std::string AppConfig::m_userMetadataPath;
	std::string AppConfig::m_derivativePath;
	std::string AppConfig::m_masterPath;
	std::string AppConfig::m_sourcePath;
	std::string AppConfig::m_userspacePath;
	std::string AppConfig::m_picturePath;
	std::string AppConfig::m_configPath;
	std::string AppConfig::m_lightroomPath;
	std::string AppConfig::m_tempPath;
	std::string AppConfig::m_logPath;
	std::string AppConfig::m_homePath;
	std::string AppConfig::m_systemPath;
	std::string AppConfig::m_indexPath;
	std::string AppConfig::m_historyPath;	
	std::string AppConfig::m_exifCommandLine;
	std::string AppConfig::m_exifToolFile;
	std::string AppConfig::m_exifToolPath;
	std::string AppConfig::m_exifMapPath;
	std::string AppConfig::m_exifMapFile;
	std::string AppConfig::m_exifFileDelim = ":";
	std::string AppConfig::m_templatePath;
	std::string AppConfig::m_backupDestinationPath;
	
	std::string AppConfig::m_sqlDatabasePath;
	std::string AppConfig::m_masterBackup1;
	std::string AppConfig::m_masterBackup2;
	std::string AppConfig::m_derivativeBackup1;
	std::string AppConfig::m_derivativeBackup2;

	std::string AppConfig::m_wwwImagePath;
	
	

	long AppConfig::m_backupMediaSize;
	ExifDateTime AppConfig::m_fromDate;
	ExifDateTime AppConfig::m_toDate;
	bool AppConfig::m_isFromDate = false;
	bool AppConfig::m_isToDate = false;
	std::string AppConfig::m_filenaming = "None";

	/*
		Default paths based on UserDrive and UserHome

	*/
	

	void AppConfig::settup() {
		getWorkspacePath();
		getMasterPath();
		getDerivativePath();
		getTempPath();
		getToolsPath();
		getHookPath();
		getTemplatePath();
		getLogPath();
		getIndexPath();
		getHistoryPath();
		getExifCommandLine();
		getExifMapPath();
		getConfigPath();
	    getHomePath();
		getPicturePath();
		getDatabasePath();
		getBackupDestinationPath();
		getBackupMediaSize();
		if (isFromDateSet() == true) {
			getFromDate().toString();
		}
		if (isToDateSet() == true) {
			getToDate().toString();
		}
		isDryRun();
		isQuiet();
		isVerbose();
		getLogLevel();
	}


	
	void SharedConfig::fileBasedValues(const char *home, const char *tmpPath) {
		CLogger &logger = CLogger::getLogger();
		logger.log(LOG_OK, CLogger::Level::INFO, "Reading configuration file ");
		// Home Path (The path to this file will be based on the home path)
		std::string homePath = home;
		setHomePath(home);
		
	// General	
		std::string quiet = "false";
		setGeneral(QUIET_LABEL, quiet, quiet);
		AppConfig::m_quiet = (STRICMP(quiet.c_str(), "true") == 0);

		std::string silent = "false";
		setGeneral(SILENT_LABEL, silent, silent);
		AppConfig::m_silent = (STRICMP(silent.c_str(), "true") == 0);

		std::string dry_run = "false";
		setGeneral(DRY_RUN_LABEL, dry_run, dry_run);
		AppConfig::m_dry_run = (STRICMP(dry_run.c_str(), "true") == 0);

		std::string logLevel = "STATUS";
		setLogging(LOG_LEVEL_LABEL, logLevel, logLevel);
		AppConfig::m_logLevel = logLevel;

		std::string consoleLevel = "STATUS";
		setLogging(CONSOLE_LEVEL_LABEL, consoleLevel, consoleLevel);
		AppConfig::m_consoleLevel = consoleLevel;

		std::string sql_on = "false";
		setGeneral(SQL_LABEL, sql_on, sql_on);
		AppConfig::m_sql_on = (STRICMP(sql_on.c_str(), "true") == 0);

		
		UserspacePath& userspacePath = UserspacePath::getObject();
		bool userOn = userspacePath.autoViewOn();
		std::string user_on = (userOn) ? "true" : "false";
		setGeneral(USERSPACE_AUTO_LABEL, user_on, user_on);
		userspacePath.setAutoViewOn((STRICMP(user_on.c_str(), "true") == 0));


		
		WorkspacePath& workspacePath = WorkspacePath::getObject();
		bool autoCheckout = workspacePath.autoCheckout();
		bool viewOn = workspacePath.autoViewOn();
		std::string autoCheckout_on = (autoCheckout) ? "true" : "false";

		std::string view_on = (viewOn) ? "true" : "false";
		setGeneral(WORKSPACE_CHECKOUT_LABEL, view_on, view_on);
		setGeneral(WORKSPACE_AUTO_CHECKOUT_LABEL, autoCheckout_on, autoCheckout_on);
		workspacePath.setAutoCheckout((STRICMP(autoCheckout_on.c_str(), "true") == 0));
		workspacePath.setAutoViewOn((STRICMP(view_on.c_str(), "true") == 0));

		PicturePath& picturePath = PicturePath::getObject();
		viewOn = picturePath.autoViewOn();
		view_on = (viewOn) ? "true" : "false";
		setGeneral(FILE_CAT_LABEL, view_on, view_on);
		picturePath.setAutoViewOn((STRICMP(view_on.c_str(), "true") == 0));

		WWWImagePath& wwwImagePath = WWWImagePath::getObject();
		viewOn = wwwImagePath.autoViewOn();
		view_on = (viewOn) ? "true" : "false";
		setGeneral(WWW_CAT_LABEL, view_on, view_on);
		wwwImagePath.setAutoViewOn((STRICMP(view_on.c_str(), "true") == 0));

		std::string filenaming = "default";
		setGeneral(FILE_RENAMING_LABEL, filenaming, filenaming);
		AppConfig::m_filenaming = filenaming;

		std::string lightroom = "false";
		setGeneral(LIGHTROOM_LABEL, lightroom, lightroom);
		AppConfig::m_lightroom = (STRICMP(lightroom.c_str(), "true") == 0);

		std::string noLightroom = "NoLightroom";
		setSystemFolders(LIGHTROOM_PATH_LABEL, AppConfig::m_lightroomPath, noLightroom);

		std::string serverMode = "false";
		setGeneral(REMOTE_SERVER_MODE_LABEL, serverMode, serverMode);
		AppConfig::m_serverMode = (STRICMP(serverMode.c_str(), "true") == 0);
		
		
	// System Folders
		// Master Archive Path
		//std::shared_ptr<ConfigBlock> folders = getSystemFolders();
		//if (folders == nullptr || getRoot().value("MasterPath", AppConfig::m_masterPath) == true) {
		//	ArchivePath::setMasterPath(AppConfig::m_masterPath);
		//}
		//
//#define CONFIG_PATH_LABEL				"ConfigPath"	 
//#define TOOLS_PATH_LABEL           		"ToolsPath"

		std::string tmpStr = tmpPath;
		std::string defaultValue = homePath + TEMP_PATH;
		if (tmpStr.empty() == false) {
			defaultValue = tmpStr;
		}
		setSystemFolders(TEMP_PATH_LABEL, AppConfig::m_tempPath, defaultValue);


		defaultValue = homePath + SYSTEM_PATH;
		setSystemFolders(SYSTEM_PATH_LABEL, AppConfig::m_systemPath, defaultValue);

		defaultValue = homePath + LOG_PATH;
		setSystemFolders(LOG_PATH_LABEL, AppConfig::m_logPath, defaultValue);

		defaultValue = homePath + TOOLS_PATH;
		setSystemFolders(TOOLS_PATH_LABEL, AppConfig::m_toolsPath, defaultValue);

		defaultValue = homePath + HOOKS_PATH;
		setSystemFolders(HOOK_SCRIPTS_PATH_LABEL, AppConfig::m_hookPath, defaultValue);

		defaultValue = homePath + SQLITEDB_PATH;
		setSystemFolders(SQL_DATABASE_PATH_LABEL, AppConfig::m_sqlDatabasePath, defaultValue);

		defaultValue = homePath + HISTORY_PATH;
		setSystemFolders(HISTORY_PATH_LABEL, AppConfig::m_historyPath, defaultValue);
		
		defaultValue = homePath + TEMPLATE_PATH;
		setSystemFolders(TEMPLATE_PATH_LABEL, AppConfig::m_templatePath, defaultValue);

		MasterPath& masterPath = MasterPath::getObject();
		defaultValue = masterPath.getPath();
		setSystemFolders(MASTER_PATH_LABEL, AppConfig::m_masterPath, defaultValue);
		
		masterPath.setPath(AppConfig::m_masterPath.c_str());

		DerivativePath& derivativePath = DerivativePath::getObject();
		defaultValue = derivativePath.getPath();
		setSystemFolders(DERIVATIVE_PATH_LABEL, AppConfig::m_derivativePath, defaultValue);
		
		derivativePath.setPath(AppConfig::m_derivativePath.c_str());

	// UserspacePath
		defaultValue = userspacePath.getPath();
		setSystemFolders(USERSPACE_PATH_LABEL, AppConfig::m_userspacePath, defaultValue);
		
		userspacePath.setPath(AppConfig::m_userspacePath.c_str());

	// WorkspacePath
		if (userspacePath.isChanged()) {
			defaultValue = AppConfig::m_userspacePath + "/Workspace";
		}
		else {
			defaultValue = workspacePath.getPath();
		}
		setSystemFolders(WORKSPACE_PATH_LABEL, AppConfig::m_workspacePath, defaultValue);
		workspacePath.setPath(AppConfig::m_workspacePath.c_str());
		
	// PicturePath
		picturePath = PicturePath::getObject();
		if (userspacePath.isChanged()) {
			
			defaultValue = AppConfig::m_picturePath + "/Picture";
		}
		else {
			defaultValue = picturePath.getPath();
		}
		setSystemFolders(PICTURE_PATH_LABEL, AppConfig::m_picturePath, defaultValue);
		picturePath.setPath(AppConfig::m_picturePath.c_str());

	// WWWImagePath
		wwwImagePath = WWWImagePath::getObject();
		if (userspacePath.isChanged()) {
			
			defaultValue = AppConfig::m_userspacePath + "/WWWPictures";
		}
		else {
			defaultValue = wwwImagePath.getPath();
		}
		setSystemFolders(WWW_CAT_LABEL, AppConfig::m_wwwImagePath, defaultValue);
		wwwImagePath.setPath(AppConfig::m_wwwImagePath.c_str());

	// UserMetadataPath
		UserMetadataPath& userMetadataPath = UserMetadataPath::getObject();
		if (userspacePath.isChanged()) {
			
			defaultValue = AppConfig::m_userMetadataPath + "/Metadata";
		}
		else {
			defaultValue = userMetadataPath.getPath();
		}
		setSystemFolders(METADATA_PATH_LABEL, AppConfig::m_userMetadataPath, defaultValue);
		userMetadataPath.setPath(AppConfig::m_userMetadataPath.c_str());



		std::string file_cat_on = "false";
		setGeneral(SQL_LABEL, file_cat_on, file_cat_on);
		AppConfig::m_file_cat_on = (STRICMP(file_cat_on.c_str(), "true") == 0);
		std::string www_cat_on = "false";
		setGeneral(SQL_LABEL, www_cat_on, www_cat_on);
		AppConfig::m_www_cat_on = (STRICMP(www_cat_on.c_str(), "true") == 0);
		
		//setSystemFolders("SystemPath", AppConfig::m_systemPath, AppConfig::m_systemPath + SYSTEM_PATH);
		//AppConfig::m_indexPath = AppConfig::m_systemPath + "/index";
		//defaultValue = homePath + "/pi";
		//AppConfig::m_indexPath = defaultValue + "/index";
		
	// External Exif Tool

		std::string emptyString = "False";
		setExternalExifTool(EXIF_ENABLE_LABEL, emptyString, emptyString);
		AppConfig::m_exifToolEnabled = (STRICMP(emptyString.c_str(), "true") == 0);

		defaultValue = homePath + CONFIG_PATH;
		setExternalExifTool(EXIF_MAP_PATH_LABEL, AppConfig::m_exifMapPath, defaultValue);

		defaultValue = homePath + CONFIG_PATH;
		setExternalExifTool(EXIF_TOOL_PATH_LABEL, AppConfig::m_exifToolPath, defaultValue);

		AppConfig::m_exifMapFile = "exiftool.ini";
		setExternalExifTool(EXIF_TOOL_LABEL, AppConfig::m_exifMapFile, AppConfig::m_exifMapFile);

		AppConfig::m_exifToolFile = "exiftool.exe";
		setExternalExifTool(EXIF_TOOL_LABEL, AppConfig::m_exifToolFile, AppConfig::m_exifToolFile);

		AppConfig::m_exifCommandLine = "[source]";
		setExternalExifTool(EXIF_COMMANDLINE_LABEL, AppConfig::m_exifCommandLine, AppConfig::m_exifCommandLine);

		emptyString = ":";
		setExternalExifTool(EXIF_FILE_DELIM_LABEL, AppConfig::m_exifFileDelim, emptyString);
	
	// Master backup one	
		std::string backupEnabled = (MasterBackupOnePath::enabled())?"true":"false";
		setMaster(BACKUP_ONE_ENABLED_LABEL, backupEnabled, backupEnabled);
		AppConfig::m_masterBackup1Enabled = (STRICMP(backupEnabled.c_str(), "true") == 0);

		MasterBackupOnePath& masterBackupOnePathObj = MasterBackupOnePath::getObject();
		masterBackupOnePathObj.enabled(AppConfig::m_masterBackup1Enabled);

		std::string defaultStr = masterBackupOnePathObj.getPath();
		setMaster(BACKUP_ONE_LABEL, AppConfig::m_masterBackup1, defaultStr);
		masterBackupOnePathObj.setPath(AppConfig::m_masterBackup1.c_str());

		// Master backup two	
		backupEnabled = (MasterBackupTwoPath::enabled()) ? "true" : "false";
		setMaster(BACKUP_TWO_ENABLED_LABEL, backupEnabled, backupEnabled);
		AppConfig::m_masterBackup2Enabled = (STRICMP(backupEnabled.c_str(), "true") == 0);

		MasterBackupTwoPath& masterBackupTwoPathObj = MasterBackupTwoPath::getObject();
		masterBackupTwoPathObj.enabled(AppConfig::m_masterBackup2Enabled);
		defaultValue = masterBackupTwoPathObj.getPath();
		
		setMaster(BACKUP_TWO_LABEL, AppConfig::m_masterBackup2, defaultValue);
		masterBackupTwoPathObj.setPath(AppConfig::m_masterBackup2.c_str());

	


	// Derivative bACKUP
		backupEnabled = (DerivativeBackupOnePath::enabled()) ? "true" : "false";
		setDerivative(BACKUP_ONE_ENABLED_LABEL, backupEnabled, backupEnabled);
		AppConfig::m_derivativeBackup1Enabled = (STRICMP(backupEnabled.c_str(), "true") == 0);

		DerivativeBackupOnePath& derivativeBackupOnePathObj = DerivativeBackupOnePath::getObject();
		derivativeBackupOnePathObj.enabled(AppConfig::m_derivativeBackup1Enabled);

		defaultValue = derivativeBackupOnePathObj.getPath();
		setDerivative(BACKUP_ONE_LABEL, AppConfig::m_derivativeBackup1, defaultValue);
		derivativeBackupOnePathObj.setPath(AppConfig::m_derivativeBackup1.c_str());

		backupEnabled = (DerivativeBackupTwoPath::enabled()) ? "true" : "false";
		setDerivative(BACKUP_TWO_ENABLED_LABEL, backupEnabled, backupEnabled);
		AppConfig::m_derivativeBackup2Enabled = (STRICMP(backupEnabled.c_str(), "true") == 0);

		DerivativeBackupTwoPath& derivativeBackupTwoPathObj = DerivativeBackupTwoPath::getObject();
		derivativeBackupTwoPathObj.enabled(AppConfig::m_derivativeBackup2Enabled);

		defaultValue = derivativeBackupTwoPathObj.getPath();
		setDerivative(BACKUP_TWO_LABEL, AppConfig::m_derivativeBackup2, defaultValue);
		derivativeBackupTwoPathObj.setPath(AppConfig::m_derivativeBackup2.c_str());

	// Network
		std::string eventsOn = AppConfig::m_eventsOn ? "true" : "false";
		setNetwork(EVENTS_ENABLED_LABEL, eventsOn, eventsOn);
		AppConfig::m_eventsOn = (STRICMP(eventsOn.c_str(), "true") == 0);
		
		std::string eventsPort = std::to_string(AppConfig::m_udpPortNum);
		setNetwork(EVENTS_PORT_LABEL, eventsPort, eventsPort);
		AppConfig::m_udpPortNum = std::stoi(eventsPort);

		std::string  udpAddress = AppConfig::m_udpAddress;
		setNetwork(EVENTS_ADDRESS_LABEL, AppConfig::m_udpAddress, udpAddress);

		std::string commandsOn = AppConfig::m_serverOn ? "true" : "false";
		setNetwork(EVENTS_ENABLED_LABEL, commandsOn, commandsOn);
		AppConfig::m_eventsOn = (STRICMP(commandsOn.c_str(), "true") == 0);
		
		std::string tcpPortNum = std::to_string(AppConfig::m_tcpPortNum);
		setNetwork(COMMANDS_PORT_LABEL, tcpPortNum, tcpPortNum);
		AppConfig::m_tcpPortNum = std::stoi(tcpPortNum);


		
		//ArchivePath::setPathToWorkspace(AppConfig::m_workspacePath);
		//ArchivePath::s(AppConfig::m_userMetadataPath);
		ArchivePath::setDerivativePath(AppConfig::m_derivativePath);
		//setSystemFolders(MASTER_VIEW_PATH_LABEL, AppConfig::m_catalogPath, ctemp);
		setWorkspacePath(AppConfig::m_workspacePath.c_str());
		setMasterPath(AppConfig::m_masterPath.c_str());

		// Master
		// Backup 1
		if (AppConfig::m_masterBackup1.empty() == false) {
			ArchivePath::setMasterBackup1Path(AppConfig::m_masterBackup1);
		}
		else {
			AppConfig::m_masterBackup1Enabled = false;
		}
		ArchivePath::setMasterBackup1Enabled(AppConfig::m_masterBackup1Enabled);
		// Backup 2
		if (AppConfig::m_masterBackup2.empty() == false) {
			ArchivePath::setMasterBackup2Path(AppConfig::m_masterBackup2);
		}
		else {
			AppConfig::m_masterBackup2Enabled = true;
		}
		ArchivePath::setMasterBackup2Enabled(AppConfig::m_masterBackup2Enabled);

		// Derivative
		// Backup 1
		if (AppConfig::m_derivativeBackup1.empty() == false) {
			ArchivePath::setDerivativeBackup1Path(AppConfig::m_derivativeBackup1);
		}
		else {
			AppConfig::m_derivativeBackup1Enabled = false;
		}
		ArchivePath::setDerivativeBackup1Enabled(AppConfig::m_derivativeBackup1Enabled);
		// Backup 2
		if (AppConfig::m_derivativeBackup2.empty() == false) {
			ArchivePath::setDerivativeBackup2Path(AppConfig::m_derivativeBackup2);
		}
		else {
			AppConfig::m_derivativeBackup2Enabled = true;
		}
		ArchivePath::setDerivativeBackup2Enabled(AppConfig::m_derivativeBackup2Enabled);


		

		logger.log(LOG_OK, CLogger::Level::INFO, "        System path:               \"%s\"", AppConfig::m_systemPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Log path:                  \"%s\"", AppConfig::m_logPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Tools path:                \"%s\"", AppConfig::m_toolsPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Hook path:                 \"%s\"", AppConfig::m_hookPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        History path:              \"%s\"", AppConfig::m_historyPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Template path:             \"%s\"", AppConfig::m_templatePath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        SQL Database path:         \"%s\"", AppConfig::m_sqlDatabasePath.c_str());
		
		logger.log(LOG_OK, CLogger::Level::INFO, "    Master Archive");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Master path:               \"%s\"", AppConfig::m_masterPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Backup One path:           \"%s\"", AppConfig::m_masterBackup1.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Backup Two path:           \"%s\"", AppConfig::m_masterBackup2.c_str());

		logger.log(LOG_OK, CLogger::Level::INFO, "    Derivative Archive");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Derivetive path:           \"%s\"", AppConfig::m_derivativePath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Backup One path:           \"%s\"", AppConfig::m_derivativeBackup1.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Backup Two path:           \"%s\"", AppConfig::m_derivativeBackup2.c_str());




		logger.log(LOG_OK, CLogger::Level::INFO, "    General");
		
		logger.log(LOG_OK, CLogger::Level::INFO, "        Verbose:                    %s", (AppConfig::m_verbose) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Quiet:                      %s", (AppConfig::m_quiet) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Silent:                     %s", (AppConfig::m_silent) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Dry run enabled:            %s", (AppConfig::m_dry_run) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Log level:                  %s", AppConfig::m_logLevel.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Console level:              %s", AppConfig::m_consoleLevel.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        SQL database:               %s", (AppConfig::m_sql_on) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Lightroom:                  %s", (AppConfig::m_lightroom) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        External Exif tool enabled: %s", (AppConfig::m_exifToolEnabled) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        RemoteServerMode:           %s", (AppConfig::m_serverMode) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Master Backup One Enabled:  %s", (AppConfig::m_masterBackup1Enabled) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Master Backup Two Enabled:  %s", (AppConfig::m_masterBackup2Enabled) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        File Cataloging Enabled:    %s", (AppConfig::m_file_cat_on) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        WWW Cataloging Enabled:     %s", (AppConfig::m_www_cat_on) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Workspace Enabled:          %s", (AppConfig::m_workspaceEnabled) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Previews Enabled:           %s", (AppConfig::m_masterViewPreview1On) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        m_masterViewEnabled:        %s", (AppConfig::m_masterViewEnabled) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        m_masterViewFullSizeOn:     %s", (AppConfig::m_masterViewFullSizeOn) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        m_masterViewThumbnailOn:    %s", (AppConfig::m_masterViewThumbnailOn) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        m_eventsOn:                 %s", (AppConfig::m_eventsOn) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "        m_serverOn:                 %s", (AppConfig::m_serverOn) ? "True" : "False");
		logger.log(LOG_OK, CLogger::Level::INFO, "    System paths");
		logger.log(LOG_OK, CLogger::Level::INFO, "        System path:               \"%s\"", AppConfig::m_systemPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Log path:                  \"%s\"", AppConfig::m_logPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Tools path:                \"%s\"", AppConfig::m_toolsPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Hook path:                 \"%s\"", AppConfig::m_hookPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        History path:              \"%s\"", AppConfig::m_historyPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Template path:             \"%s\"", AppConfig::m_templatePath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        SQL Database path:         \"%s\"", AppConfig::m_sqlDatabasePath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "    User space paths");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Userspace path:            \"%s\"", AppConfig::m_userspacePath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Workspace path:            \"%s\"", AppConfig::m_workspacePath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        WWW Image path:            \"%s\"", AppConfig::m_wwwImagePath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Picture path:              \"%s\"", AppConfig::m_picturePath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Metadata path:             \"%s\"", AppConfig::m_userMetadataPath.c_str());

		logger.log(LOG_OK, CLogger::Level::INFO, "    Master Archive");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Master path:               \"%s\"", AppConfig::m_masterPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Backup One path:           \"%s\"", AppConfig::m_masterBackup1.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Backup Two path:           \"%s\"", AppConfig::m_masterBackup2.c_str());

		logger.log(LOG_OK, CLogger::Level::INFO, "    Derivative Archive");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Derivetive path:           \"%s\"", AppConfig::m_derivativePath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Backup One path:           \"%s\"", AppConfig::m_derivativeBackup1.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Backup Two path:           \"%s\"", AppConfig::m_derivativeBackup2.c_str());

		logger.log(LOG_OK, CLogger::Level::INFO, "    External Exif Tool");
		
		logger.log(LOG_OK, CLogger::Level::INFO, "        Exif map path:             \"%s\"", AppConfig::m_exifMapPath.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Exif map file:             \"%s\"", AppConfig::m_exifMapFile.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Exif Tool:                 \"%s\"", AppConfig::m_exifToolFile.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Exif command line:         \"%s\"", AppConfig::m_exifCommandLine.c_str());
		logger.log(LOG_OK, CLogger::Level::INFO, "        Exif map file delimiter:   \"%s\"", AppConfig::m_exifFileDelim.c_str());
		
	}

	bool SharedConfig::checkPaths()
	{
		AppConfig& config = AppConfig::get();
		CLogger& logger = CLogger::getLogger();
		logger.log(LOG_OK, CLogger::Level::INFO, "    Checking System paths");
		logger.log(LOG_OK, CLogger::Level::INFO, "        System path:               \"%s\"", AppConfig::m_systemPath.c_str());

		if (SAUtils::DirExists(AppConfig::m_systemPath.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "        System path:                \"%s\" Not found", AppConfig::m_systemPath.c_str());
			return false;
		}

		logger.log(LOG_OK, CLogger::Level::INFO, "        Log path:                  \"%s\"", AppConfig::m_logPath.c_str());
		if (SAUtils::DirExists(AppConfig::m_logPath.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "        Log path:                  \"%s\" Not found", AppConfig::m_logPath.c_str());
			return false;
		}

		logger.log(LOG_OK, CLogger::Level::INFO, "        Tools path:                \"%s\"", AppConfig::m_toolsPath.c_str());
		if (SAUtils::DirExists(AppConfig::m_toolsPath.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "        Tools path:                \"%s\" Not found", AppConfig::m_toolsPath.c_str());
			return false;
		}

		logger.log(LOG_OK, CLogger::Level::INFO, "        Hook path:                 \"%s\"", AppConfig::m_hookPath.c_str());
		if (SAUtils::DirExists(AppConfig::m_hookPath.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "        Hook path:                 \"%s\" Not found", AppConfig::m_hookPath.c_str());
			return false;
		}

		logger.log(LOG_OK, CLogger::Level::INFO, "        History path:              \"%s\"", AppConfig::m_historyPath.c_str());
		if (SAUtils::DirExists(AppConfig::m_historyPath.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "        History path:              \"%s\" Not found", AppConfig::m_historyPath.c_str());
			return false;
		}

		logger.log(LOG_OK, CLogger::Level::INFO, "        Template path:             \"%s\"", AppConfig::m_templatePath.c_str());
		if (SAUtils::DirExists(AppConfig::m_templatePath.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::INFO, "        Template path:             \"%s\" Not found", AppConfig::m_templatePath.c_str());
			return false;
		}

		logger.log(LOG_OK, CLogger::Level::INFO, "        SQL Database path:         \"%s\"", AppConfig::m_sqlDatabasePath.c_str());
		if (SAUtils::DirExists(AppConfig::m_sqlDatabasePath.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "        SQL Database path:         \"%s\" Not found", AppConfig::m_sqlDatabasePath.c_str());
			return false;
		}

		logger.log(LOG_OK, CLogger::Level::INFO, "    Checking User space paths");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Userspace path:            \"%s\"", AppConfig::m_userspacePath.c_str());
		if (SAUtils::DirExists(AppConfig::m_userspacePath.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "        Userspace path:            \"%s\" Not found", AppConfig::m_userspacePath.c_str());
			return false;
		}

		if (WorkspacePath::getObject().autoViewOn())
		{
			logger.log(LOG_OK, CLogger::Level::INFO, "        Workspace path:            \"%s\"", AppConfig::m_workspacePath.c_str());
			if (SAUtils::DirExists(AppConfig::m_workspacePath.c_str()) == false) {
				logger.log(LOG_OK, CLogger::Level::FATAL, "        Workspace path:            \"%s\" Not found", AppConfig::m_workspacePath.c_str());
				return false;
			}
		}

		if (WWWImagePath::getObject().autoViewOn()) {
			logger.log(LOG_OK, CLogger::Level::INFO, "        WWW Image path:            \"%s\"", AppConfig::m_wwwImagePath.c_str());
			if (SAUtils::DirExists(AppConfig::m_wwwImagePath.c_str()) == false) {
						logger.log(LOG_OK, CLogger::Level::FATAL, "        WWW Image path:            \"%s\" Not found", AppConfig::m_wwwImagePath.c_str());
				return false;
			}
		}

		if (PicturePath::getObject().autoViewOn()) {
			logger.log(LOG_OK, CLogger::Level::INFO, "        Picture path:              \"%s\"", AppConfig::m_picturePath.c_str());
			if (SAUtils::DirExists(AppConfig::m_picturePath.c_str()) == false) {
				//			logger.log(LOG_OK, CLogger::Level::INFO, "        Picture path:              \"%s\" Not found", AppConfig::m_picturePath.c_str());
				//			return false;
			}
		}
		logger.log(LOG_OK, CLogger::Level::INFO, "        Metadata path:             \"%s\"", AppConfig::m_userMetadataPath.c_str());
		if (SAUtils::DirExists(AppConfig::m_userMetadataPath.c_str()) == false) {
//			logger.log(LOG_OK, CLogger::Level::FATAL, "        Metadata path:             \"%s\" Not found", AppConfig::m_userMetadataPath.c_str());
//			return false;
		}

		logger.log(LOG_OK, CLogger::Level::INFO, "    Master Archive");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Master path:               \"%s\"", AppConfig::m_masterPath.c_str());
		if (SAUtils::DirExists(AppConfig::m_masterPath.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "        Master path:               \"%s\" Not found", AppConfig::m_masterPath.c_str());
			return false;
		}

		logger.log(LOG_OK, CLogger::Level::INFO, "    Derivative Archive");
		logger.log(LOG_OK, CLogger::Level::INFO, "        Derivetive path:           \"%s\"", AppConfig::m_derivativePath.c_str());
		if (SAUtils::DirExists(AppConfig::m_derivativePath.c_str()) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "        Derivetive path:           \"%s\" Not found", AppConfig::m_derivativePath.c_str());
			return false;
		}

		return true;
	}


	void SharedConfig::setWorkspacePath(const char *path) {
		AppConfig::m_workspacePath = path;
		//ArchivePath::setPathToWorkspace(AppConfig::m_workspacePath);
	}

	void SharedConfig::setMasterPath(const char *path) {
		AppConfig::m_masterPath = path;
		ArchivePath::setMasterPath(AppConfig::m_masterPath);
	}



	void AppConfig::setToolsPath(const char *toolsPath) {
		AppConfig::m_toolsPath = toolsPath;
	}
	const char *AppConfig::getToolsPath() {
		return m_toolsPath.c_str();

	}
	void SharedConfig::setHomePath(const char *homePath) {
		AppConfig::m_homePath = homePath;
		ArchivePath::setPathToHome(AppConfig::m_homePath);
		AppConfig::m_configPath = homePath;
		AppConfig::m_configPath += CONFIG_PATH;
	}
	
	const char *AppConfig::getHomePath() {
		
		return m_homePath.c_str();

	}

	bool AppConfig::isMasterCatalogueEnabled()
	{
		return m_file_cat_on;
	}
	bool AppConfig::isMasterWWWCatalogueEnabled()
	{
		return m_www_cat_on;
	}
	const char *AppConfig::getMasterBackup1() {
		return m_masterBackup1.c_str();
	}

	const char *AppConfig::getMasterBackup2() {
		return m_masterBackup2.c_str();
	}

	const char* AppConfig::getDerivativeBackup1()
	{
		return m_derivativeBackup2.c_str();
	}

	const char* AppConfig::getDerivativeBackup2()
	{
		return m_derivativeBackup2.c_str();
	}

	
	bool AppConfig::isSQL() {

		return m_sql_on;

	}

	const char* AppConfig::getUserMetadataPath() {

		return m_userMetadataPath.c_str();

	}


	const char* AppConfig::getUserspacePath() {
		return m_userspacePath.c_str();
	}
	/// Gets the archive path.
	const char *AppConfig::getWorkspacePath() {
		
		return m_workspacePath.c_str();

	}
	/// Gets the archive path.
	const char *AppConfig::getMasterPath() {
		return m_masterPath.c_str();
	}

	const char *AppConfig::getLightroomPath()
	{
		return m_lightroomPath.c_str();
	}
	
	const char *AppConfig::getDerivativePath() {
		
		return m_derivativePath.c_str();

	}

	
	const char *AppConfig::getSourcePath() {
		
		return m_sourcePath.c_str();

	}

	const char *AppConfig::getHookPath() {
		
		return m_hookPath.c_str();

	}
	void SharedConfig::setArchivePath(const char *path) {
		AppConfig::m_homePath = path;
	}

	void SharedConfig::setPicturePath(const char *path) {
		AppConfig::m_picturePath = path;
	}

	void SharedConfig::setLogLevel(const char *logLevel) {
		AppConfig::m_logLevel = logLevel;
	}

	void SharedConfig::setConsoleLevel(const char *logLevel) {
		AppConfig::m_consoleLevel = logLevel;
	}

	void SharedConfig::setDerivativePath(const char *path) {
		AppConfig::m_derivativePath = path;
	}

	void SharedConfig::setSourcePath(const char *path) {
		AppConfig::m_sourcePath = path;
	}

	void SharedConfig::setDryRun(bool dryRun) {
		AppConfig::m_dry_run = dryRun;
	}

	void SharedConfig::setQuiet(bool quiet) {
		AppConfig::m_quiet = quiet;
	}

	

	void SharedConfig::setSilent(bool silent) {
		AppConfig::m_silent = silent;
	}
	void SharedConfig::setVerbose(bool verbose) {
		AppConfig::m_verbose = verbose;
	}

	void SharedConfig::setEventsOn(bool evt) {
		AppConfig::m_eventsOn = evt;
	}

	void SharedConfig::setEventPort(int port) {
		AppConfig::m_eventsOn = true;
		AppConfig::m_udpPortNum = port;
	}

	void SharedConfig::setEventAddress(const char *address) {
		AppConfig::m_eventsOn = true;
		AppConfig::m_udpAddress = address;
	}

	void SharedConfig::setBackupDestinationPath(const char * str)
	{
		AppConfig::m_backupDestinationPath = str;
	}

	void SharedConfig::setBackupMediaSize(const char * str)
	{
	}

	void SharedConfig::setFromDate(const char * str)
	{
	}

	void SharedConfig::setToDate(const char * str)
	{
	}

	const char *AppConfig::getBackupDestinationPath() {
		return m_backupDestinationPath.c_str();
	}

	const char *AppConfig::getPicturePath() {
		return m_picturePath.c_str();
	}

	const char *AppConfig::getWWWImagePath() {
		return m_wwwImagePath.c_str();
	}

	void AppConfig::setBackupDestinationPath(const char *path) {
		m_backupDestinationPath = path;
	}

	long AppConfig::getBackupMediaSize() {
		return m_backupMediaSize;
	}

	void AppConfig::setBackupMediaSize(const char *sizeStr) {
		m_backupMediaSize = strtoul(sizeStr, 0, 10);
	}

	ExifDateTime &AppConfig::getFromDate() {
		return m_fromDate;
	}

	void AppConfig::setFromDate(const char *dateStr) {
		ExifDateTime tmp(dateStr);
		m_fromDate = tmp;
	}

	ExifDateTime &AppConfig::getToDate() {
		return m_toDate;
	}

	void AppConfig::setToDate(const char *dateStr) {
		ExifDateTime tmp(dateStr);
		m_toDate = tmp;
	}

	bool AppConfig::isFromDateSet() {
		return m_isFromDate;
	}

	bool AppConfig::isToDateSet() {
		return m_isToDate;
	}
	
	const char *AppConfig::getDatabasePath() {
		return m_sqlDatabasePath.c_str();
	}

	const char *AppConfig::getTempPath() {
		return m_tempPath.c_str();
	}

	const char *AppConfig::getLogPath() {
		return m_logPath.c_str();
	}

	const char *AppConfig::getLogLevel() {
		return m_logLevel.c_str();
	}

	const char *AppConfig::getConsoleLevel() {
		return m_consoleLevel.c_str();
	}

	const char* AppConfig::getFilenaming()
	{
		return m_filenaming.c_str();
	}

	
	const char *AppConfig::getSystemPath() {
		
		return m_systemPath.c_str();
	}


	const char *AppConfig::getIndexPath() {	
		//m_indexPath = m_systemPath + "/index";
		return m_indexPath.c_str();
	}

	const char *AppConfig::getHistoryPath() {
		
		return 	m_historyPath.c_str();
	}

	const char *AppConfig::getConfigPath() {
		
		return 	m_configPath.c_str();
	}

	const char *AppConfig::getExifToolPath() {
		
		return 	m_exifToolPath.c_str();
	}

	const char* AppConfig::getExifToolFile() {

		return 	m_exifToolFile.c_str();
	}
	
	const char *AppConfig::getExifFileDelim() {
		
		return 	m_exifFileDelim.c_str();
	}

	const char *AppConfig::getExifCommandLine() {
		
		return 	m_exifCommandLine.c_str();
	}

	const char* AppConfig::getExifMapPath() {

		return 	m_exifMapPath.c_str();
	}

	const char *AppConfig::getExifMapFile() {
		
		return 	m_exifMapFile.c_str();
	}
	
	const char *AppConfig::getTemplatePath() {
		
		return 	m_templatePath.c_str();
	}

	bool AppConfig::isDryRun() const {
		return m_dry_run;
	}

	bool AppConfig::isQuiet() const {
		return m_quiet;
	}

	bool AppConfig::isSilent() const {
		return m_silent;
	}
	
	bool AppConfig::isVerbose() const {
		return m_verbose;
	}

	

	bool AppConfig::isEventsOn() {
		return m_eventsOn;
	}

	int AppConfig::eventPort() {
		return m_udpPortNum;

	}
	const char *AppConfig::eventAddress() {
		return m_udpAddress.c_str();
	}

	bool AppConfig::isServerOn() {
		return m_serverOn;
	}

	int AppConfig::serverPort() {
		return m_tcpPortNum;

	}



	void AppConfig::isServerOn(bool on) {
		m_serverOn = on;
	}

	void AppConfig::setServerPort(int port) {
		m_tcpPortNum = port;
	}

	//void setSourcePath(const char *sourcePath);

	bool AppConfig::validWorkspacePath() {
		return true;
	}
	bool AppConfig::validSourcePath() {
		return true;
	}
	bool AppConfig::validHomePath() {
		return true;
	}

	std::string AppConfig::toString() {
		/// @brief Gets the source path.
		///const char *getSourcePath();

		/// @brief Gets the archive path.
		/// user definable
		std::stringstream str;
		str << "Configuration" << '\n';
		str << "=============" << '\n';
		str << "Workspace path:          " << getWorkspacePath() << '\n';
		/// @brief Gets the Master archive path
		/// user definable
		str << "Master path:             " << getMasterPath() << '\n';
		/// @brief Gets the temp file path.
		str << "Derivative path:         " << getDerivativePath() << '\n';
		/// @brief Gets the temp file path.
		/// user definable
		str << "Temp path:               " << getTempPath() << '\n';
		/// @brief Gets tools path
		str << "Tools path:              " << getToolsPath() << '\n';
		/// @brief Gets the hooks path
		/// user definable
		/// 
		str << "Hook path:               " << getHookPath()  << '\n';
		/// @brief Gets the path to the template files.
		str << "Metadata template path:  " << getTemplatePath() << '\n';
		/// @brief Gets log file path
		str << "Log path:                " << getLogPath() << '\n';
		/// @brief Gets the path to the crc index database.
		str << "Index path:              " << getIndexPath() << '\n';
		/// @brief Gets the path the history file are stored. These files are used for
		/// @brief the history of the changes made to the archive.
		str << "History path:            " << getHistoryPath() << '\n';
		/// @brief gets external Command line
		str << "Exif tool command        " << getExifCommandLine() << '\n';
		/// @brief Gets path to the Exif Map files. For example the Exiftool map
		/// that maps exiftool keywords to Simple Archive keywords.
		str << "Exif map path:           " << getExifMapPath() << '\n';
		str << "Config path:             " << getConfigPath() << '\n';
		/// @brief Gets home path. This is the root path all default paths are made.
		str << "Home path:               " << getHomePath() << '\n';
		str << "Master view path:        " << getMasterPath() << '\n';
		str << "Database path:           " << getDatabasePath() << '\n';
		str << "Backup destination path: " << getBackupDestinationPath() << '\n';
		str << "Backup media size:       " << getBackupMediaSize() << '\n';
		if (isFromDateSet() == true) {
			str << "From date:               " << getFromDate().toString() << '\n';
		}
		if (isToDateSet() == true) {
			str << "To date:                 " << getToDate().toString() << '\n';
		}
		str << "Is dryrun:               " << (isDryRun()?"true":"false") << '\n';
		str << "Is quiet:                " << (isQuiet() ? "true" : "false") << '\n';
		str << "Is verbose:              " << (isVerbose() ? "true" : "false") << '\n';
		str << "Log level:               " << getLogLevel() << '\n';

		return str.str();
	}

	std::string AppConfig::toXMLString() {
		/// @brief Gets the source path.
		///const char *getSourcePath();

		/// @brief Gets the archive path.
		/// user definable
		std::stringstream str;
		str << "<Configuration>" << '\n';
		str << "<WorkspacePath>" << getWorkspacePath() << "</WorkspacePath>" << '\n';
		/// @brief Gets the Master archive path
		/// user definable
		str << "<MasterPath>" << getMasterPath() << "</MasterPath>" << '\n';
		/// @brief Gets the Master archive path
		/// user definable
		str << "<DerivativePath>" << this->getDerivativePath() << "</DerivativePath>" << '\n';
		/// @brief Gets the temp file path.
		/// user definable
		str << "<TempPath>" << getTempPath() << "</TempPath>" << '\n';
		/// @brief Gets tools path
		str << "<ToolsPath>" << getToolsPath() << "</ToolsPath>" << '\n';
		/// @brief Gets the hooks path
		/// user definable
		/// 
		str << "<HookPath>" << getHookPath() << "</HookPath>" << '\n';
		/// @brief Gets the path to the metadata template files.
		str << "<TemplatePath>" << getTemplatePath() << "</TemplatePath>" << '\n';
		/// @brief Gets log file path
		str << "<LogPath>" << getLogPath() << "</LogPath>" << '\n';
		/// @brief Gets the path to the crc index database.
		str << "<IndexPath>" << getIndexPath() << "</IndexPath>" << '\n';
		/// @brief Gets the path the history file are stored. These files are used for
		/// @brief the history of the changes made to the archive.
		str << "<HistoryPath>" << getHistoryPath() << "</HistoryPath>" << '\n';
		/// @brief gets external Command line
		str << "<ExternalCommandLine>" << getExifCommandLine() << "</ExternalCommandLine>" << '\n';
		/// @brief Gets path to the Exif Map files. For example the Exiftool map
		/// that maps exiftool keywords to Simple Archive keywords.
		str << "<ExifMapPath>" << getExifMapPath() << "</ExifMapPath>" << '\n';
		str << "<ConfigPath>" << getConfigPath() << "</ConfigPath>" << '\n';
		/// @brief Gets home path. This is the root path all default paths are made.
		str << "<HomePath>" << getHomePath() << "</HomePath>" << '\n';
		str << "<DatabasePath>" << getDatabasePath() << "</DatabasePath>" << '\n';
		str << "<BackupDestinationPath>" << getBackupDestinationPath() << "</BackupDestinationPath>" << '\n';
		str << "<BackupMediaSize>" << getBackupMediaSize() << "</BackupMediaSize>" << '\n';
		if (isFromDateSet() == true) {
			str << "<FromDate>" << getFromDate().toString() << "</FromDate>" << '\n';
		}
		if (isToDateSet() == true) {
			str << "<FromDate>" << getToDate().toString() << "</FromDate>" << '\n';
		}
		str << "<IsDryRun>" << (isDryRun() ? "true" : "false") << "</IsDryRun>" << '\n';
		str << "<IsQuiet>" << (isQuiet() ? "true" : "false") << "</IsQuiet>" << '\n';
		str << "<IsVerbose>" << (isVerbose() ? "true" : "false") << "</IsVerbose>" << '\n';
		str << "<LogLevel>" << getLogLevel() << "</LogLevel>" << '\n';
		str << "<Lightroom>" << (isLightroom() ? "true" : "false") << "</Lightroom>" << '\n';
		str << "</Configuration>" << '\n';
		return str.str();
	}

	
	bool AppConfig::setDefaultLocations() {

		MasterPath& masterPath = MasterPath::getObject();
		m_masterPath = masterPath.getPath();

		DerivativePath& derivativePath = DerivativePath::getObject();
		m_derivativePath = derivativePath.getPath();

		WorkspacePath& workspacePath = WorkspacePath::getObject();
		m_workspacePath = workspacePath.getPath();

		PicturePath& picturePath = PicturePath::getObject();
		m_picturePath = picturePath.getPath();

		WWWImagePath& wwwImagePath = WWWImagePath::getObject();
		m_wwwImagePath = wwwImagePath.getPath();

		return locations(MusicGuardHome::getMusicGuardHome().c_str());
	}

	bool AppConfig::locations(const char* home) {

		std::string homePath = home;
		// Repository Archive Path
		m_historyPath = homePath + HISTORY_PATH;
		return false;
	}


};


