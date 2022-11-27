#include "IaarcGet.h"

#include "Quiet.h"
#include "ConfigReader.h"
#include "MGAppOptions.h"
#include "ParseOptions.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	bool IaarcGet::doCommand() {
		MGAppOptions& appOptions = MGAppOptions::get();

		bool gotImageAddress = false;
		if (getParser().foundOption("scope") == true) {
			appOptions.m_imageAddress = getParser().optionValue("scope");
			gotImageAddress = true;
		}

		if (getParser().foundOption("comment") == true) {
			appOptions.m_comment = getParser().optionValue("comment");
		}

		if (getParser().foundOption("version") == true) {
			appOptions.m_version = getParser().optionValue("version");
		}

		if (getParser().foundOption("force") == true) {
			appOptions.m_force = true;
		}
		appOptions.setCommandMode(MGAppOptions::CommandMode::CM_Get);	
		return true;
	}
}