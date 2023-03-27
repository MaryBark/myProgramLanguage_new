#include "lexer.h"
using namespace std;

lexer::lexer(const string &file_path)
{
    _filePath = file_path;
    _currentTokenIndex = 0;
    _state = lexer_state::DEFAULT;

    open();
}

void lexer::open()
{
    ifstream in(_filePath, ios::binary);

    if (!in.is_open())
        parser::raise(errores_type::LEXER, "File not found!");

    int size = in.seekg(0, ios::end).tellg();
    in.seekg(0);

    _code.resize(size);
    in.read(&_code[0], size);
}

void lexer::next_token()
{
    if (_currentTokenIndex < _tokens.size() - 2)
    {
        ++_currentTokenIndex;
    }
}

tokenDistributor lexer::current_token()
{
    return _tokens[_currentTokenIndex];
}

tokenModel lexer::current_token_type()
{
    return current_token().type();
}

void lexer::split()
{
    _currentTokenIndex = -1;

    size_t current_line = 1;
    size_t current_pos = 0;

    string current_lexeme;

    for(auto& symbol : _code)
    {
        if (symbol == '\n')
        {
            ++current_line;
            current_pos = 0;
        }

        ++current_pos;

        if(_state == lexer_state::DEFAULT || _state == lexer_state::POSSIBLE_LINE_COMMENT)
        {
            if (symbol == '/')
            {
                if (_state == lexer_state::POSSIBLE_LINE_COMMENT)
                {
                    _state = lexer_state::IN_LINE_COMMENT;
                }
                else
                {
                    _state = lexer_state::POSSIBLE_LINE_COMMENT;
                    current_lexeme += symbol;
                    continue;
                }
            }
            else
            {
                _state = lexer_state::DEFAULT;
            }
        }

        if(_state == lexer_state::IN_LINE_COMMENT)
        {
            if (symbol == '\n')
            {
                current_lexeme.clear();
                _state = lexer_state::DEFAULT;
            }
            continue;
        }


        if(symbol == '"')
        {
            if(_state == lexer_state::DEFAULT)
            {
                _state = lexer_state::IN_STRING;
                current_lexeme += symbol;

                continue;
            }
            else if(_state == lexer_state::IN_STRING)
            {
                _state = lexer_state::DEFAULT;
                current_lexeme += symbol;

                tokenDistributor new_token(current_lexeme, current_line, current_pos);
                _tokens.push_back(new_token);
                current_lexeme.clear();

                ++_currentTokenIndex;

                continue;
            }
        }

        if(_state == lexer_state::IN_STRING)
        {
            current_lexeme += symbol;
            continue;
        }


        if(symbol == '\'')
        {
            if(_state == lexer_state::DEFAULT)
            {
                _state = lexer_state::IN_SYMBOL;
                current_lexeme += symbol;

                continue;
            }
            else if(_state == lexer_state::IN_SYMBOL)
            {
                _state = lexer_state::DEFAULT;
                current_lexeme += symbol;

                tokenDistributor new_token(current_lexeme, current_line, current_pos);
                _tokens.push_back(new_token);
                current_lexeme.clear();

                ++_currentTokenIndex;

                continue;
            }
        }

        if (_state == lexer_state::IN_SYMBOL)
        {
            current_lexeme += symbol;
            continue;
        }


        if (is_separate_symbol(symbol))
        {
            if (!current_lexeme.empty())
            {
                tokenDistributor new_token(current_lexeme, current_line, current_pos);
                _tokens.push_back(new_token);
                current_lexeme.clear();

                ++_currentTokenIndex;
            }

            if (symbol != ' ' && symbol != '\r' && symbol != '\n')
            {
                string current_symbol(1, symbol);
                tokenDistributor new_token(current_symbol, current_line, current_pos);
                _tokens.push_back(new_token);

                ++_currentTokenIndex;
            }
        }
        else
        {
            current_lexeme += symbol;
        }
    }

    if (!current_lexeme.empty())
    {
        tokenDistributor new_token(current_lexeme, current_line, current_pos);
        _tokens.push_back(new_token);
        current_lexeme.clear();

        ++_currentTokenIndex;
    }
}

//void lexer::merge()
//{
//    vector<tokenDistributor> temp_tokens;

//    size_t current_line = 1;
//    size_t current_pos = 0;

//    string temp_lexeme;
//    bool in_string = false;

//    for (int i = 0; i < _tokens.size() - 2; ++i)
//    {
//        if (_tokens[i].type() == tockens::INTEGER_CONST)
//        {
//            if (_tokens[i + 1].type() == tockens::POINT && _tokens[i + 2].type() == tockens::INTEGER_CONST)
//            {
//                string new_lexeme = _tokens[i].lexeme() + _tokens[i + 1].lexeme() + _tokens[i + 2].lexeme();

//                current_line = _tokens[i].line();
//                current_pos = _tokens[i].pos();

//                tokenDistributor new_token(new_lexeme, current_line, current_pos);

//                temp_tokens.push_back(new_token);

//                i += 3;
//            }
//        }

//        temp_tokens.push_back(_tokens[i]);
//    }
//    _tokens = temp_tokens;
//    temp_tokens.clear();


//    for (int i = 0; i < _tokens.size() - 1; ++i)
//    {
//        if (is_complex_token(_tokens[i].lexeme()[0], _tokens[i + 1].lexeme()[0]))
//        {
//            string new_lexeme = _tokens[i].lexeme() + _tokens[i + 1].lexeme();

