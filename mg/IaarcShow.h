
#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcShow : public IaarcSubCommand {
	public:
		IaarcShow(MGArgvParser& argvParser) : IaarcSubCommand("show", argvParser) {};
	protected:
		bool doCommand() override;
	};

};