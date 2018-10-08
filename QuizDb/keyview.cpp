#include <QVBoxLayout>
#include <QtGui>
#include <QClipboard>
#include "keyview.h"
//
keyView::keyView( QWidget *parent, Qt::WindowFlags fl ) 
		: QWidget ( parent, fl )
{
	setWindowTitle( tr("Key Words") );
    pwin = (MainWindow *)parent;

	QVBoxLayout * v = new QVBoxLayout( this );
	kView = new QTableView;
	v->addWidget( kView );
	setMinimumSize(600,100);
}

void keyView::setSearchModel( QStandardItemModel *model )
{
	kView->setModel( model );
//	kView->resizeColumnToContents( 0 );
//	kView->resizeColumnToContents( 1 );
//	kView->resizeColumnToContents( 2 );
}

void keyView::sizeKeyView( int rows )
{
	kView->setColumnWidth( 0, 100 );
	kView->setColumnWidth( 1, 100 );
	kView->setColumnWidth( 2, 70 );
	resize( 315, kView->rowHeight( 0 )*rows+50 );
}
