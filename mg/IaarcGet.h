#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcGet : public IaarcSubCommand {
	public:
		IaarcGet(MGArgvParser& argvParser) : IaarcSubCommand("get", argvParser) {};
	protected:
		bool doCommand() override;
	};

};