#include "MainWindow.h"
#include <iostream>
#include <QApplication>
#include <QTime>
#include "MeCore/FileUtils.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FileUtils::ins()->init(QApplication::applicationDirPath().toStdString());
	MainWindow w;
	w.showMaximized();
	return a.exec();
}
