#include "stdafx.h"
namespace IT {
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE) {
			throw ERROR_THROW(204);
		}
		IdTable table{size, 0, new Entry[size] };
		return table;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		int size = idtable.size;

		if (size >= idtable.maxsize) {
			throw ERROR_THROW(200);
		}

		//TODO добавить проверку entry

		try {
			IsId(idtable, entry.id);
			throw ERROR_THROW(201);
		}
		catch (Error::ERROR error) {
			if(error.id == 201) throw ERROR_THROW(201);
		};

		Entry* table = idtable.table;
		*(table + size) = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int index)
	{
		if (index < 0 || index >= idtable.size) {
			throw ERROR_THROW(202);
		}

		return idtable.table[index];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id, id) == 0) {
				return i;
			}
		}
		throw ERROR_THROW(202);
	}

	void Delete(IdTable& idtable) {
		delete[] idtable.table;
		delete &idtable;
	}
}