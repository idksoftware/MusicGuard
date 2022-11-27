#include "WriteMetadata.h"
#include "XMLWriter.h"
#include "JSONWriter.h"
#include "HTMLWriter.h"

#include "MetadataObject.h"
#include "SAUtils.h"
#include "CLogger.h"

namespace simplearchive {

	

	bool WriteMetadata::writeMetadata2Workspace(std::string& workspace, std::string& imageAddress, MetadataObject& metadataObject) {

		PathController pathController;
		if (pathController.splitShort(imageAddress.c_str()) == false) {
			return false;
		}
		
		std::string fullPath = workspace;

		if (SAUtils::DirExists(fullPath.c_str()) == false) {
			return false;
		}

		fullPath += '/';
		fullPath += pathController.getYear();

		if (SAUtils::DirExists(fullPath.c_str()) == false) {
			if (SAUtils::mkDir(fullPath.c_str()) == false) {
				return false;
			}
		}

		fullPath += '/';
		fullPath += pathController.getYearday();
	
		if (SAUtils::DirExists(fullPath.c_str()) == false) {
			if (SAUtils::mkDir(fullPath.c_str()) == false) {
				return false;
			}
		}
		fullPath += "/.imga";
		if (SAUtils::DirExists(fullPath.c_str()) == false) {
			if (SAUtils::mkDir(fullPath.c_str()) == false) {
				return false;
			}
			SAUtils::setHidden(fullPath.c_str());
		}
		fullPath += "/metadata";
		if (SAUtils::DirExists(fullPath.c_str()) == false) {
			if (SAUtils::mkDir(fullPath.c_str()) == false) {
				return false;
			}
		}
		std::string temp = pathController.getImage();
		if (WriteMetadata::writeMasterMetadata(fullPath, temp, metadataObject) == false) {
			return false;
		}
		
		return true;
	}
	

	bool WriteMetadata::writeUserMetadata(std::string& userMetadataPath, std::string& imageAddress, MetadataObject& metadataObject) {

		PathController pathController;
		if (pathController.splitShort(imageAddress.c_str()) == false) {
			return false;
		}

		std::string fullPath = userMetadataPath;

		if (SAUtils::DirExists(fullPath.c_str()) == false) {
			return false;
		}

		fullPath += '/';
		fullPath += pathController.getYear();

		fullPath += '/';
		fullPath += pathController.getYearday();
		if (SAUtils::DirExists(fullPath.c_str()) == false) {
			if (SAUtils::makePath(fullPath.c_str()) == false) {
				return false;
			}
		}
		std::string temp = pathController.getImage();
		if (WriteMetadata::writeMasterMetadata(fullPath, temp, metadataObject) == false) {
			return false;
		}

		return true;
	}

	

	bool WriteMetadata::writeUserspaceMasterMetadata(std::string& rootPath, MetadataObject& metadataObject) {

		std::string toxml = rootPath + ".xml";
		XMLWriter xmlWriter;
		if (xmlWriter.writeImage(metadataObject, toxml.c_str()) == false) {
			return false;
		}
		std::string tojson = rootPath + ".json";
		JSONWriter jsonWriter;
		if (jsonWriter.writeImage(metadataObject, tojson.c_str()) == false) {
			return false;
		}
		std::string tohtml = rootPath + ".html";
		HTMLWriter htmlWriter;
		if (htmlWriter.writeImage(metadataObject, tohtml.c_str()) == false) {
			return false;
		}
		return true;
	}

	bool WriteMetadata::writeMasterMetadata(std::string& rootPath, std::string& imageName, MetadataObject& metadataObject) {

		std::string toxml = rootPath + '/' + imageName + ".xml";
		XMLWriter xmlWriter;
		if (xmlWriter.writeImage(metadataObject, toxml.c_str()) == false) {
			return false;
		}
		std::string tojson = rootPath + '/' + imageName + ".json";
		JSONWriter jsonWriter;
		if (jsonWriter.writeImage(metadataObject, tojson.c_str()) == false) {
			return false;
		}
		std::string tohtml = rootPath + '/' + imageName + ".html";
		HTMLWriter htmlWriter;
		if (htmlWriter.writeImage(metadataObject, tohtml.c_str()) == false) {
			return false;
		}
		return true;
	}


	
}; // namespace
