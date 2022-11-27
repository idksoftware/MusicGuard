#pragma once
#include <string>
#include "SequenceNumber.h"

enum class ImageFileNameOption {
	Unknown,
	UseDate,
	UseNumber,
	NoRename,
	Default
};

class ImageFileNameManager final
{
	static std::string m_preName;
	static RenameType m_renameType;
	static RenameBase m_renameBase;
	static RenameBase m_version;
	static std::string m_masterPath;	
	std::string m_name;

	static RenameBase toRenameBaseEnum(std::string s);
	static RenameType toRenameTypeEnum(std::string s);

public:
	ImageFileNameManager() = default;
	~ImageFileNameManager() = default;

	static void setMasterPath(const char *path) {
		m_masterPath = path;
	}
	static bool setOption(const char* fileRenameString);
	static void setOption(const char* preName, RenameType renameType, RenameBase renameBase, RenameBase version);
	
	std::string getFileName(const char *yearDay, uint64_t dec, const char *orginalName);
	std::string getFileName(int y, int m, int d, uint64_t seq, const std::string& imagePath, const char* orginalName);

	std::string incrementFileVersion(const char* fileName);

	static ImageFileNameManager& get();
	static ImageFileNameOption getOption(std::string& name);
};

