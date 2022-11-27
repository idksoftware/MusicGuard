#include "Import.h"

#include "AppConfig.h"
#include "SAUtils.h"
#include "Quiet.h"
#include "ConfigReader.h"
#include "MGAppOptions.h"
#include "ParseOptions.h"
#include "ConfigReader.h"
#include "AppOptions.h"
#include "Environment.h"
#include "ParseProperties.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	bool Import::doCommand() {

		SIAARCConfig config;
		MGAppOptions& appOptions = MGAppOptions::get();

		bool isSourePathSet = false;
		// Source of images
		if (getParser().foundOption("source-path") == true) {
			std::string opt = getParser().optionValue("source-path");
			appOptions.m_sourcePath = opt;
			isSourePathSet = true;
		}
		if (isSourePathSet == false) {
			appOptions.m_sourcePath = SAUtils::getCurrentDirectory();
		}
		if (getParser().foundOption("lightroom") == true) {
			std::string opt = getParser().optionValue("lightroom");
			config.setLightroom();
		}

		if (getParser().foundOption("scanfile") == true) {
			std::string opt = getParser().optionValue("scanfile");
			config.setLightroom();
		}


		if (getParser().foundOption("peek") == true) {
			appOptions.m_peekOnly = true;
		}
		if (getParser().foundOption("force-date") == true) {
			std::string opt = getParser().optionValue("force-date");
			if (opt.compare("FileDate") == 0) {
				appOptions.m_useFileDate = true;
			}

			if (opt.compare("TodaysDate") == 0) {
				appOptions.m_useDateToday = true;
			}
			else {
				appOptions.m_archiveDate = ExifDate(opt.c_str());
			}
			appOptions.m_forceDate = true;

		}
		if (getParser().foundOption("default-date") == true) {
			std::string opt = getParser().optionValue("default-date");
			config.setSourcePath(opt.c_str());
			if (opt.compare("FileDate") == 0) {
				appOptions.m_useFileDate = true;
			}

			if (opt.compare("TodaysDate") == 0) {
				appOptions.m_useDateToday = true;
			}
			else {
				appOptions.m_archiveDate = ExifDate(opt.c_str());
			}
			appOptions.m_useDate = true;
		}

		if (getParser().foundOption("set") == true) {
			std::string opt = getParser().optionValue("set");
			ParseProperties parseProperties;
			if (!parseProperties.parse(opt.c_str())) {
				printf("Invalid argument for \"archive\" \"%s\"\n\n", opt.c_str());
				printf("%s", getParser().topicUsageDescription(getParser().getCurrentCommandId(), 80).c_str());
				return false;
			}
			appOptions.m_optionList = parseProperties.getOptionList();

			//noOptionsFound++;
		}

		appOptions.setCommandMode(MGAppOptions::CommandMode::CM_Import);

		Environment::setEnvironment();
		
		return true;
	}
}
/*

*/