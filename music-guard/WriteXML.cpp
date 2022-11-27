#include "WriteXML.h"
#include <sstream>
#include <iostream>
#include <fstream>

std::string WriteXML::writeTag(const char* tag, const std::string& value) {
	std::ostringstream xml;
	if (!value.empty()) {
		xml << "<" << tag << ">" << value << "</" << tag << ">\n";
	}
	else {
		xml << "<" << tag << "/>\n";
	}
	return xml.str();
}
