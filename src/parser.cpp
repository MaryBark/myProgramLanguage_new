#include "parser.h"
#include "lexer.h"

//parser::parser()
//{

//}

void parser::raise(errores_type error_type, const std::string &message, lexer *lex)
{
    std::string error_begin;

    switch (error_type)
    {
        case errores_type::LEXER:
        {
            error_begin = "Lexical error! ";
            break;
        }
        case errores_type::PARSER:
        {
            error_begin = "Syntax error! ";
            break;
        }
        case errores_type::SEMANTIC_ANALYS:
        {
            error_begin = "Semantic analys error! ";
            break;
        }
        case errores_type::CODE_GENERATION:
        {
            error_begin = "Code generation error! ";
            break;
        }
    }

    std::string error_message = error_begin + message;

//    disp.out1 << error_message << endl;

    if (lex != nullptr)
    {
        lex->print_current_token_line();
    }

    throw std::logic_error(error_message);
}
