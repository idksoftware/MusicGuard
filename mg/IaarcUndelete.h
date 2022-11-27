#pragma once
class IaarcUndelete
{
};

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcUndelete : public IaarcSubCommand {
	public:
		IaarcUndelete(MGArgvParser& argvParser) : IaarcSubCommand("undelete", argvParser) {};
	protected:
		bool doCommand() override;
	};

};