#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("Singleton Theme App");
    w.resize(300, 150);
    w.show();

    return app.exec();
}
