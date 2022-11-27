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

#ifndef SIALIB_H_
#define SIALIB_H_

#include <string>
#include <memory>


#include "SAUtils.h"
#include "ExifDate.h"
#include "ResultsPresentation.h"
/*
*/
class MGImport;

namespace simplearchive {


	
	
	
	class CompletedSummary {
		std::string m_summary;
		std::string m_result;
	public:
		CompletedSummary() = default;
		virtual ~CompletedSummary() = default;
		void setSummary(const char *s) { m_summary = s; };
		const char *getSummary() { return m_summary.c_str(); };
		void setResult(const char *s) { m_result = s; };
		const char *getResult() { return m_result.c_str(); };
	};

	class SIALib
	{
	public:

		enum class MainArchives {
			Master,			//* Show
			Derivative,			//* Show
			Both
		};

		enum class Scope {
			Workspace,		//* Initalise an archive with the default 
			Master,			//* Show
			Derivative,			//* Show
			All,			//* Show
			Main			//* show version
		};

		enum class VerifyBackups {
			Backup_1,		//* Initalise an archive with the default 
			Backup_2,			//* Show
			Both,		//* Show
			None
		};

		enum class Backups {
			Backup_1,		//* Initalise an archive with the default 
			Backup_2,			//* Show
			Both
		};

	private:
		std::string m_HomePath;
		std::shared_ptr<MGImport> m_mgImport;
	
		bool m_winsockRequired;
		bool m_socklibStarted;
		bool m_enableEvents;
		int m_udpPortNum;
		int m_tcpPortNum;
		bool m_enableServer;
		std::string m_udpAddress;
	public:
		SIALib();
		~SIALib();
		void enableEvents(const char *address, int port);
		void enableServer(int port);
		int initalise(const char* appName);
		void start();
		int complete();
		//int complete();
		

		bool scan(ResultsPresentation::FormatType& formatType, const char* file);
		bool Import(const char* filePath, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList);
		bool ImportFile(const char *filePath, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList);
		

		static const int getLastCode();
		
		static const char *getLastMessage();
		
		// INIT – Initialises the MusicGuard environment
		

		//	config – Configure MusicGuard parameters

		//	setenv – Configure MusicGuard parameters– Sets MusicGuard environment variables

		//	show – Show how the system is configured.

		//	archive – These options control the backup activities.

		//	sync – This command synchronises the primary archives with there associated backups.

		//	purge – Purges deleted images from archive

		//	validate – Validate commands

		//	allow – Controls which image file extensions are allowed into the archive.

		//	about – prints the version information

		//	help - On Administrative Housekeeping commands

		/**
		This shows the checked out images. The file path will be in the form:
		null = all archive
		year = all the year	i.e "2015"
		day  = all the day  i.e "2015-02-11"
		*/

		
		
		bool get(const char* scope, const char* comment, const char* version, bool force);

		
		bool history(const char* scope, ResultsPresentation::FormatType& formatType, const char* filepath);

		bool status(const char* scope, ResultsPresentation::FormatType& formatType, const char* filepath);

		bool show();

		bool showVersions();

		bool showCheckedOut(const char* scope, ResultsPresentation::FormatType& formatType, const char* filepath);

		

		bool listContents(const char *addressScope); // maybe not used

		

		
		
		bool exportImage(const char *distpath);

		// Not_Used bool view(const char *name);

		

		bool deleteImages(const char* scope, const char* comment, bool force);
		
		bool undeleteImages(const char* scope, const char* comment);
		
		bool purge();

		bool metadata(const char* scope, const char* formatType, const char* filePath);

		bool setProperty(const char* scope, const char* option, const char* value);
		bool setProperty(const char* scope, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList);

		bool workspace(bool sync);

		bool metadataTemplate(bool repo, bool templateFile, int args);

		bool mirror(const char *name);
		
		bool archive(const char *archivePath, const char *distPath, uint64_t sizeOfMedia, ExifDateTime *startDate, ExifDateTime *endDate);  //< Create backup volumes

		bool checkDisk();

		bool configure(const char* configOptionBlock, const char* configOption, const char* configValue);

		bool validate(Scope scope, bool main, VerifyBackups verifyBackups, bool repair);

		bool sync(MainArchives mainArchives, Backups backups);

		bool log(const char *filepath, const char* fromDate, const char* toDate, ResultsPresentation::FormatType& formatType, const char* filename);

		bool journal(const char* scope, const char* fromDate, const char* toDate, ResultsPresentation::FormatType& formatType, const char* filename);
		bool remoteServer();
	
	};

}
#endif /* SIALIB_H_ */
