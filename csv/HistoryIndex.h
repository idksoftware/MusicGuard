#pragma once

#include <string>
#include <vector>
#include <memory>

#include "MetaType.h"
#include "AddressScope.h"
#include "HistoryEvent.h"
#include "CSVIndexVisitor.h"

namespace simplearchive {

	class CSVIndexSystemHistory : public CSVIndexVisitorBase {

	public:
		/// Constructor
		/// @parm folderVisitor - pointer to FolderVisitor
		CSVIndexSystemHistory(std::shared_ptr<CSVIndexAction> indexAction) : CSVIndexVisitorBase(indexAction) {};
		// Destructor
		virtual ~CSVIndexSystemHistory() {};
		/// This Function processes the files under the root using the
		/// FolderVisitor class passed in the constructor
		virtual bool process(const char* rootFolder);
	};

	class CSVIndexImageHistory : public CSVIndexVisitorBase {
	public:
		/// Constructor
		/// @parm folderVisitor - pointer to FolderVisitor
		CSVIndexImageHistory(std::shared_ptr<CSVIndexAction> indexAction) : CSVIndexVisitorBase(indexAction) {};
		// Destructor
		virtual ~CSVIndexImageHistory() {};
		/// This Function processes the files under the root using the
		/// FolderVisitor class passed in the constructor
		virtual bool process(const char* rootFolder);
	};

	/*
	* This is a type of table indexing not tryied to a table i.e. CheckoutStatus
	*/

	class CSVIndexCheckoutStatus : public CSVIndexVisitorBase {
	public:
		/// Constructor
		/// @parm folderVisitor - pointer to FolderVisitor
		CSVIndexCheckoutStatus(std::shared_ptr<CSVIndexAction> indexAction) : CSVIndexVisitorBase(indexAction) {};
		// Destructor
		virtual ~CSVIndexCheckoutStatus() {};
		/// This Function processes the files under the root using the
		/// FolderVisitor class passed in the constructor
		virtual bool process(const char* rootFolder);
	};

	class CSVIndexMasterTable : public CSVIndexCheckoutStatus {
	public:
		/// Constructor
		/// @parm folderVisitor - pointer to FolderVisitor
		CSVIndexMasterTable(std::shared_ptr<CSVIndexAction> indexAction) : CSVIndexCheckoutStatus(indexAction) {};
		// Destructor
		virtual ~CSVIndexMasterTable() {};

	};

};