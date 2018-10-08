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

#include <QGridLayout>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlRecord>
#include "quizedit.h"
//#include "quizform.h"

quizedit::quizedit ( QWidget* parent, Qt::WindowFlags fl )
		: QWidget ( parent, fl )
{
	int i;
	
	setWindowTitle( tr("Quiz Sections") );
//	pwin = (MainWindowImpl*)parent; 
	pwin = (quiz*)parent; 
	quizFormat.setQuery( QString( "SELECT * FROM QuizFormat ORDER BY ID" ) );
	if( quizFormat.lastError().isValid() )
	{
		pwin->Err( quizFormat.lastError().text() );
		return;
	}
	numsections = quizFormat.rowCount();
	quizData.setQuery( QString( "SELECT * FROM QuizData ORDER BY Section, Key" ) );
	if( quizData.lastError().isValid() )
	{
		pwin->Err( quizData.lastError().text() );
		return;
	}

	QVBoxLayout * v0 = new QVBoxLayout;
	setLayout( v0 );
	tabWidget = new QTabWidget;
	v0->addWidget( tabWidget );

	for( i=0; i<numsections; i++ )
	{
		sectionWidget[i] = new QWidget;		
		tabWidget->addTab( sectionWidget[i], 
				quizFormat.record( i ).value( "Name" ).toString() );
		sectionEditTab( i );
	}
	
	v0->addSpacing( 5 );
	QHBoxLayout * h2 = new QHBoxLayout;
	v0->addLayout( h2 );
	ok = new QPushButton( "Apply Changes" );
	cancel = new QPushButton( "Cancel" );
	h2->addWidget( ok );
	h2->addSpacing( 20 );
	h2->addWidget( cancel );

	connect( AddRow[0], SIGNAL(clicked()), this, SLOT(AddRow0_clicked()) );
	connect( AddRow[1], SIGNAL(clicked()), this, SLOT(AddRow1_clicked()) );
	connect( AddRow[2], SIGNAL(clicked()), this, SLOT(AddRow2_clicked()) );
	connect( AddRow[3], SIGNAL(clicked()), this, SLOT(AddRow3_clicked()) );
	connect( cancel, SIGNAL(clicked()), this, SLOT(close()) );
	connect( ok, SIGNAL(clicked()), this, SLOT(OK_clicked()) );
}

