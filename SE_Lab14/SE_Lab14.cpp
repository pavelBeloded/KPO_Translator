#include <iostream>
#include "stdafx.h"

int wmain(int argc, wchar_t* argv[]) {
	setlocale(LC_ALL, "Ru");
	Log::LOG log;
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);

	}
	catch (Error::ERROR error) {
		Log::WriteError(log, error);
	}
	Log::Close(log);
	system("pause");
	return 0;
}