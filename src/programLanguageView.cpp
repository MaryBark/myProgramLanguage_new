#include "programLanguageView.h"
#include "./ui_programLanguageView.h"

#include "lexer.h"
#include "parser.h"
#include "semantic.h"


programLanguageView::programLanguageView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::programLanguageView)
{
    ui->setupUi(this);

    // подключение собственного шрифта))))
    int idFont = QFontDatabase::addApplicationFont("my_font.ttf"); //путь к шрифту
    QString myFont = QFontDatabase::applicationFontFamilies(idFont).at(0); //имя шрифта
    QFont fontMy(myFont, 80, 50, true);
    fontMy.setWeight(10);
//    ui->textBrowser->setFont(fontMy);

//    Display disp;

    try
    {
        lexer lex("test.cpp");

        lex.split();
        semantic::merge(&lex);
        lex.print();
        ui->textBrowser->setText("the program has compiled!");
    }
    catch (std::logic_error& error)
    {
        ui->textBrowser->setText(error.what());
    }

}

programLanguageView::~programLanguageView()
{
    delete ui;
}

