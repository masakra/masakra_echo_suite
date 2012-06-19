
#include "Widget.h"

#include <QtGui>

Widget::Widget( QWidget * parent )
	: QWidget( parent )
{
	createWidgets();

	setWindowTitle( tr("Echo client %1").arg( PORT ) );

	connect( &socket, SIGNAL( connected() ), SLOT( slotConnected() ) );
	connect( &socket, SIGNAL( disconnected() ), SLOT( slotDisconnected() ) );
	connect( &socket, SIGNAL( readyRead() ), SLOT( slotRead() ) );

	tcpConnect();
}

void
Widget::createWidgets()
{
	editData = new QLineEdit( this );
	editData->setEnabled( false );

	editText = new QLineEdit( this );
	editText->setEnabled( false );

	QPushButton * buttonSend = new QPushButton( tr("&Send"), this ),
				* buttonExit = new QPushButton( tr("E&xit"), this );

	connect( buttonSend, SIGNAL( clicked() ), SLOT( slotSend() ) );
	connect( buttonExit, SIGNAL( clicked() ), SLOT( slotClose() ) );

	QHBoxLayout * horLayout = new QHBoxLayout();

	horLayout->addWidget( editText );
	horLayout->addStretch();
	horLayout->addWidget( buttonSend );

	QVBoxLayout * layout = new QVBoxLayout( this );

	layout->addWidget( editData );
	layout->addLayout( horLayout );
	layout->addStretch();
	layout->addWidget( buttonExit );
}

void
Widget::slotSend()
{
	socket.write( editText->text().toAscii() );
}

void
Widget::slotRead()
{
	editData->setText( QString::fromAscii( socket.readLine().trimmed() ) );
}

void
Widget::tcpConnect()
{
	socket.connectToHost( "localhost", PORT );
}

void
Widget::slotConnected()
{
	editText->setEnabled( true );
}

void
Widget::slotDisconnected()
{
	editText->setEnabled( false );
}

void
Widget::slotClose()
{
	socket.close();
	close();
}



