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

#include "TargetsList.h"
#include "ImageExtentions.h"
#include "DirectoryVisitor.h"
#include "CLogger.h"
#include "HookCmd.h"

#undef FILECODE
#define FILECODE TARGETSLIST_CPP

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif



	void ImageItem::processHook() {
		/*
		CLogger &logger = CLogger::getLogger();
		logger.log(LOG_OK, CLogger::INFO, "process Hook Item %s\n", m_path.c_str());
		//printf("process Hook Item %s\n", m_path.c_str());
		OnFileCmd onFileCmd(m_path.c_str());
		onFileCmd.process();
		*/
	}

	void ImageItem::processFileHook() {
		CLogger &logger = CLogger::getLogger();
		logger.log(LOG_OK, CLogger::Level::INFO, "process Hook Item: %s", m_path.c_str());
		
		
		OnFileCmd onFileCmd(m_path.c_str());
		onFileCmd.process();
	}

	

	int ImportImageList::m_folderCount = 0;
	int ImportImageList::m_fileCount = 0;
	std::shared_ptr<ImageSets> ImportImageList::m_imageSets = nullptr;

	bool ImportImageList::onFile(const char *path) {
		ImageExtentions& ie = ImageExtentions::get();
		std::string tmp = path;
		std::string ext = SAUtils::getExtention(tmp);
		if (ie.isAllowed(ext.c_str()) == false) {
			return false;
		}
		std::shared_ptr<ImageItem> imageItem = std::make_shared<ImageItem>(path);
		imageItem->processFileHook();
		m_fileCount++;
		m_imageSet->insert(m_imageSet->end(), imageItem);
		return true;
	};


	/// This class creates a folder list for
	class FolderDir : public FolderVisitor {
		
		std::shared_ptr<ImportImageList> m_importList;
		std::string m_path;
	protected:
		virtual bool onStart(const char *path) {
			//if (m_importList == nullptr) {
			//	m_importList = std::make_shared<ImportList>();
			//}
			//m_importList = std::make_shared<ImportList>();
			
			CLogger &logger = CLogger::getLogger();
			logger.log(LOG_OK, CLogger::Level::INFO, "Starting reading folder: \"%s\"", path);
			return m_importList->onStart(path);
		};

		virtual bool onFile(const char *path) {
			CLogger &logger = CLogger::getLogger();
			logger.log(LOG_OK, CLogger::Level::INFO, "Reading file: %s", path);
			bool res = m_importList->onFile(path);
			if (!res) {
				std::string tmp = path;
				std::string filename = SAUtils::getFilename(tmp);
				logger.log(LOG_OK, CLogger::Level::WARNING, "Not a valid file type: \"%s\" rejecting ", filename.c_str());
				return true;
			}
			return true;
		};
		virtual bool onDirectory(const char *path) {
			CLogger &logger = CLogger::getLogger();
			logger.log(LOG_OK, CLogger::Level::INFO, "Now reading folder:  %s", path);
			return m_importList->onDirectory(path);
		};
		virtual bool onEnd() {
			CLogger &logger = CLogger::getLogger();
			//logger.log(LOG_OK, CLogger::Level::INFO, "Completed reading folder: %s", m_path->c_str());
			logger.log(LOG_OK, CLogger::Level::INFO, "Completed reading folder");
			return m_importList->onEnd();
		};
		virtual std::shared_ptr<FolderVisitor> make() {
			return (std::make_shared<FolderDir>());
		}
	public:
		FolderDir() {
			m_importList = std::make_shared<ImportImageList>();
		};
		virtual ~FolderDir() {};
		static std::shared_ptr<ImageSets> getImageSets() {
			return ImportImageList::getImageSets();
		}
		static void destroy() {

			//delete m_imageSets;
			return ImportImageList::destroy();
		}

		static int getFileCount() {
			return ImportImageList::getFileCount();
		}

		static int getFolderCount() {
			return ImportImageList::getFolderCount();
		}
	};

	

	int TargetsList::getFileCount() {
		return FolderDir::getFileCount();
	}

	int TargetsList::getFolderCount() {
		return FolderDir::getFolderCount();
	}

	TargetsList::TargetsList()
	{
	}


	TargetsList::~TargetsList()
	{
	}

	void TargetsList::process(const char *path) {
		std::shared_ptr<FolderDir> folderDir_ptr = std::make_shared<FolderDir>();
		DirectoryVisitor directoryVisitor(folderDir_ptr);
		directoryVisitor.process(path);
	}

	

	std::shared_ptr<ImageSets> TargetsList::getImageSets() {
		return FolderDir::getImageSets();
	}

	void TargetsList::destroy() {
		FolderDir::destroy();
	}