
#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcScan : public IaarcSubCommand {
	public:
		IaarcScan(MGArgvParser& argvParser) : IaarcSubCommand("scan", argvParser) {};
	protected:
		bool doCommand() override;
	};

};
