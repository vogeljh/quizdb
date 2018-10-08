#include <QtSql>
#include <QtGui>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QScrollBar>
#include "questmodel.h"
#include "keyview.h"
//
questModel::questModel( QObject *parent, QTableView *qv ) 
    : QSqlQueryModel( parent )
{
    pwin = (MainWindow *)parent;
	qview = qv;
	keyOpen = false;
}

Qt::ItemFlags questModel::flags( const QModelIndex &index ) const
{
	Qt::ItemFlags flags = QSqlQueryModel::flags(index);
	if( index.column() > 0 && index.column() < 8 )
		flags |= Qt::ItemIsEditable;
	return flags;
}

bool questModel::setData( const QModelIndex &index, const QVariant &value, int )
{
    if (index.column() < 1 || index.column() > 7)
		return false;

	QModelIndex primaryKeyIndex = QSqlQueryModel::index( index.row(), 0 );
	int id = data( primaryKeyIndex ).toInt();
    int toprow = qview->verticalScrollBar()->value();
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
    refresh();
    pwin->UpdateQuestEdit();
    qview->setCurrentIndex( index );
	qview->setFocus();
    qview->verticalScrollBar()->setValue(toprow);
	return ok;
}

void questModel::refresh()
{
	setQuery( *(pwin->GetQuestQuery()) );
	if( query().lastError().isValid() )
		pwin->Err( query().lastError().text() );
	setHeaderData( 2, Qt::Horizontal, tr( "" ) );
	setHeaderData( 3, Qt::Horizontal, tr( "" ) );
	while( canFetchMore() )
		fetchMore();
	qview->resizeRowsToContents();
}

bool questModel::setRef( int qid, const QString ref )
{
	int book, chap, verse, verses;
	QString sql;
	QSqlQuery query;

	if( !pwin->parseRef( ref, &book, &chap, &verse, &verses ) )
	{
		pwin->Err( tr("Reference could not be updated.") );
        return false;
	}
	sql = QString( "UPDATE Questions SET Book=%1,Chapter=%2,Verse=%3,Verses=%4 WHERE QID=%5" )
		.arg(book).arg(chap).arg(verse).arg(verses).arg(qid);
	return query.exec( sql );
}

bool questModel::setType( int qid, const QString &type )
{
	QSqlQuery query;
	QString sql;
    QString qtype=type;
	QSqlQueryModel typeModel;

	typeModel.setQuery( QString("SELECT Questtype, Abbrev FROM Types " )
            .append( "WHERE Abbrev = \'%1\'").arg( qtype ) );
	if( typeModel.lastError().isValid() )
	{
		pwin->Err( typeModel.lastError().text() );
		return false;
	}
	if( typeModel.rowCount() < 1 )
	{
        qtype.replace( 0, 1, qtype.left(1).toUpper() );
        typeModel.setQuery( QString("SELECT Questtype, Abbrev FROM Types " )
                .append( "WHERE Abbrev = \'%1\'").arg( qtype ) );
        if( typeModel.lastError().isValid() )
        {
            pwin->Err( typeModel.lastError().text() );
            return false;
        }
        if( typeModel.rowCount() < 1 )
        {
            typeModel.setQuery( QString("SELECT Questtype, Abbrev FROM Types " )
                    .append( "WHERE Abbrev = \'%1\'").arg( qtype.toLower() ) );
            if( typeModel.lastError().isValid() )
            {
                pwin->Err( typeModel.lastError().text() );
                return false;
            }
            if( typeModel.rowCount() < 1 )
            {
                pwin->Err( QString( "Type %1 unknown." ).arg( type ) );
                return false;
            }
        }
    }
	sql = QString( "UPDATE Questions SET Qtype=\'%1\' WHERE QID=%2" )
			.arg(typeModel.record(0).value("Questtype").toString()).arg(qid);
	return query.exec( sql );
}