void quizedit::sectionEditTab( int sec )
{
	int i, j, k, qmax;
	QSqlQueryModel typeModel, quiztypeModel;

	QVBoxLayout * v1 = new QVBoxLayout;
	QGridLayout * g1 = new QGridLayout;
	v1->addLayout( g1 );
	QLabel * l1 = new QLabel( "Seq." );
	g1->addWidget( l1, 0, 0 );
	QLabel * l2 = new QLabel( "Name" );
	g1->addWidget( l2, 0, 1 );
	QLabel * l3 = new QLabel( "#" );
	g1->addWidget( l3, 0, 2 );
	QLabel * l4 = new QLabel( "Gen Type" );
	g1->addWidget( l4, 0, 3 );
	QLabel * l5 = new QLabel( "Gen Qual" );
	g1->addWidget( l5, 0, 4 );
	QLabel * l6 = new QLabel( "Page" );
	g1->addWidget( l6, 0, 5 );
	Sequence[sec] = new QSpinBox;
	Sequence[sec]->setRange( 1, quizFormat.rowCount() );
	Sequence[sec]->setValue( sec+1 );
	g1->addWidget( Sequence[sec], 1, 0 );
	SecName[sec] = new QLineEdit( quizFormat.record( sec ).value( "Name" ).toString() );
	g1->addWidget( SecName[sec], 1, 1 );
	qcount[sec] = new QSpinBox;
	qcount[sec]->setRange( 1, 25 );
	qcount[sec]->setValue( quizFormat.record( sec ).value( "count" ).toInt() );
	g1->addWidget( qcount[sec], 1, 2 );
	GenType[sec] = new QComboBox;
	typeModel.setQuery( "Select Questtype, Qname from Types" );
	if( typeModel.lastError().isValid() )
	{
		pwin->Err( typeModel.lastError().text() );
		return;
	}
	for( i=0; i<typeModel.rowCount(); i++ )
		GenType[sec]->insertItem( i, typeModel.record(i).value("Qname").toString() );
	quiztypeModel.setQuery( "Select Qtype, Qname from QuizTypes" );
	if( quiztypeModel.lastError().isValid() )
	{
		pwin->Err( quiztypeModel.lastError().text() );
		return;
	}
	for( j=0; j<quiztypeModel.rowCount(); i++, j++ )
		GenType[sec]->insertItem( i, quiztypeModel.record(j).value("Qname").toString() );

//	GenType[sec] = new QSpinBox;
//	GenType[sec]->setRange( 1, 12 );
//	GenType[sec]->setValue( i=quizFormat.record( sec ).value( "gentype" ).toInt() );
	g1->addWidget( GenType[sec], 1, 3 );
	GenQual[sec] = new QLineEdit( quizFormat.record( sec ).value( "genqual" ).toString() );
	g1->addWidget( GenQual[sec], 1, 4 );
	SecBreak[sec] = new QCheckBox( "New" );
	if( quizFormat.record( sec ).value( "break" ).toInt() == 1 )
		SecBreak[sec]->setChecked( true );
	g1->addWidget( SecBreak[sec], 1, 5 );
	
	for( row0=0; row0<quizData.rowCount(); row0++ )
		if( quizData.record( row0 ).value( "Section" ).toInt() == sec+1 )
			break;
	for( row1=row0; row1<quizData.rowCount(); row1++ )
		if( quizData.record( row1 ).value( "Section" ).toInt() > sec+1 )
			break;
	sectionRowCount[sec] = row1-row0;

	v1->addSpacing( 5 );
	QGridLayout * g2 = new QGridLayout;
	v1->addLayout( g2 );
	QLabel * l20 = new QLabel( "Del" );
	g2->addWidget( l20, 0, 0 );
	QLabel * l21 = new QLabel( "1st" );
	g2->addWidget( l21, 0, 1 );
	QLabel * l22 = new QLabel( "last" );
	g2->addWidget( l22, 0, 2 );
	QLabel * l23 = new QLabel( "min" );
	g2->addWidget( l23, 0, 3 );
	QLabel * l24 = new QLabel( "max" );
	g2->addWidget( l24, 0, 4 );
	QLabel * l25 = new QLabel( "type" );
	g2->addWidget( l25, 0, 5 );
	QLabel * l26 = new QLabel( "quality" );
	g2->addWidget( l26, 0, 6 );
	for( qmax=quizFormat.record( sec ).value( "count" ).toInt(), 
		i=0; i<sectionRowCount[sec]+1; i++ )
	{
		delrow[sec][i] = new QCheckBox( "" );
		delrow[sec][i]->setChecked( false );
		g2->addWidget( delrow[sec][i], i+1, 0 );
		earliest[sec][i] = new QSpinBox;
		earliest[sec][i]->setRange( 1, qmax );
		g2->addWidget( earliest[sec][i], i+1, 1 );
		latest[sec][i] = new QSpinBox;
		latest[sec][i]->setRange( 1, qmax );
		g2->addWidget( latest[sec][i], i+1, 2 );
		fewest[sec][i] = new QSpinBox;
		fewest[sec][i]->setRange( 0, qmax );
		g2->addWidget( fewest[sec][i], i+1, 3 );
		most[sec][i] = new QSpinBox;
		most[sec][i]->setRange( 0, qmax );
		g2->addWidget( most[sec][i], i+1, 4 );
//		type[sec][i] = new QSpinBox;
//		type[sec][i]->setRange( 1, 12 ); // need to get max value from QuizTypes
		type[sec][i] = new QComboBox;
		for( j=0; j<typeModel.rowCount(); j++ )
			type[sec][i]->insertItem( j, typeModel.record(j).value("Qname").toString() );
		for( k=0; k<quiztypeModel.rowCount(); j++, k++ )
			type[sec][i]->insertItem( j, quiztypeModel.record(k).value("Qname").toString() );
		g2->addWidget( type[sec][i], i+1, 5 );
		if( i == sectionRowCount[sec] )
		{
			delrow[sec][i]->hide();
			earliest[sec][i]->setValue( 1 );
			earliest[sec][i]->hide();
			latest[sec][i]->setValue( qmax );
			latest[sec][i]->hide();
			fewest[sec][i]->setValue( 0 );
			fewest[sec][i]->hide();
			most[sec][i]->setValue( 3 );
			most[sec][i]->hide();
			type[sec][i]->setCurrentIndex( 0 );
			type[sec][i]->hide();
			quality[sec][i] = new QLineEdit( "a" );
			quality[sec][i]->hide();
		}
		else
		{
			earliest[sec][i]->setValue( quizData.record( row0+i )
				.value( "earliest" ).toInt() );
			latest[sec][i]->setValue( quizData.record( row0+i )
				.value( "latest" ).toInt() );
			fewest[sec][i]->setValue( quizData.record( row0+i )
				.value( "fewest" ).toInt() );
			most[sec][i]->setValue( quizData.record( row0+i )
				.value( "most" ).toInt() );
			type[sec][i]->setCurrentIndex( quizData.record( row0+i )
				.value( "type" ).toInt()-1 );
			quality[sec][i] = new QLineEdit( quizData.record( row0+i )
				.value( "quality" ).toString(), this );
		}
		g2->addWidget( quality[sec][i], i+1, 6 );
	}
	
	v1->addSpacing( 5 );
	QHBoxLayout * h1 = new QHBoxLayout;
	v1->addLayout( h1 );
	AddRow[sec] = new QPushButton( "Add Row" );
	h1->addWidget( AddRow[sec] );
	sectionWidget[sec]->setLayout( v1 );
}

