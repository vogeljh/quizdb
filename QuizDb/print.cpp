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

#include <QStringList>
#include <QProcess>
#include <QFile>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <QLabel>
#include "questclass.h"
#include "print.h"
//
print::print( QWidget * parent, Qt::WindowFlags f) 
	: QWidget(parent, f)
{
	int i, bookmax;
	QLabel *typeLabel;
	QSqlQueryModel filterModel;

	setupUi((QDialog *)this);

	connect( book1, SIGNAL(currentIndexChanged(int)), this, SLOT(book1selected(int)) );
	connect( chapter1, SIGNAL(valueChanged(int)), this, SLOT(chapter1selected(int)) );
	connect( book2, SIGNAL(currentIndexChanged(int)), this, SLOT(book2selected(int)) );
	connect( chapter2, SIGNAL(valueChanged(int)), this, SLOT(chapter2selected(int)) );
	connect( OkBox, SIGNAL(accepted()), this, SLOT(okClicked()) );
	connect( OkBox, SIGNAL(rejected()), this, SLOT(close()) );

    pwin = (MainWindow *)parent;
	vsRange = *(pwin->getVrange());
	bookmax = pwin->BookCount();
	for( i=0; i<bookmax; i++ )
	{
		book1->insertItem( i, pwin->BookName( i ) );
		book2->insertItem( i, pwin->BookName( i ) );
	}
	book1->setCurrentIndex( vsRange.startBook() );
	book2->setCurrentIndex( vsRange.endBook() );
	chapter1->setValue( vsRange.startChapter()+1 );
// not necessary to set maxima as the setcurrentIndex and setvalue commands
// automatically trigger the code that sets the maximums.
	verse1->setValue( vsRange.startVerse()+1 );
	chapter2->setValue( vsRange.endChapter()+1 );
	verse2->setValue( vsRange.endVerse()+1 );

	filterModel.setQuery( "SELECT ORDER1, ORDER2 FROM Qfilter" );
	if( filterModel.lastError().isValid() )
	{
		pwin->Err( filterModel.lastError().text() );
		return;
	}
	primary = filterModel.record( 0 ).value( "ORDER1" ).toString();
	secondary = filterModel.record( 0 ).value( "ORDER2" ).toString();

	if( primary.compare( "VID" ) == 0 )
		versebutton->setChecked( true );
	else if( primary.compare( "Qtype" ) == 0 )
	{
//		versebutton->setChecked( false );
		typebutton->setChecked( true );
	}
	else if( primary.compare( "Qsort" ) == 0 )
	{
//		versebutton->setChecked( false );
		alphabutton->setChecked( true );
	}
	else
		pwin->Err( QString( "Unknown sort order: " ).append( primary ) );
	
	if( secondary.compare( "VID" ) == 0 )
		versebutton2->setChecked( true );
	else if( secondary.compare( "Qtype" ) == 0 )
		typebutton2->setChecked( true );
	else if( secondary.compare( "Qsort" ) == 0 )
		alphabutton2->setChecked( true );
	else
		pwin->Err( QString( "Unknown sort order: " ).append( secondary ) );

	typeModel.setQuery( "SELECT Questtype,QName,Show FROM Types" );
	if( typeModel.lastError().isValid() )
	{
		pwin->Err( typeModel.lastError().text() );
		return;
	}
	numTypes = typeModel.rowCount();
	typeLabel = new QLabel( "Select Types" );
	typeLabel->setAlignment( Qt::AlignHCenter );
	TypeBox->addWidget( typeLabel );
	for( i=0; i<numTypes; i++ )
	{
//		rb[i] = new QRadioButton;
//		rb[i]->setAutoExclusive( false );
//		rb[i]->setText( typeModel.record(i).value("Qname").toString() );
//		TypeBox->addWidget( rb[i] );
		cb[i] = new QCheckBox;
		cb[i]->setText( typeModel.record(i).value("Qname").toString() );
		TypeBox->addWidget( cb[i] );
		if( typeModel.record(i).value("Show").toString()==QString("1") )
		{
//			rb[i]->setChecked( true );
			cb[i]->setChecked( true );
			typeChecked[i] = true;
		}
		else
			typeChecked[i] = false;
	}
	typesChanged = false;
}

/*$SPECIALIZATION$*/
void print::chapter2selected ( int val )
{
	int i;

	i = book2->currentIndex();
	if( i>=0 && i<pwin->BookCount() && val>0 && val<=pwin->ChapterCount(i) )
	{
		verse2->setMaximum( pwin->VerseCount( i, val-1 ) );
		verse2->setValue( pwin->VerseCount( i, val-1 ) );
	}
}

