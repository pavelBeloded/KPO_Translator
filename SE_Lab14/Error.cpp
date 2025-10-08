//#include "stdafx.h"
#include "Error.h"

namespace Error {
	// 0 - 99 - system errors
	//100- 109 - params errors
	//110 - 119 - open & read errors
	// 200 - 210 - identifier table errors

	ERROR errors[ERROR_MAX_ENTRY] = {
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5), ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "Ошибка при создании выходного файла"), 
		ERROR_ENTRY(114, "Идентификатор не определен"),
		ERROR_ENTRY_NODEF(115), ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, "Переполнение таблицы идентификаторов"),
		ERROR_ENTRY(201, "Идентификатор уже существует в таблице"),
		ERROR_ENTRY(202, "Идентификатор не найден в таблице"),
		ERROR_ENTRY(203, "Неверная запись идентификатора"),
		ERROR_ENTRY(204, "Превышен максимальный размер таблицы иденификаторов"), ERROR_ENTRY_NODEF(205), ERROR_ENTRY_NODEF(206),
		ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),

		   ERROR_ENTRY(210, "Переполнение лексической таблицы"),
		ERROR_ENTRY(211, "Недопустимый размер лексической таблицы"),
		ERROR_ENTRY(212, "Индекс выходит за границы лексической таблицы"),
		ERROR_ENTRY(213, "Неверная запись в лексической таблице"),
		ERROR_ENTRY(214, "Ошибка создания лексической таблицы"),
		ERROR_ENTRY_NODEF(215), ERROR_ENTRY_NODEF(216), ERROR_ENTRY_NODEF(217),
		ERROR_ENTRY_NODEF(218), ERROR_ENTRY_NODEF(219),

		ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230),
		ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260),
		ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY_NODEF100(600),ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),
		ERROR_ENTRY_NODEF100(900)

	};
	ERROR geterror(int id) {
		if (id < 1 || id >= ERROR_MAX_ENTRY) {
			return errors[0];
		}
		return errors[id];
	}

	ERROR geterrorin(int id, int line, int col) {
		if (id < 1 || id >= ERROR_MAX_ENTRY) {
			return errors[0];
		}
		ERROR error = errors[id];
		error.inext.col = col;
		error.inext.line = line;
		return error;
	}
};