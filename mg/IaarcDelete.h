#pragma once
class IaarcDelete
{
};
#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcDelete : public IaarcSubCommand {
	public:
		IaarcDelete(MGArgvParser& argvParser) : IaarcSubCommand("delete", argvParser) {};
	protected:
		bool doCommand() override;
	};

};
