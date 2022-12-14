#pragma once

#include <string>
#include <vector>
#include <memory>

enum class HPSource {

};

enum class HomePathType {
	Default,	// Default value
	LocalEnv,	// Local Environment set
	SystemEnv,	// System Environment set
	UserOnly,	// user only archive
	AllUsers,	// all users archive
	Unknown
};

enum class HPError {
	Ok,					// OK
	initaliseError,
	CannotLocatePath,	// Cannot locate path at default or HOME if set
	NotFound,			// Path not at default and HOME not set 
	Unknown				// Unknown state
};

enum class HomePathID {
	HomePath,
	MasterPath,
	DerivativePath,
	WorkspacePath,
	MetadataPath,
	PicturePath,
	WWWImagePath,
	UserspacePath,
	InvalidPath
};

class InitailiseHomePaths;

class HomePathsBase {
	
	
protected:

	bool m_found{ false };	// string found
	bool m_valid{ false };	// in file system
	bool m_changed{ false };	// in file system
	HomePathType m_type{ HomePathType::Unknown };
	HPError m_error{ HPError::Unknown };
	std::string m_path;

	static bool m_first;
	
	static std::string m_allUsersHomeEnvironmentPath;
	static std::string m_myselfHomeEnvironmentPath;
	static std::string m_allusersHomeDefaultPath;
	static std::string m_myselfHomeDefaultPath;
	static std::string m_homeDrive;
	static std::string m_homePathEnv;
	static std::string m_relativeRoot;

	bool baseSysInit(std::string& path, const char* relativePath, const char* enviromentPath);
	bool baseUserInit(std::string& path, const char* relativePath, const char* enviromentPath);
	void baseEnableInit(bool& option, bool defaultOption, const char* enviromentOption);
	
public:
	HomePathsBase() = default;
	virtual ~HomePathsBase() {};

	HPError error() noexcept {
		return m_error;
	}
	HomePathType type() noexcept {
		return m_type;
	}
	bool isFound() noexcept {	// string found
		return m_found;
	}
	bool isValid() noexcept {	// in file system
		return m_valid;
	}
	bool isChanged() noexcept { // changed by enviroment option 
		return m_changed;
	}

	void setPath(const char* p);
	const std::string& getPath();

	std::string errorStr();

	virtual bool init() = 0;
	virtual bool checkAndMakePath() { return true; }
	virtual HomePathID getID() const = 0;
	
	
	static bool loadEnv();
};

class MusicGuardHome {
	static std::vector<HomePathsBase*> m_list;

	bool m_found{ false };	// string found
	bool m_valid{ false };	// in file system
	HomePathType m_type{ HomePathType::Unknown };
	HPError m_error{ HPError::Unknown };
	static std::string m_imgArchiveHome;
	static std::string m_primaryPath;
	void initHomePaths();
	
	bool setArchiveHome();
	
protected:

	MusicGuardHome() noexcept {
		if (setArchiveHome() == false) {
			return; // m_error set
		}
		HomePathsBase::loadEnv();
		if (m_valid == true) {
			initHomePaths();
			init();
		}
	}

public:
	
	~MusicGuardHome() = default;

	bool init();
	bool checkAndMakePaths();
	bool checkAndMakePath();
	HPError error() noexcept {
		return m_error;
	}

	std::string errorStr();

	HomePathType type() noexcept {
		return m_type;
	}
	bool isFound() noexcept {	// string found
		return m_found;
	}
	bool isValid() noexcept {	// in file system
		return m_valid;
	}
	
	static const std::string& getMusicGuardHome();
	static const std::string& getPrimaryPath();
	static MusicGuardHome& getObject() {
		static MusicGuardHome imgArchiveHome;
		return imgArchiveHome;
	}


};



class MasterPath : public HomePathsBase {
	
public:
	MasterPath() = default;
	virtual ~MasterPath() {};

	virtual HomePathID getID() const {
		return HomePathID::MasterPath;
	};

	bool init() override;

	static MasterPath& getObject() {
		static MasterPath masterPath;
		return masterPath;
	}
};

class MasterBackupOnePath : public HomePathsBase {

	
	static bool m_enabled;
protected:

public:
	MasterBackupOnePath() = default;
	virtual ~MasterBackupOnePath() {};

	virtual HomePathID getID() const {
		return HomePathID::MasterPath;
	};

	bool init() override;
	
	void enabled(bool b) { m_enabled = b; };

	static bool enabled() { return m_enabled; };
	
	static MasterBackupOnePath& getObject() {
		static MasterBackupOnePath masterBackupOnePath;
		return masterBackupOnePath;
	}
};

class MasterBackupTwoPath : public HomePathsBase {

	
	static bool m_enabled;
protected:

public:
	MasterBackupTwoPath() = default;
	virtual ~MasterBackupTwoPath() {};

