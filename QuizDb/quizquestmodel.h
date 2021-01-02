#ifndef QUIZQUESTMODEL_H
#define QUIZQUESTMODEL_H

//
#include <QTableView>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QHeaderView>
#include <QApplication>
#include <QVBoxLayout>
#include "quizview.h"
#include "mainwindow.h"

//
class quizQuestModel : public QSqlQueryModel
{
Q_OBJECT
public:
    quizQuestModel( QObject *parent = 0, int tab = 0 );

    Qt::ItemFlags flags( const QModelIndex &index ) const;
    bool setData( const QModelIndex &index, const QVariant &value, int role );
    void updateQuizQuestionModel();

public slots:

private:
    class quizview *pwin;
    MainWindow *mainwidget;
    bool setRef( int qid, const QString ref );
    bool setType( int qid, const QString &type );
    bool setQuality( int qid, const QString &type );
    bool setPreface( int qid, const QString &preface );
    bool setQuest( int qid, const QString &quest );
    bool setAns( int qid, const QString &ans );
    bool setCR( int qid, const QString &cr );
    void refresh( int qid );
    void Err( QString msg );
    bool parseRef( const QString ref, int *book, int *chap, int *verse, int *verses );
//    QWidget *pwin;
    int quiztab;
};

#endif // QUIZQUESTMODEL_H
