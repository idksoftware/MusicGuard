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
**	Filename	: App.cpp
**	Author		: I.Ferguson
**	Version		: 1.000
**	Date		: 26-05-2015
**
** #$$@@$$# */

#include <csignal>
#include <cstdlib>
#include <cstdio>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdio.h>
#include <iostream>
#include "ver.h"
#include "MGApp.h"
#include "SAUtils.h"
#include "CLogger.h"
#include "AppConfig.h"
#include "TargetsList.h"
#include "CIDKDate.h"
#include "AboutCommand.h"
#include "SummaryFile.h"
#include "SIALib.h"
#include "UDPOut.h"

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#endif

#include <iostream>
using namespace std;

#include <string>
#include <vector>
#include "AppOptions.h"
#include "MGAppOptions.h"
#include "MGArgvParser.h"
#include "Threads.h"
#include "HookCmd.h"
#include "ImagePath.h"
#include "HomePaths.h"
#include "UpdateTemplateManager.h"
//#include "DefaultEnvironment.h"






/*
java version "1.7.0_51"
Java(TM) SE Runtime Environment (build 1.7.0_51-b13)
Java HotSpot(TM) 64-Bit Server VM (build 24.51-b03, mixed mode)
*/


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif


namespace simplearchive {

using namespace CommandLineProcessing;

MGApp::MGApp(const char* appName) : AppBase(appName, std::make_shared<MGArgvParser>()) {};

/*
class CheckoutSummary : public SummaryReporter {
protected:
	virtual ReporterEvent doProcess() {
		std::stringstream str;
		//int warnings = 0;
		//int errors = 0;
		//int competed = 0;
		std::shared_ptr<StatusList> list = getList();
		for (auto i = list->begin(); i != list->end(); i++) {
			//ReporterEvent& item = *i;
			
		}
		setSummary(str.str().c_str());

		return false;
	}
};
*/

bool MGApp::about(const char* outputType, const char* filename) {
	AboutCommand aboutCommand("client", "mg", VERSION, BUILD);
	aboutCommand.setOutputFile(filename);
	aboutCommand.setTextOutputType(outputType);

	if (aboutCommand.process() == false) {
		return false;
	}

	return true;
}

bool MGApp::initaliseArgs(int argc, char **argv) {
	
	if (m_argvParser->doInitalise(argc, argv) == false) {
		return false;
	}

	return true;
}

bool MGApp::initaliseConfig() {


	SIAARCConfig config;

	MusicGuardHome& musicGuardHome = MusicGuardHome::getObject();
	if (musicGuardHome.isValid() == false) {
		setError(13, "Error found setting MusicGuard home folder: %s.\n", musicGuardHome.errorStr().c_str());
		return false;
	}
	// Initalise without the config file i.e. set defaults.
	
	// try to set a systems temp folder 
	std::string tempPath = SAUtils::GetPOSIXEnv("TEMP");
	if (tempPath.empty() == true || tempPath.length() == 0) {
		tempPath = SAUtils::GetPOSIXEnv("TMP");
	}
	std::string homePath = MusicGuardHome::getMusicGuardHome();
	AppConfig::setDefaultLocations();
	std::string configfile = homePath + "/config/" + "config.dat";
	std::string configPath = homePath + "/config";
	// Now set the file based configuration with the possablity of overrighting defaults set prevously. 
	if (SAUtils::FileExists(configfile.c_str()) == false) {
		setError(13, "Error configuration file not found at location %s\n", configPath.c_str());
		return false;
	}

	setConfigPath(configPath.c_str());
	AppConfigReader configReader;
	configReader.setNoLogging();
	if (configReader.read(configfile.c_str(), config) == false) {
		setError(13, "Error found at line %d in the configuration file.\n", configReader.getCurrentLineNumber());
		return false;
	}
	config.fileBasedValues(homePath.c_str(), tempPath.c_str());
	if (!config.checkPaths()) {
		setError(13, "Error system path or paths not found as defined in the configuration.\n");
		return false;
	}
	setConfigured();
	musicGuardHome.checkAndMakePaths();
	
	return true;
}



bool MGApp::doRun()
{
	MGAppOptions &appOptions = MGAppOptions::get();
	AppConfig &config = AppConfig::get();
	
	SIALib siaLib;
	// Set global options
	if (appOptions.isEnventsOn() == true) {

		siaLib.enableEvents(appOptions.eventAddress(), appOptions.eventPort());
	}

	if (appOptions.isServerOn() == true) {

		siaLib.enableServer(appOptions.eventPort());
	}
	
	//printf("%s", config.toString().c_str());
	config.settup();
	
	if (isConfiguratedOk() == false) {
		setError(12, "MusicGuard Unable to start? Archive not found at the specified location \"%s\".\n"
			"Use iaadmin -i to create an empty archive at the default location (see documentation).\n", config.getHomePath());
		return false;
	}
	
	
	if (siaLib.initalise(APP_NAME) < 0) {
		return false;
	}
	/*
		INITALISING COMLETE ????
	*/
	bool ret = true;
	bool noSummary = false; // Some commands do not require summery as it breaks some output i.e. XML 
	switch (appOptions.getCommandMode()) {

		// run sub-comand
	case MGAppOptions::CommandMode::CM_Import:

		
		
		// using file list
		if (appOptions.isUsingFile()) {
			if (siaLib.ImportFile(appOptions.getFilePath(), appOptions.getOptionList())== false) {
				setError(CLogger::getLastCode(), CLogger::getLastMessage());
				return false;
			}
		}
		else {
			if (siaLib.Import(appOptions.getSourcePath(), appOptions.getOptionList()) == false) {
				setError(CLogger::getLastCode(), CLogger::getLastMessage());
				return false;
			}
		}
		
		break;
	case MGAppOptions::CommandMode::CM_Scan:
		if (siaLib.scan(appOptions.getFormatType(), appOptions.getFilePath()) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;

	case MGAppOptions::CommandMode::CM_Export:
		if (siaLib.exportImage(appOptions.getDistinationPath()) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;
	case MGAppOptions::CommandMode::CM_Show:
		if (siaLib.show() == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;
		
	case MGAppOptions::CommandMode::CM_Checkout:
	{
		
	}
		break;
	case MGAppOptions::CommandMode::CM_Checkin:
		
		break;
	case MGAppOptions::CommandMode::CM_UnCheckout:
		
		break;
	case MGAppOptions::CommandMode::CM_Get:
		if (setExitStatus(siaLib.get(appOptions.getImageAddress(), appOptions.getVersions(), appOptions.getComment(), appOptions.isForced())) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;
	case MGAppOptions::CommandMode::CM_Delete:
		if (setExitStatus(siaLib.deleteImages(appOptions.getImageAddress(), appOptions.getComment(), appOptions.isForced())) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;
	case MGAppOptions::CommandMode::CM_Undelete:
		if (siaLib.undeleteImages(appOptions.getImageAddress(), appOptions.getComment()) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;
	case MGAppOptions::CommandMode::CM_History:
	{
		if (siaLib.history(appOptions.getImageAddress(), appOptions.getFormatType(), appOptions.getFilePath()) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;
	}
	case MGAppOptions::CommandMode::CM_Status:
	{
		//if (siaLib.status(appOptions.getImageAddress()) == false) {
		//	setError(CLogger::getLastCode(), CLogger::getLastMessage());
		//	return false;
		//}
		switch (appOptions.getShowCommandOption()) {
		case MGAppOptions::ShowCommandOption::SC_ShowCheckedOut:
			if (siaLib.showCheckedOut(appOptions.getImageAddress(), appOptions.getFormatType(), appOptions.getFilePath()) == false) {
				setError(CLogger::getLastCode(), CLogger::getLastMessage());
				return false;
			}

		case MGAppOptions::ShowCommandOption::SC_ShowUncheckedOutChanges:
			
			return true;
		case MGAppOptions::ShowCommandOption::SC_Unknown:
			return false;
		}

		break;
	}
	case MGAppOptions::CommandMode::CM_Metadata:
	{
		std::string formatType = appOptions.getOption();
		if (formatType.empty()) {
			formatType = "human";
		}
		if (siaLib.metadata(appOptions.getImageAddress(), formatType.c_str(), appOptions.getFilePath()) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;
	}
#ifdef NOT_USED
	case SMGAppOptions::CommandMode::CM_View:
	{
		if (siaLib.view(appOptions.getName()) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;
	}
#endif
	case MGAppOptions::CommandMode::CM_Workspace:
	{
		if (siaLib.workspace(appOptions.isSync())) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;
	}
	case MGAppOptions::CommandMode::CM_Template:
	{
		std::string option = appOptions.getOption();
		if (!option.empty()) {
			std::string templatePath = config.getTemplatePath();
			UpdateTemplateManager updateTemplateManager(templatePath.c_str());
			if (updateTemplateManager.process(appOptions.isMaster(), appOptions.isCurrent(), option.c_str()) == false) {
				return false;
			}
		}
		if (siaLib.metadataTemplate(appOptions.isMaster(), appOptions.isCurrent(), appOptions.getArgs()) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;
	}
	case MGAppOptions::CommandMode::CM_Prop:
	{
		if(siaLib.setProperty(appOptions.getImageAddress(), appOptions.getOption(), appOptions.getValue()) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		/*
		if (siaLib.listContents(appOptions.getImageAddress()) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		*/
		break;
	}

	case MGAppOptions::CommandMode::CM_Log:
	{
		if (siaLib.log(appOptions.getImageAddress(), appOptions.getFromDate(), appOptions.getToDate(), appOptions.getFormatType(), appOptions.getFilePath()) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		noSummary = true;
		break;
	}

	case MGAppOptions::CommandMode::CM_Journal:
	{
		if (siaLib.journal(appOptions.getImageAddress(), appOptions.getFromDate(), appOptions.getToDate(), appOptions.getFormatType(), appOptions.getFilePath()) == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		noSummary = true;
		break;
	}

	case MGAppOptions::CommandMode::CM_Mode:
	{

		if (siaLib.remoteServer() == false) {
			setError(CLogger::getLastCode(), CLogger::getLastMessage());
			return false;
		}
		break;
	}
	case MGAppOptions::CommandMode::CM_Uncheckin:
		break;
	
	case MGAppOptions::CommandMode::CM_About:
	{
		return about(appOptions.getTextOutputType(), appOptions.getOutputFile());
	}
	case MGAppOptions::CommandMode::CM_Unknown:
		setError( CLogger::getLastCode(), CLogger::getLastMessage());
		break;
	default:
		setError(15, "Command not implimented at this time");
		return false;
	}
	if (noSummary == false) {
		siaLib.complete();
	}
	
	return true;
}

bool MGApp::setExitStatus(bool commandReturn)
{
	setError(CLogger::getLastCode(), CLogger::getLastMessage());
	CLogger::Level level = CLogger::getHighestLevel();
	ExitCode exitCode = ExitCode::Fatal;
	switch (level)
	{
	case CLogger::Level::TRACE:		// Trace debugging
	case CLogger::Level::FINE:		// Fine debugging
	case CLogger::Level::INFO:		// General information
	case CLogger::Level::STATUS:		// Status information
	case CLogger::Level::SUMMARY:	// Summary information
		exitCode = ExitCode::Success;
		break;
	case CLogger::Level::WARNING:	// Warning of incomplete operations
		exitCode = ExitCode::Warnings;
		break;
	case CLogger::Level::ERR:		// Failed operations
		exitCode = ExitCode::Errors;
		break;
	case CLogger::Level::FATAL:		// Application cannot complete
	case CLogger::Level::UNKNOWN:
		exitCode = ExitCode::Fatal;
		break;
	}
	setExitCode(exitCode);
	StatusReporter& statusReporter = StatusReporter::get();
	SummaryReporter summaryReporter(statusReporter.getList());
	ReporterEvent result = summaryReporter.process();
	summaryReporter.toConsole();
	return result.isOk();
}

MGApp::~MGApp() {
	CLogger::Close();
}

bool ok()
{
	cout << "OK" << endl;
	return(true);
}

bool failed()
{
	cout << "Failed" << endl;
	return(false);
}



} // simplearchive

void ctrlHandler(int s) {
	printf("Caught signal %d\n", s);
	//exit(1);

}

int main(int argc, char** argv)
{

	signal(SIGINT, ctrlHandler);

	bool error = false;
	simplearchive::MGApp app("MusicGuard iaarc");
	if (app.initalise(argc, argv) == false) {
		error = true;
	}
	else {
		if (app.Run() == false) {
			error = true;
		}
	}
	if (error) {
		int code = CommandLineProcessing::AppBase::getError();
		cout << "\n\n" << CommandLineProcessing::AppBase::getFullErrorString(); // << '\n';
	}
	return CommandLineProcessing::AppBase::getExitCode();
}


