#include <QApplication>
#include <QPushButton>
extern "C"
{
#include <libavformat/avformat.h>
}

#include "avpipe.h"
#include "mainwindow.hpp"

int main(int argc, char* argv[])
{
	QApplication app { argc, argv };

	// av_register_all();	// deprecated

	MainWindow mainwin;
	mainwin.show();

	return app.exec();
}
