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

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "types.h"
#include "codes.h"

types::types ( QWidget* parent, Qt::WindowFlags f )
		: QWidget ( parent, f )
{
	int i, numtypes;
	
    pwin = (MainWindow *)parent;
//	numtypes = pwin->TypeCount();
	
	setWindowTitle( tr("Pick Types") );
	typeModel.setQuery( "SELECT Questtype,Qname,Show FROM Types" );
	if( typeModel.lastError().isValid() )
	{
		pwin->Err( typeModel.lastError().text() );
		return;
	}
	numtypes = typeModel.rowCount();

	QVBoxLayout * v = new QVBoxLayout( this );
	for( i=0; i<numtypes; i++ )
	{
		cb[i] = new QCheckBox;
		cb[i]->setText( typeModel.record(i).value("Qname").toString() );
		v->addWidget( cb[i] );
//		if( typeModel.record(i).value("Show").toString()==QString("1") )
		if( typeModel.record(i).value("Show").toString().compare("1") == 0 )
			cb[i]->setChecked( true );
	}

	QHBoxLayout * h1 = new QHBoxLayout;
	v->addLayout( h1 );
	all = new QPushButton( "Select All", this );
	none = new QPushButton( "Unselect All", this );
	h1->addWidget( all );
	h1->addWidget( none );

	editcodes = new QPushButton( "Edit Quality Levels", this );
	v->addWidget( editcodes );

	QHBoxLayout * h2 = new QHBoxLayout;
	v->addLayout( h2 );
	ok = new QPushButton( "OK", this );
	cancel = new QPushButton( "Cancel", this );
	h2->addWidget( ok );
	h2->addWidget( cancel );

	connect( all, SIGNAL(clicked()), this, SLOT(All_clicked()) );
	connect( none, SIGNAL(clicked()), this, SLOT(None_clicked()) );
	connect( editcodes, SIGNAL(clicked()), this, SLOT(EditCodes_clicked()) );
	connect( ok, SIGNAL(clicked()), this, SLOT(OK_clicked()) );
	connect( cancel, SIGNAL(clicked()), this, SLOT(close()) );
}

/*$SPECIALIZATION$*/
void types::OK_clicked()
{
	int i; 
	QSqlQuery query;
	
	for( i=0; i<typeModel.rowCount(); i++ )
		query.exec( QString( "UPDATE Types SET Show = %1 WHERE Questtype = %2" )
			.arg( (cb[i]->isChecked()?1:0) ).arg( typeModel.record(i).value("Questtype").toString() ) );

	typeModel.setQuery( "SELECT Questtype,QName,Show FROM Types" );
	pwin->setSelectionTitle( &typeModel );
	pwin->UpdateQuestEdit();
	close();
}

void types::EditCodes_clicked()
{
	codes *dlg = 0;
	
	dlg = new codes( pwin, Qt::Window );
	dlg->show();
}

void types::All_clicked()
{
	int i;
	
	for( i=0; i<typeModel.rowCount(); i++ )
		cb[i]->setChecked( true );
}

void types::None_clicked()
{
	int i;
	
	for( i=0; i<typeModel.rowCount(); i++ )
		cb[i]->setChecked( false );
}
