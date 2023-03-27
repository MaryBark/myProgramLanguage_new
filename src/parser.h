#ifndef PARSER_H
#define PARSER_H

#pragma once

#include <string>
#include <iostream>
//#include "forDisplay.h"


class lexer;

enum class errores_type
{
    LEXER,
    PARSER,
    SEMANTIC_ANALYS,
    CODE_GENERATION
};

class parser
{
public:
//    parser();
    static void raise(errores_type error_type, const std::string& message, lexer* lex = nullptr);

//    Display disp;
};

#endif // PARSER_H
