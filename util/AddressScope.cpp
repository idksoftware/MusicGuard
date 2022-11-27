#include "AddressScope.h"
#include <vector>
//#define STANDALONE 1
#ifndef STANDALONE
#include "SAUtils.h"
#else
class SAUtils {
public:
	static bool isNumber(const std::string& s);
};

bool SAUtils::isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
#endif


class ScopeString
{
	std::string m_day;
	std::string m_month;
	std::string m_year;
	std::string m_image;
	void init(const std::string& s);
	bool m_isValid{ true };
public:
	ScopeString();
	ScopeString(const std::string& pattern);
	ScopeString(const char* d);
	int compare(ScopeString& d);
	bool isValid() { return m_isValid; };
};

ScopeString::ScopeString()
{
	m_day = '*';
	m_month = '*';
	m_year = '*';
	m_image = '*';
}

ScopeString::ScopeString(const std::string& s)
{
	init(s);
}

ScopeString::ScopeString(const char* d)
{
	std::string tmp = d;
	init(tmp);
}

bool isnum(std::string &s)
{
	return (!s.empty() && s.find_first_not_of("0123456789") == std::string::npos);
}

std::string justify(std::string s)
{
	std::string tmp = "0";
	if (s.length() == 1)
	{
		if (s[0] == '*')
		{
			return s;
		}
		tmp += s;
		return tmp;
	}
	return s;
}

void ScopeString::init(const std::string& ss)
{
	std::string tmp;
	if (ss[0] == '\"') {
		 tmp = ss.substr(1, ss.size() - 2);
		
	}
	else {
		tmp = ss;
	}
	std::string delimiter = "-";
	size_t last = 0;
	size_t next = 0;
	std::string s;
	std::string name;
	size_t pos = 0;
	if ((pos = tmp.find("/")) != std::string::npos || (pos = tmp.find("\\")) != std::string::npos)
	{
		s = tmp.substr(0, pos);
		pos++;
		name = tmp.substr(pos, tmp.length() - pos);
	}
	else
	{
		s = tmp;
	}

	std::string token[4] = {"*", "*", "*", "*"};

	int c = 0;
	if (s.find(delimiter, last) != std::string::npos)
	{
		while ((next = s.find(delimiter, last)) != std::string::npos)
		{
			token[c] = s.substr(last, next - last);
			if (!isnum(token[c]) && !(token[c].compare("*") == 0)) {
				m_isValid = false;
				return;
			};
			//printf("%s", token[c].c_str());
			c++;
			last = next + 1;
		}
		
		token[c++] = s.substr(last);
		if (!isnum(token[c]) && !(token[c].compare("*") == 0)) {
			m_isValid = false;
			return;
		};
		if (c != 3) {
			m_isValid = false;
			return;
		}
	}
	else
	{
		if (s.length() == 3 && s.compare("all") == 0) {
			m_image = "*";
			m_day = "*";
			m_month = "*";
			m_year = "*";
			
			return;
		}
		else {
			m_isValid = false;
			return;
		}
		
	}
	if (name.length() != 0)
	{
		token[3] = name;
	}
	m_image = token[3];
	m_day = justify(token[2]);
	m_month = justify(token[1]);
	m_year = token[0];
	m_isValid = true;
	//printf("%s %s %s\n", token[0].c_str(), token[1].c_str(), token[2].c_str());
}

int ScopeString::compare(ScopeString& d)
{
	if (m_year == "*" || d.m_year == "*" || m_year.compare(d.m_year) == 0)
	{
		// year matched
		if (m_month == "*" || d.m_month == "*" || m_month.compare(d.m_month) == 0)
		{
			// month matched
			if (m_day == "*" || d.m_day == "*" || m_day.compare(d.m_day) == 0)
			{
				// day matched
				if (m_image == "*" || d.m_image == "*" || m_image.compare(d.m_image) == 0)
				{
					return 0;
				}
			}
		}
	}
	return -1;
}

class AddressScopeItem
{
	ScopeString m_begin;
	ScopeString m_end;
	bool m_range;
	void init(std::string& pattern);
	bool m_isValid{ true };
public:
	AddressScopeItem(const char* pattern);
	AddressScopeItem(std::string& pattern);
	const bool isInScope(ScopeString& d);
	bool isValid();
};

