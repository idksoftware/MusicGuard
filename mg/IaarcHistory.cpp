#include "IaarcHistory.h"

#include "Quiet.h"
#include "ConfigReader.h"
#include "MGAppOptions.h"
#include "ParseOptions.h"
#include "AddressScope.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	bool IaarcHistory::doCommand() {
		MGAppOptions& appOptions = MGAppOptions::get();
		if (getParser().foundOption("list") == true) {
			std::string opt = getParser().optionValue("list");
			StatusOptions statusOptions;
			if (statusOptions.parse(opt.c_str()) == false) {
				printf("Invalid argument for \"list\" \"%s\"\n\n", opt.c_str());
				printf("%s", getParser().topicUsageDescription(getParser().getCurrentCommandId(), 80).c_str());
				return false;
			}
			appOptions.m_option = statusOptions.getOption();
		}
		else {
			appOptions.m_option = STATUS_CHECKED_OUT;
		}

		if (getParser().foundOption("scope") == true) {
			appOptions.m_imageAddress = getParser().optionValue("scope");
			AddressScope as;
			as.scope(appOptions.m_imageAddress.c_str());
			if (!as.isValid()) {
				printf("Invalid argument for \"scope\" \"%s\"\n\n", appOptions.m_imageAddress.c_str());
				printf("%s", getParser().topicUsageDescription(getParser().getCurrentCommandId(), 80).c_str());
				return false;
			}
		}

		if (getParser().foundOption("file") == true) {
			std::string opt = getParser().optionValue("file");
			appOptions.m_filePath = opt;
		}

		if (getParser().foundOption("format-type") == true) {
			std::string opt = getParser().optionValue("format-type");
			if ((appOptions.m_formatType = ResultsPresentation::parse(opt.c_str())) == ResultsPresentation::FormatType::unknown) {
				printf("Invalid argument for \"FormatType\" \"%s\"\n\n", opt.c_str());
				printf("%s", getParser().topicUsageDescription(getParser().getCurrentCommandId(), 80).c_str());
				return false;
			}
		}
		appOptions.setCommandMode(MGAppOptions::CommandMode::CM_History);
		return true;
	}
}