//            current_line = _tokens[i].line();
//            current_pos = _tokens[i].pos();

//            tokenDistributor new_token(new_lexeme, current_line, current_pos);


//            temp_tokens.push_back(new_token);

//            i += 2;
//        }

//        temp_tokens.push_back(_tokens[i]);
//    }
//    _tokens = temp_tokens;
//    temp_tokens.clear();



//    for (int i = 0; i < _tokens.size(); ++i)
//    {
//        if (_tokens[i].type() == tockens::BLOCK_COMMENT_START)
//        {
//            while (_tokens[i].type() != tockens::BLOCK_COMMENT_END)
//            {
//                ++i;
//            }
//            ++i;
//        }

//        temp_tokens.push_back(_tokens[i]);
//    }
//    _tokens = temp_tokens;
//    temp_tokens.clear();



//    for (int i = 0; i < _tokens.size() - 1; ++i)
//    {
//        if (_tokens[i].lexeme() == "#")
//        {
//            string new_lexeme = _tokens[i].lexeme() + _tokens[i + 1].lexeme();
//            current_line = _tokens[i].line();
//            current_pos = _tokens[i].pos();

//            tokenDistributor new_token(new_lexeme, current_line, current_pos);

//            temp_tokens.push_back(new_token);

//            i += 2;
//        }

//        temp_tokens.push_back(_tokens[i]);
//    }
//    _tokens = temp_tokens;
//    temp_tokens.clear();

//    _currentTokenIndex = -1;
//    for (auto& token : _tokens)
//    {
//        ++_currentTokenIndex;

//        if (token.type() == tockens::IDENTIFIER)
//        {
//            if (!is_correct_identifier(token.lexeme()))
//            {
//                parser::raise(errores_type::LEXER, "Incorrect identifier \"" + token.lexeme() + "\"!", this);
//            }
//        }
//        else if (token.type() == tockens::CHAR_CONST)
//        {
//            if (token.lexeme().size() != 3)
//            {
//                parser::raise(errores_type::PARSER, "Multi-character character constant " + token.lexeme() + "!", this);
//            }
//        }

//    }
//    _currentTokenIndex = 0;
//}

bool lexer::is_complex_token(char symbol1, char symbol2)
{
    switch (symbol1)
    {
    case '<':
    {
        return symbol2 == '=';
    }
    case '>':
    {
        return symbol2 == '=';
    }
    case '+':
    {
        return symbol2 == '=' || symbol2 == '+';
    }
    case '-':
    {
        return symbol2 == '=' || symbol2 == '-';
    }
    case '=':
    {
        return symbol2 == '=';
    }
    case '!':
    {
        return symbol2 == '=';
    }
    case '&':
    {
        return symbol2 == '&';
    }
    case '|':
    {
        return symbol2 == '|';
    }
    case ':':
    {
        return symbol2 == ':';
    }
    case '/':
    {
        return symbol2 == '*';
    }
    case '*':
    {
        return symbol2 == '/';
    }

    default:
        return false;
    }

}

void lexer::print()
{
    for (auto& token : _tokens)
    {
        token.print();
    }
}

bool lexer::is_separate_symbol(char symbol)
{
    return  symbol == ':' || symbol == ';' ||
            symbol == ',' || symbol == '.' ||
            symbol == '{' || symbol == '}' ||
            symbol == '(' || symbol == ')' ||
            symbol == '[' || symbol == ']' ||
            symbol == '*' || symbol == '/' ||
            symbol == '+' || symbol == '-' ||
            symbol == '&' || symbol == '|' ||
            symbol == '=' || symbol == '!' ||
            symbol == '<' || symbol == '>' ||
            symbol == '\''|| symbol == '"' ||
            symbol == '^' || symbol == '?' ||
            symbol == '%' || symbol == '\\'||
            symbol == '~' || symbol == ' ' ||
            symbol == '\r' ||symbol == '\n'||
            symbol == '#';
}

bool lexer::is_correct_identifier(const string &token)
{
    if (!isalpha(token[0]) && token[0] != '_')
        return false;

    for (const auto& symbol : token)
        if (!isalpha(symbol) && !isdigit(symbol) && symbol != '_')
            return false;

    return true;
}

void lexer::print_current_token_line()
{
    int i = _currentTokenIndex;
    int j = _currentTokenIndex;
    auto current_line = current_token().line();

    while (i > 0 && _tokens[i].line() == current_line)
    {
        --i;
    }
    ++i;

    int count_symbol_before = _currentTokenIndex - i;

    while (j < _tokens.size() && _tokens[j].line() == current_line)
    {
        ++j;
    }

    out1 << "line " << current_line << ": ";

    size_t count_symbol_before_current = 0;
    string underline;
    size_t size_current_token = 0;
    for (int k = i; k < j; ++k)
    {
        if (k - i == count_symbol_before)
        {
            out1 << "" << _tokens[k].lexeme() << "" << " ";
            size_current_token = _tokens[k].lexeme().size();
            continue;
        }

        out1 << _tokens[k].lexeme() << " ";

        if (k - i <= count_symbol_before)
        {
            count_symbol_before_current += _tokens[k].lexeme().size() + 1;
        }
    }

    count_symbol_before_current += 7 + to_string(current_line).size();

    for (int l = 0; l < count_symbol_before_current; ++l)
    {
        underline += ' ';
    }

    for (int l = 0; l < size_current_token; ++l)
    {
        underline += '~';
    }

//    cout << endl;
    out1 << underline;
//    cout << endl;
}