void AddressScopeItem::init(std::string& pattern)
{
	std::string s = pattern;
	m_begin = ScopeString(s);
	if (!m_begin.isValid()) {
		m_isValid = false;
	}
	m_range = false;
	// begin-2009
	/*
	std::string s = pattern;
	int pos = s.find('-');
	if (pos < 0) {
		m_begin = DataString(s);
		m_range = false;
	} else {
		std::string begin = s.substr(0, pos);
		m_begin = DataString(begin);
		std::string end = s.substr(pos+1, s.length() - (pos+1));
		m_end = DataString(end);
		m_range = false;
	}
	std::string begin = s.substr(0, pos);
	*/
}

AddressScopeItem::AddressScopeItem(std::string& pattern)
{
	init(pattern);
}

AddressScopeItem::AddressScopeItem(const char* pattern)
{
	// begin-2009
	std::string s = pattern;
	init(s);
}

const bool AddressScopeItem::isInScope(ScopeString& d)
{
	if (m_range)
	{
		if (m_begin.compare(d) <= 0 && m_end.compare(d) >= 0)
		{
			return true;
		}

		return false;
	}
	if (m_begin.compare(d) == 0)
	{
		return true;
	}
	return false;
}

bool AddressScopeItem::isValid()
{
	return m_isValid;
}

class AddressSTokenList : public std::vector<AddressScopeItem>
{
};

AddressScope::AddressScope()
{
	m_list = std::make_shared<AddressSTokenList>();
}

AddressScope::AddressScope(AddressScope& as)
{
	m_pattern = as.m_pattern;
	//m_list = std::make_shared<AddressSTokenList>(as.m_list);
	m_matchAll = as.m_matchAll;
}

AddressScope::~AddressScope()
{
}

/*
std::string remove(std::string &str)
{
	
	char *tmp = new char[str.length() + 1];
	char *s = tmp;
	if (str[0] = '{') {
		s++;
	}
	if (str[str.length - 1] = '}') {
		s[str.length - 1] = '\0';
	}
	
	return true;
}
*/
std::string removespace(std::string str)
{
	size_t m = str.length();
	int i = 0;
	while (i < m)
	{
		while (str[i] == 32)
		{
			str.erase(i, 1);
			m--;
		}
		i++;
	}
	return str;
}

// Range: 2009-2015, 2009-end, begin-2009, 2009/08/16-2015
// Item: 2009/08/16, 2009/08/17,
bool AddressScope::isInScope(const char* d)
{
	if (m_matchAll) return true;

	ScopeString date(d);
	for (auto iter = m_list->begin(); iter != m_list->end(); ++iter)
	{
		AddressScopeItem& item = *iter;
		if (item.isInScope(date))
		{
			return true;
		}
	}
	return false;
}

std::string AddressScope::makeYearScopeString(const char* d)
{
	std::string pattern = d;
	pattern += "-*-*";
	return pattern;
}


bool AddressScope::isImageInScope(const char* image)
{
	if (m_matchAll) return true;
	std::string pattern = "*-*-*/";
	pattern += image;

	ScopeString dateImage(pattern);
	for (auto iter = m_list->begin(); iter != m_list->end(); ++iter)
	{
		AddressScopeItem& item = *iter;
		if (item.isInScope(dateImage))
		{
			return true;
		}
	}
	return false;
}

void AddressScope::scopeAll()
{
	m_matchAll = true;
}


bool AddressScope::scope(const char* str)
{
	m_matchAll = false;
	std::string s = str;
	//std::string s = removespace(tmp);
	std::string delimiter = ",";

	size_t last = 0;
	size_t next = 0;
	std::string token;
	// This looks for a list of scopes i.e 12.03.2022,20.04.2022,01.04.2022
	while ((next = s.find(delimiter, last)) != std::string::npos)
	{
		token = s.substr(last, next - last);
		//printf("%s", token.c_str());
		AddressScopeItem item(token);
		m_list->push_back(item);
		if (item.isValid() == false) {
			m_isValid = false;
		}
		last = next + 1;
	}
	token = s.substr(last);
	//printf("%s", token.c_str());
	AddressScopeItem item(token);
	m_list->push_back(item);
	if (item.isValid() == false) {
		m_isValid = false;
	}
	return true;
}

bool AddressScope::isValid()
{
	return m_isValid;
}


