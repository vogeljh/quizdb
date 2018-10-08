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
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include "quizload.h"
#include "quizreview.h"

quizload::quizload ( QWidget* parent, Qt::WindowFlags fl, QSqlQueryModel *tables )
		: QWidget ( parent, fl )
{
	int i;
	
	setWindowTitle( tr("Saved Quizzes") );
    pwin = (MainWindow*)parent;
	quizcount = tables->rowCount();
	
	if( quizcount > MAXSAVEDQUIZZES )
	{
		Err( tr("Max saved quizes exceeded!") );
		quizcount = MAXSAVEDQUIZZES;
	}
	QVBoxLayout *mainbox = new QVBoxLayout;
	QGroupBox *groupBox = new QGroupBox(tr("Select Quiz to Load"));
	QVBoxLayout *vbox = new QVBoxLayout;
    QGroupBox *format = new QGroupBox(tr("Print Format"));
    QHBoxLayout *formatbox = new QHBoxLayout;

	for( i=0; i<quizcount; i++ )
	{
		cb[i] = new QRadioButton( tables->record(i).value("name").toString() );
		vbox->addWidget( cb[i] );
	}

	cb[0]->setChecked(true);
	vbox->addStretch(1);
	groupBox->setLayout(vbox);

	mainbox->addWidget( groupBox );
	mainbox->addSpacing( 5 );

    LaTeXbutton = new QRadioButton( "LaTeX" );
    RTFbutton = new QRadioButton( "RTF" );
    formatbox->addWidget( LaTeXbutton );
    formatbox->addWidget( RTFbutton );
    format->setLayout( formatbox );
    mainbox->addWidget( format );
    mainbox->addSpacing( 5 );

    QHBoxLayout * hbox = new QHBoxLayout;
	mainbox->addLayout( hbox );
	ok = new QPushButton( "Load" );
	cancel = new QPushButton( "Cancel" );
	hbox->addWidget( ok );
	hbox->addSpacing( 20 );
	hbox->addWidget( cancel );

	setLayout( mainbox );

	connect( cancel, SIGNAL(clicked()), this, SLOT(cancel_clicked()) );
	connect( ok, SIGNAL(clicked()), this, SLOT(OK_clicked()) );
}

/*$SPECIALIZATION$*/
void quizload::OK_clicked()
{
    int i, numquizzes, quiznum, printformat;
	QSqlQuery quizQuery;
	QSqlQueryModel quizModel;
	quizreview *dlgreview = 0;

	for( i=0; i<quizcount; i++ )
		if( cb[i]->isChecked() )
			break;	

    quizQuery.exec( QString( "DELETE FROM Quiz" ) );
	if( quizQuery.lastError().isValid() )
		pwin->Err( quizQuery.lastError().text() );
	else
	{
        printformat = (LaTeXbutton->isChecked() ? LATEX : RTF );
		quizQuery.exec( QString( "INSERT INTO Quiz SELECT * FROM \'%1\'" )
				.arg( cb[i]->text() ) );
		if( quizQuery.lastError().isValid() )
			pwin->Err( quizQuery.lastError().text() );
		else
		{
			quizModel.setQuery( QString( "SELECT * FROM Quiz ORDER BY quiznum" ) );
			while( quizModel.canFetchMore() )
				quizModel.fetchMore();

			if( quizModel.lastError().isValid() )
			{
				Err( quizModel.lastError().text() );
				return;
			}
            numquizzes = quizModel.record(quizModel.rowCount()-1)
                    .value("quiznum").toInt()+1;

            saveTypeModel.setQuery( QString( "SELECT Questtype, Show FROM Types" ) );
			if( saveTypeModel.lastError().isValid() )
			{
				pwin->Err( saveTypeModel.lastError().text() );
				pwin->Err( "Fatal error making quizzes!" );
				close();
				return;
			}
			saveQualityModel.setQuery( QString( "SELECT Qtype, Quality, Show FROM Quality" ) );
			if( saveQualityModel.lastError().isValid() )
			{
				pwin->Err( saveQualityModel.lastError().text() );
				pwin->Err( "Fatal error making quizzes!" );
				close();
				return;
			}
			quizQuery.exec( QString( "UPDATE Types SET Show=\'1\'" ) );
			quizQuery.exec( QString( "UPDATE Quality SET Show=\'1\'" ) );
			loaded = true;

            for( quiznum=0; quiznum<numquizzes; quiznum++ )
                qCquiz[quiznum] = new quizClass( quiznum, printformat,
                                                 pwin->getViewer( printformat) );

            dlgreview = new quizreview( qCquiz, numquizzes, pwin, Qt::Window,
						pwin->GetdbFiledialog() );
            dlgreview->show();
		}
	}
	cancel->setText( QString( "Done" ) );
	ok->hide();
//	close();
}

void quizload::cancel_clicked()
{
	int i;
	QSqlQuery query;

	if( loaded )
	{
		for( i=0; i<saveTypeModel.rowCount(); i++ )
			query.exec( 
				QString( "UPDATE Types SET Show=\'%1\' WHERE Questtype=%2" )
				.arg( saveTypeModel.record(i).value( "Show" ).toInt() )
				.arg( saveTypeModel.record(i).value( "Questtype" ).toInt() ) );
		for( i=0; i<saveQualityModel.rowCount(); i++ )
			query.exec( QString( "UPDATE Quality SET Show=\'%1\' WHERE Qtype=%2 " )
				.append( "AND Quality=\'%3\'" )
				.arg( saveQualityModel.record(i).value( "Show" ).toInt() )
				.arg( saveQualityModel.record(i).value( "Qtype" ).toInt() )
				.arg( saveQualityModel.record(i).value( "Quality" ).toString() ) );
	}
	close();
}

void quizload::Err( QString msg )
{
	pwin->Err( msg );
}
