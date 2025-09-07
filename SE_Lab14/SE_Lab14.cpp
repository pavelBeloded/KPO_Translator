#include <iostream>
#include <cwchar>
#include "stdafx.h"

int wmain(int argc, wchar_t* argv[]) {
	setlocale(LC_ALL, "Ru");
	Log::LOG log ;
	Out::OUT out;
	Parm::PARM parm{};
	try {
		parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		out = Out::getout(parm.out);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		Out::WriteIn(out, in);
	}
	catch (Error::ERROR error) {
		if (log.stream == nullptr) {
			if (parm.in[0] == '\0') {
				wcscpy_s(parm.log, L"logs.txt");
			}
			log = Log::getlog(parm.log);
			Log::WriteLog(log);
		}
		Log::WriteError(log, error);
		if (error.id == 111) {
			Out::WriteError(out, error);
		}
	}
	Log::Close(log);
	system("pause");
	return 0;
}