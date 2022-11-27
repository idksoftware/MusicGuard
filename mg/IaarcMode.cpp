#include "IaarcMode.h"

#include "Quiet.h"
#include "ConfigReader.h"
#include "MGAppOptions.h"
#include "ParseOptions.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	bool IaarcMode::doCommand() {
		MGAppOptions& appOptions = MGAppOptions::get();
		if (getParser().foundOption("remote-server") == true) {
			//config.setServerModeON();
		}
		appOptions.setCommandMode(MGAppOptions::CommandMode::CM_Mode);
		return true;
	}
}