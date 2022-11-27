
#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcHistory : public IaarcSubCommand {
	public:
		IaarcHistory(MGArgvParser& argvParser) : IaarcSubCommand("history", argvParser) {};
	protected:
		bool doCommand() override;
	};

};