#include "algas.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Algas w;
    w.show();

    return a.exec();
}
