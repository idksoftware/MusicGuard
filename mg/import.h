#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class Import : public IaarcSubCommand {
	public:
		Import(MGArgvParser& argvParser) : IaarcSubCommand("import", argvParser) {};
	protected:
		bool doCommand() override;
	};

};