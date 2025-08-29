#include "mainwidget.h"

#include <QApplication>

#include "model/data.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LOG() << model::Message::makeId();

    MainWidget w;
    w.show();
    return a.exec();
}