void print::book2selected( int index )
{
	int c, v;

	if( index>=0 && index<pwin->BookCount())
	{
		c = pwin->ChapterCount( index );
		v = pwin->VerseCount( index, c-1 );
		chapter2->setMaximum( c );
		chapter2->setValue( c );
		verse2->setMaximum( v );
		verse2->setValue( v );
	}
}

void print::chapter1selected ( int val )
{
	int i;

	i = book1->currentIndex();
	if( i>=0 && i<pwin->BookCount() && val>0 && val<=pwin->ChapterCount(i)  )
	{
		verse1->setMaximum( pwin->VerseCount( i, val-1 ) );
	}
}

void print::book1selected( int index )
{
	if( index>=0 && index<pwin->BookCount() )
	{
		chapter1->setMaximum( pwin->ChapterCount( index ) );
	}
}

void print::okClicked()
{
	int i;
	QSqlQuery query;
	QString orderQuery;
	
	vsRange.setStartAddress( book1->currentIndex(), chapter1->value()-1, 
			verse1->value()-1 );
	vsRange.setEndAddress( book2->currentIndex(), chapter2->value()-1, 
			verse2->value()-1 );
	query.exec( QString( "UPDATE Qfilter SET VID1=\'%1\', VID2=\'%2\'" )
			.arg( vsRange.startIndex() ).arg( vsRange.endIndex() ) );
	if( query.lastError().isValid() )
		pwin->Err( query.lastError().text() );

//set print order
	orderQuery = QString( "UPDATE Qfilter SET ORDER1=\'");
	if( versebutton->isChecked() )
		orderQuery.append( "VID\', ORDER2=\'" );//primary = ORDERBYVERSE;
	else if( typebutton->isChecked() )
		orderQuery.append( "Qtype\', ORDER2=\'" );//primary = ORDERBYTYPE;
	else/*  if( alphabutton->isChecked() )*/
		orderQuery.append( "Qsort\', ORDER2=\'" );//primary = ORDERBYALPHA;
	
	if( versebutton2->isChecked() )
		orderQuery.append( "VID\'" );//secondary = ORDERBYVERSE;
	else if( typebutton2->isChecked() )
		orderQuery.append( "Qtype\'" );//secondary = ORDERBYTYPE;
	else/* if( alphabutton2->isChecked() )*/
		orderQuery.append( "Qsort\'" );//secondary = ORDERBYALPHA;

	query.exec( orderQuery );
	if( query.lastError().isValid() )
	{
		pwin->Err( query.lastError().text() );
	}

//set print format
	if( twocolumnbutton->isChecked() )
		printFormat = TWOCOLUMN;
	else if( fronttobackbutton->isChecked() )
		printFormat = FRONTTOBACK;
	else if( sidebysidebutton->isChecked() )
		printFormat = SIDEBYSIDE;
	else/* if( noanswerbutton->isChecked() )*/
		printFormat = NOANSWER;

//set output format
	if( LaTeXButton->isChecked() )
		LaTeX = true;
	else
		LaTeX = false;

//set highlighting
	if( KeyWordButton->isChecked() )
		showKey = true;
	else
		showKey = false;
			
//check and set types as needed
	for( i=0; i<numTypes; i++ )
	{
//		if( rb[i]->isChecked() != typeChecked[i] )
		if( cb[i]->isChecked() != typeChecked[i] )
		{
			query.exec( 
				QString( "UPDATE Types SET Show = %1 WHERE Questtype = %2" )
//				.arg( (rb[i]->isChecked()?1:0) ).arg( typeModel.record(i)
				.arg( (cb[i]->isChecked()?1:0) ).arg( typeModel.record(i)
				.value("Questtype").toString() ) );
			typesChanged = true;
		}
		
	}

	if( LaTeX )
		printLaTeXQuestions();
	else
		printRTFQuestions();

//check if types were changed, and reset accordingly
	if( typesChanged )
		for( i=0; i<numTypes; i++ )
//			if( rb[i]->isChecked() != typeChecked[i] )
			if( cb[i]->isChecked() != typeChecked[i] )
				query.exec( 
					QString( "UPDATE Types SET Show = %1 WHERE Questtype = %2" )
					.arg( (typeChecked[i]?1:0) ).arg( typeModel.record(i)
					.value("Questtype").toString() ) );
	close();
}

