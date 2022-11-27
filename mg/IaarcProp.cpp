#include "IaarcProp.h"

#include "Quiet.h"
#include "ConfigReader.h"
#include "MGAppOptions.h"
#include "ParseOptions.h"
#include "ParseProperties.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	bool IaarcProp::doCommand() {
		int noOptionsFound = 0;
		MGAppOptions& appOptions = MGAppOptions::get();
		if (getParser().foundOption("scope") == true) {
			appOptions.m_imageAddress = getParser().optionValue("scope");
			noOptionsFound++;
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
			
			noOptionsFound++;
		}
		if (noOptionsFound != 2) {
			printf("No options found");
			printf("%s", getParser().topicUsageDescription(getParser().getCurrentCommandId(), 80).c_str());
			return false;
		}

		appOptions.setCommandMode(MGAppOptions::CommandMode::CM_Prop);

		return true;
	}
}