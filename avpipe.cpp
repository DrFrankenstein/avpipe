#include <QApplication>
#include <QPushButton>
extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
}

#include "avpipe.h"
#include "Gui/MainWindow.hpp"

int main(int argc, char* argv[])
{
	QApplication app { argc, argv };

	// av_register_all();	// deprecated
	::av_log_set_level(AV_LOG_DEBUG);

	MainWindow mainwin;
	mainwin.show();

    return QApplication::exec();
}