void print::printLaTeXQuestions()
{
	int i, sectionnum, sections;
	QString sql;
	QString startlist;
	QString endlist;
	QString filename;
	QString program;
	QStringList arguments;
	QProcess *pdflatex;
	QProcess *pdf;
	questClass *question;
	int numrows=0;
	
//	sql = QString( "SELECT q, Chap, Chapter FROM Quest" );
//	sql = QString( "SELECT q, Chap, Chapter, VID, Verses FROM Quest" );
// 	sql = QString( "SELECT * FROM QuestLaTeX" );
 	sql = QString( "SELECT * FROM Quest " );
	sql.append( pwin->SQLOrder() );
	qmodel.setQuery( sql );
	while( qmodel.canFetchMore() )
		qmodel.fetchMore();
	numQuest = qmodel.rowCount();

	filename = pwin->GetdbFiledialog();
	filename.append( "/quest.tex" );
	QFile file( filename );
	if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
	{
		pwin->Err( QString( "Can't open %1 for writing" ).arg( filename ) );
		return;
	}
	QTextStream out( &file );

	out << "\\documentclass{article}\n";
	out << "\\usepackage{quiz}\n";
	if( printFormat == FRONTTOBACK )
	{
		startlist = QString( "\\begin{qseplist}\n" );
		endlist = QString( "\\end{qseplist}\n" );
//		numrows = InputBox("How many rows? ", "Front-To-Back Format", 10)
		numrows = 10;
		int qht = 44 / numrows * 18 - 1;
		out << "\\fronttoback\n";
		out << "\\setlength{\\qht}{" << qht << "pt}\n";
	}
	else
	{
		startlist = QString( "\\begin{qlist}\n" );
		endlist = QString( "\\end{qlist}\n" );
		if( printFormat == SIDEBYSIDE )
			out << "\\sidebyside\n";
		else
		{
			out << "\\twocolumns\n";
			if( printFormat == NOANSWER )
				out << "\\questonly\n";
		}
	}
	out << "\\begin{document}\n";
	if( printFormat == FRONTTOBACK )
	{
		out << startlist;
		FrontToBack( &out, numrows );
	}
	else
	{
		out << MainTitle();
		if( primary.compare( "VID" ) == 0)// == ORDERBYVERSE )
		{
			out << SectionTitle( true,  
				qmodel.record( 0 ).value( "Chap" ).toString() );
			sections = true;
		}
		else if( primary.compare( "Qtype" ) == 0)// == ORDERBYTYPE )
		{
            if( qmodel.record(0).value( "Qtype" ).toInt() == 9 )
                out << SectionTitle( true,
                    qmodel.record( 0 ).value( "Header" ).toString() );
            else
                out << SectionTitle( true,
                    qmodel.record( 0 ).value( "Header" ).toString().
                    replace( tr(": "), tr("s") ) );
			sections = true;
		}
		else
		{
			out << SectionTitle( true,  QString( "" ) );
			sections = false;
		}
		out << startlist;
		
		for( i=sectionnum=0; i<numQuest; i++ )
		{
			question = new questClass( qmodel.record( i ) );
			question->setLaTeX( true );
			if( printFormat == NOANSWER )
				question->showAnswer( false );
			if( !showKey )
				question->showKeyWords( false );
			if( sections && i>0 && primary.compare( "VID" ) == 0)//==ORDERBYVERSE )
			{
				if( !(qmodel.record( i ).value( "Chapter" ).toInt() == 
					qmodel.record( i-1 ).value( "Chapter" ).toInt() ) ) 
				{
					out << endlist;
					out << SectionTitle( sections, 
							qmodel.record( i ).value( "Chap" ).toString() );
					out << startlist;
				}
			}
			else if( sections && i>0 && primary.compare( "Qtype" ) == 0)//==ORDERBYTYPE )
			{
//                if( !(qmodel.record( i ).value( "Header" ).toString().
//					compare( qmodel.record( i-1 ).value( "Header" ).toString())==0))
                if( !(qmodel.record( i ).value( "Qtype" ).toInt() ==
                    qmodel.record( i-1 ).value( "Qtype" ).toInt()) )
                {
					out << endlist;
                    if( qmodel.record( i ).value( "Qtype" ).toInt() == 9 )
                        out << SectionTitle( true,
                            qmodel.record( i ).value( "Header" ).toString() );
                    else
                        out << SectionTitle( true,
                            qmodel.record( i ).value( "Header" ).toString().
                            replace( tr(": "), tr("s") ) );
					out << startlist;
				}
			}
			if( primary.compare( "Qtype" ) == 0)//==ORDERBYTYPE )
				question->showPreface( false );	
			out << question->formatted();
			delete question;
		}
	}
	
	out << endlist;
	out << "\\end{document}\n";
	file.close();
/*	
	QString TeXpath( getenv( "TEXINPUTS" ) );
	if( TeXpath.isEmpty() )
	{
		Err( tr( "TEXINPUTS environment variable not defined." ) );
		return;
	}
*/
	pdflatex = new QProcess( this );
	pdflatex->setWorkingDirectory( pwin->GetdbFiledialog() );
/*
	QStringList environment = QProcess::systemEnvironment();
	for ( i=0; i < environment.size(); i++ )
	{
		Err( environment.at(i) );
	}
*/
	program = QString( "pdflatex" );
	arguments.clear();
	arguments << "quest";
	pdflatex->start( program, arguments );
	if( !pdflatex->waitForFinished( 5000 ) )
	{
		pwin->Err( pdflatex->errorString() );
/*
		QByteArray tmp = pdflatex->readAllStandardError();
		QString emsg( tmp );
		Err( emsg );
		for( i=0; i<30; i++ )
		{
//			tmp = pdflatex->readAllStandardOutput();
			tmp = pdflatex->readLine();
			if( tmp.isEmpty() )
				break;
			emsg.clear();
			emsg.append( tmp );
			Err( emsg );
		}
*/
 		return;
	}
/*	else
		qDebug() << "pdflatex:" << pdflatex->readAll();
*/
	pdf = new QProcess( this );
	pdf->setWorkingDirectory( pwin->GetdbFiledialog() );
    program = pwin->getViewer( LATEX );
	arguments.clear();
	arguments << "quest.pdf";
	pdf->start( program, arguments );
//	if( !pdf->waitForFinished() )
//	{
//		pwin->Err( pdf->errorString() );
//		return;
//	}
}

