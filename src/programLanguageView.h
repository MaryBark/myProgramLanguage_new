#ifndef PROGRAMLANGUAGEVIEW_H
#define PROGRAMLANGUAGEVIEW_H

#include <QMainWindow>
#include <QFontDatabase>
#include "lexer.h"
#include "parser.h"
#include "semantic.h"
//#include "forDisplay.h"

QT_BEGIN_NAMESPACE
namespace Ui { class programLanguageView; }
QT_END_NAMESPACE

class programLanguageView : public QMainWindow
{
    Q_OBJECT

public:
    programLanguageView(QWidget *parent = nullptr);
    ~programLanguageView();

private:
    Ui::programLanguageView *ui;
};
#endif // PROGRAMLANGUAGEVIEW_H
