#include "tokenDistributor.h"
#include "QString"

using namespace std;

// как это сделать без дефайнов????
#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
#define QS(x)    (QString::fromLocal8Bit(x))
#else
#define QS(x)    (QString::fromUtf8(x))
#endif

tokenDistributor::tokenDistributor(const std::string& lexema, size_t line, size_t pos)
{
    _lexeme = lexema;
    _type = retunrTokenType(lexema);

    _line = line;
    _pos = pos;
}

tokenModel tokenDistributor::retunrTokenType(const std::string &lexema)
{
    if (lexema == QS("постоянно").toStdString())
        return tokenModel::CONST;

    // типы данных
    if (lexema == QS("целый").toStdString())
        return tokenModel::INT;
    if (lexema == QS("двойной").toStdString())
        return tokenModel::DOUBLE;
    if (lexema == QS("буль").toStdString())
        return tokenModel::BOOL;
    if (lexema == QS("пустота").toStdString())
        return tokenModel::VOID;
    if (lexema == QS("символ").toStdString())
        return tokenModel::CHAR;
    if (lexema == QS("строка").toStdString())
        return tokenModel::STRING;
    if (lexema == QS("автоматический").toStdString())
        return tokenModel::AUTO;

    // циклы
    if (lexema == QS("цикл").toStdString())
        return tokenModel::FOR;
    if (lexema == QS("пока").toStdString())
        return tokenModel::WHILE;
    if (lexema == QS("делай").toStdString())
        return tokenModel::DO_WHILE;

    // операции с циклами
    if (lexema == QS("прервать").toStdString())
        return tokenModel::BREAK;
    if (lexema == QS("продолжить").toStdString())
        return tokenModel::CONTINUE;

    // операторы условия
    if (lexema == QS("если").toStdString())
        return tokenModel::IF;
    if (lexema == QS("тогда").toStdString())
        return tokenModel::ELSE;

    // операторы отношений
    if (lexema == ">")
        return tokenModel::GREATER;
    if (lexema == "<")
        return tokenModel::LESS;
    if (lexema == "<=")
        return tokenModel::LESS_EQUAL;
    if (lexema == ">=")
        return tokenModel::GREATER_EQUAL;

    if (lexema == "==")
        return tokenModel::EQUAL;
    if (lexema == "!=")
        return tokenModel::NOT_EQUAL;

    // логические операторы
    if (lexema == "&&")
        return tokenModel::AND;
    if (lexema == "||")
        return tokenModel::OR;
    if (lexema == "!")
        return tokenModel::EXCLAMATION;

    // математические операторы
    if (lexema == "+")
        return tokenModel::PLUS;
    if (lexema == "-")
        return tokenModel::MINUS;
    if (lexema == "*")
        return tokenModel::STAR;
    if (lexema == "/")
        return tokenModel::SLASH;
    if (lexema == "++")
        return tokenModel::INC;
    if (lexema == "--")
        return tokenModel::DEC;
    if (lexema == "^")
        return tokenModel::DEG;


    // скобки
    if (lexema == "{")
        return tokenModel::LBRA;
    if (lexema == "}")
        return tokenModel::RBRA;
    if (lexema == "(")
        return tokenModel::LPAR;
    if (lexema == ")")
        return tokenModel::RPAR;
    if (lexema == "[")
        return tokenModel::LSQR;
    if (lexema == "]")
        return tokenModel::RSQR;

    // assign
    if (lexema == "=")
        return tokenModel::ASSIGN;
    if (lexema == "+=")
        return tokenModel::ADD_ASSIGN;
    if (lexema == "-=")
        return tokenModel::SUB_ASSIGN;
    if (lexema == "*=")
        return tokenModel::MUL_ASSIGN;
    if (lexema == "/=")
        return tokenModel::DIV_ASSIGN;


    // функция
    if (lexema == QS("верни").toStdString())
        return tokenModel::RETURN;

    if (lexema == QS("процедура").toStdString())
        return tokenModel::PROCEDURE;


    // выделение памяти
    if (lexema == QS("память").toStdString())
        return tokenModel::NEW;
    if (lexema == QS("удалить").toStdString())
        return tokenModel::DELETE;


    // логические операторы
    if (lexema == QS("истина").toStdString())
        return tokenModel::TRUE;
    if (lexema == QS("ложь").toStdString())
        return tokenModel::FALSE;


    if (lexema == QS("переключатель").toStdString())
        return tokenModel::SWITCH;
    if (lexema == QS("выбор").toStdString())
        return tokenModel::CASE;
    if (lexema == QS("по умолчанию").toStdString())
        return tokenModel::DEFAULT;

    // другие символы
    if (lexema == ";")
        return tokenModel::SEMICOLON;
    if (lexema == ":")
        return tokenModel::COLON;
    if (lexema == ",")
        return tokenModel::COMMA;
    if (lexema == ".")
        return tokenModel::POINT;
    if (lexema == "?")
        return tokenModel::QUESTION;
    if (lexema == "::")
        return tokenModel::ACCESS_OPERATOR;
    if (lexema == "&")
        return tokenModel::AMPERSAND;

    // комментарии
    if (lexema == "//")
        return tokenModel::LINE_COMMENT;
    if (lexema == "/*")
        return tokenModel::BLOCK_COMMENT_START;
    if (lexema == "*/")
        return tokenModel::BLOCK_COMMENT_END;

    if (lexema[0] == '#')
        return tokenModel::PREPROCESSOR_DIRECTIVE;

    if (is_integer(lexema))
        return tokenModel::INTEGER_CONST;

    if (is_double(lexema))
        return tokenModel::DOUBLE_CONST;

    if (is_string(lexema))
        return tokenModel::STRING_CONST;

    if (is_char(lexema))
        return tokenModel::CHAR_CONST;

    return tokenModel::IDENTIFIER;
}