class VersionScopeItem
{
	int m_begin;
	int m_end;
	bool m_range;
	bool m_error;
	bool init(std::string& pattern, int version);
	bool isScope(const char* pattern, int version);
	std::string m_pattern;
	int m_maxVersion;
public:
	VersionScopeItem(const char* pattern, int maxVersion);
	VersionScopeItem(std::string& pattern, int maxVersion);
	~VersionScopeItem();
	bool isInScope(int version);
	bool isValid();
};

class VersionTokenList : public std::vector<VersionScopeItem>
{

};

bool VersionScopeItem::init(std::string& pattern, int version)
{
	int num = -1;
	if (m_pattern[0] == '[')
	{
		//int rangeCharPos = m_pattern.find('-', 1);
		//std::string first = m_pattern.substr(1, m_pattern.length() - )
		return true;
	}
	if (m_pattern[0] == '*')
	{
		return true;
	}
	if (!SAUtils::isNumber(m_pattern))
	{
		return false;
	}
	num = std::stoi(m_pattern);
	if (version != num)
	{
		return false;
	}
	return true;
}

VersionScopeItem::VersionScopeItem(const char* pattern, int maxVersion)
{
	m_pattern = pattern;
	m_maxVersion = maxVersion;
}

VersionScopeItem::VersionScopeItem(std::string& pattern, int maxVersion)
{
	m_pattern = pattern;
	m_maxVersion = maxVersion;
}

VersionScopeItem::~VersionScopeItem()
{
}


bool VersionScopeItem::isInScope(int version)
{
	if (m_pattern[0] == '[')
	{
		//int rangeCharPos = m_pattern.find('-', 1);
		//std::string first = m_pattern.substr(1, m_pattern.length() - )
		return true;
	}
	if (m_pattern[0] == '*')
	{
		return true;
	}
	if (isScope(m_pattern.c_str(), version) == false)
	{
		return false;
	}
	return true;
}

bool VersionScopeItem::isValid()
{
	return false;
}


bool VersionScopeItem::isScope(const char* pattern, int version)
{
	std::string m_pattern = pattern;

	if (m_pattern[0] != '[' || m_pattern[m_pattern.length() - 1] != ']')
	{
		return false;
	}

	size_t delimt = m_pattern.find_first_of('-', 1);
	if (delimt == std::string::npos)
	{
		return false;
	}

	std::string fs = m_pattern.substr(1, delimt - 1);

	if (SAUtils::isNumber(fs) == false)
	{
		return false;
	}
	int first = std::stoi(fs);

	std::string ls = m_pattern.substr(delimt + 1, m_pattern.length() - (delimt + 2));
	int end = 0;
	if (ls[0] == '@')
	{
		end = m_maxVersion;
	}
	else
	{
		if (SAUtils::isNumber(ls) == false)
		{
			return false;
		}
		end = std::stoi(ls);
	}
	//printf("First: %d End: %d\n", first, end);
	if (version >= first && version <= end)
	{
		return false;
	}
	return true;
}

VersionScope::VersionScope(int maxVersion) : m_maxVersion(maxVersion), m_list(std::make_unique<VersionTokenList>())
{
}


VersionScope::~VersionScope()
{
}

bool VersionScope::scope(const char* str)
{
	m_matchAll = false;
	std::string tmp = str;
	std::string s = removespace(tmp);
	std::string delimiter = ",";

	size_t last = 0;
	size_t next = 0;
	std::string token;
	while ((next = s.find(delimiter, last)) != std::string::npos)
	{
		token = s.substr(last, next - last);
		//printf("%s", token.c_str());
		if (token[0] == '*')
		{
			m_matchAll = true;
		}
		m_list->push_back(VersionScopeItem(token, m_maxVersion));
		last = next + 1;
	}
	token = s.substr(last);
	//printf("%s", token.c_str());
	m_list->push_back(VersionScopeItem(token, m_maxVersion));
	return false;
}

void VersionScope::scopeAll()
{
	m_matchAll = true;
}

bool VersionScope::isInScope(int version)
{
	if (m_matchAll) return true;

	for (auto iter = m_list->begin(); iter != m_list->end(); ++iter)
	{
		VersionScopeItem& item = *iter;
		if (item.isInScope(version))
		{
			return true;
		}
	}
	return false;
}
