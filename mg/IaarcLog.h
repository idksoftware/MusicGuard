#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcLog : public IaarcSubCommand {
	public:
		IaarcLog(MGArgvParser& argvParser) : IaarcSubCommand("log", argvParser) {};
	protected:
		bool doCommand() override;
	};

};