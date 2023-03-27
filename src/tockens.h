#ifndef TOCKENS_H
#define TOCKENS_H

#pragma once
#include <iostream>
#include <string>
#include <QFontDatabase>
#include <QFont>


// подключение собственного шрифта))))
//int idFont = QFontDatabase::addApplicationFont("my_font.ttf"); //путь к шрифту
//QString myFont = QFontDatabase::applicationFontFamilies(idFont).at(0); //имя шрифта
//QFont fontMy(myFont, 80, 50, true);


enum class tokenModel
{
//    fontMy.setsetWeight(10);
    IDENTIFIER,

    INTEGER_CONST,
    DOUBLE_CONST,
    STRING_CONST,
    CHAR_CONST,

    // лигические операторы
    TRUE,
    FALSE,


    CONST,


    // типы данных
    UNDEFINED,

    INT,
    DOUBLE,
    BOOL,
    CHAR,
    STRING,
    VOID,
    AUTO,

    // циклы
    DO_WHILE,
    WHILE,
    FOR,
    // операции с циклами
    BREAK,
    CONTINUE,

    // переключатель
    SWITCH,
    CASE,
    DEFAULT,

    // операторы условия
    IF,
    ELSE,


    // операторы отношений
    LESS, // <
    GREATER, // >
    LESS_EQUAL, // <=
    GREATER_EQUAL, // >=

    // операторы или равно
    EQUAL, // ==
    NOT_EQUAL, // !=


    // Операторы и или не равно
    AND, // &&
    OR, // ||
    EXCLAMATION, // !

    // Математические операторы
    PLUS,  // +
    MINUS, // -
    STAR,  // *
    SLASH, // /
    INC,   // ++
    DEC,   // --
    DEG,   // ^

    // скобки
    LBRA, // {
    RBRA, // }
    LPAR, // (
    RPAR, // )
    LSQR, // [
    RSQR, // ]


    // assign
    ASSIGN,     // =
    ADD_ASSIGN, // +=
    SUB_ASSIGN, // -=
    MUL_ASSIGN, // *=
    DIV_ASSIGN, // /=

    // Функции
    FUNCTION,
    PROCEDURE,
    RETURN,

    // другие символы
    SEMICOLON, // ;
    COLON,     // :
    COMMA,     // ,
    POINT,     // .
    QUESTION,  // ?
    AMPERSAND, // &

    // комментарии
    LINE_COMMENT, // //
    BLOCK_COMMENT_START, // /*
    BLOCK_COMMENT_END, // */

    // операторы выделения и удаления памяти
    NEW,
    DELETE,

    PREPROCESSOR_DIRECTIVE,


    ACCESS_OPERATOR, // ::
};

#endif // TOCKENS_H
