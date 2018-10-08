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
#include "mainwindow.h"
#include "errmsg.h"
#include "quizquestionclass.h"
//
quizQuestionClass::quizQuestionClass( int quiznum, int sectionnum, int questionnum, int printformat )
{
	QSqlQueryModel qzModel;
	QSqlQueryModel qModel;
	
	qQCquizID = quiznum;
	qQCsecID = sectionnum;
	qQCquestID = questionnum;
    qQCprintformat = printformat;

	qzModel.setQuery( QString( "SELECT * from Quiz WHERE quiznum=%1 AND ")
			.append("section=%2 AND qnum=%3" )
			.arg(quiznum).arg(sectionnum).arg(questionnum) );
	if( qzModel.lastError().isValid() )
	{
		Err( qzModel.lastError().text() );
		return;
	}

	if( qzModel.rowCount() < 1 )
		qQCqid = qQCvid = qQCkey = -1;
	else
	{
		qQCqid = qzModel.record(0).value("qid").toInt();
		qQCvid = qzModel.record(0).value("vid").toInt();
		qQCkey = qzModel.record(0).value("key").toInt();
	 
		qModel.setQuery( QString( "SELECT * FROM Quest WHERE QID=%1" )
				.arg(qQCqid) );
		if( qModel.lastError().isValid() )
		{
			Err( qModel.lastError().text() );
			return;
		}
	
		quest = new questClass( qModel.record(0) );
        if( qQCprintformat%2 == LATEX )
            quest->setLaTeX( true );
        else
            quest->setLaTeX( false );
        if( qQCprintformat / HIGHLIGHT )
            quest->setHighlight( true );
        else
            quest->setHighlight( false );
        quest->shiftFtv( true );
	}
//		setQuestion( qzModel.record(0).value("qid").toInt(),
//				qQCvid = qzModel.record(0).value("vid").toInt(),
//				qQCkey = qzModel.record(0).value("key").toInt() );

}

//
quizQuestionClass::~quizQuestionClass()
{
}
//

void quizQuestionClass::setQuestion( int qid, int key, int vid )
{
	QSqlQueryModel qModel;
	QSqlQueryModel qzModel;
	QSqlQuery query;
	
	qQCqid = qid;
	qQCvid = vid;
	qQCkey = key;
 
 	qzModel.setQuery( QString( "SELECT * FROM Quiz WHERE " )
					.append( "qnum=%1 AND section=%2 and quiznum=%3" )
					.arg(qQCquestID).arg(qQCsecID).arg(qQCquizID) );
	if( qzModel.lastError().isValid() )
	{
		Err( qzModel.lastError().text() );
		return;
	}

	if( qzModel.rowCount() > 0 )
	{
		query.exec( QString( "DELETE FROM Quiz WHERE " )
					.append( "qnum=%1 AND section=%2 and quiznum=%3" )
					.arg(qQCquestID).arg(qQCsecID).arg(qQCquizID) );
		
		if( query.lastError().isValid() )
		{
			Err( query.lastError().text() );
		}
	}
		
	query.exec( QString( "INSERT INTO Quiz VALUES (%1, %2, %3, %4, %5, %6)" )
			.arg( qQCquizID ).arg( qQCsecID ).arg( qQCquestID )
			.arg( qid ).arg( key ).arg( vid ) );
	if( query.lastError().isValid() )
	{
		Err( query.lastError().text() );
	}
	
	qModel.setQuery( QString( "SELECT * FROM Quest WHERE QID=%1" ).arg(qid) );
	if( qModel.lastError().isValid() )
	{
		Err( qModel.lastError().text() );
		return;
	}

	quest = new questClass( qModel.record(0) );
    if( qQCprintformat%2 == LATEX )
        quest->setLaTeX( true );
    else
        quest->setLaTeX( false );
    if( qQCprintformat / HIGHLIGHT )
        quest->setHighlight( true );
    else
        quest->setHighlight( false );
//	quest->setLaTeX( true );
	quest->shiftFtv( true );
}

int quizQuestionClass::verseIndex()
{
	return( quest->verseIndex() );
}

QString quizQuestionClass::bookAbbrev()
{
	return( quest->bookAbbrev() );
}

QString quizQuestionClass::bookChapter()
{
	return( quest->bookChapter() );
}

int quizQuestionClass::chapter()
{
	return( quest->chapter() );
}

int quizQuestionClass::verse()
{
	return( quest->verse() );
}

int quizQuestionClass::numVerses()
{
	return( quest->numVerses() );
}

int quizQuestionClass::questCode()
{
	return( quest->questCode() );
}

QString quizQuestionClass::preface()
{
	return( quest->preface() );
}

QString quizQuestionClass::question()
{
	return( quest->question() );
}

QString quizQuestionClass::answer()
{
	return( quest->answer() );
}

QString quizQuestionClass::crossRef()
{
	return( quest->crossRef() );
}

int quizQuestionClass::used()
{
	return( quest->used() );
}

QString quizQuestionClass::reference()
{
	return( quest->reference() );
}

void quizQuestionClass::showQuestion( bool flag )
{
	quest->showQuestion( flag );
}

void quizQuestionClass::showAnswer( bool flag )
{
	quest->showAnswer( flag );
}

void quizQuestionClass::setLaTeX( bool flag )
{
    quest->setLaTeX( flag );
}

void quizQuestionClass::setHighlight( bool flag )
{
    quest->setHighlight( flag );
}

void quizQuestionClass::showKeyWords( bool flag )
{
	quest->showKeyWords( flag );
}

void quizQuestionClass::showPreface( bool flag )
{
	quest->showPreface( flag );
}

void quizQuestionClass::shiftFtv( bool flag )
{
	quest->shiftFtv( flag );
}

bool quizQuestionClass::isRefq()
{
	return( quest->isRefq() );
}

bool quizQuestionClass::isSitq()
{
	return( quest->isSitq() );
}

bool quizQuestionClass::isFtvq()
{
	return( quest->isFtvq() );
}

QString quizQuestionClass::formatted( int number )
{
    return( quest->formatted( number ) );
}

int quizQuestionClass::quiznum()
{
	return( qQCquizID );
}

int quizQuestionClass::secnum()
{
	return( qQCsecID );
}

int quizQuestionClass::questnum()
{
	return( qQCquestID );
}

int quizQuestionClass::qid()
{
	return( qQCqid );
}

int quizQuestionClass::vid()
{
	return( qQCvid );
}

int quizQuestionClass::key()
{
	return( qQCkey );
}

void quizQuestionClass::Err( QString msg )
{
	errmsg dlg;
	
	dlg.message->setText( msg );
	dlg.exec();
}
