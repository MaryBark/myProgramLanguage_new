#include "semantic.h"

using namespace std;

void semantic::merge(lexer * _lexer)
{
    vector<tokenDistributor> temp_tokens;

    size_t current_line = 1;
    size_t current_pos = 0;

    string temp_lexeme;
    bool in_string = false;

    for (int i = 0; i < _lexer->tokens().size() - 2; ++i)
    {
        if (_lexer->tokens()[i].type() == tokenModel::INTEGER_CONST)
        {
            if (_lexer->tokens()[i + 1].type() == tokenModel::POINT && _lexer->tokens()[i + 2].type() == tokenModel::INTEGER_CONST)
            {
                string new_lexeme = _lexer->tokens()[i].lexeme() + _lexer->tokens()[i + 1].lexeme() + _lexer->tokens()[i + 2].lexeme();

                current_line = _lexer->tokens()[i].line();
                current_pos = _lexer->tokens()[i].pos();

                tokenDistributor new_token(new_lexeme, current_line, current_pos);

                temp_tokens.push_back(new_token);

                i += 3;
            }
        }

        temp_tokens.push_back(_lexer->tokens()[i]);
    }
    _lexer->tokens() = temp_tokens;
    temp_tokens.clear();

    for (int i = 0; i < _lexer->tokens().size() - 1; ++i)
    {
        if (lexer::is_complex_token(_lexer->tokens()[i].lexeme()[0], _lexer->tokens()[i + 1].lexeme()[0]))
        {
            string new_lexeme = _lexer->tokens()[i].lexeme() + _lexer->tokens()[i + 1].lexeme();

            current_line = _lexer->tokens()[i].line();
            current_pos = _lexer->tokens()[i].pos();

            tokenDistributor new_token(new_lexeme, current_line, current_pos);


            temp_tokens.push_back(new_token);

            i += 2;
        }

        temp_tokens.push_back(_lexer->tokens()[i]);
    }
    _lexer->tokens() = temp_tokens;
    temp_tokens.clear();



    for (int i = 0; i < _lexer->tokens().size(); ++i)
    {
        if (_lexer->tokens()[i].type() == tokenModel::BLOCK_COMMENT_START)
        {
            while (_lexer->tokens()[i].type() != tokenModel::BLOCK_COMMENT_END)
            {
                ++i;
            }
            ++i;
        }

        temp_tokens.push_back(_lexer->tokens()[i]);
    }
    _lexer->tokens() = temp_tokens;
    temp_tokens.clear();


    for (int i = 0; i < _lexer->tokens().size() - 1; ++i)
    {
        if (_lexer->tokens()[i].lexeme() == "#")
        {
            string new_lexeme = _lexer->tokens()[i].lexeme() + _lexer->tokens()[i + 1].lexeme();
            current_line = _lexer->tokens()[i].line();
            current_pos = _lexer->tokens()[i].pos();

            tokenDistributor new_token(new_lexeme, current_line, current_pos);

            temp_tokens.push_back(new_token);

            i += 2;
        }

        temp_tokens.push_back(_lexer->tokens()[i]);
    }
    _lexer->tokens() = temp_tokens;
    temp_tokens.clear();

    size_t temp_CurrentTokenIndex = -1;
    for (auto& token : _lexer->tokens())
    {
        ++temp_CurrentTokenIndex/*_currentTokenIndex*/;
        _lexer->setCurrentTokenIndex(temp_CurrentTokenIndex);

        if (token.type() == tokenModel::IDENTIFIER)
        {
            if (!lexer::is_correct_identifier(token.lexeme()))
            {
                parser::raise(errores_type::LEXER, "Incorrect identifier \"" + token.lexeme() + "\"!", _lexer);
            }
        }
        else if (token.type() == tokenModel::CHAR_CONST)
        {
            if (token.lexeme().size() != 3)
            {
                parser::raise(errores_type::PARSER, "Multi-character character constant " + token.lexeme() + "!", _lexer);
            }
        }

    }
    _lexer->setCurrentTokenIndex(0);
}
