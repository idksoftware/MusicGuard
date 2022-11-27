#include "IaarcTemplate.h"

#include "Quiet.h"
#include "ConfigReader.h"
#include "MGAppOptions.h"
#include "IAParseOptions.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	bool IaarcTemplate::doCommand() {
		MGAppOptions& appOptions = MGAppOptions::get();
		IAParseOptions iaParseOptions;
		bool res = false;
		std::string opt;
		appOptions.m_args = 0;
		appOptions.m_level = true;
		appOptions.m_repo = true;
		if (getParser().foundOption("level") == true) {
			std::string opt = getParser().optionValue("level");
			res = iaParseOptions.parseLevelOptions(opt.c_str());
			if (!res) {
				printf("Invalid argument for \"level\" \"%s\"\n\n", opt.c_str());
				printf("%s", getParser().topicUsageDescription(getParser().getCurrentCommandId(), 80).c_str());
				return false;
			}
			appOptions.m_level = iaParseOptions.isCurrent();
			appOptions.m_args++;
		}
		if (getParser().foundOption("archive") == true) {
			std::string opt = getParser().optionValue("archive");
			res = iaParseOptions.parseArchiveOptions(opt.c_str());
			if (!res) {
				printf("Invalid argument for \"archive\" \"%s\"\n\n", opt.c_str());
				printf("%s", getParser().topicUsageDescription(getParser().getCurrentCommandId(), 80).c_str());
				return false;
			}
			appOptions.m_repo = iaParseOptions.isMaster();
			appOptions.m_args++;
		}
		if (getParser().foundOption("option") == true) {
			std::string opt = getParser().optionValue("option");
			//printf("option string %s\n", opt.c_str());
			appOptions.m_option = opt;
			appOptions.m_args++;
		}
		appOptions.setCommandMode(MGAppOptions::CommandMode::CM_Template);
		return true;
	}
}