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
#include <QSqlRecord>
#include <QSqlError>
#include <QDate>
#include <QTextStream>
#include <QProcess>
#include <QStringList>
#include <QFile>
#include "quizview.h"
#include "quizreview.h"
#include "errmsg.h"
#include "questclass.h"

quizreview::quizreview ( quizClass *quizzes[], int numquizzes, QWidget* parent, 
                Qt::WindowFlags fl, QString qzpath )
		: QWidget ( parent, fl )
{
	int i;
	QSqlQueryModel quizmodel;
	
    setWindowTitle( tr("Review Quizzes") );
    filename = qzpath;
    reviewQuiz = quizzes;
	quizCount = numquizzes;
	
	QVBoxLayout *mainbox = new QVBoxLayout;
	QGroupBox *groupBox = new QGroupBox(tr("Select Quiz to Review"));
	QVBoxLayout *vbox = new QVBoxLayout;

	for( i=0; i<quizCount; i++ )
	{
		cb[i] = new QRadioButton( QString( "Quiz #%1" ).arg(i+1) );
		vbox->addWidget( cb[i] );
	}

	cb[0]->setChecked(true);
	vbox->addStretch(1);
	groupBox->setLayout(vbox);

	save = new QPushButton( "Save" );
	done = new QPushButton( "Done" );
	review = new QPushButton( "Review" );
	cancel = new QPushButton( "Cancel" );

	mainbox->addWidget( groupBox );
	mainbox->addSpacing( 5 );
	QHBoxLayout * hbox = new QHBoxLayout;
	mainbox->addLayout( hbox );
	hbox->addWidget( review );
	hbox->addSpacing( 20 );
	hbox->addWidget( save );
	QHBoxLayout * hbox2 = new QHBoxLayout;
	mainbox->addLayout( hbox2 );
	hbox2->addWidget( done );
	hbox2->addSpacing( 5 );
	hbox2->addWidget( cancel );

	setLayout( mainbox );

	connect( cancel, SIGNAL(clicked()), this, SLOT(close()) );
	connect( review, SIGNAL(clicked()), this, SLOT(review_clicked()) );
	connect( done, SIGNAL(clicked()), this, SLOT(done_clicked()) );
	connect( save, SIGNAL(clicked()), this, SLOT(save_clicked()) );
}

/*$SPECIALIZATION$*/
void quizreview::review_clicked()
{
	quizview *qwin = 0;
	int i;

	for( i=0; i<quizCount; i++ )
		if( cb[i]->isChecked() )
			break;	

    qwin = new quizview( reviewQuiz[i], this, Qt::Window );
	qwin->show();
}

void quizreview::done_clicked()
{
    close();
    if( reviewQuiz[0]->getPrintFormat()%2 == LATEX )
        printLaTeXQuizzes();
    else
        printRTFQuizzes();
}

void quizreview::save_clicked()
{
	QSqlQuery saveQuery;
	QSqlQueryModel tableNameModel;

	QDate date = QDate::currentDate();

	tableNameModel.setQuery( QString("SELECT name FROM sqlite_master WHERE " )
			.append( "type=\'table\' AND name=\'Qz%1'" ).arg(date.toString()) );
	if( tableNameModel.lastError().isValid() )
	{
		Err( tableNameModel.lastError().text() );
		return;
	}
	if( tableNameModel.rowCount() < 1 )
	{
		saveQuery.exec( QString( "CREATE TABLE \'Qz%1\' AS " )
				.append( "SELECT * FROM Quiz" ).arg(date.toString()) );
	}
	else
	{
		saveQuery.exec( QString( "DELETE FROM \'Qz%1\'" )
				.arg(date.toString() ) );
		saveQuery.exec( QString( "INSERT INTO \'Qz%1\' SELECT * FROM Quiz" )
				.arg(date.toString() ) );
	}
	if( saveQuery.lastError().isValid() )
	{
		Err( saveQuery.lastError().text() );
		return;
	}
	Err( QString( "Saved as Qz%1." ).arg( date.toString() ) );
}