/*$SPECIALIZATION$*/
void quizedit::AddSection_clicked()
{
}

void quizedit::DeleteSection_clicked()
{
}

void quizedit::OK_clicked()
{
	int sec;
	QSqlQuery query;
		
	query.exec( QString( "BEGIN" ) );
	if( query.lastError().isValid() )
	{
		pwin->Err( query.lastError().text() );
		return;
	}

	for( sec=0; sec<numsections; sec++ )
	{
		if( updateQuizFormat( sec ) < 0 )
			return;
	}
	
	query.exec( QString( "COMMIT" ) );
	if( query.lastError().isValid() )
	{
		pwin->Err( query.lastError().text() );
		query.exec( QString( "ROLLBACK" ) );
		return;
	}
//	pwin->LoadQuizData();
	close();
}

int quizedit::updateQuizFormat( int section )
{
	int i, newsec;
	QSqlQuery query;
	
	query.exec( QString( "DELETE FROM QuizFormat WHERE ID=%1" ).arg( section+1 ) );
	if( query.lastError().isValid() )
	{
		pwin->Err( query.lastError().text() );
		query.exec( QString( "ROLLBACK" ) );
		return( -1 );
	}

	if( (newsec = Sequence[section]->value()-1) < section )
	{
		for( i=section; i>newsec; i-- )
		{
			query.exec( QString( "UPDATE QuizFormat SET ID = %1 WHERE ID = %2" ).arg( i+1 ).arg( i ) );
			if( query.lastError().isValid() )
			{
				pwin->Err( query.lastError().text() );
				query.exec( QString( "ROLLBACK" ) );
				return( -1 );
			}
		}
	}
	else if( newsec > section )
	{
		for( i=section; i<newsec; i++ )
		{
			query.exec( QString( "UPDATE QuizFormat SET ID = %1 WHERE ID = %2" ).arg( i+1 ).arg( i+2 ) );
			if( query.lastError().isValid() )
			{
				pwin->Err( query.lastError().text() );
				query.exec( QString( "ROLLBACK" ) );
				return( -1 );
			}
			query.clear();
		}
	}
	
	query.exec( QString( "INSERT INTO QuizFormat VALUES (%1, \'%2\', %3, %4, \'%5\', %6)" )
		.arg( newsec+1 ).arg( SecName[section]->text() )
		.arg( qcount[section]->value() ).arg( GenType[section]->currentIndex()+1 )
		.arg( GenQual[section]->text() ).arg( (SecBreak[section]->isChecked()?1:0) ) );
	if( query.lastError().isValid() )
	{
		pwin->Err( query.lastError().text() );
		query.exec( QString( "ROLLBACK" ) );
		return( -1 );
	}
	query.clear();
	
	query.exec( QString( "DELETE FROM QuizData WHERE Section=%1" ).arg( section+1 ) );
	if( query.lastError().isValid() )
	{
		pwin->Err( query.lastError().text() );
		query.exec( QString( "ROLLBACK" ) );
		return( -1 );
	}
	query.clear();

	for( i=0; i<sectionRowCount[section]; i++ )
	{
		if( !delrow[section][i]->isChecked() )
		{
			query.exec( 
				QString( "INSERT INTO QuizData (Section, earliest, latest, " )
				.append( "fewest, most, type, quality) VALUES " )
				.append( "(%1, %2, %3, %4, %5, %6, '%7')" )
				.arg( section+1 ).arg( earliest[section][i]->value() )
				.arg( latest[section][i]->value() )
				.arg( fewest[section][i]->value() )
				.arg( most[section][i]->value() )
				.arg( type[section][i]->currentIndex()+1 )
				.arg( quality[section][i]->text() ) );
			if( query.lastError().isValid() )
			{
				pwin->Err( query.lastError().text() );
				query.exec( QString( "ROLLBACK" ) );
				return( -1 );
			}
			query.clear();
		}
	}

	return( 0 );
}

void quizedit::AddRow0_clicked()
{
	AddNewRow( 0 );
}

void quizedit::AddRow1_clicked()
{
	AddNewRow( 1 );
}

void quizedit::AddRow2_clicked()
{
	AddNewRow( 2 );
}

void quizedit::AddRow3_clicked()
{
	AddNewRow( 3 );
}

void quizedit::AddNewRow( int tab )
{
	delrow[tab][sectionRowCount[tab]]->show();
	earliest[tab][sectionRowCount[tab]]->show();
	latest[tab][sectionRowCount[tab]]->show();
	fewest[tab][sectionRowCount[tab]]->show();
	most[tab][sectionRowCount[tab]]->show();
	type[tab][sectionRowCount[tab]]->show();
	quality[tab][sectionRowCount[tab]]->show();
	sectionRowCount[tab]++;
	AddRow[tab]->hide();
}

void quizedit::Err( QString msg )
{
	pwin->Err( msg );
}
