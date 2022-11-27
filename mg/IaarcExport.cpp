#include "IaarcExport.h"

#include "Quiet.h"
#include "ConfigReader.h"
#include "MGAppOptions.h"
#include "ParseOptions.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	bool IaarcExport::doCommand() {
		MGAppOptions& appOptions = MGAppOptions::get();

		if (getParser().foundOption("dist-path") == true) {
			std::string opt = getParser().optionValue("source-path");
			appOptions.m_sourcePath = opt;
			//isSourePathSet = true;
		}

		if (getParser().foundOption("scope") == true) {
			appOptions.m_imageAddress = getParser().optionValue("scope");
		}

		if (getParser().foundOption("comment") == true) {
			appOptions.m_comment = getParser().optionValue("comment");
		}

		if (getParser().foundOption("force") == true) {
			appOptions.m_force = true;
		}

		if (getParser().foundOption("version") == true) {
			std::string opt = getParser().optionValue("version");
			appOptions.m_version = opt.c_str();
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
		//if (noOptionsFound != 2) {
		//	printf("No options found");
		//	printf("%s", getParser().topicUsageDescription(getParser().getCurrentCommandId(), 80).c_str());
		//	return false;
		//}


		appOptions.setCommandMode(MGAppOptions::CommandMode::CM_Export);
		return true;
	}
}