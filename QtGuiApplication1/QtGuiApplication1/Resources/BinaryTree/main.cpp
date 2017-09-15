#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	w.setWindowTitle("BinaryTree Demo");
    w.resize(MainWindow_Width, MainWindow_Height);
    w.show();

    return a.exec();
}
