#include "range.h"
#include <QComboBox>
#include <QSpinBox>
//
range::range( QWidget * parent, Qt::WindowFlags f) 
	: QWidget(parent, f)
{
	int i, bookmax;
	setupUi(this);

	connect( book1, SIGNAL(currentIndexChanged(int)), this, SLOT(book1selected(int)) );
	connect( chapter1, SIGNAL(valueChanged(int)), this, SLOT(chapter1selected(int)) );
	connect( book2, SIGNAL(currentIndexChanged(int)), this, SLOT(book2selected(int)) );
	connect( chapter2, SIGNAL(valueChanged(int)), this, SLOT(chapter2selected(int)) );
	connect( ok, SIGNAL(clicked()), this, SLOT(rangedlg_ok()) );
	connect( cancel, SIGNAL(clicked()), this, SLOT(close()) );

    pwin = (MainWindow *)parent;
	vsRange = pwin->getVrange();
	bookmax = pwin->BookCount();
	for( i=0; i<bookmax; i++ )
	{
		book1->insertItem( i, pwin->BookName( i ) );
		book2->insertItem( i, pwin->BookName( i ) );
	}
	book1->setCurrentIndex( vsRange->startBook() );
	book2->setCurrentIndex( vsRange->endBook() );
	chapter1->setValue( vsRange->startChapter()+1 );
// not necessary to set maxima as the setcurrentIndex and setvalue commands
// automatically trigger the code that sets the maximums.
	verse1->setValue( vsRange->startVerse()+1 );
	chapter2->setValue( vsRange->endChapter()+1 );
	verse2->setValue( vsRange->endVerse()+1 );
}

/*$SPECIALIZATION$*/
void range::chapter2selected ( int val )
{
	int i;

	i = book2->currentIndex();
	if( i>=0 && i<pwin->BookCount() && val>0 && val<=pwin->ChapterCount(i) )
	{
		verse2->setMaximum( pwin->VerseCount( i, val-1 ) );
		verse2->setValue( pwin->VerseCount( i, val-1 ) );
	}
}

void range::book2selected( int index )
{
	int c, v;

	if( index>=0 && index<pwin->BookCount())
	{
		c = pwin->ChapterCount( index );
		v = pwin->VerseCount( index, c-1 );
		chapter2->setMaximum( c );
		chapter2->setValue( c );
		verse2->setMaximum( v );
		verse2->setValue( v );
	}
}

void range::chapter1selected ( int val )
{
	int i;

	i = book1->currentIndex();
	if( i>=0 && i<pwin->BookCount() && val>0 && val<=pwin->ChapterCount(i)  )
	{
		verse1->setMaximum( pwin->VerseCount( i, val-1 ) );
	}
}

void range::book1selected( int index )
{
	if( index>=0 && index<pwin->BookCount() )
	{
		chapter1->setMaximum( pwin->ChapterCount( index ) );
	}
}

void range::rangedlg_ok()
{
	vsRange->setStartAddress( book1->currentIndex(), chapter1->value()-1, 
			verse1->value()-1 );
	vsRange->setEndAddress( book2->currentIndex(), chapter2->value()-1, 
			verse2->value()-1 );
	pwin->setVrange();
	close();
}

//

