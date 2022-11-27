


#include <filesystem>
#include "IaarcScan.h"
#include "AppConfig.h"
#include "SAUtils.h"
#include "Quiet.h"
#include "ConfigReader.h"
#include "MGAppOptions.h"
#include "ParseOptions.h"
#include "ConfigReader.h"

using namespace CommandLineProcessing;
namespace fs = std::filesystem;
namespace simplearchive {

	bool IaarcScan::doCommand() {

		SIAARCConfig config;
		MGAppOptions& appOptions = MGAppOptions::get();

		bool isSourePathSet = false;
		if (getParser().foundOption("source-path") == true) {
			std::string opt = getParser().optionValue("source-path");
			config.setSourcePath(opt.c_str());
			isSourePathSet = true;
		}
		if (isSourePathSet == false) {
			config.setSourcePath(SAUtils::getCurrentDirectory().c_str());
		}

		if (getParser().foundOption("file") == true) {
			std::string opt = getParser().optionValue("file");
			appOptions.m_filePath = opt;
		}
		else {
			fs::path path = fs::temp_directory_path();
			appOptions.m_filePath = path.string();
		}

		if (getParser().foundOption("format-type") == true) {
			std::string opt = getParser().optionValue("format-type");
			if ((appOptions.m_formatType = ResultsPresentation::parse(opt.c_str())) == ResultsPresentation::FormatType::unknown) {
				printf("Invalid argument for \"FormatType\" \"%s\"\n\n", opt.c_str());
				printf("%s", getParser().topicUsageDescription(getParser().getCurrentCommandId(), 80).c_str());
				return false;
			}
		}
		else {
			appOptions.m_formatType = ResultsPresentation::FormatType::csv;
		}

		appOptions.setCommandMode(MGAppOptions::CommandMode::CM_Scan);
		return true;
	}
}