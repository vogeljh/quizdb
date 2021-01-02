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

        qzModel[tab] = new quizModel( quiz, quiz->quizNumber(), tab, this, qzView[tab] );
        updateQuizModel( tab );

		qzView[tab]->setModel( qzModel[tab] );
		qzView[tab]->setColumnWidth( 0, 700 );
//		qzModel[tab]->setHeaderData( 0, Qt::Horizontal, tr( "Question" ) );
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
    menu.addAction(editQuestionAct);
    menu.addAction(editQuestionCopyAct);
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

    editQuestionAct = new QAction(tr("&Edit Question"), this);
    editQuestionAct->setShortcut(tr("Ctrl+E"));
    editQuestionAct->setStatusTip(tr("Edit the question"));
    connect(editQuestionAct, SIGNAL(triggered()), this, SLOT(editQuestion()));

    editQuestionCopyAct = new QAction(tr("Edit Question &Copy"), this);
    editQuestionCopyAct->setShortcut(tr("Ctrl+C"));
    editQuestionCopyAct->setStatusTip(tr("Edit a copy of the question"));
    connect(editQuestionCopyAct, SIGNAL(triggered()), this, SLOT(editQuestionCopy()));
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

void quizview::editQuestionCopy()
{
    editQuizQuestion( 1 );
    editquestioncopied = true;
}

void quizview::editQuestion()
{
    editQuizQuestion( 0 );
    editquestioncopied = false;
}

void quizview::editQuizQuestion( int copy )
{
    int qid, qnum, numrows;
    QSqlQueryModel quizQueryModel;
    QSqlQuery query;
    QString sql;
    bool ok;

    qnum = qzModel[section]->quizQuestNumber();

    sql = QString( "SELECT qid FROM QuizView where quiznum=%1 AND section=%2 AND qnum=%3" )
                  .arg(viewquiz->quizNumber()).arg(section).arg(qnum);
    quizQueryModel.setQuery( sql );
    if( quizQueryModel.lastError().isValid() )
    {
        pwin->Err( quizQueryModel.lastError().text() );
        return;
    }

    qid = quizQueryModel.record( 0 ).value( 0 ).toInt();

    if( copy )
    {
        sql = QString( "INSERT INTO Questions (Book, Chapter, Verse, Qtype, "
            "Quality, Verses, Preface, Question, Answer, CR) "
            "SELECT Book, Chapter, Verse, Qtype, Quality, Verses, Preface, Question, "
            "Answer, CR FROM Questions WHERE QID=%1" ).arg( qid );
        ok = query.exec( sql );
        if( !ok )
            pwin->Err( query.lastError().text() );
        ok = query.exec( "select last_insert_rowid()");
        if( !ok )
            pwin->Err( query.lastError().text() );
        copied_qid = query.value( 0 ).toInt();
    }

    quizEditQuestQuery = QString( "SELECT QID,Ref,Tabbrev,Quality,Preface,Question,Answer,CR,Used,Qsort,VID,Verses FROM Quest" )
            .append( " where QID = %1" ).arg( qid );

    quizQuestEditModel = new quizQuestModel( this, section );
    quizQuestEditModel->setQuery( quizEditQuestQuery );
    if( quizQuestEditModel->lastError().isValid() )
    {
        pwin->Err( quizQuestEditModel->lastError().text() );
        return;
    }
    if( (numrows=quizQuestEditModel->rowCount())-1 )
    {
        pwin->Err( QString( "edit query returned %1 rows." ).arg( numrows ) );
    }

    quizQuestEdit = new quizQuestEditView( this, qnum, Qt::Window );
    quizQuestEdit->setQuizModel( quizQuestEditModel );
    quizQuestEditModel->updateQuizQuestionModel();

    quizQuestEdit->show();
}

void quizview::sizeQuizEditView()
{
    quizQuestEdit->sizeQuizQuestEditView();
}

QString *quizview::GetQuestQuery()
{
    return( &quizEditQuestQuery );
}

void quizview::updateQuizModel( int tab )
{
    QString sql;

    sql = QString( "SELECT q FROM QuizView "
        "WHERE quiznum=%1 AND section=%2 ORDER BY qnum" )
        .arg( viewquiz->quizNumber() ).arg( tab );
    qzModel[tab]->setQuery( sql );
    if( qzModel[tab]->lastError().isValid() )
    {
        pwin->Err( qzModel[tab]->lastError().text() );
        return;
    }

    qzModel[tab]->setHeaderData( 0, Qt::Horizontal, tr( "Question" ) );
}

void quizview::updateQuestion( int qnum )
{
    int qid, key, vid;

    qid = viewquiz->section( section )->question( qnum )->qid();
    key = viewquiz->section( section )->question( qnum )->key();
    vid = viewquiz->section( section )->question( qnum )->vid();
    viewquiz->section( section )->question( qnum )->setQuestion( qid, key, vid );
    updateQuizModel( section );
}

/*
 * See notes in quizquesteditview. As implemented, the changes were undone in the quiz view and the quiz class, but
 * the changes in the main "Questions" table cannot be readily undone.
void quizview::cancelEdit()
{
    QSqlQuery query;
    bool ok;

    if( editquestioncopied )
    {
        ok = query.exec( QString( "DELETE from Questions WHERE qid=%1").arg(copied_qid) );
        if( !ok )
            pwin->Err( query.lastError().text() );
    }
}
*/
