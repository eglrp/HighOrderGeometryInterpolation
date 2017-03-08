#include <QApplication>
#include <QList>
#include <QImage>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


	MainWindow w;
	w.show();

	return a.exec();
}