bool questModel::setQuality( int qid, const QString &quality )
{
	QSqlQuery query;
	QString sql;
	QSqlQueryModel qualityModel;
	QSqlQueryModel questModel;

	questModel.setQuery( QString( "SELECT Qtype, Quality FROM Questions " )
			.append( "WHERE QID = \'%1\'" ).arg( qid ) );
	if( questModel.lastError().isValid() )
	{
		pwin->Err( questModel.lastError().text() );
		return false;
	}
	if( questModel.rowCount() < 1 )
	{
		pwin->Err( QString( "Question not found: QID = %1. Unable to save." ) );
		return false;
	}
	qualityModel.setQuery( QString( "SELECT Qtype, Quality FROM Quality " )
			.append( "WHERE Qtype = \'%1\' AND Quality = \'%2\'" )
			.arg( questModel.record( 0 ).value( "Qtype" ).toString() )
            .arg( quality.toLower() ) );
	if( qualityModel.lastError().isValid() )
	{
		pwin->Err( qualityModel.lastError().text() );
		return false;
	}
	if( qualityModel.rowCount() < 1 )
	{
        pwin->Err( QString( "Quality %1 unknown." ).arg( quality ) );
        return false;
	}
	else
	{
		sql = QString( "UPDATE Questions SET Quality=\'%1\' WHERE QID=%2" )
                .arg( quality.toLower() ).arg( qid );
		return query.exec( sql );
	}
}

bool questModel::setPreface( int qid, const QString &preface )
{
	QSqlQuery query;
	QString sql;

	sql = QString( "UPDATE Questions SET Preface=\'%1\' WHERE QID=%2" ).arg(preface).arg(qid);
	return query.exec( sql );
}

bool questModel::setQuest( int qid, const QString &quest )
{
	QSqlQuery query;
	QString sql;

	sql = quest;
	sql.replace( tr("'"), tr("''") );
	sql = QString( "UPDATE Questions SET Question=\'%1\' WHERE QID=%2" ).arg(sql).arg(qid);
	return query.exec( sql );
}

bool questModel::setAns( int qid, const QString &ans )
{
	QSqlQuery query;
	QString sql;

	sql = ans;
	sql.replace( tr("'"), tr("''") );
	sql = QString( "UPDATE Questions SET Answer=\'%1\' WHERE QID=%2" ).arg(sql).arg(qid);
	return query.exec( sql );
}

bool questModel::setCR( int qid, const QString &CR )
{
	QSqlQuery query;
	QString sql;

	sql = QString( "UPDATE Questions SET CR=\'%1\' WHERE QID=%2" ).arg(CR).arg(qid);
	return query.exec( sql );
}

bool questModel::insertRow( bool copied )
{
	QSqlQuery query;
	QString sql;
	QModelIndex id, id1, id2, id3, id4;
	int book, chap, verse, verses, qid;
	QString qtype, quality;
	QString qref; 
	bool ok;

	id = qview->currentIndex();
	qid = index(id.row(),0).data().toInt();
	if( copied )
	{
		sql = QString( "INSERT INTO Questions (Book, Chapter, Verse, Qtype, "
			"Quality, Verses, Preface, Question, Answer, CR) "
			"SELECT Book, Chapter, Verse, Qtype, Quality, Verses, Preface, Question, "
			"Answer, CR FROM Questions WHERE QID=%1" ).arg( qid );
	}
	else
	{
		id1 = QSqlQueryModel::index( id.row(), 1 );
		id2 = QSqlQueryModel::index( id.row(), 2 );
		id3 = QSqlQueryModel::index( id.row(), 3 );
		qref = data( id1 ).toString();
		qtype = data( id2 ).toString();
		quality = data( id3 ).toString();
		if( !pwin->parseRef( qref, &book, &chap, &verse, &verses ) )
			pwin->Err( tr( "Illegal reference!" ) );
		sql = QString( "INSERT INTO Questions (Book, Chapter, Verse, Qtype, Quality, Verses, "
		 	"Preface, Question, Answer, CR, Used) "
			"VALUES ( %1, %2, %3, \'%4\', \'%5\', 0, '', '', '', '', 0 )" )
			.arg( book )
			.arg( chap )
			.arg( verse )
			.arg( qtype )
			.arg( quality );
	}
	ok = query.exec( sql );
	if( !ok )
		pwin->Err( query.lastError().text() );

	id = QSqlQueryModel::index( qid=qview->rowAt( 1 ), id.column() );
	refresh();
	qview->scrollTo( id, QAbstractItemView::PositionAtTop );
	return ok;
}

