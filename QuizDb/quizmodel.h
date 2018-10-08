#ifndef QUIZMODEL_H
#define QUIZMODEL_H
//
#include <QSqlQueryModel>
#include <QTableView>
#include <QModelIndex>
#include "quizclass.h"
#include "quizview.h"
//
class quizModel : public QSqlQueryModel
{
Q_OBJECT
public:
	quizModel( quizClass *quiz, int qz, int sec, QObject *parent = 0, 
			QTableView *qv = 0 );
	
	Qt::ItemFlags flags( const QModelIndex &index ) const;
	bool setData( const QModelIndex &index, const QVariant &value, int role );
	bool replace();
	bool moveUp();
	bool moveDown();
	
private:
	void refresh();
	quizview *pwin;
	quizClass *qclass;
	QTableView *qview;
	int quiznum;
	int section;
	bool swap( int, int );
};
#endif
