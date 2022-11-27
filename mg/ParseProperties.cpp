#include "ParseProperties.h"
#include "SAUtils.h"
#include "DBDefines.h"
#include <algorithm> 
#include <cctype>
#include <locale>

enum class Type {
	Text,
	Integer,
	Float,
	Date,
	Unknown
};

struct {
	const char* n_name;
	Type m_type;
} PropertiesList[] = {
	
	{ DB_TITLE, Type::Text },
	{ DB_RATING, Type::Integer },
	{ DB_LOCATION, Type::Text },
	{ DB_SIZE, Type::Integer },
};




// trim from both ends (in place)
static inline void trim(std::string& s) {
	if (s[0] == '{') {
		s = s.substr(1, s.length() - 1);
	}
	if (s[s.length() - 1] == '}') {
		s = s.substr(0, s.length()-1);
	}
}

Option ParseProperties::process(std::string& optionString)
{
	return Option();
}

bool ParseProperties::parse(const char* optionString)
{
	std::string os = optionString;
	if (m_list == nullptr) {
		m_list = std::make_shared<std::vector<std::shared_ptr<OptionItem>>>();
	}
	if (os[0] == '{' && os[os.length() - 1] == '}') {
		trim(os);
		std::vector<std::string> list = split(os, ',');
		for (auto s : list) {
			
			if (parseItem(s.c_str()) == false) {
				return false;
			}
			std::shared_ptr<OptionItem> item = std::make_shared<OptionItem>(m_option, m_value);
			m_list->push_back(item);
		}

	}
	else {
		if (parseItem(os.c_str()) == false) {
			return false;
		}
		std::shared_ptr<OptionItem> item = std::make_shared<OptionItem>(m_option, m_value);
		m_list->push_back(item);
	}
	return true;
}

bool ParseProperties::parseItem(const char* optionString)
{
	bool ret = processArgs(optionString);
	if (!ret) {
		return false;
	}

	int n = sizeof(PropertiesList) / sizeof(PropertiesList[0]);

	for (int i = 0; i < n; i++) {
		if (iequals(m_option, PropertiesList[i].n_name)) {
			m_option = PropertiesList[i].n_name; // make sure the correct name is used i.e. Tags and not tags
			switch (PropertiesList[i].m_type) {
			case Type::Text:
				return true;
			case Type::Integer:
				return isNumber(m_value);
			case Type::Float:
				return isFloatNumber(m_value);
			case Type::Date:
				return true;
			case Type::Unknown:
				break;
			default:
				break;
			}
		}
	}
	return false;
}
