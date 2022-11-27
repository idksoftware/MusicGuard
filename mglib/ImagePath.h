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

#ifndef IMAGEPATH_H_
#define IMAGEPATH_H_
#include <string>
//#include "IntegrityManager.h"
#include "AppPaths.h"

namespace simplearchive {

#define IMAGE_NAME              "ImageName"
#define RELATIVE_PATH           "RelativePath"
#define IMAGE_PATH              "ImagePath"
#define YEAR                    "Year"
#define YYYYMMDD                "YearMonthDay"
#define PATH_TO_ARCHIVE         "ArchivePath"
#define DATA_PATH               "DataPath"
#define METADATA_PATH_LABLE           "MetadataPath"
#define MAIN_METADATA_PATH      "GlobalMetadataPath"

/**
* This class contains the paths for the archives.
* The archives consist of a primary Master Archive and a number
* of continuously backed-up Backup Archives.
*/


class ImagePath {
	std::string m_currentSourcePath;

	std::string m_relpath;
	std::string m_imagePath;
	std::string m_imageName;
	std::string m_encodedImageName;
	std::string m_imageAddress;
	std::string m_orginalName;
	std::string m_yearStr;
	std::string m_yyyymmddStr;
	std::string m_yearStrPath;
	//std::string m_yyyymmddStrPath;
	std::string m_workspaceImageAddress;
	std::string m_userPictuesImageAddress;
	std::string m_userWWWImageAddress;
	std::string m_userMetadataImageAddress;

	std::string m_MasterYearStrPath;
	std::string m_MasterYyyymmddStrPath;
	
	
	std::string m_dataPath;
	std::string m_dbPath;
	std::string m_metadataPath;
	std::string m_relMetadataPath;

	std::string m_localMasterDataPath;
	std::string m_localMasterMetadataPath;
	std::string m_localMasterDBPath;
	// Local Master history path
	std::string m_localMasterHistoryPath;

	static std::string m_pathToWorkspace;
	static std::string m_pathToPictures;
	static std::string m_pathToWWWImages;
	static std::string m_pathToUserMetadata;

	static std::string m_pathToPrimaryIndex;
	static std::string m_primaryMetadataPath;
	static std::string m_mainMetadataPath;
//	static std::string m_userDefinedSequenceNumberPath;
	static std::string m_mainDupsPath;
	static std::string m_mainHistory;

	//static ArchiveFolder *m_Master;
	static std::string m_pathToMaster;
	static std::string m_masterSystemPath;
	static std::string m_MasterMetadataPath;
	static std::string m_MasterSequenceNumberPath;
	static std::string m_MasterHistory;
	static std::string m_MasterJournalPath;
	static std::string m_MasterCatalog;
	
	static std::string m_pathToDerivative;

	void init(std::string &yyyymmddStr);

	static std::string createImageAddress(std::string& rootPath, const char* imageAddress);
	static bool checkUserspaceRoot(std::string& rootPath);
	static bool createUserspaceRoot(std::string& rootPath);

public:
	ImagePath(time_t time);
	ImagePath(const char *filepath);
	ImagePath(std::string &yyyymmddStr);
	bool copyFile2Workspace(std::string  pathToSourceRoot, const std::string& file, const std::string& sequenceFile);
	bool copyFile2Picture(std::string  pathToSourceRoot, const std::string& file, const std::string& sequenceFile);
	virtual ~ImagePath();
	
	static bool initPaths();
	static void createPrimaryIndexMetadataPath();
	static void createMasterSystemPath();

	void createMasterImageAddresses(std::string localPath);
	void createUserSpaceHistoryPath();

	static bool isWorkspaceOn();
	static bool checkWorkspace();
	//static bool createWorkspace();

	static bool isPictureOn();
	static bool checkPicture();

	static bool isWWWImageOn();
	static bool checkWWWImage();

	void createWorkspaceImageAddress();
	void createPictureImageAddress();
	void createWWWImageAddress();
	static std::string createWorkspaceImageAddress(const char* imageAddress);
	static std::string createPictureImageAddress(const char* imageAddress);
	static std::string createWWWImageAddress(const char* imageAddress);
	static std::string createUserMetadataImageAddress(const char* imageAddress);
	static bool createUserMetadataAddress(const char* root, const char* imageAddress, std::string& matadataPath);

