#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("Prototype GUI Application");
    w.resize(500, 500);
    w.show();

    return app.exec();
}
