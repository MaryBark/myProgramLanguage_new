#ifndef TOKENDISTRIBUTOR_H
#define TOKENDISTRIBUTOR_H

#include "tockens.h"



class tokenDistributor
{
public:
    explicit tokenDistributor(const std::string& lexema,
                              size_t line = 0,
                              size_t pos = 0);

    static tokenModel retunrTokenType(const std::string& lexema);

    static bool is_string(const std::string& current_lexeme);
    static bool is_char(const std::string& current_lexeme);
    static bool is_integer(const std::string& current_lexeme);
    static bool is_double(const std::string& current_lexeme);

    static std::string token_type_to_string(tokenModel input_type);

    void print();


    tokenModel type() const {return _type;}
    std::string lexeme() const   {return _lexeme;}
    size_t line() const     {return _line;}
    size_t pos() const      {return _pos;}

    void setType(const tokenModel& type) {_type = type;}
    void setLexeme(const std::string& lexeme) {_lexeme = lexeme;}
    void setLine(const size_t& line)     {_line = line;}
    void setPos(const size_t& pos)       {_pos = pos;}

private:
    tokenModel _type;
    std::string _lexeme;

    size_t _line;
    size_t _pos;
};

#endif // TOKENDISTRIBUTOR_H
