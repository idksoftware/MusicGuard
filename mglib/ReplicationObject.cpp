#include "ReplicationObject.h"
#include "SAUtils.h"
#include "MetadataObject.h"
#include "WriteMetadata.h"
#include "HomePaths.h"
#include "CLogger.h"

namespace simplearchive {

	bool ReplicationObject::createMetadata(ImagePath& imagePath, MetadataObject& metadataObject) {
		CLogger& logger = CLogger::getLogger();
		std::string name = imagePath.getImageName();
		std::string workspaceMetadataAddress;
		std::string userspaceMetadataAddress;
		WorkspacePath& workspacePath = WorkspacePath::getObject();
		UserspacePath& userspacePath = UserspacePath::getObject();

		
		
		if (ReplicationObject::writeUserspaceMasterMetadata(imagePath, name, metadataObject) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "Fataled to write image \"%s\" Userspace", imagePath.getImageName().c_str());
			return false;
		}
		
		if (ReplicationObject::writeMetadata2Workspace(imagePath, name, metadataObject) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "Fataled to write image \"%s\" workspace", imagePath.getImageName().c_str());
			return false;
		}

		// Write the metadata to the primary index
		if (ReplicationObject::writeMetadata2PrimaryIndex(imagePath, name, metadataObject) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "Fataled to write image \"%s\" primary index", imagePath.getImageName().c_str());
			return false;
		}

		// Write the metadata to the Master archive
		if (ReplicationObject::writeMetadata2MasterDatabase(imagePath, name, metadataObject) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "Fataled to write image \"%s\" master database", imagePath.getImageName().c_str());
			return false;
		}
		return true;
	}

	bool ReplicationObject::updateMetadata(ImagePath& imagePath, MetadataObject& metadataObject)
	{
		CLogger& logger = CLogger::getLogger();
		std::string name = imagePath.getImageName();
		if (ReplicationObject::writeMetadata2Workspace(imagePath, name, metadataObject) == false) {
			logger.log(LOG_OK, CLogger::Level::WARNING, "Unable to update workspace");
		}
		if (ReplicationObject::writeMetadata2PrimaryIndex(imagePath, name, metadataObject) == false) {
			logger.log(LOG_OK, CLogger::Level::WARNING, "Unable to update workspace");
		}
		if (ReplicationObject::writeMetadata2MasterDatabase(imagePath, name, metadataObject) == false) {
			logger.log(LOG_OK, CLogger::Level::WARNING, "Unable to update master database");
		}
		return true;
	}

	bool ReplicationObject::checkinMetadata(ImagePath& imagePath, std::string versionName, MetadataObject& metadataObject,
		DerivativeMetadataRow& derivativeMetadata)
	{
		CLogger& logger = CLogger::getLogger();
		std::string name = imagePath.getImageName();

		if (ReplicationObject::writeMetadata2Workspace(imagePath, name, metadataObject) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "Fataled to write image \"%s\" metadata to workspace", versionName.c_str());
			return false;
		}
		
		if (ReplicationObject::writeDerivativeMetadat2Workspace(imagePath, versionName, derivativeMetadata, name) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "Fataled to write image \"%s\" metadata to workspace", versionName.c_str());
			return false;
		}
		if (ReplicationObject::writeMetadata2PrimaryIndex(imagePath, versionName, metadataObject) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "Fataled to write image \"%s\" metadata to primary index", versionName.c_str());
			return false;
		}
		if (ReplicationObject::writeMetadata2DerivativesDatabase(versionName, derivativeMetadata, name) == false) {
			logger.log(LOG_OK, CLogger::Level::FATAL, "Fataled to write image \"%s\" metadata Derivatives Database", versionName.c_str());
			return false;
		}

		return true;
	}

	

	bool ReplicationObject::writeMetadata2DerivativesDatabase(std::string& versionName, DerivativeMetadataRow& metadataObject, std::string& imageName) {
		if (ArchivePath::isDerivativeEnabled() == true) {
			DerivativePath& derivativePath = DerivativePath::getObject();

			std::string path = derivativePath.getPath();
			path += +"/metadata";;
			if (writeDerivativeMetadata(path, versionName, metadataObject, imageName) == false) {
				return false;
			}
		}
		return true;
	}


	bool ReplicationObject::writeUserspaceMasterMetadata(ImagePath& imagePath, std::string& imageName, MetadataObject& metadataObject) {
		if (UserspacePath::autoViewOn()) {
			UserspacePath& userspacePath = UserspacePath::getObject();
			std::string userspaceMetadataAddress;
			
			ImagePath::createUserMetadataAddress(userspacePath.getPath().c_str(), imagePath.getImageAddress().c_str(), userspaceMetadataAddress);
			//imagePath.setImageName(imageName.c_str());;
			if (WriteMetadata::writeUserspaceMasterMetadata(userspaceMetadataAddress, metadataObject) == false) {
				return false;
			}
		}
		return true;
	}

	bool ReplicationObject::writeDerivativeMetadata(std::string& rootPath, std::string& versionName, DerivativeMetadataRow& metadataObject, std::string& imageName) {

		
		return true;
	}

	bool ReplicationObject::writeMetadata2Workspace(ImagePath& imagePath, std::string& imageName, MetadataObject& metadataObject) {

		if (WorkspacePath::autoViewOn()) {
			WorkspacePath& workspacePath = WorkspacePath::getObject();
			
			std::string path = workspacePath.getPath();

			imagePath.setImageName(imageName.c_str());;
			std::string imageAddress = imagePath.getUserMetadataAddress();
			if (WriteMetadata::writeMetadata2Workspace(path, imageAddress, metadataObject) == false) {
				return false;
			}
		}
		return true;
	}

	bool ReplicationObject::writeDerivativeMetadat2Workspace(ImagePath& imagePath, std::string& versionName, DerivativeMetadataRow& derivativeMetadata, std::string& imageName) {
		if (WorkspacePath::autoViewOn()) {

			WorkspacePath& workspacePath = WorkspacePath::getObject();

			std::string imageAddress = imagePath.getImageAddress();
			std::string path = workspacePath.getPath();
			
			/*
			std::string toxml = m_workspacePath + '/';
			std::string relpath = imagePath.getRelativePath();
			toxml += imagePath.getYear(relpath);
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			toxml = m_workspacePath + '/';
			toxml += imagePath.getRelativePath();
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			toxml += "/.imga";
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			toxml += "/metadata";
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			if (writeDerivativeMetadata(toxml, versionName, derivativeMetadata, imageName) == false) {
				return false;
			}
			*/
		}
		return true;
	}

	bool ReplicationObject::writeMetadata2PrimaryIndex(ImagePath& imagePath, std::string& imageName, MetadataObject& metadataObject) {

		MusicGuardHome imgArchiveHome = MusicGuardHome::getObject();
		std::string primaryIndexPath = imgArchiveHome.getPrimaryPath();
		
		std::string primaryIndexObjectMetadataPath = primaryIndexPath + "/metadata";

		if (SAUtils::DirExists(primaryIndexObjectMetadataPath.c_str()) == false) {
			return false;
		}
		std::string toxml = primaryIndexObjectMetadataPath + '/';
		std::string relpath = imagePath.getRelativePath();
		toxml += imagePath.getYear(relpath);
		if (SAUtils::DirExists(toxml.c_str()) == false) {
			if (SAUtils::mkDir(toxml.c_str()) == false) {
				return false;
			}
		}
		toxml = primaryIndexObjectMetadataPath + '/';
		toxml += imagePath.getRelativePath();
		if (SAUtils::DirExists(toxml.c_str()) == false) {
			if (SAUtils::mkDir(toxml.c_str()) == false) {
				return false;
			}
		}


		if (WriteMetadata::writeMasterMetadata(toxml, imageName, metadataObject) == false) {
			return false;
		}
		return true;
	}

	bool ReplicationObject::writeMetadata2MasterDatabase(ImagePath& imagePath, std::string& imageName, MetadataObject& metadataObject) {
		if (ArchivePath::isMasterEnabled() == true) {

			std::string toxml = ImagePath::getPathToMaster();
			std::string relpath = imagePath.getRelativePath();
			toxml += '/';
			toxml += imagePath.getYear(relpath);
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			toxml = ImagePath::getPathToMaster() + '/';
			toxml += imagePath.getRelativePath();
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			toxml += "/metadata";
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			if (WriteMetadata::writeMasterMetadata(toxml, imageName, metadataObject) == false) {
				return false;
			}
		}
		if (ArchivePath::isMasterBackup1Enabled() == true) {
			std::string path = ArchivePath::getMasterBackup1Path();
			//std::string path = m_master.getBackup1Object().getRepositoryPath().getRepositoryPath();
			std::string toxml = path;
			toxml += '/';
			std::string relpath = imagePath.getRelativePath();
			toxml += imagePath.getYear(relpath);
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			toxml = path + '/';
			toxml += imagePath.getRelativePath();
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			toxml += "/metadata";
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			if (WriteMetadata::writeMasterMetadata(toxml, imageName, metadataObject) == false) {
				return false;
			}
		}
		if (ArchivePath::isMasterBackup2Enabled() == true) {
			std::string path = ArchivePath::getMasterBackup2Path();
			//std::string path = m_master.getBackup2Object().getRepositoryPath().getRepositoryPath();
			std::string toxml = path;
			std::string relpath = imagePath.getRelativePath();
			toxml += '/';
			toxml += imagePath.getYear(relpath);
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			toxml = path + '/';
			toxml += imagePath.getRelativePath();
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			toxml += "/metadata";
			if (SAUtils::DirExists(toxml.c_str()) == false) {
				if (SAUtils::mkDir(toxml.c_str()) == false) {
					return false;
				}
			}
			if (WriteMetadata::writeMasterMetadata(toxml, imageName, metadataObject) == false) {
				return false;
			}
		}
		return true;
	}


	/*
	bool RepositoryObject::writeMetadata(ImagePath& imagePath, MetadataObject& metadataObject) {

		std::string imageAddress = imagePath.getImageName();

		std::string path = getRepositoryPath().getMetadataPath();
		if (WriteMetadata::writeMasterMetadata(path, imageAddress, metadataObject) == false) {
			return false;
		}
		*/
		/*
		std::string toxml = getRepositoryPath().getMetadataPath() + '/' + imagePath.getImageName() + ".xml";
		XMLWriter xmlWriter;
		if (xmlWriter.writeImage(metadataObject, toxml.c_str()) == false) {
			return false;
		}
		std::string tojson = getRepositoryPath().getMetadataPath() + '/' + imagePath.getImageName() + ".json";
		JSONWriter jsonWriter;
		if (jsonWriter.writeImage(metadataObject, tojson.c_str()) == false) {
			return false;
		}
		std::string tohtml = getRepositoryPath().getMetadataPath() + '/' + imagePath.getImageName() + ".html";
		HTMLWriter htmlWriter;
		if (htmlWriter.writeImage(metadataObject, tohtml.c_str()) == false) {
			return false;
		}
		*/
		//return true;
	//}

	/*
	bool ReplicationObject::writeMetadata2DerivativesDatabase(std::string& versionName, DerivativeMetadataRow& metadataObject, std::string& imageName) {
		if (ArchivePath::isDerivativeEnabled() == true) {
			DerivativePath& derivativePath = DerivativePath::getObject();
			std::string path = derivativePath.getPath();
			path += +"/metadata";;
			if (writeDerivativeMetadata(path, versionName, metadataObject, imageName) == false) {
				return false;
			}
		}
		return true;
	}
	*/
	
	/*
	bool ReplicationObject::writeDerivativeMetadata(std::string& rootPath, std::string& versionName, DerivativeMetadataRow& metadataObject, std::string& imageName) {

		if (WriteMetadata::writeDerivativeMetadata(rootPath, versionName, metadataObject, imageName) == false) {
			return false;
		}
		return true;
	}
	*/
}