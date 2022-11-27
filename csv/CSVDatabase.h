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

#ifndef CSVDATABASE_H_
#define CSVDATABASE_H_

#include "SAUtils.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>
#include "DBDefines.h"
#include "MetadataObject.h"
#include "CSVTable.h"
//#include "ArchivePath.h"


#define MetadataTableName		"Metadata"
#define MetadataTableFilename	"Metadata.csv"


namespace simplearchive {
/**
 * @brief This is the main interface into the CSV Database. This Database is used
 * to create a Comma Separated Value based database.
 * The created files in the database are stored in a directory tree. This directory tree
 * is defined by a year folder, day folder hierarchy much like the main archive folder hierarchy
 * The aim is to limit the resulting files to a manageable size.
 * In addition so the metadata records are also a manageable length, the matedata is spit up
 * into sections. each section it  associated by a unique sequence number. Which will become the primary
 * key to each of these table files This sequence number is generated by other the SQL database or this
 * database if the SQL one is not enabled.
 */
class MirrorDB;



class CSVMasterTable : public CSVTable {
	CSVMasterTable();
	
	static std::string m_dbpath;
	//std::unique_ptr<MirrorDB> m_mirrorDB;
	
public:
	/// Set the database path for the archive. This will normally under Master/.root
	static void setDBPath(const char *path);
	/// gets the database instance.
	static CSVMasterTable &get();
	/// destructor
	virtual ~CSVMasterTable();
	
	void add(MetadataObject &metadataObject, const char *relpath);
	const MetadataObject *get(unsigned int idx, const char *path);
	SharedMTRow get(const char *name, const char *path);
	bool put(const char *name, const char *path, MetadataObject &mo);

	bool copy(const char *path);
	bool validate(const char *path);
	bool showMasterMetadata(const char* addressScope, const char* formatType, const char* filePath);
	bool setMasterMetadata(const char* addressScope, std::shared_ptr<std::vector<std::shared_ptr<OptionItem>>> optionList);
	bool setMasterMetadata(const char* addressScope, const char* option, const char* value);


};

//class MirrorDB;

// Note there two databass need to be combined into one



} /* namespace simplearchive */
#endif /* CSVDATABASE_H_ */
