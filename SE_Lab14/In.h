#pragma once
#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDL '\n'

#define IN_CODE_TABLE {\
In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
In::IN::T, In::IN::F, In::IN::T, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::T, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
\
In::IN::F, In::IN::T, In::IN::T, In::IN::F, In::IN::T, In::IN::T, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::T, In::IN::F, In::IN::F, In::IN::T,  \
In::IN::T, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::T, In::IN::F, In::IN::I, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
In::IN::F, In::IN::T, In::IN::T, In::IN::F, In::IN::T, In::IN::T, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::T, In::IN::F, In::IN::F, In::IN::T,  \
In::IN::T, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::T, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
\
In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
\
'-', In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F, In::IN::F,  \
}


namespace In {
	struct IN {
		enum Chars {
			T = 1024,
			F = 2048,
			I = 4096
		};
		int size;
		int lines;
		int ignore;
		unsigned char* text;
		int code[256];
	};
	IN getin(wchar_t infile[]);

}