/***************************************************************************
 *   Copyright (C) 2007 by Jeff Vogel   *
 *   vogeljh@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDialog>
#include "errmsg.h"
#include "quizsectionclass.h"
//
quizSectionClass::quizSectionClass( int quiznum, int sectionnum, int printformat )
{
	int i;
	QSqlQueryModel qzModel, qModel;
	
	qSCquiznum = quiznum;
	qSCsecnum = sectionnum;
//	Err( QString( "qSCsecnum=%1; sectionnum=%2").arg(qSCsecnum).arg(sectionnum) );
	loadQuizFormat();

	for( i=0; i<qCount; i++ )
        qSCquest[i] = new quizQuestionClass( quiznum, sectionnum, i, printformat );
}

//
quizSectionClass::~quizSectionClass()
{
}
//

void quizSectionClass::Err( QString msg )
{
	errmsg dlg;
	
	dlg.message->setText( msg );
	dlg.exec();
}

quizQuestionClass *quizSectionClass::question( int i )
{
	return( qSCquest[i] );
}

bool quizSectionClass::isBreak()
{
	return( qzBreak );
}

QString quizSectionClass::sectionTitle()
{
	return( secTitle );
}

int quizSectionClass::questCount()
{
	return( qCount );
}

void quizSectionClass::loadQuizFormat()
{
	int i;
	QSqlQueryModel qmodel;
	
	qmodel.setQuery( QString( "SELECT * FROM QuizData WHERE Section = %1" )
			.arg( qSCsecnum+1 ) );
	if( qmodel.lastError().isValid() )
	{
		Err( qmodel.lastError().text() );
		return;
	}
	qzdatarows = qmodel.rowCount();
	for( i=0; i<qzdatarows; i++ )
	{
		key[i] = qmodel.record( i ).value( "key" ).toInt();
		earliest[i] = qmodel.record( i ).value( "earliest" ).toInt();
		latest[i] = qmodel.record( i ).value( "latest" ).toInt();
		fewest[i] = qmodel.record( i ).value( "fewest" ).toInt();
		most[i] = qmodel.record( i ).value( "most" ).toInt();
		qtype[i] = qmodel.record( i ).value( "type" ).toInt();
		quality[i] = qmodel.record( i ).value( "quality" ).toString();
	}
	
	qmodel.setQuery( QString( "SELECT * FROM QuizFormat WHERE ID = %1" )
			.arg( qSCsecnum+1 ) );
	if( qmodel.lastError().isValid() )
	{
		Err( qmodel.lastError().text() );
		return;
	}

	secTitle = qmodel.record( 0 ).value( "Name" ).toString();
	qCount = qmodel.record( 0 ).value( "count" ).toInt();
//	Err( QString( "qCount=%1" ).arg(qCount) );
	gentype = qmodel.record( 0 ).value( "gentype" ).toInt();
	genqual = qmodel.record( 0 ).value( "genqual" ).toString();
	qzBreak = qmodel.record( 0 ).value( "break" ).toBool();
}

bool quizSectionClass::replaceQuestion( int qnum )
{
	QSqlQueryModel qModel;
	QSqlQueryModel qzModel;
	QSqlQuery query;
    int qkey, i, qzquestrows, allowed=0;
	int replaceType;
	QString replaceQuality;
		
	qzModel.setQuery( QString( "SELECT key FROM Quiz WHERE quiznum=%1 AND ")
			.append( "section=%2 AND qnum=%3" ).arg( qSCquiznum )
			.arg( qSCsecnum ).arg( qnum ) );
	if( qzModel.lastError().isValid() )
	{
		Err( qzModel.lastError().text() );
		return false;
	}
	else if( qzModel.rowCount() < 1 )
	{
		Err( QString( "Error replacing quiz %1, section %2, question %3 ")
				.append( "(Cannnot find it!)" ).arg( qSCquiznum+1 )
				.arg( qSCsecnum+1 ).arg( qnum+1 ) );
		return false;
	}
	qkey = qzModel.data( qzModel.index(0,0) ).toInt();

	if( qkey > 0 )
	{
		for( i=0; i<qzdatarows; i++ )
			if( key[i] == qkey )
				break;
		if( i == qzdatarows )
		{
			Err( QString( "key %1 not found." ).arg( qkey ) );
			return false;
		}
		replaceType = qtype[i];
		replaceQuality = quality[i];
	}
	else
	{
		replaceType = gentype;
		replaceQuality = genqual;		
	}

    if( (qzquestrows = quizQuery( replaceType, replaceQuality, &qModel, &allowed )) == 0 )
		return false;
	else
	{
		query.exec( QString( "Delete from Quiz WHERE quiznum=%1 AND " )
				.append( "section=%2 AND qnum=%3" ).arg( qSCquiznum )
				.arg( qSCsecnum ).arg( qnum ) );
        return( ChooseQuest( &qModel, qnum, qzquestrows, qkey, &allowed )
				>= 0 ? true : false );
	}
}

int quizSectionClass::quizQuery( int qtype, QString quality, 
        QSqlQueryModel *qmodel, int *allowed )
{
	int i, j, rows, numtypes;
	QString sql, typelist;
	QSqlQuery query;
	QSqlQueryModel model;
	
	query.exec( QString( "UPDATE Types SET Show=\'0\'" ) );
	query.exec( QString( "UPDATE Quality SET Show=\'0\'" ) );

	model.setQuery( QString( "SELECT COUNT() FROM Types" ) );
	if( model.lastError().isValid() )
	{
		Err( model.lastError().text() );
		return( -1 );
	}
	numtypes = model.record(0).value(0).toInt();

	if( qtype > numtypes )
	{ // This is a composite type (multiple types) defined in QuizTypes table
		model.setQuery( QString( "SELECT TYPES FROM QuizTypes WHERE Qtype = %1" )
				.arg( qtype ) );
		if( model.lastError().isValid() )
        {
			Err( model.lastError().text() );
			return( -1 );
		}
		typelist = model.record(0).value(0).toString();
		
		for( j=0; j<typelist.length(); j++ )
		{
			query.exec( QString( "UPDATE Types SET Show=\'1\' WHERE Questtype = %1" )
				.arg( typelist.mid(j,1).toInt() ) );
			for( i=0; i<quality.length(); i++ )
				query.exec( QString( "UPDATE Quality SET Show=\'1\' WHERE Qtype = %1" )
						.append( " AND Quality = \'%2\'" )
						.arg( typelist.mid(j,1).toInt() )
						.arg( quality.mid(i,1) ) );
		}
	}
    else
	{ //this is a single type
		query.exec( QString( "UPDATE Types SET Show=\'1\' WHERE Questtype = %1" )
			.arg( qtype ) );
		for( i=0; i<quality.length(); i++ )
			query.exec( QString( "UPDATE Quality SET Show=\'1\' WHERE Qtype = %1" )
					.append( " AND Quality = \'%2\'" ).arg( qtype )
					.arg( quality.mid(i,1) ) );
	}

    for(j=*allowed; j<10; j++)
    {
        if( qSCsecnum < 3 )
            qmodel->setQuery( QString( "SELECT QID, VID, Used FROM Quest " )
                .append( "WHERE Used<%1" ).arg(j+1) );
        else
            qmodel->setQuery( QString( "SELECT QID, VID, Used FROM Quest " ) );
        while( qmodel->canFetchMore() )
            qmodel->fetchMore();
        rows = qmodel->rowCount();
        if( rows > 0 )
        {
            *allowed = j;
            break;
        }
    }
    if( rows == 0 )
        Err( QString( "No unused questions of type %1.").arg( typelist ) );
/*
    qmodel->setQuery( QString( "SELECT QID, VID, Used FROM Quest " )
    //        .append( "WHERE Used=0" ) );
            .append( "WHERE Used<%1" ).arg(qSCquiznum+1) );

    while( qmodel->canFetchMore() )
		qmodel->fetchMore();
	rows = qmodel->rowCount();
	if( rows == 0 )
		Err( QString( "No questions of type %1.").arg( typelist ) );
*/

