#include "stdafx.h"
#include <fstream>
#include <cwctype>
#include <iostream>

namespace Out {
	OUT getout(wchar_t outfile[]) {
		OUT out = INITOUT;
		out.stream = new std::ofstream(outfile);
		if (!out.stream->is_open()) {
			throw ERROR_THROW(113);
		}
		wcscpy_s(out.outfile, outfile);
		return out;
	}

	void WriteIn(OUT out, In::IN in) {
		*out.stream << in.text;
		return;
	}

	void WriteError(OUT log, Error::ERROR error) {
		using namespace std;
		if (!log.stream->is_open()) {
			std::cout << "Ошибка " << error.id << ": " << error.message << std::endl << std::endl;
			if (error.inext.line != -1) {
				std::cout << "строка " << error.inext.line << " позиция " << error.inext.col << std::endl << std::endl;
			}
		}
		else {
			*log.stream << "Ошибка " << error.id << ": " << error.message << std::endl << std::endl;
			if (error.inext.line != -1) {
				*log.stream << "строка " << error.inext.line << " позиция " << error.inext.col << std::endl << std::endl;
			}
		}
	}

	void Close(OUT out) {
		out.stream->close();
	}
}
