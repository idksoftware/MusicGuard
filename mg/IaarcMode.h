#pragma once
class IaarcMode
{
};
#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcMode : public IaarcSubCommand {
	public:
		IaarcMode(MGArgvParser& argvParser) : IaarcSubCommand("mode", argvParser) {};
	protected:
		bool doCommand() override;
	};

};