// reset the codes table so all questions are accessible
	query.exec( QString( "UPDATE Types SET Show=\'1\'" ) );
	if( qmodel->lastError().isValid() )
	{
		Err( qmodel->lastError().text() );
		return( -1 );
	}
	query.exec( QString( "UPDATE Quality SET Show=\'1\'" ) );
	if( qmodel->lastError().isValid() )
	{
		Err( qmodel->lastError().text() );
		return( -1 );
	}
	return( rows );
}

int quizSectionClass::ChooseQuest( QSqlQueryModel *qmodel, const int qnum, 
            const int numq, const int key, int *allowed )
{
	int j, rnum;
	QSqlQuery query;
	QSqlQueryModel qzModel;

	for( j=0; j<50; j++ )
	{
		rnum = rand() % numq;
        if( (qmodel->record( rnum ).value( "Used" ).toInt() < (*allowed)+1) || (qSCsecnum == 3) )
        {
//            if( qSCquiznum == 2 )
//                Err( QString( "j: %1; QID %2; Used: %3" ).arg( j )
//                     .arg(qmodel->record( rnum ).value( "QID" ).toInt())
//                     .arg(qmodel->record( rnum ).value( "Used" ).toInt()) );
/* 
 * The commented version only checks that the same verse is not used within the same section of a quiz.
 * The more strict version that follows checks against all previous questions selected for the quiz.
 * This will create a guaranteed problem if a quiz is written on a passage with less verses than the total number of
 * questions in a quiz - typically 40 (20 regular, 10 bonus, 5 overtime, 5 replacement). 
 *
 *			qzModel.setQuery( QString( "SELECT qnum FROM Quiz WHERE quiznum=%1 AND section=%2 AND VID=%3" )
 *						.arg( qznum ).arg( sec ).arg( qmodel->record( rnum ).value( "VID" ).toInt() ) );
 */
			qzModel.setQuery( QString( "SELECT qnum FROM Quiz WHERE " )
                    .append( "quiznum=%1 AND VID=%2" ).arg( qSCquiznum )
					.arg( qmodel->record( rnum ).value( "VID" ).toInt() ) );
			if( qzModel.lastError().isValid() )
			{
				Err( qzModel.lastError().text() );
				return -1;
			}
			if( qzModel.rowCount() == 0 )
				break;
		}
	}
	if( j==50 )
		Err( QString( "Unable to find legal question; quiz %1 section %2 " )
				.append( "question %3.").arg( qSCquiznum+1 ).arg( qSCsecnum+1 )
				.arg( qnum+1 ) );
    if( qSCsecnum < 3 )
        query.exec( QString( "UPDATE Questions SET Used = Used+1 WHERE QID = %1" )
			.arg( qmodel->record( rnum ).value( "QID" ).toInt() ) );
	if( query.lastError().isValid() )
	{
		Err( query.lastError().text() );
	}

	qSCquest[qnum]->setQuestion( qmodel->record( rnum ).value( "QID" ).toInt(),
			key, qmodel->record( rnum ).value( "VID" ).toInt() );
	
    return( rnum );
}

