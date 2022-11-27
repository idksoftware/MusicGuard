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

#include <sstream>
#include <fstream>
#include "JournalFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

namespace simplearchive {

class JournalData {
	friend class CSVJournalFile;
	uint64_t m_id;
	std::string m_name;
	uint64_t m_size;
	uint64_t m_crc;
	std::string m_md5;
	ExifDateTime m_created;
	ExifDateTime m_modified;
	std::string toString();
	std::string toXMLString();
public:
	JournalData();
	virtual ~JournalData();
};

JournalData::JournalData() {
	m_size = 0;
	m_crc = 0;
	m_id = -1;
}

JournalData::~JournalData() {}

CSVJournalFile::CSVJournalFile() {

}

CSVJournalFile::~CSVJournalFile() {
}
bool CSVJournalFile::writeCSV(const char *path) {

	std::ofstream file(path, std::ios::out);
	if (file.is_open() == false) {
		return false;
	}
	for (std::vector<JournalData>::iterator i = begin(); i != end(); i++) {
		JournalData &data = *i;
		file << data.toString() << '\n';

	}
	file.close();

	return true;
}
bool CSVJournalFile::writeXML(const char *path) {

	std::ofstream file(path, std::ios::out);
	if (file.is_open() == false) {
		return false;
	}
	file << "<Journal>\n";
	for (std::vector<JournalData>::iterator i = begin(); i != end(); i++) {
		JournalData &data = *i;
		file << "<Data>\n" <<data.toXMLString() << "</Data>\n";

	}
	file << "</Journal>\n";
	file.close();

	return true;
}
bool CSVJournalFile::add(uint64_t id, const char *name, uint64_t size, uint64_t crc,
					const char *md5, ExifDateTime &created, ExifDateTime &modified) {
	JournalData journalData;
	journalData.m_id = id;
	journalData.m_name = name;
	journalData.m_size = size;
	journalData.m_crc = crc;
	journalData.m_md5 = md5;
	journalData.m_created = created;
	journalData.m_modified = modified;
	push_back(journalData);
	return true;
}

void CSVJournalFile::clearUp() {
	clear();
}

std::string JournalData::toString() {

	std::stringstream s;
	s << m_id << ':' << m_name << ':' << m_size << ':' << m_crc << ':' << m_md5 << ':' << m_created.current() << ':' << m_modified.current();
	return s.str();

}

std::string JournalData::toXMLString() {

	std::stringstream s;
	s << "\t<Id>" << m_id << "</Id>\n\t<Name>" << m_name << "</Name>\n\t<Size>" << m_size << "</Size\n\t<Crc>" << m_crc << "</Crc>\n\t<Md5>" << m_md5
							<< "</Md5>\n\t<Created>" << m_created.current() << "</Created>\n\t<Modified>" << m_modified.current() << "</Modified>\n";
	return s.str();

}
} /* namespace simplearchive */
