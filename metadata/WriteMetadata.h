#pragma once


#include <string>

#include "MetadataObject.h"
#include "pathcontroller.h"
//class MetadataObject;
//class DerivativeMetadataRow;

namespace simplearchive {

	
	
	class WriteMetadata
	{
		
		
	public:

		
		static bool writeMasterMetadata(std::string& rootPath, std::string& imageName, MetadataObject& metadataObject);

		static bool writeMetadata2Workspace(std::string& workspace, std::string& imageAddress, MetadataObject& metadataObject);

		static bool writeUserspaceMasterMetadata(std::string& rootPath, MetadataObject& metadataObject);

		static bool writeUserMetadata(std::string& userMetadataPath, std::string& imageAddress, MetadataObject& metadataObject);
		
	};
	
}; // namespace
