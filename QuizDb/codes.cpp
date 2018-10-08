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

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QChar>
#include "codes.h"

codes::codes ( QWidget* parent, Qt::WindowFlags fl )
		: QWidget ( parent, fl )
{
    pwin = (MainWindow *)parent;

	setWindowTitle( tr("Quality") );
	box = new QVBoxLayout( this );
	numtypes = buildLayout();
	setLayout( box );
	show();
}

int codes::buildLayout()
{
	int i, j;

	typeModel.setQuery( "SELECT Questtype, Qname, Abbrev FROM Types" );
	if( typeModel.lastError().isValid() )
	{
		Err( typeModel.lastError().text() );
		return( 0 );
	}

	QGridLayout *grid = new QGridLayout;
	box->addLayout( grid );
	for( j=0; j<MAXQUALITYLEVELS; j++ )
	{
		qlbl[j] = new QLabel( QChar( 97+j ) );
		grid->addWidget( qlbl[j], 0, j+1 );
	}

	for( i=0; i<typeModel.rowCount(); i++ )
	{
		qualityModel.setQuery( QString( "SELECT * FROM Quality WHERE " )
			.append( "Qtype=%1 ORDER BY Quality" )
			.arg( typeModel.record(i).value( "Questtype" ).toInt() ) );
		if( qualityModel.lastError().isValid() )
		{
			Err( qualityModel.lastError().text() );
			return( 0 );
		}
		if( qualityModel.rowCount() > MAXQUALITYLEVELS )
		{
			Err( QString( "Too Many Quality Levels: Type = %1." )
				.arg( typeModel.record(i).value( "Questtype" ).toInt() ) );
			return( 0 );
		}

		tlbl[i] = new QLabel( typeModel.record(i).value("Abbrev").toString() );
		grid->addWidget( tlbl[i], i+1, 0 );

		for( j=0; j<qualityModel.rowCount(); j++ )
		{
			cb[i][j] = new QCheckBox;
			grid->addWidget( cb[i][j], i+1, j+1 );
			if( qualityModel.record(j).value("Show").toString()==QString("1") )
				cb[i][j]->setChecked( true );
		}
	}

	QHBoxLayout * h3 = new QHBoxLayout;
	box->addLayout( h3 );
	ok = new QPushButton( "OK", this );
	cancel = new QPushButton( "Cancel", this );
	h3->addWidget( ok );
	h3->addWidget( cancel );
	connect( ok, SIGNAL(clicked()), this, SLOT(OK_clicked()) );
	connect( cancel, SIGNAL(clicked()), this, SLOT(Cancel_clicked()) );
	return( typeModel.rowCount() );
}

void codes::OK_clicked()
{
	int i, j; 
	QSqlQuery query;
	
	for( i=0; i<typeModel.rowCount(); i++ )
	{
		for( j=0; j<MAXQUALITYLEVELS; j++ )
		{
			query.exec( QString( "UPDATE Quality SET Show = %1 WHERE " )
				.append( "Qtype = %2 AND Quality = \'%3\'" )
				.arg( (cb[i][j]->isChecked()?1:0) )
				.arg( typeModel.record(i).value("Questtype").toInt() )
				.arg( QChar( 97+j ) ) );
			if( query.lastError().isValid() )
			{
				Err( query.lastError().text() );
				return;
			}
		}
	}
	close();
}

void codes::Cancel_clicked()
{
	close();
}

void codes::Err( QString msg )
{
	pwin->Err( msg );
}
