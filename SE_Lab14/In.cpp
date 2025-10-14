#include "In.h"
#include <fstream>
#include "stdafx.h"
#include <string>
using namespace std;

namespace In {
	IN getin(wchar_t infile[]) {
		ifstream file(infile, ios::binary);
		if (!file.is_open()) {
			throw ERROR_THROW(110);
		}
		int pos = 0;
		IN in = { 0,0,0, nullptr, IN_CODE_TABLE };
		in.text = new unsigned char[IN_MAX_LEN_TEXT];
		int linePos = 1;
		while (!file.eof() && pos < IN_MAX_LEN_TEXT - 1) {
			unsigned char c = file.get();
			if (file.eof()) break;
			switch (in.code[c]) {
			case in.S:
			case in.T:
				linePos++;
				in.text[pos++] = c;
				if (c == IN_CODE_ENDL) 
				{
					in.lines++;
					linePos = 1;
				}
				break;
			case in.I:
				in.ignore++;
				if (c == IN_CODE_ENDL) {
					in.lines++;
					linePos = 1;
				}
				break;
			case in.F:
				throw ERROR_THROW_IN(111, in.lines + 1, linePos);
				break;
			default:
				if (c == IN_CODE_ENDL) {
					in.lines++;
					linePos = 1;
				}
				in.text[pos++] = in.code[c];
			}

		}
		in.size = pos;
		in.text[in.size] = '\0';

		file.close();
		return in;
	}
}
