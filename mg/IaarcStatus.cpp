#include "IaarcStatus.h"


#include "Quiet.h"
#include "ConfigReader.h"
#include "MGAppOptions.h"
#include "ParseOptions.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	bool IaarcStatus::doCommand() {
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
		appOptions.setCommandMode(MGAppOptions::CommandMode::CM_Status);
		return true;
	}
}
