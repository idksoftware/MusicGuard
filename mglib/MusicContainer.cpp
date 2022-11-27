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

#include <time.h>
#ifdef LINUX
//#include <ctime.h>
#endif
#include "MetadataObject.h"
#include "MusicContainer.h"
#include "ImageExtentions.h"
#include "SAUtils.h"
#include "CDate.h"
#include "CLogger.h"

namespace simplearchive {

#undef FILECODE
#define FILECODE IMAGECONTAINER_CPP
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif


MusicContainer::MusicContainer(const char *path, const char *imageName) {
	m_PictureNode = nullptr;
	m_RawNode = nullptr;
	m_Path = path;
	m_Name = imageName;
	m_Time = -1;
	m_error = 0;
}


MusicContainer::MusicContainer() {
	m_PictureNode = nullptr;
	m_RawNode = nullptr;
}


MusicContainer::~MusicContainer() {
	
}



bool MusicContainer::add(std::shared_ptr<MetadataObject>& metadataObject) {
	CLogger &logger = CLogger::getLogger();

	//
	const char *imagefile = metadataObject->getName().c_str();
	ImageExtentions &imageExtentions = ImageExtentions::get();
	ImageType type = imageExtentions.getType(imagefile);
	switch (type.getType()) {
	// Found Picture Image
	case ImageType::Type::PICTURE_EXT:
		logger.log(LOG_OK, CLogger::Level::INFO, "found pic: %s", imagefile);
		if (m_PictureNode == nullptr) {
			/* not sure needed
			if (BasicMetadata->isExifFound()) {
				const ExifDateTime &dateTime = BasicMetadata->getDateTimeDigitized();
				logger.log(LOG_OK, CLogger::INFO, "Using Exif date: %d ", ((ExifDateTime&)dateTime).toString().c_str());
				m_Time = dateTime.getTime();
			}
			*/
			logger.log(LOG_ASSOCIATING, CLogger::Level::STATUS, "Associating: %s with %s", imagefile, m_Name.c_str());
			//print();
			m_PictureNode = std::make_shared<MusicNode>(type, metadataObject);
		}
		//m_PictureNode->setImageId(BasicMetadata, metadataObject);
		
		

		/*
		else {
			struct stat info;

			if (stat(((BasicMetadataFactory *)imageId)->getPath().c_str(), &info) != 0) {
				return false;
			}
		}
		*/
		
		break;
	// Found RAW Image
	case ImageType::Type::RAW_EXT:
	
		logger.log(LOG_OK, CLogger::Level::INFO, "found raw: %s", imagefile);
		if (m_RawNode == nullptr) {
			logger.log(LOG_OK, CLogger::Level::STATUS, "Associating: %s with %s", imagefile, m_Name.c_str());
			m_RawNode = std::make_shared<MusicNode>(type, metadataObject);
		}
		//m_RawNode->setImageId(imageId, metadataObject);
		
		//m_RawFile = imagefile;
		break;
	case ImageType::Type::UNKNOWN_EXT:
	default:
		logger.log(LOG_OK, CLogger::Level::ERR, "No extention found for this file type %s", imagefile);
		m_error = -1;
		return false;
	}

	return true;
}

void MusicContainer::PostProcess() {
	
	/*
	if (m_PictureNode != nullptr) {
		m_BasicMetadata = &(m_PictureNode->getBasicMetadata());
	} else if (m_RawNode != nullptr) {
		m_BasicMetadata = &(m_RawNode->getBasicMetadata());
	}
	else {
		// Error
		m_error = -1;
	}
	*/
	if ((m_PictureNode != nullptr) && (m_RawNode != nullptr)) {
		const MetadataObject& picMO = m_PictureNode->getMetadataObject();
		m_RawNode->setMetadataObject(picMO);
	
	}
}

void MusicContainer::print() {
	CLogger &logger = CLogger::getLogger();
	
	logger.log(LOG_OK, CLogger::Level::FINE, "Item Name: %s", m_Name.c_str());
	if (hasPictureFile()) {
		logger.log(LOG_OK, CLogger::Level::FINE, "Picture File: %s", m_PictureNode->getFile().c_str());
		MTRow row = m_PictureNode->getMetadataObject();
		logger.log(LOG_OK, CLogger::Level::FINE, "Picture metadata: %s", row.toDebugString().c_str());
	}
	else
	{
		logger.log(LOG_OK, CLogger::Level::FINE, "No Picture File");
	}
	if (hasRawFile()) {
		logger.log(LOG_OK, CLogger::Level::FINE, "RAW File: %s", m_RawNode->getFile().c_str());
		MTRow row = m_RawNode->getMetadataObject();
		logger.log(LOG_OK, CLogger::Level::FINE, "RAW metadata: %s", row.toDebugString().c_str());
	}
	else {
		logger.log(LOG_OK, CLogger::Level::FINE, "No RAW File");
	}
}

const std::string& MusicNode::getFile() const {
	return m_file;
}

void MusicNode::setMetadataObject(const MetadataObject& metadataObject) {
	//m_metadataObject->update(metadataObject);
}
/*
void MusicNode::setImageId(const BasicMetadataFactory*& imageId, const MetadataObject *metadataObject) {
	m_imageId = imageId;
	m_metadataObject = metadataObject;
	if (m_metadataObject != nullptr) {
		MetadataObject &mo = (MetadataObject &)*metadataObject;
		BasicMetadataFactory *id = (BasicMetadataFactory *)imageId;
		setImageID2Metadata(id, mo);
	}
}
*/

/*
void MusicNode::setImageID2Metadata(BasicMetadataFactory *imageIdData, MetadataObject &metadataObject) {
	
	
	imageIdData->setMetadataObject(metadataObject);
}
*/

/*
void MusicNode::setMetadataObject(
		const MetadataObject*& metadataObject) {
	m_metadataObject = metadataObject;
	if (m_metadataObject != nullptr) {
		MetadataObject &mo = (MetadataObject &)*metadataObject;
		//BasicMetadataFactory *id = (BasicMetadataFactory *)m_BasicMetadata;
		//setImageID2Metadata(m_BasicMetadata, mo);
	}
}
*/

} /* namespace simplearchive */