	std::string& getWorkspaceImageAddress()
	{
		return m_workspaceImageAddress;
	}
	
	void setImageName(const char *imageName) {
		m_imageName = imageName;
	}

	void setEncodedImageName(const char* imageName) {
		m_encodedImageName = imageName;
	}

	void setOrginalName(const char *imageName) {
		m_orginalName = imageName;
	}

	void switchOrginalName(const char *imageName) {
		m_orginalName = m_imageName;
		m_imageName = imageName;
	}

	const std::string& getImageName() const noexcept {
		return m_imageName;
	}

	const std::string& getEncodedImageName() const noexcept {
		return m_encodedImageName;
	}

	const std::string& getOrginalName() const noexcept {
		return m_orginalName;
	}

	void setCurrentSourcePath(const char *currentSourcePath) {
		m_currentSourcePath = currentSourcePath;
	}

	const std::string& getCurrentSourcePath() const noexcept {
		return m_currentSourcePath;
	}

	const std::string& getDataPath() const noexcept {
		return m_localMasterDataPath;
	}

	const std::string& getImageAddress() {
		m_imageAddress = m_relpath.substr(5, 10);
		m_imageAddress += '/';
		m_imageAddress += m_imageName;
		return m_imageAddress;
	}

	const std::string& getUserMetadataAddress() {
		m_imageAddress = m_relpath.substr(5, 10);
		m_imageAddress += '/';
		m_imageAddress += m_imageName;
		return m_imageAddress;
	}

	const std::string& getImagePath() {
		m_imagePath = m_relpath.c_str();
		m_imagePath += '/';
		m_imagePath += m_imageName;
		return m_imagePath;
	}

	const std::string& getLocalMasterPath() noexcept {
		return m_MasterYyyymmddStrPath;
	}

	const std::string& getLocalMasterMetadataPath() const noexcept {
		return m_localMasterMetadataPath;
	}
	
	const std::string& getLocalMasterHistoryPath() const noexcept {
		return m_localMasterHistoryPath;
	}

	const std::string& getRelMetadataPath() const noexcept {
		return m_relMetadataPath;
	}

	const std::string& getDBPath() const {
		return m_localMasterDBPath;
	}

	const std::string& getYearStr() const {
		return m_yearStr;
	}

	const std::string& getYearStrPath() const {
		return m_yearStrPath;
	}

	const std::string& getYyyymmddStr() const {
		return m_yyyymmddStr;
	}

	const std::string& getUserspaceMetadataPath() {
		return m_pathToUserMetadata;
	}

	static const std::string& getPathToWorkspace() {
		return m_pathToWorkspace;
	}

	static const std::string& getPathToPictures() {
		return m_pathToPictures;
	}

	static const std::string& getPathToWWWImages() {
		return m_pathToWWWImages;
	}

	static const std::string& getPathToUserMetadata() {
		return m_pathToUserMetadata;
	}

	


	static const std::string& getPathToMaster() {
		return m_pathToMaster;
	}

	const std::string& getPathToPrimaryIndex() const {
		return m_pathToPrimaryIndex;
	}

	const std::string& getRelativePath() const {

		return m_relpath;
	}

	// main
	/// @brief The dups path is set in the configuation file (Default is $Master_FOLDER/root/dups)
	/// 
	static const std::string& getMainDupsPath() {
		return m_mainDupsPath;
	}

	static const std::string& getMainMetadataPath() {
		return m_mainMetadataPath;
	}

	//static const std::string& getMainSequenceNumberPath() {
	//	return m_mainSequenceNumberPath;
	//}

	// Master
	

	static const std::string& getMainMasterMetadataPath() {
		return m_MasterMetadataPath;
	}

	static const std::string& getMasterSequenceNumberPath() {
		return m_MasterSequenceNumberPath;
	}

	// Get Master history path
	static const std::string& getMasterHistoryPath() {
		return m_MasterHistory;
	}

	// Get Master history path
	static const std::string& getMasterCatalogPath() {
		return m_MasterCatalog;
	}

	// Get Master journal path
	static const std::string& getMasterJournalPath() {
		return m_MasterJournalPath;
	}

	static std::string getYearDay(std::string &dataImage) {
		return dataImage.substr(0, 10);
	}

	static std::string getYear(std::string &path) {
		return path.substr(0, 4);
	}
};

} /* namespace simplearchive */
#endif /* IMAGEPATH_H_ */
