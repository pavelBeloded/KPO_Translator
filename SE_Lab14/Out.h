#pragma once
#include <fstream>
#include "stdafx.h"

namespace Out {
	struct OUT {
		wchar_t outfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};
	static const OUT INITOUT{ L"", NULL };
	OUT getout(wchar_t logfile[]);
	void WriteIn(OUT out, In::IN in);
	void WriteError(OUT log, Error::ERROR error);
	void Close(OUT out);
}
