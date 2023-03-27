#ifndef LEXER_H
#define LEXER_H

#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <QList>
#include <sstream>
#include <memory>

#include "tokenDistributor.h"
#include "parser.h"
//#include "forDisplay.h"


enum class lexer_state
{
    DEFAULT,
    IN_STRING,
    IN_SYMBOL,
    POSSIBLE_LINE_COMMENT,
    IN_LINE_COMMENT
};


class lexer
{
public:
    explicit lexer(const std::string& file_path);

    void open();

    void next_token();

    tokenDistributor current_token();

    tokenModel current_token_type();

    void split();

//    void merge();

    static bool is_complex_token(char symbol1, char symbol2);

    void print();

    static bool is_separate_symbol(char symbol);

    static bool is_correct_identifier(const std::string& token);

    void print_current_token_line();


    std::string filePath() const                 { return _filePath; }
    std::string code() const                     { return _code;  }
    std::vector<tokenDistributor> tokens() const { return _tokens; }
    /*std::shared_ptr<*/lexer_state/*>*/ state() const               { return _state; }
    size_t currentTokenIndex() const        { return _currentTokenIndex; }


    void setFilePath(const std::string & filePath)                 { _filePath          = filePath;          }
    void setCode(const std::string & code)                         { _code              = code;              }
    void setTokens(const std::vector<tokenDistributor>& tokens)    { _tokens            = tokens;            }
    void setState(const /*std::shared_ptr<*/lexer_state/*>*/& state)                   { _state             = state;             }
    void setCurrentTokenIndex(const size_t&currentTokenIndex) { _currentTokenIndex = currentTokenIndex; }


private:
    std::string _filePath;
    std::string _code;
    std::vector<tokenDistributor> _tokens;

    /*std::shared_ptr<*/lexer_state/*>*/ _state;

    size_t _currentTokenIndex;


    std::stringstream out1;
};

#endif // LEXER_H
