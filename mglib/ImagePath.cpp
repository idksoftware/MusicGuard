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

#include "ImagePath.h"
#include "HomePaths.h"
#include "SAUtils.h"
#include "CDate.h"
#include <stdio.h>
#include <sstream>
#include <iomanip>
//#include "IntegrityManager.h"
#include "pathcontroller.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

namespace simplearchive {

// User spaces
std::string ImagePath::m_pathToWorkspace;
std::string ImagePath::m_pathToPictures;
std::string ImagePath::m_pathToWWWImages;
std::string ImagePath::m_pathToUserMetadata;


std::string ImagePath::m_mainMetadataPath;
std::string ImagePath::m_mainDupsPath;
std::string ImagePath::m_mainHistory;
std::string ImagePath::m_pathToPrimaryIndex;
std::string ImagePath::m_primaryMetadataPath;

std::string ImagePath::m_pathToMaster;
std::string ImagePath::m_masterSystemPath;
std::string ImagePath::m_MasterMetadataPath;
std::string ImagePath::m_MasterSequenceNumberPath;

std::string ImagePath::m_pathToDerivative;


std::string ImagePath::m_MasterHistory;
std::string ImagePath::m_MasterCatalog;
std::string ImagePath::m_MasterJournalPath;




bool ImagePath::initPaths()
{

	
	m_pathToPictures = PicturePath::getObject().getPath();
	m_pathToWWWImages = WWWImagePath::getObject().getPath();
	m_pathToUserMetadata = UserMetadataPath::getObject().getPath();

	m_pathToPrimaryIndex = MusicGuardHome::getPrimaryPath();
	m_pathToWorkspace = WorkspacePath::getObject().getPath();
	m_pathToUserMetadata = UserMetadataPath::getObject().getPath();
	m_pathToMaster = MasterPath::getObject().getPath();
	m_pathToDerivative = DerivativePath::getObject().getPath();
	//IntegrityManager &integrityManager = IntegrityManager::get();
	//integrityManager.setPaths(m_pathToMaster.c_str(), m_pathToDerivative.c_str(), m_pathToWorkspace.c_str(), MusicGuardHome::getMusicGuardHome().c_str());
	if (SAUtils::DirExists(m_pathToMaster.c_str()) == false) {
		return false;
	}
	if (SAUtils::DirExists(m_pathToDerivative.c_str()) == false) {
		return false;
	}
	createMasterSystemPath();
	createPrimaryIndexMetadataPath();

	if (m_MasterMetadataPath.empty() == true) {
		m_MasterMetadataPath = m_masterSystemPath + METADATA_PATH;
		if (SAUtils::DirExists(m_MasterMetadataPath.c_str()) == false) {
			SAUtils::mkDir(m_MasterMetadataPath.c_str());
		}
		
		m_MasterSequenceNumberPath = m_masterSystemPath + IMAGEID_PATH;
		if (SAUtils::DirExists(m_MasterSequenceNumberPath.c_str()) == false) {
			SAUtils::mkDir(m_MasterSequenceNumberPath.c_str());
		}
		m_MasterJournalPath = m_masterSystemPath + JOURNAL_PATH;
		if (SAUtils::DirExists(m_MasterJournalPath.c_str()) == false) {
			SAUtils::mkDir(m_MasterJournalPath.c_str());
		}
		m_MasterHistory = m_masterSystemPath + HISTORY_PATH;
		if (SAUtils::DirExists(m_MasterHistory.c_str()) == false) {
			SAUtils::mkDir(m_MasterHistory.c_str());
		}
		
		
	}
	return true;
}

ImagePath::ImagePath(time_t time) {

	CDate date(time);
	
	int year = date.getYear();
	int month = date.getMonth();
	int day = date.getDay();
	//printf("Time: %.4d %.2d %.2d", year, month, day);

	m_yearStr = SAUtils::to_string(year);
	std::stringstream s;
	s << year << '-' << std::setw(2) << std::setfill('0') << month
		<< '-' << std::setw(2) << std::setfill('0') << day;
	std::string tmp = s.str();
	init(tmp);
}

ImagePath::ImagePath(std::string & yyyymmddStr) {
	init(yyyymmddStr);
}

void ImagePath::init(std::string &yyyymmddStr) {

	m_yearStr = getYear(yyyymmddStr);
	m_yyyymmddStr = yyyymmddStr;

	// This needs to be removed as workspaces
	createWorkspaceImageAddress();
	createPictureImageAddress();
	createWWWImageAddress();

	//createUserSpaceMetadataPath();
	createPrimaryIndexMetadataPath();

	m_relpath = getYearStr() + '/' + getYyyymmddStr();

	// Master
	m_MasterYearStrPath = m_pathToMaster + '/' + m_yearStr;
	if (SAUtils::DirExists(m_MasterYearStrPath.c_str()) == false) {
		SAUtils::mkDir(m_MasterYearStrPath.c_str());

	}

	m_MasterYyyymmddStrPath = m_MasterYearStrPath + '/' + m_yyyymmddStr;
	std::string localPath = m_MasterYyyymmddStrPath;

	createMasterImageAddresses(localPath);
}

void ImagePath::createWorkspaceImageAddress()
{
	if (WorkspacePath::autoViewOn()) {
		m_workspaceImageAddress = createImageAddress(m_pathToWorkspace, m_yyyymmddStr.c_str());
	}
}

void ImagePath::createPictureImageAddress()
{
	if (PicturePath::autoViewOn()) {
		m_userPictuesImageAddress = createImageAddress(m_pathToPictures, m_yyyymmddStr.c_str());
	}
}

void ImagePath::createWWWImageAddress()
{
	if (WWWImagePath::autoViewOn()) {
		m_userWWWImageAddress = createImageAddress(m_pathToWWWImages, m_yyyymmddStr.c_str());
	}
}

bool ImagePath::createUserMetadataAddress(const char *root, const char* imageAddress, std::string& metadataPath)
{
	PathController pathController;
	if (pathController.splitShort(imageAddress) == false) {
		return false;
	}

	metadataPath = root;

	if (SAUtils::DirExists(metadataPath.c_str()) == false) {
		return false;
	}
	metadataPath += "/.imga/";
	if (SAUtils::DirExists(metadataPath.c_str()) == false) {
		if (SAUtils::mkDir(metadataPath.c_str()) == false) {
			return false;
		}
	}
	metadataPath += pathController.getYear();

	if (SAUtils::DirExists(metadataPath.c_str()) == false) {
		if (SAUtils::mkDir(metadataPath.c_str()) == false) {
			return false;
		}
	}

	metadataPath += '/';
	metadataPath += pathController.getYearday();

	if (SAUtils::DirExists(metadataPath.c_str()) == false) {
		if (SAUtils::mkDir(metadataPath.c_str()) == false) {
			return false;
		}
	}
	
	metadataPath += "/metadata";
	if (SAUtils::DirExists(metadataPath.c_str()) == false) {
		if (SAUtils::mkDir(metadataPath.c_str()) == false) {
			return false;
		}
	}
	metadataPath += '/';
	metadataPath += pathController.getImage();
	return true;
}

std::string ImagePath::createWorkspaceImageAddress(const char* imageAddress)
{
	return createImageAddress(m_pathToWorkspace, imageAddress);
}

std::string ImagePath::createPictureImageAddress(const char* imageAddress)
{
	return createImageAddress(m_pathToPictures, imageAddress);
}

std::string ImagePath::createWWWImageAddress(const char* imageAddress)
{
	return createImageAddress(m_pathToWWWImages, imageAddress);
}

std::string ImagePath::createUserMetadataImageAddress(const char* imageAddress)
{
	return createImageAddress(m_pathToUserMetadata, imageAddress);
}

bool ImagePath::checkUserspaceRoot(std::string& rootPath)
{
	std::string temp = rootPath;
	if (SAUtils::DirExists(temp.c_str()) == false) {
		return false;
	}
	return true;
}

bool ImagePath::createUserspaceRoot(std::string& rootPath)
{
	std::string temp = rootPath;
	if (SAUtils::DirExists(temp.c_str()) == false) {
		if (SAUtils::mkDir(temp.c_str()) == false) {
			return false;
		}
	}
	temp += "/.imga";
	if (SAUtils::DirExists(temp.c_str()) == false) {
		if (SAUtils::mkDir(temp.c_str()) == false) {
			return false;
		}
		SAUtils::setHidden(temp.c_str());
	}
	if (SAUtils::setHidden(temp.c_str()) == false) {
		return false;
	}
	return true;
}

bool ImagePath::isWorkspaceOn()
{
	if (WorkspacePath::getObject().autoViewOn()) {
		return true;
	}
	return false;
}


bool ImagePath::checkWorkspace()
{
	if (WorkspacePath::getObject().autoViewOn()) {
		return checkUserspaceRoot(m_pathToWorkspace);
	}
	return true;
}

bool ImagePath::isPictureOn()
{
	if (PicturePath::getObject().autoViewOn()) {
		return true;
	}
	return false;
}


bool ImagePath::checkPicture()
{
	if (PicturePath::getObject().autoViewOn()) {
		return checkUserspaceRoot(m_pathToPictures);
	}
	return true;
}


bool ImagePath::isWWWImageOn()
{
	if (WWWImagePath::getObject().autoViewOn()) {
		return true;
	}
	return false;
}


bool ImagePath::checkWWWImage()
{
	if (WWWImagePath::getObject().autoViewOn()) {
		return checkUserspaceRoot(m_pathToWWWImages);
	}
	return true;
}
/*
bool ImagePath::createWorkspace()
{
	return createUserspaceRoot(m_pathToWorkspace);
}
*/

std::string ImagePath::createImageAddress(std::string& rootPath, const char* imageAddress)
{
	std::string path = rootPath;
	PathController pathController;
	pathController.split(imageAddress);
	std::string imageName = pathController.getImage();
	path += '/';
	path += pathController.getYear();
	if (SAUtils::DirExists(path.c_str()) == false) {
		SAUtils::mkDir(path.c_str());
	}
	path += '/';
	path += pathController.getYearday();
	if (SAUtils::DirExists(path.c_str()) == false) {
		SAUtils::mkDir(path.c_str());
	}
	if (!pathController.getImage().empty()) {
		path += '/';
		path += pathController.getImage();
	}
	return path;
}

void ImagePath::createMasterSystemPath() {
	m_masterSystemPath = m_pathToMaster;
	m_masterSystemPath += SYSTEM_PATH;
	if (SAUtils::DirExists(m_masterSystemPath.c_str()) == false) {
		SAUtils::mkDir(m_masterSystemPath.c_str());

	}
}

void ImagePath::createUserSpaceHistoryPath() {
	m_pathToUserMetadata = m_pathToWorkspace + "/.imga";
	if (SAUtils::DirExists(m_pathToUserMetadata.c_str()) == false) {
		SAUtils::mkDir(m_pathToUserMetadata.c_str());
	}
	SAUtils::setHidden(m_pathToUserMetadata.c_str());
	m_pathToUserMetadata += "/history";
	if (SAUtils::DirExists(m_pathToUserMetadata.c_str()) == false) {
		SAUtils::mkDir(m_pathToUserMetadata.c_str());
	}
}

void ImagePath::createPrimaryIndexMetadataPath() {
	if (m_primaryMetadataPath.empty() == true) {
		m_primaryMetadataPath = m_pathToPrimaryIndex;
		m_primaryMetadataPath += "/metadata";
		if (SAUtils::DirExists(m_primaryMetadataPath.c_str()) == false) {
			SAUtils::mkDir(m_primaryMetadataPath.c_str());
		}
	}
}



void ImagePath::createMasterImageAddresses(std::string localPath)
{
	m_localMasterDataPath = localPath + MASTER_IMAGE_PATH;
	m_localMasterMetadataPath = localPath + METADATA_PATH;
	
	if (SAUtils::DirExists(localPath.c_str()) == false) {
		SAUtils::mkDir(localPath.c_str());
		if (SAUtils::DirExists(localPath.c_str()) == false) {
			throw std::exception();
		}
	}
	SAUtils::mkDir(m_localMasterDataPath.c_str());
	SAUtils::mkDir(m_localMasterMetadataPath.c_str());
	
	//IntegrityManager &integrityManager = IntegrityManager::get();
	//integrityManager.addMasterDayFolder(m_yyyymmddStr.c_str());
}



ImagePath::ImagePath(const char *filepath) {
	//IntegrityManager &m_integrityManager = IntegrityManager::get();
	PathController pathController;
	pathController.splitShort(filepath);
	//m_imageAddress = pathController.
	m_imageName = pathController.getImage();
	std::string path = pathController.getYearday();
	init(path);
}


bool ImagePath::copyFile2Workspace(std::string  pathToSourceRoot, const std::string& file, const std::string& sequenceFile) {
	//IntegrityManager &integrityManager = IntegrityManager::get();
	std::string from = pathToSourceRoot + "/" + file;
	std::string to = m_workspaceImageAddress + '/' + sequenceFile;
	
	// Working Archive
	if (SAUtils::copy(from.c_str(), to.c_str()) == false) {
		return false;
	}

	// this can only be done after the file copy
	//integrityManager.addMasterDayFolder(m_yyyymmddStr.c_str());
	//integrityManager.addMasterFile(m_yyyymmddStr.c_str(), sequenceFile.c_str());
	return true;
}

bool ImagePath::copyFile2Picture(std::string  pathToSourceRoot, const std::string& file, const std::string& sequenceFile) {
	//IntegrityManager& integrityManager = IntegrityManager::get();
	std::string from = pathToSourceRoot + "/" + file;
	std::string to = m_userPictuesImageAddress + '/' + sequenceFile;

	if (SAUtils::copy(from.c_str(), to.c_str()) == false) {
		return false;
	}

	return true;
}


ImagePath::~ImagePath() {

}


} /* namespace simplearchive */
