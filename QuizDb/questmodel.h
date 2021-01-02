#ifndef QUESTMODEL_H
#define QUESTMODEL_H
//
#include <QTableView>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QHeaderView>
#include "mainwindow.h"
//
class questModel : public QSqlQueryModel
{
Q_OBJECT
public:
	questModel( QObject *parent = 0, QTableView *qv = 0 );
	
	Qt::ItemFlags flags( const QModelIndex &index ) const;
	bool setData( const QModelIndex &index, const QVariant &value, int role );
	bool insertRow( bool copied );
	bool deleteRow();
	bool showKey();
	
private:
	bool setRef( int qid, const QString ref );
	bool setType( int qid, const QString &type );
	bool setQuality( int qid, const QString &type );
	bool setPreface( int qid, const QString &preface );
	bool setQuest( int qid, const QString &quest );
	bool setAns( int qid, const QString &ans );
	bool setCR( int qid, const QString &cr );
	void refresh();
    MainWindow *pwin;
    QTableView *qview;
	bool keyOpen;
};

#endif
