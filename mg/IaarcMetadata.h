#pragma once

#include "MGArgvParser.h"

using namespace CommandLineProcessing;

namespace simplearchive {

	class IaarcMetadata : public IaarcSubCommand {
	public:
		IaarcMetadata(MGArgvParser& argvParser) : IaarcSubCommand("metadata", argvParser) {};
	protected:
		bool doCommand() override;
	};

};

