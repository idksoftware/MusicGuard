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
**	Filename	: MGAppOptions.cpp
**	Author		: I.Ferguson
**	Version		: 1.000
**	Date		: 26-05-2015
**
** #$$@@$$# */

#include "ConfigReader.h"
#include "MGAppOptions.h"
#include "AppConfig.h"
#include "SAUtils.h"
#include "stdio.h"
#include "MGArgvParser.h"
#include "Environment.h"
#include "EnvFunc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

using namespace CommandLineProcessing;
namespace simplearchive {

bool MGAppOptions::m_list = false;
bool MGAppOptions::m_usingFile = false;
bool MGAppOptions::m_peekOnly = false;
bool MGAppOptions::m_eventsOn = false; // UDP events
bool MGAppOptions::m_serverOn = true; // false;
bool MGAppOptions::m_forceDate = false; // false;
bool MGAppOptions::m_force = false; // false;
bool MGAppOptions::m_useDate = false;
bool MGAppOptions::m_useFileDate = false;
bool MGAppOptions::m_useDateToday = false;
bool MGAppOptions::m_sync = false;
bool MGAppOptions::m_level = false;
bool MGAppOptions::m_repo = false;

ExifDate MGAppOptions::m_archiveDate;

std::string MGAppOptions::m_name;
MGAppOptions::CommandMode MGAppOptions::m_commandMode = MGAppOptions::CommandMode::CM_Unknown;
std::string MGAppOptions::m_comment;
std::string MGAppOptions::m_imageAddress;
std::string MGAppOptions::m_sourcePath;
std::string MGAppOptions::m_distinationPath;
std::string MGAppOptions::m_filePath;
std::string MGAppOptions::m_version = "@";
std::string MGAppOptions::m_FromDate;
std::string MGAppOptions::m_ToDate;
std::string MGAppOptions::m_option;
std::string MGAppOptions::m_value;
std::string MGAppOptions::m_outputFile;
std::string MGAppOptions::m_textOutputType;

int MGAppOptions::m_args = 0;
MGAppOptions::ShowCommandOption MGAppOptions::m_showCommandOption;
std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> MGAppOptions::m_optionList = nullptr;

int MGAppOptions::m_udpPortNum = 64321;
std::string MGAppOptions::m_udpAddress = "127.0.0.1";
int MGAppOptions::m_tcpPortNum = 64322;
ResultsPresentation::FormatType MGAppOptions::m_formatType = ResultsPresentation::FormatType::Human;


MGAppOptions::MGAppOptions() : m_argvParser(std::make_unique<MGArgvParser>()) {
	m_usingFile = false;
	m_archiveDate.now();
};


DefaultArgumentsContainer MGAppOptions::defaultArgumentsContainer;


MGAppOptions::~MGAppOptions() {}



MGAppOptions::CommandMode MGAppOptions::getCommandMode() {
	return m_commandMode;
}

bool MGAppOptions::setCommandMode(const char *modeString) {
	std::string mode = modeString;

	if (mode.compare("add") == 0) {
		m_commandMode = CommandMode::CM_Import;
		return true;
	}
	else if (mode.compare("add") == 0) {
		m_commandMode = CommandMode::CM_Export;
		return true;
	}
	else if (mode.compare("add") == 0) {
		m_commandMode = CommandMode::CM_Checkout;
		return true;
	}
	else if (mode.compare("add") == 0) {
		m_commandMode = CommandMode::CM_Checkin;
		return true;
	}
	else if (mode.compare("add") == 0) {
		m_commandMode = CommandMode::CM_Uncheckin;
		return true;
	}
	m_commandMode = CommandMode::CM_Unknown;
	//CommandLineProcessing::AppOptions::setError(12, "Unable to start, Command unknown .");
	return false;
}

void MGAppOptions::setCommandMode(const MGAppOptions::CommandMode mode) {
	m_commandMode = mode;
}

int MGAppOptions::getArgs() {
	return m_args;
}

const char *MGAppOptions::getName() {
	return m_name.c_str();
}

void MGAppOptions::setName(const char *name) {
	m_name = name;
}

const char *MGAppOptions::getComment() {
	return m_comment.c_str();
}
const char *MGAppOptions::getImageAddress() {
	return m_imageAddress.c_str();
}

const char* MGAppOptions::getVersions() {
	return m_version.c_str();
}

const char* MGAppOptions::getSourcePath() {
	return m_sourcePath.c_str();
}

const char *MGAppOptions::getDistinationPath() {
	return m_distinationPath.c_str();
}
const char *MGAppOptions::getFilePath() {
	return m_filePath.c_str();
}

const char* MGAppOptions::getFromDate()
{
	return m_FromDate.c_str();
}

const char* MGAppOptions::getToDate()
{
	return m_ToDate.c_str();
}

const char* MGAppOptions::getOption()
{
	return m_option.c_str();
}

const char* MGAppOptions::getValue()
{
	return m_value.c_str();
}

bool MGAppOptions::isEnventsOn() {
	return m_eventsOn;
}

int MGAppOptions::eventPort() {
	return m_udpPortNum;
	
}
const char *MGAppOptions::eventAddress() {
	return m_udpAddress.c_str();
}

bool MGAppOptions::isServerOn() {
	return m_serverOn;
}

int MGAppOptions::serverPort() {
	return m_tcpPortNum;

}

bool MGAppOptions::getUseFileDate() {
	return m_useFileDate;
}

bool MGAppOptions::getUseDateToday() {
	return m_useDateToday;
}

bool MGAppOptions::isDataForced() {
	return m_forceDate;
}

bool MGAppOptions::isForced() {
	return m_force;
}

bool MGAppOptions::isSync()
{
	return m_sync;
}

bool MGAppOptions::isCurrent()
{
	return m_level;
}

bool MGAppOptions::isMaster()
{
	return m_repo;
}

const char* MGAppOptions::getOutputFile()
{
	return m_outputFile.c_str();
}
const char* MGAppOptions::getTextOutputType()
{
	return m_textOutputType.c_str();
}

std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> MGAppOptions::getOptionList()
{
	return m_optionList;
}

ExifDate &MGAppOptions::getArchiveDate() {
	return m_archiveDate;
}

void MGAppOptions::setDefaultArguments(std::string s) {
	defaultArgumentsContainer.push_back(s);
}

DefaultArgumentsContainer& MGAppOptions::getDefaultArguments() {
	return defaultArgumentsContainer;
}

ResultsPresentation::FormatType& MGAppOptions::getFormatType() {
	return m_formatType;
}


bool StatusOptions::parse(const char* optionString)
{
	if (iequals(optionString, STATUS_CHECKED_OUT)) {
		m_option = STATUS_CHECKED_OUT;
		MGAppOptions::m_showCommandOption = MGAppOptions::ShowCommandOption::SC_ShowCheckedOut;
		return true;
	}
	else if (iequals(optionString, STATUS_CHECKED_IN)) {
		m_option = STATUS_CHECKED_IN;
		MGAppOptions::m_showCommandOption = MGAppOptions::ShowCommandOption::SC_ShowCheckedIn;
		return true;
	}
	else if (iequals(optionString, STATUS_DELETED)) {
		m_option = STATUS_DELETED;
		return true;
	}
	return false;
}


} /* namespace simplearchive */
