#include <QtSql>
#include <QtGui>
#include <QItemSelectionModel>
#include "quizmodel.h"
//
quizModel::quizModel( quizClass *quiz, int qz, int sec, QObject *parent, 
		QTableView *qv ) 
	: QSqlQueryModel( parent )
{
	pwin = (quizview *)parent;	
	qview = qv;
	quiznum = qz;
	section = sec;
	qclass = quiz;
}

Qt::ItemFlags quizModel::flags( const QModelIndex &index ) const
{
	Qt::ItemFlags flags = QSqlQueryModel::flags(index);
	if( index.column() < 0 )
		flags |= Qt::ItemIsEditable;
	return flags;
}

bool quizModel::setData( const QModelIndex &index, const QVariant &value, int )
{
	QSqlQuery query;
	QString sql;
	int i, qnum, qnew;

	QModelIndex primaryKeyIndex = QSqlQueryModel::index( index.row(), 0 );
	qnum = data( primaryKeyIndex ).toInt();
//	QModelIndex nextIndex = QSqlQueryModel::index( index.row()+1, index.column() );
	clear();

	bool ok = true;
	switch( index.column() )
	{
		case 0:
			qnew = value.toInt();
			if( qnew == qnum )
				break;
			sql = QString( "UPDATE Quiz SET qnum=0 WHERE qnum=%1 AND section=%2 and quiznum=%3" )
				.arg(qnum).arg(section).arg(quiznum);
			if( !query.exec( sql ) )
			{
				pwin->Err( query.lastError().text() );
				ok = false;	
			}
			
			if( qnew > qnum )
			{
				for( i=qnum; i<qnew; i++ )
				{
					sql = QString( "UPDATE Quiz SET qnum=%1 WHERE qnum=%2 AND section=%3 and quiznum=%4" )
						.arg(i).arg(i+1).arg(section).arg(quiznum);
					if( !query.exec( sql ) )
					{
						pwin->Err( query.lastError().text() );
						ok = false;	
					}
				}
				sql = QString( "UPDATE Quiz SET qnum=%1 WHERE qnum=0 AND section=%2 and quiznum=%3" )
					.arg(qnew).arg(section).arg(quiznum);
				if( !query.exec( sql ) )
				{
					pwin->Err( query.lastError().text() );
					ok = false;	
				}
			}
			else // qnew < qnum
			{
				for( i=qnum; i>qnew; i-- )
				{
					sql = QString( "UPDATE Quiz SET qnum=%1 WHERE qnum=%2 AND section=%3 and quiznum=%4" )
						.arg(i).arg(i-1).arg(section).arg(quiznum);
					if( !query.exec( sql ) )
					{
						pwin->Err( query.lastError().text() );
						ok = false;	
					}
				}
				sql = QString( "UPDATE Quiz SET qnum=%1 WHERE qnum=0 AND section=%2 and quiznum=%3" )
					.arg(qnew).arg(section).arg(quiznum);
				if( !query.exec( sql ) )
				{
					pwin->Err( query.lastError().text() );
					ok = false;	
				}
			}
			break;
		case 1:
			sql = QString( "UPDATE Quiz SET q=\'%1\' WHERE qnum=%2 AND section=%3 and quiznum=%4" )
				.arg(value.toString()).arg(qnum).arg(section).arg(quiznum);
			if( !query.exec( sql ) )
			{
				pwin->Err( query.lastError().text() );
				ok = false;	
			}
			break;
	}
	refresh();

	return ok;
}

void quizModel::refresh()
{
	setQuery( QString( "SELECT q FROM QuizView where quiznum=%1 AND section=%2 ORDER BY qnum" )
		.arg(quiznum).arg(section) );
//	setHeaderData( 0, Qt::Horizontal, tr( "#" ) );
	setHeaderData( 0, Qt::Horizontal, tr( "Question" ) );
//	qview->setColumnWidth( 0, 700 );
}

bool quizModel::replace()
{
	int qnum = qview->currentIndex().row();
//	if( !pwin->replaceQuestion( quiznum, section, qnum ) )
	if( !pwin->replaceQuestion( section, qnum ) )
		return false;
		
	refresh();
	return true;
}

bool quizModel::swap( int qnum1, int qnum2 )
{
	QSqlQueryModel q1;
	QSqlQueryModel q2;

	q1.setQuery( QString( "SELECT * FROM Quiz WHERE " )
					.append( "qnum=%1 AND section=%2 and quiznum=%3" )
					.arg(qnum1).arg(section).arg(quiznum) );
	if( q1.lastError().isValid() )
	{
		pwin->Err( q1.lastError().text() );
		return false;
	}
	q2.setQuery( QString( "SELECT * FROM Quiz WHERE " )
					.append( "qnum=%1 AND section=%2 and quiznum=%3" )
					.arg(qnum2).arg(section).arg(quiznum) );
	if( q2.lastError().isValid() )
	{
		pwin->Err( q2.lastError().text() );
		return false;
	}
	qclass->section(section)->question(qnum1)->setQuestion(
			q2.record(0).value("qid").toInt(),
			q2.record(0).value("key").toInt(),
			q2.record(0).value("vid").toInt() );
	qclass->section(section)->question(qnum2)->setQuestion(
			q1.record(0).value("qid").toInt(),
			q1.record(0).value("key").toInt(),
			q1.record(0).value("vid").toInt() );
	refresh();

	return true;
}

bool quizModel::moveUp()
{
//	QSqlQuery query;
//	QString sql;
//	bool ok = true;

	int qnum = qview->currentIndex().row();
	return( swap( qnum, qnum-1 ) );
}

bool quizModel::moveDown()
{
//	QSqlQuery query;
//	QString sql;
//	bool ok = true;

	int qnum = qview->currentIndex().row();
	return( swap( qnum, qnum+1 ) );
}