void print::printRTFQuestions()
{
	int i, sections;
	QString sql;
	QString starthead;
	QString startquest;
	QString endquest;
	QString filename;
	QString program;
	QStringList arguments;
	QProcess *rtf;
	questClass *question;
	
	sql = QString( "SELECT * FROM Quest " );
	sql.append( pwin->SQLOrder() );
	qmodel.setQuery( sql );
	while( qmodel.canFetchMore() )
		qmodel.fetchMore();
	numQuest = qmodel.rowCount();

	filename = pwin->GetdbFiledialog();
	filename.append( "/quest.rtf" );
	QFile file( filename );
	if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
	{
		pwin->Err( QString( "Can't open %1 for writing" ).arg( filename ) );
		return;
	}
	QTextStream out( &file );

	out << "{\\rtf1\\ansi\\deff0 {\\fonttbl {\\f0\\froman Nimbus Roman No9 L;}}\n";
	out << "\\margl720\\margr720\\margt720\\margb720\n";

	if( printFormat == FRONTTOBACK )
	{
		pwin->Err( "Front-To-Back not supported in RTF Format" );
		file.close();
		return;
	}
	else if( printFormat == SIDEBYSIDE )
	{
		pwin->Err( "Side-by-Side not supported in RTF Format" );
		file.close();
		return;
	}
	else
		out << "\\cols2 \\colsx360 \\colw5000 \\tx360\n";

	out << "\\fs32 " << MainTitle() << "\\par\\sa0\\keepn\n";
	out << "\\fs28 " << SectionTitle( (sections = (primary.compare( "VID" ) == 0)),//==ORDERBYVERSE)), 
			qmodel.record( 0 ).value( "Chap" ).toString() ) <<  "\\par\\keepn\\fs20\n";
	for( i=0; i<numQuest; i++ )
	{
		question = new questClass( qmodel.record( i ) );
		question->setLaTeX( false );
		if( printFormat == NOANSWER )
			question->showAnswer( false );
		if( !showKey )
			question->showKeyWords( false );
		if( sections && i>0 )
		{
			if( !(qmodel.record( i ).value( "Chapter" ).toInt() == 
				qmodel.record( i-1 ).value( "Chapter" ).toInt() ) ) 
			{
				out << "\\par\\par\\sa0\\fs28 "; 
				out << SectionTitle( sections, qmodel.record( i ).value( "Chap" ).toString() );
				out << "\\par\\fs20\n";
			}
		}
		out << question->formatted();
	}
	
    out << "\\par }\n";
    file.close();
	rtf = new QProcess( this );
	rtf->setWorkingDirectory( pwin->GetdbFiledialog() );
//    program = QString( "libreoffice" );
    program = pwin->getViewer( RTF );
    arguments.clear();
//	arguments << pwin->getViewArgs() << "quest.rtf";
    arguments << "quest.rtf";
	rtf->start( program, arguments );
}

