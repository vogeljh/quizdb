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
#include "quizclass.h"
//
quizClass::quizClass( int quiznum, int sectioncount, int questcount[], int printformat, QString viewer )
{
	int i, secnum;
//	QSqlQueryModel qzModel, qModel;
	
    qCquiznum = quiznum;
    qCsectioncount = sectioncount;
    for( i=0; i<MAXSECTIONS; i++ )
        qCquestioncount[i] = questcount[i];
    qCprintformat = printformat;
    qCviewer = viewer;
/*
    qzModel.setQuery( QString( "SELECT ID from QuizFormat" ) );
	if( qzModel.lastError().isValid() )
	{
		Err( qzModel.lastError().text() );
		return;
	}
*/

    for( secnum=0; secnum<qCsectioncount; secnum++ )
    {
        qCsection[secnum] = new quizSectionClass( quiznum, secnum, questcount[secnum], printformat );
	}
}

//
quizClass::~quizClass()
{
}
//

void quizClass::Err( QString msg )
{
	errmsg dlg;
	
	dlg.message->setText( msg );
	dlg.exec();
}

quizSectionClass *quizClass::section( int i )
{
	return( qCsection[i] );
}

int quizClass::makeQuiz()
{
	int sec;
	
	srand( time( NULL ) );
	
    for( sec=0; sec<qCsectioncount; sec++ )
		if( qCsection[sec]->makeSection() < 0 )
			return( -1 );

	return( 0 );
}

int quizClass::quizNumber()
{
    return( qCquiznum );
}

int quizClass::sectionCount()
{
    return( qCsectioncount );
}

int quizClass::questionCount(int section )
{
    return( qCquestioncount[section] );
}

void quizClass::setPrintFormat( int format )
{
    qCprintformat = format;
}

int quizClass::getPrintFormat()
{
    return( qCprintformat );
}

void quizClass::setViewer( QString viewer )
{
    qCviewer = viewer;
}

QString quizClass::getViewer()
{
    return( qCviewer );
}