bool tokenDistributor::is_string(const string &current_lexeme)
{
    return current_lexeme.front() == '"' && current_lexeme.back() == '"';
}

bool tokenDistributor::is_char(const string &current_lexeme)
{
    return current_lexeme.front() == '\'' && current_lexeme.back() == '\'';
}

bool tokenDistributor::is_integer(const string &current_lexeme)
{
    for (const auto& symbol : current_lexeme)
        if (symbol < '0' || symbol > '9')
            return false;
    return true;
}

bool tokenDistributor::is_double(const string &current_lexeme)
{
    bool point = false;

    for (const char& s : current_lexeme)
    {
        if (s == '.' && !point)
        {
            point = true;
            continue;
        }

        if (s == '.')
            return false;

        if (s < '0' || s > '9')
            return false;

    }

    return true;
}

string tokenDistributor::token_type_to_string(tokenModel input_type)
{
    switch (input_type)
    {
    case tokenModel::IDENTIFIER:
    {
        return QS("неизвестный").toStdString();
    }
    case tokenModel::INTEGER_CONST:
    {
        return QS("целый постоянно").toStdString();
    }
    case tokenModel::DOUBLE_CONST:
    {
        return QS("двойной постоянно").toStdString();
    }
    case tokenModel::STRING_CONST:
    {
        return QS("строка постоянно").toStdString();
    }
    case tokenModel::CHAR_CONST:
    {
        return QS("символ постоянно").toStdString();
    }
    case tokenModel::TRUE:
    {
        return QS("истина").toStdString();
    }
    case tokenModel::FALSE:
    {
        return QS("ложь").toStdString();
    }
    case tokenModel::CONST:
    {
        return QS("постоянно").toStdString();
    }
    case tokenModel::UNDEFINED:
    {
        return QS("неопределенный").toStdString();
    }
    case tokenModel::INT:
    {
        return QS("целый").toStdString();
    }
    case tokenModel::DOUBLE:
    {
        return QS("двойной").toStdString();
    }
    case tokenModel::BOOL:
    {
        return QS("буль").toStdString();
    }
    case tokenModel::CHAR:
    {
        return QS("симфол").toStdString();
    }
    case tokenModel::STRING:
    {
        return QS("строка").toStdString();
    }
    case tokenModel::VOID:
    {
        return QS("пустота").toStdString();
    }
    case tokenModel::AUTO:
    {
        return QS("автоматический").toStdString();
    }
    case tokenModel::DO_WHILE:
    {
        return QS("делать пока").toStdString();
    }
    case tokenModel::WHILE:
    {
        return QS("пока").toStdString();
    }
    case tokenModel::FOR:
    {
        return QS("цикл").toStdString();
    }
    case tokenModel::BREAK:
    {
        return QS("прервать").toStdString();
    }
    case tokenModel::CONTINUE:
    {
        return QS("продолжить").toStdString();
    }
    case tokenModel::SWITCH:
    {
        return QS("переключатель").toStdString();
    }
    case tokenModel::CASE:
    {
        return QS("выбор").toStdString();
    }
    case tokenModel::DEFAULT:
    {
        return QS("по умолчанию").toStdString();
    }
    case tokenModel::IF:
    {
        return QS("если").toStdString();
    }
    case tokenModel::ELSE:
    {
        return QS("тогда").toStdString();
    }
    case tokenModel::LESS:
    {
        return "less";
    }
    case tokenModel::GREATER:
    {
        return "greater";
    }
    case tokenModel::LESS_EQUAL:
    {
        return "less and equal";
    }
    case tokenModel::GREATER_EQUAL:
    {
        return "greater and equal";
    }
    case tokenModel::EQUAL:
    {
        return "equal";
    }
    case tokenModel::NOT_EQUAL:
    {
        return "not equal";
    }
    case tokenModel::AND:
    {
        return "logic and";
    }
    case tokenModel::OR:
    {
        return "logic or";
    }
    case tokenModel::EXCLAMATION:
    {
        return "exclamation";
    }
    case tokenModel::PLUS:
    {
        return "plus";
    }
    case tokenModel::MINUS:
    {
        return "minus";
    }
    case tokenModel::STAR:
    {
        return "star";
    }
    case tokenModel::SLASH:
    {
        return "true";
    }
    case tokenModel::INC:
    {
        return "inc";
    }
    case tokenModel::DEC:
    {
        return "dec";
    }
    case tokenModel::LBRA:
    {
        return "lbra";
    }
    case tokenModel::RBRA:
    {
        return "rbra";
    }
    case tokenModel::LPAR:
    {
        return "lpar";
    }
    case tokenModel::RPAR:
    {
        return "rpar";
    }
    case tokenModel::LSQR:
    {
        return "lsqr";
    }
    case tokenModel::RSQR:
    {
        return "rsqr";
    }
    case tokenModel::ASSIGN:
    {
        return "assign";
    }
    case tokenModel::ADD_ASSIGN:
    {
        return "add assign";
    }
    case tokenModel::SUB_ASSIGN:
    {
        return "sun assign";
    }
    case tokenModel::MUL_ASSIGN:
    {
        return "mul assign";
    }
    case tokenModel::DIV_ASSIGN:
    {
        return "true";
    }
    case tokenModel::FUNCTION:
    {
        return "function";
    }
    case tokenModel::PROCEDURE:
    {
        return QS("процедура").toStdString();
    }
    case tokenModel::RETURN:
    {
        return QS("верни").toStdString();
    }
    case tokenModel::SEMICOLON:
    {
        return "semicolon";
    }
    case tokenModel::COLON:
    {
        return "colon";
    }
    case tokenModel::COMMA:
    {
        return "comma";
    }
    case tokenModel::POINT:
    {
        return "point";
    }
    case tokenModel::QUESTION:
    {
        return "question";
    }
    case tokenModel::AMPERSAND:
    {
        return "ampersand";
    }
    case tokenModel::LINE_COMMENT:
    {
        return "line comment";
    }
    case tokenModel::BLOCK_COMMENT_START:
    {
        return "block comment start";
    }
    case tokenModel::BLOCK_COMMENT_END:
    {
        return "block comment end";
    }
    case tokenModel::NEW:
    {
        return QS("память").toStdString();
    }
    case tokenModel::DELETE:
    {
        return QS("удалить").toStdString();
    }
    case tokenModel::PREPROCESSOR_DIRECTIVE:
    {
        return "preprocessor directive";
    }
    case tokenModel::ACCESS_OPERATOR:
    {
        return "access operator";
    }

    default:
        return "";
    }
}

void tokenDistributor::print()
{
    cout << _lexeme << " with type: \"" << token_type_to_string(_type) << "\" " <<
            "\tline:" << _line <<
            "\tposition:" << _pos <<
            "\n";
}
