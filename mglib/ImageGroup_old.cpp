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

#include "ImageGroup.h"
#include "MusicContainer.h"
//#include "ImageExtentions.h"
#include "SAUtils.h"
#include <vector>
#include <stdio.h>

#include "CLogger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

namespace simplearchive {

ImageGroup::ImageGroup(const char *path) {
	m_path = path;
}

bool ImageGroup::add(MusicContainer *imageContainer)
{
	push_back(imageContainer);
	return true;
}

MusicContainer *ImageGroup::find(const char *imageFilename) {
	std::string filenameOnly = SAUtils::getFilePathNoExt(imageFilename);
	for (std::vector<MusicContainer *>::iterator i = begin(); i != end(); i++) {
		MusicContainer *imageContainer = *i;
		if (imageContainer->getName().compare(filenameOnly) == 0) {
			return imageContainer;
		}
	}
	return NULL;
}

MusicContainer &ImageGroup::add(std::shared_ptr<MetadataObject>& metadataObject)
{
	CLogger &logger = CLogger::getLogger();
	const std::string &imageFilename = metadataObject->getName();
	std::string filenameOnly = SAUtils::getFilenameNoExt(imageFilename);
	MusicContainer *imageContainer = nullptr;
	if ((imageContainer = find(filenameOnly.c_str())) != nullptr) {
		// Second Instance with this name so needs to be assocated.
		logger.log(LOG_OK, CLogger::Level::INFO, "Found name: %s, Associating: %s with %s", imageFilename.c_str(), imageFilename.c_str(), imageContainer->getName().c_str());
		imageContainer->add(metadataObject);
	} else {
		// First Instance with this name.
		// note all images share the same path in the group.
		logger.log(LOG_OK, CLogger::Level::INFO, "New image name: %s using %s", filenameOnly.c_str(), metadataObject->getName().c_str());
		imageContainer = new MusicContainer(getPath(), filenameOnly.c_str());
		imageContainer->add(metadataObject);
		add(imageContainer);
	}
	return *imageContainer;
}

bool ImageGroup::addMetadata(const char *filename)
{

	/*
	ImageExtentions& ie = ImageExtentions::get();
	if (ie.IsValidXML(filename) == false) {
		return false;
	}
	*/

	MusicContainer *imageContainer = nullptr;
	if ((imageContainer = find(filename)) != nullptr) {
		imageContainer->add(filename);
	}
	add(new MusicContainer(getPath(), filename));
	return true;
}

ImageGroup::~ImageGroup() {
	for (std::vector<MusicContainer *>::iterator i = begin(); i != end(); i++) {
		MusicContainer *imageContainer = *i;
		delete imageContainer;
	}
	clear();
}

ImageGroups::~ImageGroups() {
	for (std::vector<ImageGroup *>::iterator i = begin(); i != end(); i++) {
		ImageGroup *imageGroup = *i;
		delete imageGroup;
	}
	clear();
}

} /* namespace simplearchive */