int quizSectionClass::makeSection()
{
	QSqlQueryModel qmodel;
	QSqlQueryModel qzModel;
    int i, j, id, qnum, rnum, qty, qzquestrows, row, allowed;
	QList<int> avlbl, unused;
	
	unused.clear();
	for( i=0; i<qCount; i++ )
		unused << i;
	for( row=0; row<qzdatarows; row++ )
	{
//      qzquestrows = quizQuery( qtype[row], quality[row], &qmodel, &allowed );
//		if( qzquestrows > 0 )
//		{
        if( most[row] > qCount / 7 + 1 )
        {
            Err( QString( "Reduce special questions in section %1." )
                    .arg(qSCsecnum) );
            return( -1 );
        }
        if( most[row] > fewest[row] )
            qty = rand() % (most[row] - fewest[row] + 1) + fewest[row];
        else
            qty = most[row];

        for( allowed=0; allowed<10; allowed++ )
        {
            qzquestrows = quizQuery( qtype[row], quality[row], &qmodel, &allowed );
            if( qzquestrows >= qty )
                break;
        }
        if( allowed == 10 )
        {
            Err( QString( "No usable questions of type %1 found." ).arg(qtype[row]) );
            return( -1 );
        }
            for( i=0; i<qty; i++ )
			{
				if( earliest[row] == latest[row] )
				{ // typical for replacement questions- only 1 question # legal
					avlbl.clear();
					avlbl << latest[row]-1;
				}
				else if( i == 0 )
				{ //set avlbl = all unused questions between earliest and latest
					avlbl = unused;
					for( j=1; j<earliest[row]; j++ )
						if( avlbl.first() < earliest[row]-1 )
							avlbl.removeFirst();
					for( j=qCount; j>latest[row]; j-- )
						if( avlbl.last() > latest[row]-1 )
							avlbl.removeLast();
				}
				else // remove from avlbl last question # selected plus 3 to 
				{	// either side (if not already used)
					while( (id < avlbl.size()) && (avlbl.at( id ) < qnum+4) )
						avlbl.removeAt( id );
					for( j=id-1; j>id-4 && j>=0; j-- )
					{
						if( avlbl.at( j ) > qnum-4 )
							avlbl.removeAt( j );
						else
							break;
					}
				}
				if( avlbl.size() < 1 )
				{ // this should only happen if a bad quiz format is specified.
					Err( QString( "No suitable question spacing: " )
							.append( "quiz %1 section %2 key %3." )
							.arg(qSCquiznum).arg(qSCsecnum).arg(key[row]) );
					return( -1 );
				}
				if( avlbl.size() < 2 ) // only one legal question number; 
										// therefore don't select randomly
					qnum = avlbl.first();
				else
					qnum = avlbl.at( id = rand() % (avlbl.size()) );
				unused.removeAt( unused.indexOf( qnum ) );
                rnum = ChooseQuest( &qmodel, qnum, qzquestrows, key[row], &allowed );
				if( rnum < 0 )
					return( -1 );
/* the following code would ensure previously used questions don't get 
 * re-selected.  But in almost all cases, it ends up costing more time to update
 * the query than to just check and ensure that the selected question was not
 * marked used.  That check takes place inside ChooseQuest.
				qmodel.setQuery( qmodel.query().executedQuery() );					
				if( qmodel.lastError().isValid() )
				{
					Err( qmodel.lastError().text() );
					return;
				}
				qzquestrows = qmodel.rowCount();
*/
			}
//		}
//		else
//		{
//			Err( QString( "No unused questions of type %1." )
//					.arg(key[row]) );
//			return( -1 );
//		}
	}
	/* fill in general questions*/
    qzquestrows = quizQuery( gentype, genqual, &qmodel, &allowed );
	for( i=0; i<unused.size(); i++ )
        if( (rnum = ChooseQuest( &qmodel, unused.at(i), qzquestrows, 0, &allowed )) < 0 )
			return( -1 );

	return( 0 );
}
