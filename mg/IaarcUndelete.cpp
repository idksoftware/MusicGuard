#include "IaarcUndelete.h"

#include "Quiet.h"
#include "ConfigReader.h"
#include "MGAppOptions.h"
#include "ParseOptions.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	bool IaarcUndelete::doCommand() {
		MGAppOptions& appOptions = MGAppOptions::get();
		if (getParser().foundOption("scope") == true) {
			appOptions.m_imageAddress = getParser().optionValue("scope");
		}

		if (getParser().foundOption("list") == true) {
			appOptions.m_list = true;
		}

		if (getParser().foundOption("file") == true) {
			appOptions.m_filePath = getParser().optionValue("file");
			appOptions.m_usingFile = true;
		}

		if (getParser().foundOption("comment") == true) {
			appOptions.m_comment = getParser().optionValue("comment");
		}

		if (getParser().foundOption("force") == true) {
			appOptions.m_force = true;
		}

		appOptions.setCommandMode(MGAppOptions::CommandMode::CM_Undelete);
		return true;
	}
}