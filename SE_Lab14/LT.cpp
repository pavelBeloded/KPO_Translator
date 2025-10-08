#include "stdafx.h"
#include "LT.h"
#include <string>
#include <iostream>


LT::Keyword keywords[KEYWORDS_COUNT]{
    {"string", LEX_STRING},
    {"integer", LEX_INTEGER},
    {"function", LEX_FUNCTION},
    {"declare", LEX_DECLARE},
    {"return", LEX_RETURN},
    {"print", LEX_PRINT},
    {"main", LEX_MAIN}
};

LT::Separator separators[SEPARATORS_COUNT]{
    {';', LEX_SEMICOLON},
    {',', LEX_COMMA},
    {'{', LEX_LEFTBRACE},
    {'}', LEX_BRACELET},
    {'(', LEX_LEFTHESIS},
    {')', LEX_RIGHTHESIS},
};

LT::Operation operations[OPERATIONS_COUNT]{
    {'+', LEX_PLUS},
    {'-', LEX_MINUS},
    {'/', LEX_DIRSLASH},
    {'*', LEX_STAR},
    {'=', LEX_EQUAL}
};


namespace LT {
    LexTable Create(int size) {
        if (size <= 0 || size > LT_MAXSIZE) {
            throw ERROR_THROW(211);
        }

            LexTable table{ size, 0, new Entry[size] };
            return table;
    }

    void Delete(LexTable& lextable) {
        if (lextable.table != nullptr) {
            delete[] lextable.table;
            lextable.table = nullptr;
        }
        lextable.size = 0;
        lextable.maxsize = 0;
    }

    void FillLT(LexTable& lextable, In::IN& in)
    {
        int inSize = in.size;
        std::string word = "";
        unsigned char* text = in.text;
        int line = 0;
        int idxTI = 0;
        int linePos = 1;
        bool wasQuote = false; 

        for (int i = 0; i < inSize; i++, linePos++)
        {
            bool checked = false;
            unsigned char c = text[i];

            if (c == '\'')
                wasQuote = !wasQuote;

            if ((c == ' ' || c == '|') && !wasQuote)
            {
                if (word.length() == 0)
                {
                    if (c == '|')
                    {
                        line++;
                        linePos = 1;
                    }
                    continue;
                }

                char lexem = checkForKeyword(word);
                if (lexem)
                {
                    Add(lextable, { lexem, line, idxTI });
                    word.clear();
                    if (c == '|') { line++; linePos = 1; }
                    continue;
                }

                if (isLiteral(word))
                {
                    Add(lextable, { LEX_LITERAL, line, idxTI });
                    word.clear();
                    if (c == '|') { line++; linePos = 1; }
                    continue;
                }

                if (isId(word))
                {
                    Add(lextable, { LEX_ID, line, idxTI });
                    word.clear();
                    if (c == '|') { line++; linePos = 1; }
                    continue;
                }

                throw ERROR_THROW_IN(114, line + 1, linePos);
            }

            for (Separator separator : separators)
            {
                if (c == separator.separator && !wasQuote)
                {
                    if (!word.empty())
                    {
                        char lexem = checkForKeyword(word);
                        if (lexem)
                            Add(lextable, { lexem, line, idxTI });
                        else if (isLiteral(word))
                            Add(lextable, { LEX_LITERAL, line, idxTI });
                        else if (isId(word))
                            Add(lextable, { LEX_ID, line, idxTI });
                        else
                            throw ERROR_THROW_IN(114, line + 1, linePos);

                        word.clear();
                    }

                    Add(lextable, { separator.lexem, line, idxTI });
                    checked = true;
                    break;
                }
            }

            if (checked) continue;

            for (Operation operation : operations)
            {
                if (c == operation.operation && !wasQuote)
                {
                    if (!word.empty())
                    {
                        char lexem = checkForKeyword(word);
                        if (lexem)
                            Add(lextable, { lexem, line, idxTI });
                        else if (isLiteral(word))
                            Add(lextable, { LEX_LITERAL, line, idxTI });
                        else if (isId(word))
                            Add(lextable, { LEX_ID, line, idxTI });
                        else
                            throw ERROR_THROW_IN(114, line + 1, linePos);

                        word.clear();
                    }

                    Add(lextable, { operation.lexem, line, idxTI });
                    checked = true;
                    break;
                }
            }

            if (checked) continue;

            // добавляем символ в текущее слово
            word += c;
        }

        // добавление последнего слова (если есть)
        if (!word.empty())
        {
            char lexem = checkForKeyword(word);
            if (lexem)
                Add(lextable, { lexem, line, idxTI });
            else if (isLiteral(word))
                Add(lextable, { LEX_LITERAL, line, idxTI });
            else if (isId(word))
                Add(lextable, { LEX_ID, line, idxTI });
            else
                throw ERROR_THROW_IN(114, line + 1, linePos);
        }
    }

    bool isId(std::string word) {
        if (isdigit(word[0])) return false;
        for (char c : word) {
            if (!islower(c)) return false;
        }
        return true;
    }

    bool isLiteral(std::string word) {
        if (word.size() >= 2 && word.front() == '\'' && word.back() == '\'')
            return true;  

        bool allDigits = !word.empty();
        for (char c : word)
            if (!isdigit(c)) allDigits = false;

        return allDigits;
    }

    char checkForKeyword(std::string word) {
        for (Keyword keyword : keywords) {
            if (keyword.keyword == word) {
                return keyword.lexem;
            }
        }
        return 0; 
    }

    void Add(LexTable& lextable, Entry entry) {
        if (lextable.size >= lextable.maxsize) {
            throw ERROR_THROW(210);
        }

        if (entry.sn < 0 || entry.idxTI < -1) {
            throw ERROR_THROW(213);
        }

       
        lextable.table[lextable.size] = entry;
        lextable.size++;
    }

    Entry GetEntry(LexTable& lextable, int index) {
        if (index < 0 || index >= lextable.size) {
            throw ERROR_THROW(212);
        }

        if (lextable.table == nullptr) {
            throw ERROR_THROW(213);
        }

        return lextable.table[index];
    }

}
