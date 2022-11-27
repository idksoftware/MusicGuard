#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcJournal : public IaarcSubCommand {
	public:
		IaarcJournal(MGArgvParser& argvParser) : IaarcSubCommand("journal", argvParser) {};
	protected:
		bool doCommand() override;
	};

};