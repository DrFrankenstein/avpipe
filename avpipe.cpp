#include <QApplication>
#include <QPushButton>
extern "C"
{
#include <libavcodec/avcodec.h>
}

#include "avpipe.h"

int main(int argc, char* argv[])
{
	QApplication app { argc, argv };

	QPushButton button { "Hello, World!" };
	button.show();

	return app.exec();
}
