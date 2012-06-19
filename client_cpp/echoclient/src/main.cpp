

#include <QApplication>
#include <QTextCodec>

#include "Widget.h"

int
main( int argc, char ** argv )
{
	QApplication app( argc, argv );

	// for QString::toAscii()
	// for correct translation non US-ASCII
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("KOI8-R") );

	Widget widget;

	widget.show();

	return app.exec();
}


