#pragma once

#include <string>

class WriteXML
{
public:
	WriteXML() = default;
	~WriteXML() = default;
	std::string writeTag(const char* tag, const std::string& value);
};

