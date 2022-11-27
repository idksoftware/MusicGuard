#pragma once
class IaarcProp
{
};
#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcProp : public IaarcSubCommand {
	public:
		IaarcProp(MGArgvParser& argvParser) : IaarcSubCommand("prop", argvParser) {};
	protected:
		bool doCommand() override;
	};

};