void quizreview::printLaTeXQuizzes()
{
	int section, questnum, quiznum;
	QString pathname;
	QString sql;
	QSqlQuery query;
	QSqlQueryModel qzmodel;
	QString program;
	QStringList arguments;
	QProcess *pdflatex;
	QProcess *pdf;

	pathname = filename;
	filename.append( QString( "/quiz.tex" ) );
	QFile file( filename );
	if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
	{
		Err( QString( "Can't open %1 for writing" ).arg( filename ) );
		return;
	}
	QTextStream out( &file );

	out << "\\documentclass{article}\n";
	out << "\\usepackage{quiz}\n";
	out << "\\begin{document}\n";
	
	for( quiznum=0; quiznum<quizCount; quiznum++ )
	{
		out << "\\quiz{Quiz \\#" << quiznum+1 << "}\n";
		for( section=0; section<reviewQuiz[quiznum]->sectionCount(); section++ )
		{
			if( section )
			{
				if( section < reviewQuiz[quiznum]->sectionCount() && 
						reviewQuiz[quiznum]->section(section)->isBreak() )
					out << "\\pagebreak\n";
				out << "\\subsubsection*{Quiz \\#" << quiznum+1 << " " << 
						reviewQuiz[quiznum]->section(section)->sectionTitle() << 
						" Questions}\n";
			}
			out << "\\begin{qnumlist}\n";

			for( questnum=0; questnum<reviewQuiz[quiznum]->section(section)->
						questCount(); questnum++ )
			{
				out << reviewQuiz[quiznum]->section(section)->
						question(questnum)->formatted();
			}

			out << "\\end{qnumlist}\n";
		}
	}
	
	out << "\\end{document}\n";
	file.close();
	pdflatex = new QProcess( this );
	pdflatex->setWorkingDirectory( pathname );
	program = QString( "pdflatex" );
	arguments.clear();
	arguments << QString( "quiz" );
	pdflatex->start( program, arguments );
	if( !pdflatex->waitForFinished( 5000 ) )
	{
		Err( pdflatex->errorString() );
 		return;
	}
	pdf = new QProcess( this );
	pdf->setWorkingDirectory( pathname );
//	program = QString( "okular" );
    program = reviewQuiz[0]->getViewer();
	arguments.clear();
	arguments << QString( "quiz.pdf" );
	pdf->start( program, arguments );
// reset types and codes to default view
/*
	for( i=0; i<saveTypeModel.rowCount(); i++ )
		query.exec( 
			QString( "UPDATE Types SET Show=\'%1\' WHERE Questtype=%2" )
			.arg( saveTypeModel.record(i).value( "Show" ).toInt() )
			.arg( saveTypeModel.record(i).value( "Questtype" ).toInt() ) );
	for( i=0; i<saveQualityModel.rowCount(); i++ )
		query.exec( 
			QString( "UPDATE Quality SET Show=\'%1\' WHERE Qtype=%2 AND Quality=\'%3\'" )
			.arg( saveQualityModel.record(i).value( "Qtype" ).toInt() )
			.arg( saveQualityModel.record(i).value( "Quality" ).toInt() )
			.arg( saveQualityModel.record(i).value( "Code" ).toString() ) );
*/
}

