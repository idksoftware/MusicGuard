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

#ifndef IMAGEINDEX_H_
#define IMAGEINDEX_H_

#include <string>
#include <memory>
#include <cstdlib>
#include "CSVArgs.h"

namespace simplearchive {


class ImageId {
	std::string m_name;
	uint64_t m_crc;
	std::string m_md5;
	std::string m_location;
	std::string m_version;
public:
	ImageId() {};
	ImageId(const char *dataString) {
		
		CSVArgs csvArgs(':');
		csvArgs.process(dataString);
		
		std::string crcStr = csvArgs.at(0);
		m_crc = std::stoull(crcStr.c_str(),NULL,16);
		m_name = csvArgs.at(1);
		m_md5 = csvArgs.at(2);
		m_location = csvArgs.at(3);
		m_version = csvArgs.at(4);
	}

	ImageId(const char *name, uint64_t crc, const char *md5, const char *path, int version) :
		m_name(name), m_crc(crc), m_md5(md5), m_location(path)
	{
		m_version = std::to_string(version);
	}

	//bool add(const char *name, uint64_t crc, const char *md5);
	
	uint64_t getCrc() const {
		return m_crc;
	}

	void setCrc(uint64_t crc) {
		this->m_crc = crc;
	}

	const std::string& getMd5() const {
		return m_md5;
	}

	void setMd5(const std::string& md5) {
		this->m_md5 = md5;
	}

	const std::string& getName() const {
		return m_name;
	}

	const std::string& getLocation() const {
		return m_location;
	}

	void setName(const std::string& name) {
		this->m_name = name;
	}
};


class DupDataFile;
class MetadataObject;
class MirrorImageIndex;
class FileInfo;
class DupCache;

typedef std::unique_ptr<DupDataFile> DupDataFile_Ptr;

/**/



class ImageIndex {

	//std::unique_ptr<MirrorImageIndex> m_mirrorImageIndex;
	std::unique_ptr<DupCache> m_dupCache;
	
	std::string m_dbpath;
	unsigned char m_data[4];
	/** Adds to primary and backups */
	bool add(const char *name, uint64_t crc, const char *md5, const char *path, int version, const char *orginal);
	/** Adds to the Image index db using the given path */
	bool add(const char *name, uint64_t crc, const char *md5, const char *imagePath, int version, const char *rootPath, const char *orginal);
	DupDataFile_Ptr findDupDataFile(uint64_t crc);
	DupDataFile_Ptr findDupDataFile(uint64_t crc, const char *root);
	/**
	 * This function is used to update the path to the image with the addition of the root db folder.
	 */
	bool updatePath(uint64_t crc, const char *path, int version, const char *root);
protected:
	const char *getRootPath() {
		return m_dbpath.c_str();
	}
public:
	ImageIndex();
	virtual ~ImageIndex();

	/** initalise the image index database with the primary path */
	bool init(const char *path);
	/**
	*	This function returns true if added, false if dup
	*/
	bool add(const MetadataObject &metadata);
	bool add(const FileInfo& fileInfo, const char *orginal);
	bool IsDup(uint64_t crc);
	bool add2DupCache(const MetadataObject &metadata);
	bool add2DupCache(const FileInfo& fileInfo);
	bool isDupInCache(uint64_t crc);
	std::string FindDup(uint64_t crc);
	/**
	* This function is used to update the path to the image.
	*/
	bool updatePath(uint64_t crc, const char *path, int version);
	ImageId findDup(uint64_t crc) {
		std::string data = FindDup(crc);
		if (data.empty()) {
			ImageId imageId;
			return imageId;	// return empty object
		}
		ImageId imageId(data.c_str());
		return imageId;
	}
};

} /* namespace simplearchive */
#endif /* ImageIndex_H_ */