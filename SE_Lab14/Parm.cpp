#include "Parm.h"
#include "stdafx.h"
#include <cwchar>

namespace Parm {
	PARM getparm(int argc, wchar_t* argv[]) {
		PARM parms{};
		if (argc == 1) throw ERROR_THROW(100);
		for (int i = 1; i < argc; i++) {
			if (wcsstr(argv[i], PARM_IN) == argv[i]) {
				const wchar_t* parmValue = argv[i] + wcslen(PARM_IN);
				if (wcslen(parmValue) > PARM_MAX_SIZE) {
					throw ERROR_THROW(104);
				}
				wcscpy_s(parms.in, parmValue);
				continue;
			}
			if (wcsstr(argv[i], PARM_LOG) == argv[i]) {
				const wchar_t* parmValue = argv[i] + wcslen(PARM_LOG);
				if (wcslen(parmValue) > PARM_MAX_SIZE) {
					throw ERROR_THROW(104);
				}
				wcscpy_s(parms.log, parmValue);
				continue;

			}
			if (wcsstr(argv[i], PARM_OUT) == argv[i]) {
				const wchar_t* parmValue = argv[i] + wcslen(PARM_OUT);
				if (wcslen(parmValue) > PARM_MAX_SIZE) {
					throw ERROR_THROW(104);
				}
				wcscpy_s(parms.out, parmValue);
				continue;
			}
		}

		if (parms.in[0] == '\0') throw ERROR_THROW(100);
		if (parms.out[0] == '\0') {
			wcscpy_s(parms.out, parms.in);
			wcscat_s(parms.out, PARM_OUT_DEFAULT_EXT);
		}
		if (parms.log[0] == '\0') {
			wcscpy_s(parms.log, parms.in);
			wcscat_s(parms.log, PARM_LOG_DEFAULT_EXT);
		}
		return parms;
	}
}