	virtual HomePathID getID() const {
		return HomePathID::MasterPath;
	};

	bool init() override;
	
	void enabled(bool b) { m_enabled = b; };

	static bool enabled() { return m_enabled; };
	
	static MasterBackupTwoPath& getObject() {
		static MasterBackupTwoPath masterBackupTwoPath;
		return masterBackupTwoPath;
	}
};



class DerivativePath : public HomePathsBase {

public:
	DerivativePath() = default;
	virtual ~DerivativePath() {};
	
	
	HomePathID getID() const override {
		return HomePathID::DerivativePath;
	};

	
	bool init() override;
	
	static DerivativePath& getObject() {
		static DerivativePath derivativePath;
		return derivativePath;
	}
};

class DerivativeBackupOnePath : public HomePathsBase {

	static bool m_enabled;
protected:

public:
	DerivativeBackupOnePath() = default;
	virtual ~DerivativeBackupOnePath() {};

	virtual HomePathID getID() const {
		return HomePathID::MasterPath;
	};

	bool init() override;
	
	void enabled(bool b) { m_enabled = b; };

	static bool enabled() { return m_enabled; };
	
	static DerivativeBackupOnePath& getObject() {
		static DerivativeBackupOnePath derivativeBackupOnePath;
		return derivativeBackupOnePath;
	}
};

class DerivativeBackupTwoPath : public HomePathsBase {

	static bool m_enabled;
protected:

public:
	DerivativeBackupTwoPath() = default;
	virtual ~DerivativeBackupTwoPath() {};

	virtual HomePathID getID() const {
		return HomePathID::MasterPath;
	};

	bool init() override;
	void enabled(bool b) { m_enabled = b; };

	static bool enabled() { return m_enabled; };
	
	static DerivativeBackupTwoPath& getObject() {
		static DerivativeBackupTwoPath derivativeBackupTwoPath;
		return derivativeBackupTwoPath;
	}
};

class UserspacePath : public HomePathsBase {

	static std::string m_hidden;
	static bool m_autoView;
protected:

public:
	UserspacePath() = default;
	virtual ~UserspacePath() {};

	HomePathID getID() const override {
		return HomePathID::UserspacePath;
	};

	bool init() override;
	bool checkAndMakePath() override;
	void setAutoViewOn(bool b) { m_autoView = b; };

	static bool autoViewOn();
	
	static const std::string& getHidden() { return m_hidden; };
	static UserspacePath& getObject() {
		static UserspacePath userspacePath;
		return userspacePath;
	}
};

class WorkspacePath : public HomePathsBase {

	static std::string m_hidden;
	static bool m_autoView;
	static bool m_autoCheckout;
protected:
	
public:
	WorkspacePath() = default;
	virtual ~WorkspacePath() {};
	
	HomePathID getID() const override {
		return HomePathID::WorkspacePath;
	};

	bool init() override;
	bool checkAndMakePath() override;
	void setAutoCheckout(bool b) { m_autoCheckout = b; };
	void setAutoViewOn(bool b) { m_autoView = b; };

	static bool autoCheckout();
	static bool autoViewOn();
	
	static WorkspacePath& getObject() {
		static WorkspacePath workspacePath;
		return workspacePath;
	}
};

class PicturePath : public HomePathsBase {

	static std::string m_hidden;
	static bool m_autoView;
public:
	PicturePath() = default;
	virtual ~PicturePath() {};
	
	HomePathID getID() const override {
		return HomePathID::PicturePath;
	};

	bool init() override;
	bool checkAndMakePath() override;
	void setAutoViewOn(bool b) { m_autoView = b; };

	static bool autoViewOn();

	static PicturePath& getObject() {
		static PicturePath picturePath;
		return picturePath;
	}
};

class WWWImagePath : public HomePathsBase {

	static std::string m_hidden;
	static bool m_autoView;
public:
	WWWImagePath() = default;
	virtual ~WWWImagePath() {};

	HomePathID getID() const override {
		return HomePathID::WWWImagePath;
	};

	bool init();
	bool checkAndMakePath() override;
	void setAutoViewOn(bool b) { m_autoView = b; };

	static bool autoViewOn();
	
	static WWWImagePath& getObject() {
		static WWWImagePath wwwImagePath;
		return wwwImagePath;
	}
};

class UserMetadataPath : public HomePathsBase {

	static bool m_autoView;
public:
	UserMetadataPath() = default;
	virtual ~UserMetadataPath() {};

	HomePathID getID() const override {
		return HomePathID::MetadataPath;
	};

	bool init();
	bool checkAndMakePath();
	
	void setAutoViewOn(bool b) { m_autoView = b; };

	static bool autoViewOn();
	
	static UserMetadataPath& getObject() {
		static UserMetadataPath userMetadataPath;
		return userMetadataPath;
	}
};
