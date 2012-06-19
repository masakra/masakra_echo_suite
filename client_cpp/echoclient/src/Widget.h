
#ifndef WIDGET_H
#define WIDGET_H

#define PORT 7000

#include <QTcpSocket>
#include <QWidget>

/** \class Widget
 *
 * \brief Dialog window
 *
 * The echo client.
 * Will connect at `localhost' 7000.
 *
 * \sa void tcpConnect()
 */

class QLineEdit;

class Widget : public QWidget
{
	Q_OBJECT

	private:
		void createWidgets();

		QLineEdit * editData,
				  * editText;

		QTcpSocket socket;

		/** \fn void tcpConnect()
		 *
		 * \brief Connect to echo server
		 */
		void tcpConnect();

	private Q_SLOTS:
		void slotSend();
		void slotRead();
		void slotConnected();
		void slotDisconnected();
		void slotClose();

	public:
		Widget( QWidget * parent = NULL );
};

#endif

