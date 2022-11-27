
#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcExport : public IaarcSubCommand {
	public:
		IaarcExport(MGArgvParser& argvParser) : IaarcSubCommand("export", argvParser) {};
	protected:
		bool doCommand() override;
	};

};
