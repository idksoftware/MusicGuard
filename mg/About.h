#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class About : public IaarcSubCommand {
	public:
		About(MGArgvParser& argvParser) : IaarcSubCommand("about", argvParser) {};
	protected:
		bool doCommand() override;
	};

};