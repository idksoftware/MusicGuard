#pragma once
#include <vector>
#include <map>
#include <mutex>
#include <memory>
#include "SAUtils.h"
//#include "LogDocument.h"
#include "CIDKDate.h"



	class ImportJournalItem;
	class ImportJournal : public std::vector <std::shared_ptr<ImportJournalItem>>
	{
		std::string writeTag(const char* tag, const std::string& value, int tab);
		std::string writeTag(const char* tag, const int value, int tab);
		std::map<std::string, int> m_index;
		std::string m_logNameStr;
		std::string m_xmlNameStr;
		std::string m_rootPath;
		int m_count;
		int m_current;
		std::string m_curlogfilepath;
		std::string m_curxmlfilepath;
	public:
		enum class Result {
			Incomplete,
			Imported,
			Duplicate,
			Error,
			Unknown
		};
	private:
		//bool write(const char *journalFilePath);
		//bool writeXML(const char *journalFilePath);
	public:
		ImportJournal(std::string& logName, std::string& rootPath);
		virtual ~ImportJournal();
		bool add(const char* filepath);
		bool update(const char* filepath, Result result, const char* location = 0);

		size_t numberOfImages() { return size(); }
		bool setCurrent(const char* imagesPath);
		size_t getCurrentImageIndex();
		bool write() {
			std::string path = m_rootPath;
			path += '/';
			path += m_logNameStr.c_str();
			m_curlogfilepath = path;
			return write(path.c_str());
		}
		bool writeXML() {
			std::string path = m_rootPath;
			path += '/';
			path += m_xmlNameStr.c_str();
			m_curxmlfilepath = path;
			return writeXML(path.c_str());
		}

		const char* getCurJournalLogFilepath()
		{
			return m_curlogfilepath.c_str();
		}

		const char* getCurJournalXMLFilepath()
		{
			return m_curxmlfilepath.c_str();
		}

		bool write(const char* journalFilePath);
		bool writeXML(const char* journalFilePath);
	};

	class ImportJournalItem {
		std::string m_filepath;
		ImportJournal::Result m_result;
		std::string m_location;
		bool m_validated;
		const char *ResultString(ImportJournal::Result& result);
	public:
		ImportJournalItem(const char *filepath);
		void setResult(ImportJournal::Result result);
		void setLocation(const char *location);
		void setValidated();
		std::string toString();
		const char *getSourceImage();
		const char *getLocation();
		const char *getResult();
		ImportJournal::Result getResultEnum();
		bool isValidated();
	};


	class ImportJournalManager {
		static std::string m_journalFilePath;
		ImportJournalManager();
		ImportJournalManager(const ImportJournalManager& src);
		ImportJournalManager& operator=(const ImportJournalManager& rhs);
		std::unique_ptr<ImportJournal> m_importJournal;
	public:
		static void setJournalFilePath(const char *journalRoot) {
			m_journalFilePath = journalRoot;
			if (SAUtils::DirExists(m_journalFilePath.c_str()) == false) {
				SAUtils::mkDir(m_journalFilePath.c_str());
			}
			m_journalFilePath += "/import";
			if (SAUtils::DirExists(m_journalFilePath.c_str()) == false) {
				SAUtils::mkDir(m_journalFilePath.c_str());
			}

		}
		static ImportJournal& GetJournal();
		static bool save();
		virtual ~ImportJournalManager();
		//const char* getCurJournalLogFilepath();
		//const char* getCurJournalXMLFilepath();
	};