QString print::MainTitle()
{
	QString qtitle;
//	int type, numselectedtypes;
	
	qtitle = "\\maintitle{";
	if( selectedTypesTitle().compare( "Practice Questions" ) == 0 )
		qtitle.append( "Practice Questions" );
	else
	{
		if( primary.compare( "Qtype" ) == 0)// == ORDERBYTYPE )
			qtitle.append( verseRangeTitle() );
		else
			qtitle.append( selectedTypesTitle() );
	} 
	qtitle.append( "}\n" );
	return( qtitle );
}

QString print::SectionTitle( int sections, QString stitle )
{
	QString qtitle;
	if( sections )
		qtitle = QString( "\\sectiontitle{%1}\n" ).arg( stitle );
	else
		qtitle = QString( "\\sectiontitle{%1}\n" ).arg( pwin->getVerseRangeLabel() );
	return( qtitle );
}

void print::FrontToBack( QTextStream *out, int numrows )
{
	int i, row, column, donerow, donecol;
	questClass *question;
	bool done;
	
	done = false;
	i = 0;
	while( !done )
	{
		for( column=0; column<2; column++ )
		{
			for( row=donecol=0, donerow=numrows; row<numrows; row++ )
			{
				if( i == numQuest )
				{
					done = true;
					if( row > 0 )
					{
						donerow = row;
						donecol = column;
					}
					break;
				}
				else
				{
					question = new questClass( qmodel.record( i ) );
					question->setLaTeX( true );
					question->showAnswer( false );
					if( !showKey )
						question->showKeyWords( false );
					(*out) << question->formatted();
					delete question;
					i++;
				}
			}
			if( row > 0 )
				(*out) << "\\newpage\n";
			if( done )
			{
				if( donecol == 0 )
				{
					(*out) << "\\mbox{}\n";
					(*out) << "\\newpage\n";
				}
				break;
			}
		}
		for( column=0; column<2; column++ )
		{
			if( done )
			{
				if( donecol == 0 )
				{
					(*out) << "\\mbox{}\n";
					(*out) << "\\newpage\n";
					column++;
					i -= donerow;
				}
				else
				{
					if( column == 0 )
						i -= donerow;
					else
						i -= (donerow + numrows);
				}
			}
			else
				i -= (column+1)*numrows;
			for( row=0; row<numrows; row++ )
			{
				question = new questClass( qmodel.record( i ) );
				question->setLaTeX( true );
				question->showQuestion( false );
				if( !showKey )
					question->showKeyWords( false );
				(*out) << question->formatted();
				delete question;
				if( ++i == numQuest )
					break;
			}
//			if( done && (column == 0) && (donecol == 0) )
//			{
//				out << "\\mbox{}\n";
//			}
			if( !done || ((column == 0) && (donecol == 1)) )
				(*out) << "\\newpage\n";
		}
		if( !done )
			i += numrows;
		if( i == numQuest )
			done = true;
	}
}

QString print::selectedTypesTitle()
{
	int i, j;
	QString selected;
	QSqlQueryModel typeModel;

// Show Types
	typeModel.setQuery( "SELECT Questtype,QName,Show FROM Types" );
	if( typeModel.lastError().isValid() )
	{
		pwin->Err( typeModel.lastError().text() );
		return( "" );
	}
	selected.clear();
	for( i=j=0; i<typeModel.rowCount(); i++ )
	{
		if( typeModel.record(i).value("Show").toString() == QString( "1" ) )
		{
//			if( selected.length() < 120 )
//			{
				if( !selected.isEmpty() )
					selected.append( "s, " );
				selected.append( typeModel.record(i).value("Qname").toString() );
//			}
//			else
//				selected.append( "s ..." );
		}
		else
			j = 1;
	}

	if( j == 0 || selected.isEmpty())
		selected = QString( "Practice Questions" );
	else
		selected.append( "s" );
	return( selected );
}

QString print::verseRangeTitle()
{
	return( QString( "%1 %2:%3 - %4 %5:%6" )
		.arg( pwin->AbbrevName( vsRange.startBook() ) )
		.arg( vsRange.startChapter()+1 )
		.arg( vsRange.startVerse()+1 )
		.arg( pwin->AbbrevName( vsRange.endBook() ) )
		.arg( vsRange.endChapter()+1 )
		.arg( vsRange.endVerse()+1 ) );
}
