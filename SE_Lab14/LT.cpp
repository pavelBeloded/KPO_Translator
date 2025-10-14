#include "stdafx.h"
#include "LT.h"
#include "IT.h"
#include "Error.h"
#include <string>
#include <vector>
#include <cctype>
#include <new>

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
    {';', LEX_SEMICOLON}, {',', LEX_COMMA},
    {'{', LEX_LEFTBRACE}, {'}', LEX_BRACELET},
    {'(', LEX_LEFTHESIS}, {')', LEX_RIGHTHESIS}
};

LT::Operation operations[OPERATIONS_COUNT]{
    {'+', LEX_PLUS}, {'-', LEX_MINUS},
    {'/', LEX_DIRSLASH}, {'*', LEX_STAR},
    {'=', LEX_EQUAL}
};

namespace LT {

    bool isId(const std::string& word) {
        if (word.empty() || !isalpha(word[0])) {
            return false;
        }
        for (char c : word) {
            if (!isalnum(c)) {
                return false;
            }
        }
        return true;
    }

    bool isNumericLiteral(const std::string& word) {
        if (word.empty()) return false;
        for (char c : word) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

    bool isStringLiteral(const std::string& word) {
        return word.length() >= 2 && word.front() == '\'' && word.back() == '\'';
    }

    char getKeywordLexem(const std::string& word) {
        for (const auto& kw : keywords) {
            if (kw.keyword == word) {
                return kw.lexem;
            }
        }
        return 0;
    }

    enum class Context {
        GLOBAL,
        DECLARE_SECTION,
        FUNCTION_DECLARATION,
        PARAMETER_LIST
    };

    void FillLTIT(LexTable& lextable, IT::IdTable& idtable, In::IN& in) {
        std::vector<Context> contextStack;
        contextStack.push_back(Context::GLOBAL);

        IT::IDDATATYPE lastDataType = IT::UNKNOWN;
        bool nextIsFunctionName = false;
        bool isInsideString = false;

        std::string word = "";
        int line = 1;
        int pos = 1;

        auto processWord = [&]() {
            if (word.empty()) {
                return;
            }

            char lexem = getKeywordLexem(word);
            if (lexem) {
                Add(lextable, { lexem, line, LT_TI_NULLIDX });
                if (lexem == LEX_DECLARE) contextStack.push_back(Context::DECLARE_SECTION);
                else if (lexem == LEX_FUNCTION) {
                    contextStack.push_back(Context::FUNCTION_DECLARATION);
                    nextIsFunctionName = true;
                }
                else if (lexem == LEX_STRING) lastDataType = IT::STR;
                else if (lexem == LEX_INTEGER) lastDataType = IT::INT;
            }
            else if (isNumericLiteral(word)) {
                int value = std::stoi(word);
                int idx = IT::AddIntLiteral(idtable, value, line);
                Add(lextable, { LEX_LITERAL, line, idx });
            }
            else if (isStringLiteral(word)) {
                std::string literalContent = word.substr(1, word.length() - 2);
                int idx = IT::AddStringLiteral(idtable, literalContent, line);
                Add(lextable, { LEX_LITERAL, line, idx });
            }
            else if (isId(word)) {
                IT::IDTYPE idType = IT::V;
                Context currentContext = contextStack.back();

                if (nextIsFunctionName) {
                    idType = IT::F;
                    nextIsFunctionName = false;
                }
                else if (currentContext == Context::PARAMETER_LIST) {
                    idType = IT::P;
                }
                else if (currentContext == Context::DECLARE_SECTION) {
                    idType = IT::V;
                }

                int idx = IT::AddId(idtable, word, lastDataType, idType, line);
                Add(lextable, { LEX_ID, line, idx });
            }
            else {
                throw ERROR_THROW_IN(114, line, pos);
            }
            word.clear();
            };


        for (int i = 0; i < in.size; ++i) {
            const unsigned char c = in.text[i];

            if (isInsideString) {
                word += c;
                if (c == '\'') {
                    isInsideString = false;
                    processWord();
                }
                pos++;
                continue;
            }

            if (c == '\'') {
                processWord();
                isInsideString = true;
                word += c;
                pos++;
                continue;
            }

            if (isspace(c)) {
                processWord();
                if (c == '\n') {
                    line++;
                    pos = 1;
                }
                else {
                    pos++;
                }
                continue;
            }

            bool is_separator = false;
            for (const auto& sep : separators) {
                if (c == sep.separator) {
                    processWord();
                    Add(lextable, { sep.lexem, line, LT_TI_NULLIDX });
                    if (c == '(' && contextStack.back() == Context::FUNCTION_DECLARATION) {
                        contextStack.back() = Context::PARAMETER_LIST;
                    }
                    else if (c == ')' && !contextStack.empty() && contextStack.back() == Context::PARAMETER_LIST) {
                        contextStack.pop_back();
                    }
                    else if (c == ';' && !contextStack.empty() && contextStack.back() == Context::DECLARE_SECTION) {
                        contextStack.pop_back();
                    }
                    else if (c == '{' && !contextStack.empty() && contextStack.back() == Context::FUNCTION_DECLARATION) {
                        contextStack.pop_back();
                    }
                    pos++;
                    is_separator = true;
                    break;
                }
            }
            if (is_separator) continue;

            bool is_operation = false;
            for (const auto& op : operations) {
                if (c == op.operation) {
                    processWord();
                    Add(lextable, { op.lexem, line, LT_TI_NULLIDX });
                    pos++;
                    is_operation = true;
                    break;
                }
            }
            if (is_operation) continue;

            word += c;
            pos++;
        }
        processWord();
    }

    LexTable Create(int size) {
        if (size <= 0 || size > LT_MAXSIZE) {
            throw ERROR_THROW(211);
        }
        try {
            return LexTable{ size, 0, new Entry[size] };
        }
        catch (const std::bad_alloc&) {
            throw ERROR_THROW(214);
        }
    }

    void Add(LexTable& lextable, Entry entry) {
        if (lextable.size >= lextable.maxsize) {
            throw ERROR_THROW(210);
        }
        lextable.table[lextable.size++] = entry;
    }

    Entry GetEntry(LexTable& lextable, int index) {
        if (index < 0 || index >= lextable.size) {
            throw ERROR_THROW(212);
        }
        return lextable.table[index];
    }

    void Delete(LexTable& lextable) {
        if (lextable.table != nullptr) {
            delete[] lextable.table;
            lextable.table = nullptr;
        }
    }
}