bool questModel::deleteRow()
{
	QSqlQuery query;
	QString sql;
	QModelIndex id;
	int qid;
	bool ok;

	id = qview->currentIndex();
	qid = index(id.row(),0).data().toInt();
	sql = QString( "DELETE FROM Questions WHERE QID=%1" ).arg( qid );
	ok = query.exec( sql );
	if( !ok )
		pwin->Err( query.lastError().text() );
	id = QSqlQueryModel::index( qid=qview->rowAt( 1 ), id.column() );
	refresh();
	qview->scrollTo( id, QAbstractItemView::PositionAtTop );
	return ok;
}

bool questModel::showKey()
{
	QSqlQueryModel kModel, aModel;
	QModelIndex id;
	int vid, numverses, numrows, row;
	static keyView *kView=0;
	QString kQuery, aQuery, keyItem, keyItem2;

	id = qview->currentIndex();
	vid = index(id.row(),10).data().toInt();
	numverses = index(id.row(),11).data().toInt();
	kQuery = QString( "SELECT VID,Word FROM KView WHERE VID>%1 AND VID<%2" )
				.arg(vid-1).arg(vid+numverses+1);
	kModel.setQuery( kQuery );
	if( kModel.lastError().isValid() )
	{
		pwin->Err( kModel.lastError().text() );
		return false;
	}
	aQuery = QString( "SELECT VID,Word,Ref FROM AView WHERE VID>%1 AND VID<%2" )
				.arg(vid-1).arg(vid+numverses+1);
	aModel.setQuery( aQuery );
	if( aModel.lastError().isValid() )
	{
		pwin->Err( aModel.lastError().text() );
		return false;
	}
	numrows = (kModel.rowCount()>aModel.rowCount()?kModel.rowCount():aModel.rowCount());
	if( numrows == 0 )
	{
		pwin->Err( "No Key Words." );
		return false;
	}

	QStandardItemModel *keyModel = new QStandardItemModel();
	if( keyOpen )
	{
		keyModel->clear();
	}
	else
	{
		kView = new keyView( pwin, Qt::Window );
		kView->setMinimumSize( QSize( 250, 100 ) );
	}
	keyModel->setColumnCount( 3 );
	keyModel->setHorizontalHeaderLabels( QStringList() << "Key Word" << "Almost Key" << "Cross Ref" ); 
	for( row=0; row<numrows; row++ )
	{
		if( row < kModel.rowCount() )
			keyItem = kModel.record( row ).value( "Word" ).toString();
		else
			keyItem = QString( "" );
		QStandardItem *item = new QStandardItem( QString(keyItem) );
		keyModel->setItem( row, 0, item );
		if( row < aModel.rowCount() )
		{
			keyItem = aModel.record( row ).value( "Word" ).toString();
			keyItem2 = aModel.record( row ).value( "Ref" ).toString();
		}
		else
		{
			keyItem = QString( "" );
			keyItem2 = QString( "" );
		}
		QStandardItem *item2 = new QStandardItem( QString( keyItem ) );
		keyModel->setItem( row, 1, item2 );
		QStandardItem *item3 = new QStandardItem( QString( keyItem2 ) );
		keyModel->setItem( row, 2, item3 );
	}
	kView->setSearchModel( keyModel );
	keyOpen = true;
	kView->sizeKeyView( numrows );
	kView->show();
	return true;
}
