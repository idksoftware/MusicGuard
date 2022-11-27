#include "DBDefines.h"
#include "MetadataTemplateManager.h"
#include "MetadataObject.h"

namespace simplearchive {

	MasterMetadataTemplateSchema MasterMetadataTemplateRow::m_tableSchema;

	std::unique_ptr<ConfigBlock>	MetadataTemplateManager::m_templateFile(new ConfigBlock);
	MasterMetadataTemplateRow MetadataTemplateManager::m_masterMetadataTemplateRow;
	
	//Config *MetadataTemplate::m_templateFile = 0;


	MetadataTemplateManager& MetadataTemplateManager::GetInstance()
	{
		static MetadataTemplateManager metadataTempleteManager;
		return metadataTempleteManager;
	}

	MetadataTemplateManager::~MetadataTemplateManager() {}

	static std::string defaultStr = "";


	std::string& MetadataTemplateManager::getValue(const char* key) {
		std::map<std::string, std::string>::iterator it;

		if ((it = m_templateFile->find(key)) == m_templateFile->end()) {
			return defaultStr;
		}
		return it->second;
	}

	bool MetadataTemplateManager::readMaster(const char* path, bool level, bool current)
	{
		std::string templatePath = path;

		if (current) {
			if (MetadataTemplateManager::readMaster(templatePath.c_str(), "master.tpl") == false) {
				return false;
			}
		}
		else {
			if (level) {
				if (MetadataTemplateManager::readMaster(templatePath.c_str(), "master_current.tpl") == false) {
					return false;
				}
			}
			else {
				if (MetadataTemplateManager::readMaster(templatePath.c_str(), "master_base.tpl") == false) {
					return false;
				}
			}
		}
		MasterMetadataTemplateResultsPresentation resultsPresentation(m_masterMetadataTemplateRow);
		resultsPresentation.writeHuman();
		return true;
	}

	

	bool MetadataTemplateManager::readMaster(const char* path, const char* datafile) {

		ConfigReader configReader;
		if (configReader.read(path, datafile, *m_templateFile) == false) {
			return false;
		}
		//templateFile.printAll();
		for (std::map<std::string, std::string>::iterator ii = m_templateFile->begin(); ii != m_templateFile->end(); ++ii) {
			std::string& value = getValue((*ii).first.c_str());
			//printf("\"%s\" = \"%s\"\n", (*ii).first.c_str(), (*ii).second.c_str());
			if (value.compare("")) {
				value = (*ii).second.c_str();
			}
			try {
				MTColumn& col = m_masterMetadataTemplateRow.columnAt((*ii).first.c_str());
				col = (*ii).second.c_str();
			}
			catch (std::invalid_argument& e) {
				printf("%s", e.what());
			}
			catch (MTTypeException& e) {
				const char* tmp = e.what();
				printf("%s\n", tmp);
			}
		}
		return true;
	}

	

	bool MetadataTemplateManager::write(const char* datafile) {
		return true;
	}

	MetadataObject_ptr MetadataTemplateManager::getMetadataObject() {
		MetadataObject_ptr metadataObject = std::make_unique<MetadataObject>();

		for (std::map<std::string, std::string>::iterator ii = m_templateFile->begin(); ii != m_templateFile->end(); ++ii) {
			//std::string &value = getValue((*ii).first.c_str());
			//printf("\"%s\" opt:\"%s\"\n", (*ii).first.c_str(), (*ii).second.c_str());
			try {
				MTColumn& col = metadataObject->columnAt((*ii).first.c_str());
				col = (*ii).second.c_str();
			}
			catch (std::invalid_argument& e) {
				printf("%s", e.what());
			}
			catch (MTTypeException& e) {
				const char* tmp = e.what();
				printf("%s\n", tmp);
			}
			
		}
		return metadataObject;
	}
}