#pragma once
#include <string>
#include "ImagePath.h"
#include "ArchivePath.h"

namespace simplearchive {

	class MetadataObject;
	class DerivativeMetadataRow;

	class ReplicationObject
	{
	public:
		static bool createMetadata(ImagePath& imagePath, MetadataObject& metadataObject);
		static bool updateMetadata(ImagePath& imagePath, MetadataObject& metadataObject);
		static bool checkinMetadata(ImagePath& imagePath, std::string versionName, MetadataObject& metadataObject,
																			DerivativeMetadataRow& DerivativeMetadataObject);

		static bool writeUserspaceMasterMetadata(ImagePath& imagePath, std::string& imageName, MetadataObject& metadataObject);
		static bool writeDerivativeMetadata(std::string& rootPath, std::string& versionName, DerivativeMetadataRow& metadataObject, std::string& imageName);
		static bool writeMetadata2Workspace(ImagePath& imagePath, std::string& imageName, MetadataObject& metadataObject);
		static bool writeDerivativeMetadat2Workspace(ImagePath& imagePath, std::string& versionName, DerivativeMetadataRow& derivativeMetadata, std::string& imageName);
		static bool writeMetadata2PrimaryIndex(ImagePath& imagePath, std::string& imageName, MetadataObject& metadataObject);
		static bool writeMetadata2MasterDatabase(ImagePath& imagePath, std::string& imageName, MetadataObject& metadataObject);
		static bool writeMetadata2DerivativesDatabase(std::string& versionName, DerivativeMetadataRow& metadataObject, std::string& imageName);
		
	};

}