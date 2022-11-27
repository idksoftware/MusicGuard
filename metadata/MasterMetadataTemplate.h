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


#ifndef METADATATEMPLATE_H_
#define METADATATEMPLATE_H_

#include <map>
#include <mutex>
#include "ConfigReader.h"
#include "ResultsPresentation.h"

namespace simplearchive {



/**
 * @brief Metadata Container
 *
 * This contains the metadata Object that is created as an outcome of the substitution process.
 * This process is contained in this class using the Configuration reader class ConfigReader
 * using the configuration container. As each template is read the contents will be placed
 * into this class. At the end of the process the contents of the Config class is copied into
 * the Metadata Object class MetadataObject. This class will be used for further substitutions
 * by the Exif reading and user defined metadata information.
 *
 */
#include "DBDefines.h"

class MetadataObject;

typedef std::shared_ptr<MetadataObject> MetadataObject_ptr;
typedef std::unique_ptr<ConfigBlock> Config_ptr;
//class Config;


class MasterMetadataTemplateSchema : public MTTableSchema {
public:
	MasterMetadataTemplateSchema() noexcept : MTTableSchema(TABLE_METADATA_TEMPLATE) {
/*
		// Description
		add(MTSchema(MTType::Text, DB_DESCRIPTION));
		add(MTSchema(MTType::Text, DB_LABEL));
		add(MTSchema(MTType::Text, DB_TITLE));
		add(MTSchema(MTType::Text, DB_SUBJECT));
		add(MTSchema(MTType::Integer, DB_RATING));
		add(MTSchema(MTType::Integer, DB_RATINGPERCENT));
		add(MTSchema(MTType::Text, DB_TAGS));// template
		add(MTSchema(MTType::Text, DB_KEYWORDS));// template
		// Origin
		add(MTSchema(MTType::Text, DB_COMMENT));// template
		add(MTSchema(MTType::Text, DB_AUTHOR));

		// Cammara
		add(MTSchema(MTType::Text, DB_COPYRIGHT));
		add(MTSchema(MTType::Text, DB_MAKER));
		add(MTSchema(MTType::Text, DB_MODEL));	

		// Location
		add(MTSchema(MTType::Text, DB_LATITUDE));
		add(MTSchema(MTType::Text, DB_LONGITUDE));
		add(MTSchema(MTType::Text, DB_LOCATION));
		add(MTSchema(MTType::Text, DB_SCENE));// template

		// IPTC
		add(MTSchema(MTType::Text, DB_SOURCEURL));			// template
		add(MTSchema(MTType::Text, DB_USAGERIGHTS));// template
		add(MTSchema(MTType::Text, DB_COPYRIGHTURL));// template
		add(MTSchema(MTType::Text, DB_HEADLINE));// template
		add(MTSchema(MTType::Text, DB_CATEGORY));// template
		add(MTSchema(MTType::Text, DB_SOURCE));// template
		add(MTSchema(MTType::Text, DB_INSTRUCTIONS));// template

		add(MTSchema(MTType::Text, DB_CREATOR));// template
		add(MTSchema(MTType::Text, DB_JOBTITLE));// template
		add(MTSchema(MTType::Text, DB_ADDRESS));// template
		add(MTSchema(MTType::Text, DB_CITY));// template
		add(MTSchema(MTType::Text, DB_STATE));// template
		add(MTSchema(MTType::Text, DB_POSTALCODE));// template
		add(MTSchema(MTType::Text, DB_COUNTRY));// template
		add(MTSchema(MTType::Text, DB_PHONE));// template
		add(MTSchema(MTType::Text, DB_EMAIL));// template
		add(MTSchema(MTType::Text, DB_WEBSITE));// template
*/
	}
};

class MasterMetadataTemplateRow : public MTRow {
	static MasterMetadataTemplateSchema m_tableSchema;

public:
	MasterMetadataTemplateRow() : MTRow(m_tableSchema) {};
	//MetadataTemplateRow(const MTRow& row) : MTRow(row) {};
	MasterMetadataTemplateRow(const MTRow& row) : MTRow(m_tableSchema) {

		for (unsigned int i = 0; i < row.size(); i++) {
			MTColumn& c1 = *at(i);
			MTColumn& c2 = *row.at(i);
			c1 = c2;
		}

	}

	
};
/*
	Note table of one row
*/
class MasterMetadataTemplatePartition : public MTTable {
public:
	MasterMetadataTemplatePartition() : MTTable(new MasterMetadataTemplateSchema) {};
	virtual ~MasterMetadataTemplatePartition() {};

};


class MasterMetadataTemplateResultsPresentation {
	MTRow m_row;
	std::shared_ptr<MTTableSchema> m_tableSchema;
public:
	MasterMetadataTemplateResultsPresentation(MTRow row) : m_row(row), m_tableSchema(new MasterMetadataTemplateSchema) {};
	~MasterMetadataTemplateResultsPresentation() = default;

	bool writeHuman();
	bool writeXML(); 
	bool writeCSV();
	bool writeJson();
	bool writeHtml();
};




} /* namespace simplearchive */
#endif /* METADATATEMPLATE_H_ */
