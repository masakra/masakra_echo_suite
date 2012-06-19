#!/usr/local/bin/python

# \file echoclient.py
# \brief The simple echo client
# \author Sergey N Chursanov
# \date 19.06.2012

import sys
from PyQt4 import QtGui, QtCore, QtNetwork


# Widget class
class Widget( QtGui.QWidget ):
	"""\brief Dialog window

	Will connect at startup to 'localhost' 7000.
	"""

	def __init__( self, parent = None ):
		QtGui.QWidget.__init__( self, parent )

		self.setWindowTitle( 'simple Qt/Python application' )
		#
		##
		### create widgets
		##
		#
		self.editData = QtGui.QLineEdit( self )
		self.editData.setEnabled( False )

		self.editText = QtGui.QLineEdit( self )
		self.editText.setEnabled( False )

		buttonSend = QtGui.QPushButton( self.tr("&Send"), self )
		self.connect( buttonSend, QtCore.SIGNAL( 'clicked()' ), self.slotSend )

		buttonExit = QtGui.QPushButton( self.tr("E&xit"), self )
		self.connect( buttonExit, QtCore.SIGNAL( 'clicked()' ), self.slotClose )

		horLayout = QtGui.QHBoxLayout()

		horLayout.addWidget( self.editText )
		horLayout.addStretch()
		horLayout.addWidget( buttonSend )

		layout = QtGui.QVBoxLayout( self )

		layout.addWidget( self.editData )
		layout.addLayout( horLayout )
		layout.addStretch()
		layout.addWidget( buttonExit )
		#
		##
		### socket
		##
		#
		self.socket = QtNetwork.QTcpSocket()
		self.connect( self.socket, QtCore.SIGNAL( 'connected()' ), self.slotConnected )
		self.connect( self.socket, QtCore.SIGNAL( 'disconnected()' ), self.slotDisconnected )
		self.connect( self.socket, QtCore.SIGNAL( 'readyRead()' ), self.slotRead )

		self.socket.connectToHost( 'localhost', 7000 )

	def slotSend( self ):
		"""\brief Send a data to echo server"""
		self.socket.write( self.editText.text().toAscii() )

	def slotRead( self ):
		"""\brief Receive a data from echo server"""
		data = self.socket.readLine().trimmed()
		self.editData.setText( unicode( data, 'KOI8-R' ) )

	def slotConnected( self ):
		self.editText.setEnabled( True )

	def slotDisconnected( self ):
		self.editText.setEnabled( False )

	def slotClose( self ):
		self.socket.close()
		self.close()

# start here

app = QtGui.QApplication( sys.argv )

# for correct QString::toAscii() behavior
QtCore.QTextCodec.setCodecForCStrings( QtCore.QTextCodec.codecForName( 'KOI8-R' ) )

widget = Widget()
widget.show()

sys.exit( app.exec_() )


