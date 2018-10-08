#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlError>
#include <QSqlRecord>
#include "quizview.h"
#include "quizmodel.h"

quizModel *qzModel[MAXSECTIONS];

quizview::quizview ( quizClass *quiz, QWidget* parent, Qt::WindowFlags fl )
        : QWidget ( parent , fl )
{
	int tab;
	QSqlQueryModel *tabModel;
	QString sql;
	QString q;
	QTableView *qzView[MAXSECTIONS];
		
    setWindowTitle( QString( "Review Quiz #%1" ).arg(quiz->quizNumber()+1) );
	setMinimumSize( 800, 720 );
	pwin = (quizreview *)parent;
	viewquiz = quiz;
//	quiznum = qznum;
	createMenu();

	QVBoxLayout * v1 = new QVBoxLayout;
	setLayout( v1 );
	tabwidget = new QTabWidget;
	v1->addWidget( tabwidget );
	tabModel = new QSqlQueryModel;
	sql = QString( "SELECT Name FROM QuizFormat ORDER BY ID" );
	tabModel->setQuery( sql );
	if( tabModel->lastError().isValid() )
	{
		pwin->Err( tabModel->lastError().text() );
		return;
	}

	for( tab=0; tab<quiz->sectionCount(); tab++ )
	{
		qzView[tab] = new QTableView;
		tabwidget->addTab( qzView[tab], tabModel->record( tab ).value( "Name" ).toString() );
//		vheader[tab] = qzView[tab]->verticalHeader();
//		connect( (const QObject*)(vheader[tab]), SIGNAL(sectionClicked(int)), this, SLOT(qzEdit(int)) );

		qzModel[tab] = new quizModel( quiz, quiz->quizNumber(), tab, this, qzView[tab] );
		sql = QString( "SELECT q FROM QuizView "
			"WHERE quiznum=%1 AND section=%2 ORDER BY qnum" )
			.arg( quiz->quizNumber() ).arg( tab );
		qzModel[tab]->setQuery( sql );
		if( qzModel[tab]->lastError().isValid() )
		{
			pwin->Err( qzModel[tab]->lastError().text() );
			return;
		}

		qzView[tab]->setModel( qzModel[tab] );
		qzView[tab]->setColumnWidth( 0, 700 );
		qzModel[tab]->setHeaderData( 0, Qt::Horizontal, tr( "Question" ) );

/*
		for( i=0; i<qzModel[tab]->rowCount(); i++ )
		{
			q = qzModel[tab]->record( i ).value( "q" ).toString();
			j = q.indexOf( tr(" A. ") );
			q.replace( j, 1, QString(QChar::LineSeparator).append( "      " ) );
			q.insert(0, QString( "%1. ").arg( i+1 ) );
			new QListWidgetItem( qzmodel.record( i ).value( "q" ).toString(), qzView[tab] );
			new QListWidgetItem( q, qzView[tab] );
		}
*/
	}

	QHBoxLayout * h1 = new QHBoxLayout;
	v1->addLayout( h1 );
	ok = new QPushButton( "OK", this );
	h1->addWidget( ok );
	cancel = new QPushButton( "Cancel", this );
	h1->addWidget( cancel );
	connect( ok, SIGNAL(clicked()), this, SLOT(OK_clicked()) );
	connect( cancel, SIGNAL(clicked()), this, SLOT(close()) );
}

void quizview::OK_clicked()
{
	close();
//	pwin->reviewOK( quiznum );
}

void quizview::Err( QString msg )
{
	pwin->Err( msg );
}

void quizview::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);

	section = tabwidget->currentIndex();
	menu.addAction(replaceAct);
	menu.addAction(moveUpAct);
	menu.addAction(moveDownAct);
	menu.exec(event->globalPos());
}

void quizview::createMenu()
{
	replaceAct = new QAction(tr("&Replace Question"), this);
	replaceAct->setShortcut(tr("Ctrl+R"));
	replaceAct->setStatusTip(tr("Choose a different question of the same type"));
	connect(replaceAct, SIGNAL(triggered()), this, SLOT(replace()));
	
	moveUpAct = new QAction(tr("Move &Up"), this);
	moveUpAct->setShortcut(tr("Ctrl+U"));
	moveUpAct->setStatusTip(tr("Move this question 1 spot earlier in the quiz"));
	connect(moveUpAct, SIGNAL(triggered()), this, SLOT(moveUp()));
	
	moveDownAct = new QAction(tr("Move &Down"), this);
	moveDownAct->setShortcut(tr("Ctrl+D"));
	moveDownAct->setStatusTip(tr("Move this question 1 spot later in the quiz"));
	connect(moveDownAct, SIGNAL(triggered()), this, SLOT(moveDown()));
}

void quizview::replace()
{
	qzModel[section]->replace();
}

void quizview::moveUp()
{
	qzModel[section]->moveUp();
}

void quizview::moveDown()
{
	qzModel[section]->moveDown();
}

bool quizview::replaceQuestion( int sec, int qnum )
{
	return( viewquiz->section(sec)->replaceQuestion( qnum ) );
}
