#include "ImageFileNameManager.h"
#include "SequenceNumber.h"
#include "FileVersion.h"

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

//#include "SAUtils.h"

std::string ImageFileNameManager::m_preName;
RenameType ImageFileNameManager::m_renameType = RenameType::NoRename;
RenameBase ImageFileNameManager::m_renameBase = RenameBase::Base16;
RenameBase ImageFileNameManager::m_version = RenameBase::Base16;


//ImageFileNameOption ImageFileNameManager::m_option = ImageFileNameOption::Default;
std::string ImageFileNameManager::m_masterPath;


std::string getExtention(const std::string& file)
{
	std::string ext = file.substr(file.find_last_of(".") + 1);
	return ext;
}

std::string getExtention(const char* file)
{
	std::string filestr = file;
	return getExtention(filestr);
}

static std::string getFilenameNoExt(const std::string& file)
{
	size_t sp = file.find_last_of("/\\");

	std::string name;
	if (sp != -1)
	{
		name = file.substr(++sp);
	}
	const size_t ep = file.find_last_of('.');
	name = file.substr(0, ep);
	return name;
}

static std::string getFilenameNoExt(const char* file)
{
	std::string filestr = file;
	return getFilenameNoExt(filestr);
}


std::string toLowerStr(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return str;
}



ImageFileNameManager& ImageFileNameManager::get() {
	static ImageFileNameManager imageFileNameManager;
	return imageFileNameManager;
}



bool ImageFileNameManager::setOption(const char* fileRenameString)
{
	std::string str = fileRenameString;

	size_t end = str.find_first_of('{');
	if (end == std::string::npos) {
		return false;
	}
	m_preName = str.substr(0, end);
	size_t start = end;
	end = str.find_first_of('}', start);
	if (end == std::string::npos) {
		return false;
	}
	std::string seq = str.substr(start + 1, end - (start + 1));
	start = str.find_first_of('[', end);
	if (start == std::string::npos) {
		return false;
	}
	end = str.find_first_of(']', start);
	if (end == std::string::npos) {
		return false;
	}
	std::string version = str.substr(start + 1, end - (start + 1));
	m_version = toRenameBaseEnum(version);
	start = seq.find_first_of('-', 0);
	std::string nameType = seq.substr(0, start);
	m_renameType = toRenameTypeEnum(nameType);
	std::string renameBase = seq.substr(start+1, seq.length() - (start + 1));
	m_renameBase = toRenameBaseEnum(renameBase);
	return true;
}

void ImageFileNameManager::setOption(const char* preName, RenameType renameType, RenameBase renameBase, RenameBase version)
{
	m_preName = preName;
	m_renameType = renameType;
	m_renameBase = renameBase;
	m_version = version;
}

std::string ImageFileNameManager::getFileName(const char *yearDay, uint64_t seq, const char * orginalName)
{

	std::string yearDayStr = yearDay;
	int y = atoi(yearDayStr.substr(0,4).c_str());
	std::string tmp = yearDayStr.substr(5, 2).c_str();
	int m = atoi(yearDayStr.substr(5, 2).c_str());
	tmp = yearDayStr.substr(5, 2).c_str();
	int d = atoi(yearDayStr.substr(8, 2).c_str());
	tmp = yearDayStr.substr(8, 2).c_str();
	std::string imagePath = m_masterPath;
	imagePath += '/';
	imagePath += yearDayStr.substr(0, 4);
	imagePath += '/';
	imagePath += yearDayStr;
	imagePath += "/images";
	return getFileName(y, m, d, seq, imagePath, orginalName);
	//return orginalName;
}

std::string ImageFileNameManager::getFileName(int y, int m, int d, uint64_t seq, const std::string& imagePath, const char * orginalName)
{
	std::string ext = getExtention(orginalName);
	std::string name = getFilenameNoExt(orginalName);
	std::string fullPath = imagePath;
	fullPath += '/';
	fullPath += orginalName;

	std::shared_ptr<ImageSequence> sequence = nullptr;
	switch (m_renameType) {
	case RenameType::Sequence:
		sequence = std::make_unique<NumberSequence>((int32_t)seq);
		sequence->setBase(m_renameBase);
		break;
	case RenameType::Date:
		sequence = std::make_unique<DateSequence>(y, m, d, fullPath.c_str());
		sequence->setBase(m_renameBase);
		break;
	case RenameType::Readabledate:
		sequence = std::make_unique<ReadabledateSequence>(y, m, d, fullPath.c_str());
		sequence->setBase(m_renameBase);
		break;
	case RenameType::NoRename:
	case RenameType::Unknown:
	default:
		sequence = std::make_unique<NoRenameSequence>(fullPath.c_str());
		sequence->setBase(m_renameBase);
	}
	m_name = sequence->toSequence();
	m_name += '.';
	m_name += ext;
	return m_name;
}

RenameBase ImageFileNameManager::toRenameBaseEnum(std::string str)
{
	std::string s = toLowerStr(str);
	if (s == "base32") {
		return RenameBase::Base32;
	}
	else if (s == "base16") {
		return RenameBase::Base16;
	}
	else if (s == "base10") {
		return RenameBase::Base10;
	}
	return RenameBase::Unknown;
}

RenameType ImageFileNameManager::toRenameTypeEnum(std::string str)
{
	std::string s = toLowerStr(str);
	if (s == "sequence") {
		return RenameType::Sequence;
	}
	else if (s == "date") {
		return RenameType::Date;
	}
	else if (s == "readabledate") {
		return RenameType::Readabledate;
	}
	else if (s== "norename") {
		return RenameType::NoRename;
	}
	return RenameType::Unknown;
}

std::string ImageFileNameManager::incrementFileVersion(const char *fileName)
{
	FileVersion fileVersion(fileName);
	fileVersion.increment();
	return fileVersion.getFilename();
}