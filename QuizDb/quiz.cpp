#include "quiz.h"
#include "quizedit.h"
#include "quizreview.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QSqlError>
#include <QSqlQuery>

quiz::quiz( QWidget * parent, Qt::WindowFlags f) 
	: QWidget(parent, f)
{
	int i, bookmax;

	setupUi(this);
    pwin = (MainWindow *)parent;
	connect( book1, SIGNAL(currentIndexChanged(int)), this, SLOT(book1selected(int)) );
	connect( chapter1, SIGNAL(valueChanged(int)), this, SLOT(chapter1selected(int)) );
	connect( book2, SIGNAL(currentIndexChanged(int)), this, SLOT(book2selected(int)) );
	connect( chapter2, SIGNAL(valueChanged(int)), this, SLOT(chapter2selected(int)) );
//	connect( EditButton, SIGNAL(clicked()), this, SLOT(editquizbutton_clicked()) );
//	connect( OkButton, SIGNAL(clicked()), this, SLOT(OkButton_clicked()) );
//	connect( CancelButton, SIGNAL(clicked()), this, SLOT(close()) );
    QuizSpinBox->setMaximum( MAXQUIZZES );
    vsRange = *(pwin->getVrange());
	bookmax = pwin->BookCount();
	prepared = false;

	for( i=0; i<bookmax; i++ )
	{
		book1->insertItem( i, pwin->BookName( i ) );
		book2->insertItem( i, pwin->BookName( i ) );
	}
	book1->setCurrentIndex( vsRange.startBook() );
	book2->setCurrentIndex( vsRange.endBook() );
	chapter1->setValue( vsRange.startChapter()+1 );
	chapter1->setMaximum( pwin->ChapterCount( vsRange.startBook() ) );
	verse1->setValue( vsRange.startVerse()+1 );
    verse1->setMaximum( pwin->VerseCount( vsRange.startBook(),
			pwin->ChapterCount(vsRange.startBook())-1 ) );
	chapter2->setValue( vsRange.endChapter()+1 );
	chapter2->setMaximum( pwin->ChapterCount( vsRange.endBook() ) );
    verse2->setValue( vsRange.endVerse()+1 );
//    verse2->setMaximum( pwin->VerseCount( vsRange.endBook(),
//			pwin->ChapterCount( vsRange.endBook() )-1 ) );
    verse2->setMaximum( pwin->VerseCount( vsRange.endBook(),
            vsRange.endChapter() ) );
}
//
/*$SPECIALIZATION$*/
void quiz::chapter2selected ( int val )
{
	int i;

	i = book2->currentIndex();
	if( i>=0 && i<pwin->BookCount() && val>0 && val<=pwin->ChapterCount(i) )
	{
		verse2->setMaximum( pwin->VerseCount( i, val-1 ) );
		verse2->setValue( pwin->VerseCount( i, val-1 ) );
	}
}

void quiz::book2selected( int index )
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

void quiz::chapter1selected ( int val )
{
	int i;

	i = book1->currentIndex();
	if( i>=0 && i<pwin->BookCount() && val>0 && val<=pwin->ChapterCount(i)  )
	{
		verse1->setMaximum( pwin->VerseCount( i, val-1 ) );
	}
}

void quiz::book1selected( int index )
{
	if( index>=0 && index<pwin->BookCount() )
	{
		chapter1->setMaximum( pwin->ChapterCount( index ) );
	}
}

void quiz::OkButton_clicked()
{
	quizreview *dlg = 0;
	int quiznum;
    int printformat;
    int questioncount[MAXSECTIONS];
    int sectioncount;
	QSqlQuery query;
    QSqlQueryModel qmodel;

	if( TimesUsedCheckBox->isChecked() )
	{
		query.exec( QString( "UPDATE Questions SET Used = 0" ) );
		if( query.lastError().isValid() )
		{
			pwin->Err( query.lastError().text() );
			return;
		}
	}
	
	saveTypeModel.setQuery( QString( "SELECT Questtype, Show FROM Types" ) );
	if( saveTypeModel.lastError().isValid() )
	{
		pwin->Err( saveTypeModel.lastError().text() );
		pwin->Err( "Fatal error making quizzes!" );
		close();
		return;
	}
	saveQualityModel.setQuery( QString( "SELECT Qtype, Quality, Show FROM Quality" ) );
	if( saveQualityModel.lastError().isValid() )
	{
		pwin->Err( saveQualityModel.lastError().text() );
		pwin->Err( "Fatal error making quizzes!" );
		close();
		return;
	}
	prepared = true;
	query.exec( QString( "UPDATE Types SET Show=\'1\'" ) );
	query.exec( QString( "UPDATE Quality SET Show=\'1\'" ) );
	query.exec( QString( "DELETE FROM Quiz" ) );
	numquizzes = QuizSpinBox->value();
    printformat = (LaTeXradioButton->isChecked() ? LATEX : RTF );
    if( HighlightKeyCheckBox->isChecked() )
    {
        printformat += HIGHLIGHT;
    }

    qmodel.setQuery( QString( "SELECT * FROM QuizFormat" ) );
    if( qmodel.lastError().isValid() )
    {
        Err( qmodel.lastError().text() );
        return;
    }
    sectioncount = qmodel.rowCount();
    for( int i=0; i<MAXSECTIONS; i++ )
    {
        if( i < sectioncount )
        {
            questioncount[i] = qmodel.record( i ).value( "count" ).toInt();
        }
        else
        {
            questioncount[i] = 0;
        }
    }

    for( quiznum=0; quiznum<numquizzes; quiznum++ )
	{
		statusLabel->setText( QString( "Making Quiz #%1..." ).arg(quiznum+1) );
		update();
		qApp->processEvents();
        qCquiz[quiznum] = new quizClass( quiznum, sectioncount, questioncount, printformat, pwin->getViewer( printformat ) );
		if( qCquiz[quiznum]->makeQuiz() < 0 )
		{
			pwin->Err( "Fatal error making quizzes!" );
			close();
			return;
        }
	}
	statusLabel->clear();
	dlg = new quizreview( qCquiz, numquizzes, pwin, Qt::Window, 
				pwin->GetdbFiledialog() );
	dlg->show();
	CancelButton->setText( QString( "Done" ) );
	OkButton->hide();
//	close();
}

void quiz::cancel_clicked()
{
	int i;
	QSqlQuery query;

	if( prepared )
	{
		for( i=0; i<saveTypeModel.rowCount(); i++ )
			query.exec( 
				QString( "UPDATE Types SET Show=\'%1\' WHERE Questtype=%2" )
				.arg( saveTypeModel.record(i).value( "Show" ).toInt() )
				.arg( saveTypeModel.record(i).value( "Questtype" ).toInt() ) );
		for( i=0; i<saveQualityModel.rowCount(); i++ )
			query.exec( QString( "UPDATE Quality SET Show=\'%1\' WHERE Qtype=%2 " )
				.append( "AND Quality=\'%3\'" )
				.arg( saveQualityModel.record(i).value( "Show" ).toInt() )
				.arg( saveQualityModel.record(i).value( "Qtype" ).toInt() )
				.arg( saveQualityModel.record(i).value( "Quality" ).toString() ) );
	}
	close();
}

void quiz::editQuiz_clicked()
{
	quizedit *dlg = 0;
	
	dlg = new quizedit( this, Qt::Window );
	dlg->show();
}

quizClass *quiz::quizzes( int i )
{
	if( i > 0 && i < numquizzes+1 )
		return( qCquiz[i-1] );
	else
		return( 0 );
}

void quiz::Err( QString msg )
{
	pwin->Err( msg );
}
