#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QtGui>
//#include <QClipboard>
#include "quizquesteditview.h"

quizQuestEditView::quizQuestEditView(QWidget *parent, int qnum, Qt::WindowFlags fl )
    : QWidget ( parent, fl )
{
    setWindowTitle( tr("Edit Quiz Question") );
    pwin = (quizview *)parent;
    editqnum = qnum;

    QVBoxLayout * v = new QVBoxLayout( this );
    setLayout( v );

    quizQuestEdit = new QTableView;
    v->addWidget( quizQuestEdit );

    QHBoxLayout * h = new QHBoxLayout;
    h->addSpacing( 900 );
    QPushButton *okbutton = new QPushButton( "Ok", this );
    h->addWidget( okbutton );
//    QPushButton *cancelbutton = new QPushButton( "Cancel", this );
//    h->addWidget( cancelbutton );
    v->addLayout( h );

    setMinimumSize(1300, 50);

    connect( okbutton, SIGNAL(clicked()), this, SLOT(OK_clicked()) );
//    connect( cancelbutton, SIGNAL(clicked()), this, SLOT(Cancel_clicked()) );
}

void quizQuestEditView::OK_clicked()
{
    pwin->updateQuestion( editqnum );
    close();
}

/*
 * Turns out there is not a good way to cancel the edit. As the program runs now, the changes are made in the "Questions"
 * table. The quiz view and the quiz question class each have a record of what was, so perhaps there is a way to retrieve that
 * info and put it back into the database. But if someone does not want to save the changes, the obvious solution is to change
 * it back.
void quizQuestEditView::Cancel_clicked()
{
    pwin->cancelEdit();
    close();
}
*/

void quizQuestEditView::setQuizModel( quizQuestModel *model )
{
    quizQuestEdit->setModel( model );
    quizeditmodel = model;
}

void quizQuestEditView::sizeQuizQuestEditView( )
{
    quizQuestEdit->hideColumn( 0 );
    for( int col=8; col<12; col++ )
    {
        quizQuestEdit->hideColumn( col );
    }
    for( int col=1; col<4; col++ )
    {
        quizQuestEdit->resizeColumnToContents( col );
    }
    quizQuestEdit->setColumnWidth( 4, 200 );
    quizQuestEdit->setColumnWidth( 5, 360 );
    quizQuestEdit->setColumnWidth( 6, 400 );
    quizQuestEdit->setColumnWidth( 7, 100 );
    quizQuestEdit->resizeRowsToContents();
}
