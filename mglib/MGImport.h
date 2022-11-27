#pragma once

#include <memory>
#include <string>
#include "SAUtils.h"
#include "ResultsPresentation.h"
#include "MetadataObject.h"
#include "ArchiveObject.h"

using namespace simplearchive;

	class ImageIndex;
	class ImageSets;
	class ImportJournal;
	

class MGImport
{
	bool m_Error;

	std::string m_MasterPath;
	std::string m_indexPath;
	std::string m_workspacePath;
	std::string m_templatePath;

	int m_folders;
	int m_imageFiles;
	int m_imageFilesRejected;
	int m_imageFilesCompleted;
	

	bool m_doDryRun;
	void copyBasicExit(MetadataObject& metadataObject);
	void copyExternalExif(MetadataObject& metadataObject);
	void applyMetadataOptions(MetadataObject& metadataObject, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList);

	void print(const MetadataObject& mo);
	std::shared_ptr<ImageSets> processFiles(const char* sourcePath);
	
	bool processImageGroupSets(std::shared_ptr<ImageSets> imageSets, ImportJournal& importJournal, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList);
public:
	MGImport();
	/// @brief This initalises the archive builder

	/// @param appdir - Index Path
	/// @param userrootdir - secondary root archive folder
	bool Init();
	//bool scanForImages(const char* filePath, ResultsPresentation::FormatType& formatType, const char* file);
	/// @param sourcePath - source folder were the images to be imported reside.
	bool Import(const char* sourcePath, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList, bool peekImport = false);
	bool ImportFile(const char* filePath, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList);
	
	/// Distructor
	virtual ~MGImport();
	/// @brief The 
	bool IsError()
	{
		return (!m_Error);
	}
	
};