void quizreview::printRTFQuizzes()
{
    int section, questnum, quiznum;
    QString pathname;
    QString sql;
    QSqlQuery query;
    QSqlQueryModel qzmodel;
    QString program;
    QStringList arguments;
    QProcess *rtf;

    pathname = filename;
    filename.append( QString( "/quiz.rtf" ) );
    QFile file( filename );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        Err( QString( "Can't open %1 for writing" ).arg( filename ) );
        return;
    }
    QTextStream out( &file );

    out << "{\\rtf1\\ansi\\deff0 {\\fonttbl {\\f0\\froman Nimbus Roman No9 L;}}\n";
    out << "\\margl720\\margr720\\margt720\\margb720\n";

    for( quiznum=0; quiznum<quizCount; quiznum++ )
    {
//        out << "\\fs32 Quiz \\#" << quiznum+1 << "\\par\\sa0\\keepn\n";
        out << "\\par \\par \\pard\\plain\n";
        out << "\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}";
        out << "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24";
        out << "\\alang1025\\loch\\f0\\fs24\\lang1033";
        if( quiznum > 0 )
            out << "\\pagebb";
        out << "\\nowidctlpar\\tx285{\\dbch\\af2\\rtlch ";
        out << "\\ltrch\\loch\\fs20\\loch\\f2\n\\tab }";
        out << "{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\nQuiz \\#";
        out << quiznum+1 << "}\n";
        for( section=0; section<reviewQuiz[quiznum]->sectionCount(); section++ )
        {
            if( section )
            {
                out << "\\par \\par \\pard\\plain\n";
                out << "\\s0\\ql\\widctlpar{\\*\\hyphen2\\hyphlead2\\hyphtrail2\\hyphmax0}";
                out << "\\ltrpar\\cf0\\hich\\af0\\langfe2052\\dbch\\af0\\afs24";
                out << "\\alang1025\\loch\\f0\\fs24\\lang1033";
                if( section < reviewQuiz[quiznum]->sectionCount() &&
                        reviewQuiz[quiznum]->section(section)->isBreak() )
                    out << "\\pagebb";
                out << "\\nowidctlpar\\tx285{\\dbch\\af2\\rtlch ";
                out << "\\ltrch\\loch\\fs20\\loch\\f2\n\\tab }";
                out << "{\\cf1\\b\\dbch\\af2\\ab\\rtlch \\ltrch\\loch\\loch\\f2\nQuiz ";
                out << quiznum+1 << " " << reviewQuiz[quiznum]->section(section)->sectionTitle();
                out << " Questions}\n";
//                out << "\\par \\par \\pard\\plain\\fs28 Quiz \\#" << quiznum+1 << " " <<
//                       reviewQuiz[quiznum]->section(section)->sectionTitle() << " Questions\\par\\sa0\\keepn\n";
            }

            for( questnum=0; questnum<reviewQuiz[quiznum]->section(section)->
                        questCount(); questnum++ )
            {
                reviewQuiz[quiznum]->section(section)->question(questnum)->setLaTeX( false );
                out << reviewQuiz[quiznum]->section(section)->
                        question(questnum)->formatted( questnum+1 );
            }
        }
    }

    out << "\\par }\n";
    file.close();
    rtf = new QProcess( this );
    rtf->setWorkingDirectory( pathname );
//	program = pwin->getViewer();
//    program = QString( "libreoffice" );
    program = reviewQuiz[0]->getViewer();
    arguments.clear();
//	arguments << pwin->getViewArgs() << "quest.rtf";
    arguments << "quiz.rtf";
    rtf->start( program, arguments );
// reset types and codes to default view
/*
    for( i=0; i<saveTypeModel.rowCount(); i++ )
        query.exec(
            QString( "UPDATE Types SET Show=\'%1\' WHERE Questtype=%2" )
            .arg( saveTypeModel.record(i).value( "Show" ).toInt() )
            .arg( saveTypeModel.record(i).value( "Questtype" ).toInt() ) );
    for( i=0; i<saveQualityModel.rowCount(); i++ )
        query.exec(
            QString( "UPDATE Quality SET Show=\'%1\' WHERE Qtype=%2 AND Quality=\'%3\'" )
            .arg( saveQualityModel.record(i).value( "Qtype" ).toInt() )
            .arg( saveQualityModel.record(i).value( "Quality" ).toInt() )
            .arg( saveQualityModel.record(i).value( "Code" ).toString() ) );
*/
}

void quizreview::Err( QString msg )
{
	errmsg dlg( this );
	
	dlg.message->setText( msg );
	dlg.exec();
}
