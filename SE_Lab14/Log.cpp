#include "stdafx.h"
#include <fstream>
#include <cwctype>
#include <cstdarg>
#include <ctime>
#include <iostream>

namespace Log {
	LOG getlog(wchar_t logfile[]) {
		LOG log = INITLOG;
		log.stream = new std::ofstream(logfile, std::ios::out | std::ios::app);
		if (!log.stream->is_open()) {
			throw ERROR_THROW(112);
		}
		wcscpy_s(log.logfile, logfile);
		return log;
	}

	void WriteLine(LOG log, char* c, ...) {
		va_list args;
		va_start(args, c);
		char* str = nullptr;
		while ((str = va_arg(args, char*)) != "") {
			if (str[0] == '\0') break;
			*log.stream << str;
		}
		va_end(args);
	}

	void WriteLine(LOG log, wchar_t* c, ...) {
		if (!log.stream || !log.stream->is_open()) return;

		va_list args;
		va_start(args, c);

		wchar_t* wstr = c;

		while (wstr != nullptr && wstr[0] != L'\0') {
			size_t requiredSize = wcslen(wstr) * 4 + 1;
			char* buffer = new char[requiredSize];
			size_t convertedLength = 0;

			errno_t err = wcstombs_s(&convertedLength, buffer, requiredSize, wstr, _TRUNCATE);

			if (err == 0) {
				(*log.stream) << buffer;
			}

			delete[] buffer;
			wstr = va_arg(args, wchar_t*);
		}

		va_end(args);
		(*log.stream) << std::endl;
	}

	void WriteLog(LOG log) {
		time_t now = time(nullptr);
		struct tm localTime;
		localtime_s(&localTime, &now);
		char timeBuffer[100];
		strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &localTime);
		*log.stream << "-----  Протокол ----- " << timeBuffer << "------\n";
		return;
	}

	void WriteParm(LOG log, Parm::PARM parm) {
		if (!log.stream || !log.stream->is_open()) return;

		*log.stream << "----- Параметры -----" << std::endl;

		char buffer[PARM_MAX_SIZE * 4];

		auto convert = [&](const wchar_t* src) -> const char* {
			std::memset(buffer, 0, sizeof(buffer));
			size_t converted = 0;

			errno_t err = wcstombs_s(&converted, buffer, sizeof(buffer), src, _TRUNCATE);
			return (err == 0) ? buffer : "[ошибка преобразования]";
			};

		*log.stream << "-log: " << convert(parm.log) << std::endl;
		*log.stream << "-in : " << convert(parm.in) << std::endl;
		*log.stream << "-out: " << convert(parm.out) << std::endl;
	}

	void WriteIn(LOG log, In::IN in) {
		*log.stream << "---- Статистика -----" << std::endl;
		*log.stream << "Количество символов: " << in.size << std::endl;
		*log.stream << "Проигнорировано: " << in.ignore << std::endl;
		*log.stream << "Количество строк: " << in.lines << std::endl;
		return;
	}

	void WriteError(LOG log, Error::ERROR error) {
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

	void Close(LOG log) {
		log.stream->close();
	}


}