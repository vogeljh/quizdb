#include <QtSql>
#include <QtGui>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QScrollBar>
#include "mainwindow.h"
#include "quizquestmodel.h"

quizQuestModel::quizQuestModel( QObject *parent, int tab )
    : QSqlQueryModel( parent )
{
    const QWidgetList topLevelWidgets = QApplication::topLevelWidgets();
    QString sql;

    mainwidget = (MainWindow *)topLevelWidgets[0];
    pwin = (quizview *)parent;
    quiztab = tab;
}

Qt::ItemFlags quizQuestModel::flags( const QModelIndex &index ) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if( index.column() > 0 && index.column() < 8 )
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool quizQuestModel::setData( const QModelIndex &index, const QVariant &value, int )
{
    if (index.column() < 1 || index.column() > 7)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index( index.row(), 0 );
    int id = data( primaryKeyIndex ).toInt();
    clear();

    bool ok;
    switch( index.column() )
    {
        case 1:	ok = setRef( id, value.toString() ); break;
        case 2:	ok = setType( id, value.toString() ); break;
        case 3:	ok = setQuality( id, value.toString() ); break;
        case 4:	ok = setPreface( id, value.toString() ); break;
        case 5:	ok = setQuest( id, value.toString() ); break;
        case 6:	ok = setAns( id, value.toString() ); break;
        case 7:	ok = setCR( id, value.toString() ); break;
        default: ok = false;
    }
    if( !ok && query().lastError().isValid() )
        pwin->Err( query().lastError().text() );
    refresh( id );

    return ok;
}

void quizQuestModel::refresh( int qid )
{
    setQuery( QString( "SELECT QID,Ref,Tabbrev,Quality,Preface,Question,Answer,CR,")
                .append( "Used,Qsort,VID,Verses FROM Quest" )
                .append( " where QID = %1" ).arg( qid ) );
    if( query().lastError().isValid() )
        pwin->Err( query().lastError().text() );
    updateQuizQuestionModel();
}

bool quizQuestModel::setRef( int qid, const QString ref )
{
    int book, chap, verse, verses;
    QString sql;
    QSqlQuery query;

    if( !mainwidget->parseRef( ref, &book, &chap, &verse, &verses ) )
    {
        mainwidget->Err( tr("Reference could not be updated.") );
        return false;
    }
    sql = QString( "UPDATE Questions SET Book=%1,Chapter=%2,Verse=%3,Verses=%4 WHERE QID=%5" )
        .arg(book).arg(chap).arg(verse).arg(verses).arg(qid);
    return query.exec( sql );
}

bool quizQuestModel::setType( int qid, const QString &type )
{
    QSqlQuery query;
    QString sql;
    QString qtype=type;
    QSqlQueryModel typeModel;

    typeModel.setQuery( QString("SELECT Questtype, Abbrev FROM Types " )
            .append( "WHERE Abbrev = \'%1\'").arg( qtype ) );
    if( typeModel.lastError().isValid() )
    {
        mainwidget->Err( typeModel.lastError().text() );
        return false;
    }
    if( typeModel.rowCount() < 1 )
    {
        qtype.replace( 0, 1, qtype.left(1).toUpper() );
        typeModel.setQuery( QString("SELECT Questtype, Abbrev FROM Types " )
                .append( "WHERE Abbrev = \'%1\'").arg( qtype ) );
        if( typeModel.lastError().isValid() )
        {
            mainwidget->Err( typeModel.lastError().text() );
            return false;
        }
        if( typeModel.rowCount() < 1 )
        {
            typeModel.setQuery( QString("SELECT Questtype, Abbrev FROM Types " )
                    .append( "WHERE Abbrev = \'%1\'").arg( qtype.toLower() ) );
            if( typeModel.lastError().isValid() )
            {
                mainwidget->Err( typeModel.lastError().text() );
                return false;
            }
            if( typeModel.rowCount() < 1 )
            {
                mainwidget->Err( QString( "Type %1 unknown." ).arg( type ) );
                return false;
            }
        }
    }
    sql = QString( "UPDATE Questions SET Qtype=\'%1\' WHERE QID=%2" )
            .arg(typeModel.record(0).value("Questtype").toString()).arg(qid);
    return query.exec( sql );
}

bool quizQuestModel::setQuality( int qid, const QString &quality )
{
    QSqlQuery query;
    QString sql;
    QSqlQueryModel qualityModel;
    QSqlQueryModel questModel;

    questModel.setQuery( QString( "SELECT Qtype, Quality FROM Questions " )
            .append( "WHERE QID = \'%1\'" ).arg( qid ) );
    if( questModel.lastError().isValid() )
    {
        mainwidget->Err( questModel.lastError().text() );
        return false;
    }
    if( questModel.rowCount() < 1 )
    {
        mainwidget->Err( QString( "Question not found: QID = %1. Unable to save." ) );
        return false;
    }
    qualityModel.setQuery( QString( "SELECT Qtype, Quality FROM Quality " )
            .append( "WHERE Qtype = \'%1\' AND Quality = \'%2\'" )
            .arg( questModel.record( 0 ).value( "Qtype" ).toString() )
            .arg( quality.toLower() ) );
    if( qualityModel.lastError().isValid() )
    {
        mainwidget->Err( qualityModel.lastError().text() );
        return false;
    }
    if( qualityModel.rowCount() < 1 )
    {
        mainwidget->Err( QString( "Quality %1 unknown." ).arg( quality ) );
        return false;
    }
    else
    {
        sql = QString( "UPDATE Questions SET Quality=\'%1\' WHERE QID=%2" )
                .arg( quality.toLower() ).arg( qid );
        return query.exec( sql );
    }
}

bool quizQuestModel::setPreface( int qid, const QString &preface )
{
    QSqlQuery query;
    QString sql;

    sql = QString( "UPDATE Questions SET Preface=\'%1\' WHERE QID=%2" ).arg(preface).arg(qid);
    return query.exec( sql );
}

bool quizQuestModel::setQuest( int qid, const QString &quest )
{
    QSqlQuery query;
    QString sql;
    /*
                    query.exec( QString( "UPDATE QuizFormat SET ID = %1 WHERE ID = %2" ).arg( i ).arg( i+1 ) );
                    if( query.lastError().isValid() )
                    {
                        pwin->Err( query.lastError().text() );
                        query.exec( QString( "ROLLBACK" ) );
                        return;
                    }
    */
    sql = quest;
    sql.replace( tr("'"), tr("''") );
    sql = QString( "UPDATE Questions SET Question=\'%1\' WHERE QID=%2" ).arg(sql).arg(qid);
    return query.exec( sql );
}

bool quizQuestModel::setAns( int qid, const QString &ans )
{
    QSqlQuery query;
    QString sql;

    sql = ans;
    sql.replace( tr("'"), tr("''") );
    sql = QString( "UPDATE Questions SET Answer=\'%1\' WHERE QID=%2" ).arg(sql).arg(qid);
    return query.exec( sql );
}

bool quizQuestModel::setCR( int qid, const QString &CR )
{
    QSqlQuery query;
    QString sql;

    sql = QString( "UPDATE Questions SET CR=\'%1\' WHERE QID=%2" ).arg(CR).arg(qid);
    return query.exec( sql );
}

void quizQuestModel::updateQuizQuestionModel()
{
    setHeaderData( 2, Qt::Horizontal, tr( "Type" ) );
    setHeaderData( 3, Qt::Horizontal, tr( "Qual" ) );
    pwin->sizeQuizEditView();
}

