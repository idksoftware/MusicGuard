#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcStatus : public IaarcSubCommand {
	public:
		IaarcStatus(MGArgvParser& argvParser) : IaarcSubCommand("status", argvParser) {};
	protected:
		bool doCommand() override;
	};

};
