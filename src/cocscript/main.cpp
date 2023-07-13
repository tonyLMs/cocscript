#include "cocscript.h"
#include <QtWidgets/QApplication>

//1700*978

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cocscript w;
    w.show();
    return a.exec();
}