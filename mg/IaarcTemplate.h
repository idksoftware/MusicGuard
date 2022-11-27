#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcTemplate : public IaarcSubCommand {
	public:
		IaarcTemplate(MGArgvParser& argvParser) : IaarcSubCommand("template", argvParser) {};
	protected:
		bool doCommand() override;
	};

};