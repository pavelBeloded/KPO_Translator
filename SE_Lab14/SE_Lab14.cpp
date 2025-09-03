#include <iostream>
#include "stdafx.h"

int wmain(int argc, wchar_t* argv[]) {
	setlocale(LC_ALL, "Ru");
	Log::LOG log;
	Out::OUT out;
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		out = Out::getout(parm.out);
		Out::WriteIn(out, in);
	}
	catch (Error::ERROR error) {
		Log::WriteError(log, error);
		if (error.id == 111) {
			Out::WriteError(out, error);
		}
	}
	Log::Close(log);
	system("pause");
	return 0;
}