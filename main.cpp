#include <QApplication>
#include "Info.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Info info;
    info.test();
    return a.exec();
}
