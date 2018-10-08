#include <QVBoxLayout>
#include <QtGui>
#include <QClipboard>
#include "bible.h"

bible::bible ( QWidget* parent, Qt::WindowFlags fl )
		: QWidget ( parent, fl )
{
	setWindowTitle( tr("Search Results") );
    pwin = (MainWindow *)parent;

	QVBoxLayout * v = new QVBoxLayout( this );
	sview = new QTableView;
	v->addWidget( sview );
	setMinimumSize(600,100);
	connect( sview, SIGNAL(clicked(const QModelIndex &)), this, SLOT(verseCopy(const QModelIndex &)) );
	createMenu();
}

void bible::setSearchModel( QSqlQueryModel *model )
{
	sview->setModel( model );
	sview->resizeColumnToContents( 0 );
//	sview->resizeColumnToContents( 1 );
	sview->setColumnWidth( 1, 460 );
	sview->resizeRowsToContents();
}

void bible::closeEvent(QCloseEvent *event)
{
	pwin->searchClosed();
	event->accept();
}

void bible::createMenu()
{
	insertCopyAct = new QAction(tr("&Copy Verse"), this);
	insertCopyAct->setShortcut(tr("Ctrl+C"));
	insertCopyAct->setStatusTip(tr("Copy verse text into clipboard"));
	connect(insertCopyAct, SIGNAL(triggered()), this, SLOT(copyVerse()));
}

void bible::copyVerse()
{
//	Err(tr("Invoked <b>Edit|Copy</b>"));
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText( vselected );
}

void bible::verseCopy( const QModelIndex &id )
{
	QMenu menu(this);
// fix this
	vselected = sview->model()->data( id ).toString();
	menu.addAction(insertCopyAct);
	menu.exec(QCursor::pos());
}
