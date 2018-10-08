#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFileDialog>
#include <QProcess>
#include <QtGui>
#include "mainwindowimpl.h"
#include "range.h"
#include "types.h"
#include "order.h"
#include "format.h"
#include "errmsg.h"
#include "quizzes.h"
#include "questview.h"
#include "bible.h"
//
QuestView *qvmodel;
//
MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) 
	: QMainWindow(parent, f)
{
	setupUi( this );
	connect( FileButton, SIGNAL(clicked()), this, SLOT(FileButton_clicked()) );
	connect( PrintQuest, SIGNAL(clicked()), this, SLOT(PrintQuest_clicked()) );
	connect( RangeButton, SIGNAL(clicked()), this, SLOT(RangeButton_clicked()) );
	connect( TypeButton, SIGNAL(clicked()), this, SLOT(TypeButton_clicked()) );
	connect( OrderButton, SIGNAL(clicked()), this, SLOT(OrderButton_clicked()) );
	connect( FormatButton, SIGNAL(clicked()), this, SLOT(FormatButton_clicked()) );
	connect( QuizButton, SIGNAL(clicked()), this, SLOT(QuizButton_clicked()) );
	connect( SearchButton, SIGNAL(clicked()), this, SLOT(SearchButton_clicked()) );
	connect( SearchBox, SIGNAL(returnPressed()), this, SLOT(SearchButton_clicked()) );
	vheader = QuestEdit->verticalHeader();
	qvmodel = new QuestView( this, QuestEdit );
	QuestEdit->setModel( qvmodel );
	connect( vheader, SIGNAL(sectionClicked(int)), this, SLOT(qedit(int)) );
	createMenu();
	dbname.clear();
	dbpath.clear();
	searchOpen = false;
}
/*$SPECIALIZATION$*/

void MainWindowImpl::SetDb( QSqlDatabase *database )
{
	db = database;
}

QSqlDatabase * MainWindowImpl::GetDb()
{
	return( db );
}

int MainWindowImpl::LoadDb()
{

	dbpath.append( getenv( "QUIZZING" ) );
	if( dbpath.isEmpty() )
	{
		Err( tr( "QUIZZING environment variable not defined." ) );
		return( -1 );
	}
	
	dbfiledialog = dbpath;
	if( !dbname.isEmpty() )
	{
		dbpath = dbname;
		db->setDatabaseName( dbpath );
		if( !db->open() )
		{
			Err( QString( "Can't open database: %1" ).arg( db->lastError().text() ) );
			db->close();
			if( GetDatabase( CHANGEDB ) )
			{
				close();
				return( -1 );
			}
		}
	}
	else
	{
		dbpath.append( "/Quizzing.cfg" );
		QFile file( dbpath );
		if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
		{
			Err( QString( "Can't find %1" ).arg( dbpath ) );
			dbpath.clear();
			if( GetDatabase( NEWDB ) )
			{
				close();
				return( -1 );
			}
		}
		else
		{
			QByteArray line = file.readLine();
			if( line.at( line.length()-1 ) == '\n' )
				line.chop( 1 );
			dbpath = QString( line );
			line = file.readLine();
			if( line.at( line.length()-1 ) == '\n' )
				line.chop( 1 );
			dbfiledialog = QString( line );
			file.close();

			db->setDatabaseName( dbpath );
			if( !db->open() )
			{
				Err( QString( "Can't open database: %1" ).arg( db->lastError().text() ) );
				db->close();
				if( GetDatabase( CHANGEDB ) )
				{
					close();
					return( -1 );
				}
			}
		}
	}
	GetBookData();
	GetTypeData();
	SetSelections();
	UpdateQuestEdit();
	return( 0 );
}

int MainWindowImpl::GetDatabase( int dbmode )
{
	QString path;
	
	path = GetdbFiledialog();
	dbpath = QFileDialog::getOpenFileName( this, "Choose a database", path, "Databases (*.db)" );

	if( dbpath.isEmpty() )
		return( -1 );
	
	if( dbmode )
		db->close();

	db->setDatabaseName( dbpath );
	if( !db->open() )
	{
		Err( QString( "Can't open database: %1" ).arg( db->lastError().text() ) );
		db->close();
		dbpath.clear();
		return( -1 );
	}

	return( 0 );
}

QString MainWindowImpl::GetdbPath()
{
	return( dbpath );
}

QString MainWindowImpl::GetdbFiledialog()
{
	return( dbfiledialog );
}

int MainWindowImpl::GetBookData()
{
	int numchaps, i, j, k;
	QSqlQueryModel bmodel;
	QSqlQueryModel vmodel;

	bmodel.setQuery( "SELECT BookName, Abbrev, Chapters FROM Books" );
	if( bmodel.lastError().isValid() )
	{
		Err( bmodel.lastError().text() );
		return( -1 );
	}
	numbooks = bmodel.rowCount();
	
	vmodel.setQuery( "SELECT Verses FROM VerseCount" );
	if( vmodel.lastError().isValid() )
	{
		Err( vmodel.lastError().text() );
		return( -1 );
	}
	numchaps = vmodel.rowCount();
	for( i=j=0; i<numbooks; i++ )
	{
		booknames[i] = bmodel.record( i ).value( "BookName" ).toString();
		bookabbrev[i] = bmodel.record( i ).value( "Abbrev" ).toString();
		chapters[i] = bmodel.record( i ).value( "Chapters" ).toInt();
		for( k=0; k<chapters[i]; j++, k++ )
		{
			verses[i][k] = vmodel.record( j ).value( "Verses" ).toInt();
		}
	}
	
	return( 0 );
}

int MainWindowImpl::GetTypeData()
{
	int i;
	QSqlQueryModel tmodel;
	QSqlQueryModel cmodel;

	tmodel.setQuery( "SELECT Questtype,QName FROM Types" );
	if( tmodel.lastError().isValid() )
	{
		Err( tmodel.lastError().text() );
		return( -1 );
	}
	numtypes = tmodel.rowCount();

	for( i=0; i<numtypes; i++ )
	{
		qtypenumber[i] = tmodel.record( i ).value( "Questtype" ).toInt();
		qtypename[i] = tmodel.record( i ).value( "QName" ).toString();
	}
	
	cmodel.setQuery( "SELECT Code,Ctype,Show,Preface,Finish FROM Qcodes" );
	if( cmodel.lastError().isValid() )
	{
		Err( cmodel.lastError().text() );
		return( -1 );
	}
	numcodes = cmodel.rowCount();
	
	for( i=0; i<numcodes; i++ )
	{
		codelist[i] = cmodel.record( i ).value( "Code" ).toString();
		ctypelist[i] = cmodel.record( i ).value( "Ctype" ).toInt();
		codeshow[i] = cmodel.record( i ).value( "Show" ).toBool();
		prefacelist[i] = cmodel.record( i ).value( "Preface" ).toBool();
		finishlist[i] = cmodel.record( i ).value( "Finish" ).toBool();
	}
	
	return( 0 );
}

void MainWindowImpl::SetSelections()
{
	int i;

	for( i=0; i<numtypes; i++ )
		typeselected[i] = true;
	for( i=0; i<numcodes; i++ )
		codeselected[i] = codeshow[i];

	booklimits[0] = chapterlimits[0] = 0;
	verselimits[0] = 1;
	booklimits[1] = numbooks-1;
	chapterlimits[1] = chapters[booklimits[1]]-1;
	verselimits[1] = verses[booklimits[1]][chapterlimits[1]];

	qorder = qorder2 = ORDERBYVERSE;

	setVID();
	questionorder->setText( "Verse Order" );
	questiontypes->setText( "All" );
	questionformat->setText( "2 Columns" );
}

void MainWindowImpl::setVID()
{
	QString vrange;
	
	VID[0] = 128*(32*booklimits[0]+chapterlimits[0])+verselimits[0];
	VID[1] = 128*(32*booklimits[1]+chapterlimits[1])+verselimits[1];
	vrange = QString( "%1 %2:%3 - %4 %5:%6" )
		.arg( booknames[booklimits[0]] )
		.arg( chapterlimits[0]+1 )
		.arg( verselimits[0] )
		.arg( booknames[booklimits[1]] )
		.arg( chapterlimits[1]+1 )
		.arg( verselimits[1] );
	verserange->setText( vrange );
}

void MainWindowImpl::RangeButton_clicked()
{
	range *dlg = 0;
	
	dlg = new range( this, Qt::Window );
	dlg->show();
}

void MainWindowImpl::TypeButton_clicked()
{
	types *dlg = 0;
	
	dlg = new types( this, Qt::Window );
	dlg->show();
}

void MainWindowImpl::OrderButton_clicked()
{
	order *dlg = 0;
	
	dlg = new order( this, Qt::Window );
	dlg->show();
}

void MainWindowImpl::FormatButton_clicked()
{
	format *dlg = 0;
	
	dlg = new format( this, Qt::Window );
	dlg->show();
}

void MainWindowImpl::FileButton_clicked()
{
	GetDatabase(CHANGEDB);
	GetBookData();
	GetTypeData();
	setVID();
	UpdateQuestEdit();
	return;
}

void MainWindowImpl::QuizButton_clicked()
{
	quizzes *dlg = 0;
	
	dlg = new quizzes( this, Qt::Window );
	dlg->show();
}

void MainWindowImpl::SearchButton_clicked()
{
	static bible *bview = 0;
	QString search;
	QString BibleQuery;
	QString where;
	int i, numverses, book, chap, verse, verses, searchvid[2];
	
	search = SearchBox->text();
	if( search.length() > 0 )
	{
		if( search.at(0) == QChar( '@' ) )
		{
			search.remove( 0, 1 );
			parseRef( search, &book, &chap, &verse, &verses ); 
			searchvid[0] = 128*(32*(book-1)+chap-1)+verse;
			searchvid[1] = 128*(32*(book-1)+chap-1)+verse+verses;
			BibleQuery = QString( "SELECT Ref,Contents FROM Bible WHERE VID>%1 AND VID<%2" )
				.arg(searchvid[0]-1).arg(searchvid[1]+1);
		}
		else
		{
			search.insert( 0, tr("like('\%") );
			for( i=7; i<search.length(); i++ )
			{
				if( search.at( i ) == '&' )
				{
					search.replace( i, 1, tr("\%',Contents) AND like('\%") );
					i+=24;
				}
				else if( search.at( i ) == '|' )
				{
					search.replace( i, 1, tr("\%',Contents) OR like('\%") );
					i+=23;
				}
			}
			search.append( tr("\%',Contents)") );
			BibleQuery = QString( "SELECT Ref,Contents FROM Bible WHERE %1 AND VID>%2 AND VID<%3" )
				.arg(search).arg(VID[0]-1).arg(VID[1]+1);
		}
		bibleModel.setQuery( BibleQuery );
		if( bibleModel.lastError().isValid() )
		{
			Err( bibleModel.lastError().text() );
			return;
		}
		numverses = bibleModel.rowCount();
		if( numverses == 0 )
		{
			Err( "Search string not found." );
			return;
		}
		if( searchOpen )
			bview->setSearchModel( &bibleModel );
		else
		{
			bview = new bible( this, Qt::Window );
			bview->setSearchModel( &bibleModel );
			bview->show();
			searchOpen = true;
		}
	}
}

void MainWindowImpl::searchClosed()
{
	searchOpen = false;
}


QString *MainWindowImpl::GetQuestQuery()
{
	return( &QuestQuery );
}

void MainWindowImpl::SetQuestEditColumns()
{
	QuestEdit->resizeColumnToContents( 1 );
	QuestEdit->resizeColumnToContents( 2 );
//	QuestEdit->resizeColumnToContents( 3 );
	QuestEdit->setColumnWidth( 3, 100 );
	QuestEdit->setColumnWidth( 4, 360 );
	QuestEdit->setColumnWidth( 5, 400 );
	QuestEdit->setColumnWidth( 6, 100 );
	QuestEdit->hideColumn( 0 );	
	QuestEdit->hideColumn( 7 );	
	QuestEdit->hideColumn( 8 );	
	QuestEdit->hideColumn( 9 );	
}

void MainWindowImpl::UpdateQuestEdit()
{
	QuestQuery = QString( "SELECT QID,Ref,Qtype,Preface,Question,Answer,CR,Used,Qsort,VID FROM Quest" );
	QuestQuery.append( SQLFilter() );
	QuestQuery.append( SQLOrder() );
	qvmodel->setQuery( QuestQuery );
	while( qvmodel->canFetchMore() )
		qvmodel->fetchMore();
	if( qvmodel->lastError().isValid() )
	{
		Err( qvmodel->lastError().text() );
		return;
	}
	numquest = qvmodel->rowCount();
//	QuestEdit->setModel( qvmodel );
	qvmodel->setHeaderData( 2, Qt::Horizontal, tr( "" ) );
	SetQuestEditColumns();
//	QuestEdit->show();
}

void MainWindowImpl::PrintQuest_clicked()
{
	int i, j, sections;
	QSqlQueryModel qmodel;
	QString sql;
	QString startlist;
	QString endlist;
	QString filename;
	QString program;
	QStringList arguments;
	QProcess *pdflatex;
	QProcess *pdf;
	int numrows;
	
 	sql = QString( "SELECT q, Chap, Chapter FROM Quest" );
	sql.append( SQLFilter() );
	sql.append( SQLOrder() );
	qmodel.setQuery( sql );
	while( qmodel.canFetchMore() )
		qmodel.fetchMore();
	numquest = qmodel.rowCount();

	filename = GetdbFiledialog();
	filename.append( "/quest.tex" );
	QFile file( filename );
	if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
	{
		Err( QString( "Can't open %1 for writing" ).arg( filename ) );
		return;
	}
	QTextStream out( &file );

	out << "\\documentclass{article}\n";
	out << "\\usepackage{quiz}\n";
	if( qform == FRONTTOBACK )
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
		if( qform == SIDEBYSIDE )
			out << "\\sidebyside\n";
		else
		{
			out << "\\twocolumns\n";
			if( qform == NOANSWER )
				out << "\\questonly\n";
		}
	}
	out << "\\begin{document}\n";
	if( qform == FRONTTOBACK )
	{
		out << startlist;
		FrontToBack( &out, &qmodel, numrows );
	}
	else
	{
		out << MainTitle();
		getOrder( &i, &j );
		out << SectionTitle( (sections = (i==ORDERBYVERSE)), 
				qmodel.record( 0 ).value( "Chap" ).toString() );
		out << startlist;
		
		for( i=0; i<numquest; i++ )
		{
			if( sections && i>1 )
			{
				if( !(qmodel.record( i ).value( "Chapter" ).toInt() == 
					qmodel.record( i-1 ).value( "Chapter" ).toInt() ) ) 
				{
					out << endlist;
					out << SectionTitle( sections, qmodel.record( i ).value( "Chap" ).toString() );
					out << startlist;
				}
			}
			out << LatexQFormat( qmodel.record(i).value( "q" ).toString() );
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
	pdflatex->setWorkingDirectory( GetdbFiledialog() );
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
		Err( pdflatex->errorString() );
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
	pdf->setWorkingDirectory( GetdbFiledialog() );
	program = QString( "kpdf" );
	arguments.clear();
	arguments << "quest.pdf";
	pdf->start( program, arguments );
	if( !pdf->waitForFinished() )
	{
		Err( pdf->errorString() );
		return;
	}
}

QString MainWindowImpl::MainTitle()
{
	QString qtitle;
	
	qtitle = "\\maintitle{";
	if( questiontypes->text().compare( "All" ) == 0 )
		qtitle.append( "Practice Questions" );
	else
		qtitle.append( questiontypes->text() );
	qtitle.append( "}\n" );
	return( qtitle );
}

QString MainWindowImpl::SectionTitle( int sections, QString chaptitle )
{
	QString qtitle;
	if( sections )
		qtitle = QString( "\\sectiontitle{%1}\n" ).arg( chaptitle );
	else
		qtitle = QString( "\\sectiontitle{%1}\n" ).arg( verserange->text() );
	return( qtitle );
}

void MainWindowImpl::FrontToBack( QTextStream *out, QSqlQueryModel *qmodel, int numrows )
{
	int i, row, column, donerow, donecol;
	bool done;
	
	done = false;
	i = 0;
	while( !done )
	{
		for( column=0; column<2; column++ )
		{
			for( row=donecol=0, donerow=numrows; row<numrows; row++ )
			{
				if( i == numquest )
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
					(*out) << LatexFormatQ( qmodel->record(i).value( "q" ).toString() );
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
				(*out) << LatexFormatA( qmodel->record(i).value( "q" ).toString() );
				if( ++i == numquest )
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
		if( i == numquest )
			done = true;
	}
}

QString MainWindowImpl::LatexQFormat( QString qst )
{
	int i, j;
	
	for( i=j=0; i<qst.length(); i++, j++ )
	{
		if( (qst.at(i) == QChar( '=' )) || (qst.at(i) == QChar( '_' )) )
		{
			if( qst.at(i) == QChar( '=' ) ) /* the next word is almost key - italicize it*/
				qst.insert( i, "{\\it " );
			else
				qst.insert( i, "{\\bf " );
			qst.remove( i+=5, 1 );
			for( i++; i<qst.length(); i++ )
				if( !IsSameWord( qst, i ) )
					break;
			qst.insert( i, "}" );
		}
		else if( qst.at(i) == QChar( '\"' ) ) /*this is a double-quote (")*/
		{
			qst.remove( i, 1 );
			if( qst.at(i).isLetter() || (qst.at(i) == QChar ( '\'' )) )
				qst.insert( i, "``" );
			else
				qst.insert( i, "\'\'" );
		}
	}
	qst.append( "\n" );

	return( qst );
}

QString MainWindowImpl::LatexFormatQ( QString qst )
{
	int a, l;
	static QString qonly;
	
	qonly = qst;	
	a = qonly.indexOf( tr("}{") );
	l = qonly.length();
	qonly.remove( a+2, l-a-3 );
	return( LatexQFormat( qonly ) );
}

QString MainWindowImpl::LatexFormatA( QString qst )
{
	int a;
	static QString aonly;
	
	aonly = qst;
	a = aonly.indexOf( tr("}{") );
	if( qst.at(2) == QChar( '[' ) )
	{
		aonly.remove( 2, 1 );
		aonly.insert( 2, "{" );
	}
	aonly.remove( 3, a-3 );
	
	return( LatexQFormat( aonly ) );
}

bool MainWindowImpl::IsSameWord( QString qst, int i )
{
	if( (qst.at(i).isLetterOrNumber() || (qst.at(i) == QChar('\'') && qst.at(i+1).isLetter()) ||
	qst.at(i) == QChar('-')) && !(qst.at(i) == QChar('}')))
		return( true );
	else
		return( false );
}

QString MainWindowImpl::SQLFilter()
{
	int i, j;
	QString filter;

	filter = QString( " WHERE (" );
	for( i=j=0; i<numcodes; i++ )
	{
		if( codeselected[i] )
		{
			if( j )
				filter.append( " OR " );
			filter.append( QString( "Qtype = \'%1\'" ).arg( codelist[i] ) );
			j++;
		}
	}
	if( j && j<i )
		filter.append( ") AND" );
	else
		filter = QString( " WHERE" );

	filter.append( QString( " VID>%1 AND VID<%2" ).arg(VID[0]-1).arg(VID[1]+1) );

	return( filter );
}

QString MainWindowImpl::SQLOrder()
{
	QString order;

	if( qorder == ORDERBYVERSE )
		order = QString( " ORDER BY VID" );
	else if( qorder == ORDERBYTYPE )
		order = QString( " ORDER BY Qtype" );
	else if( qorder == ORDERBYALPHA )
		order = QString( " ORDER BY Qsort" );
	
	if( qorder2 == ORDERBYVERSE && !(qorder == ORDERBYVERSE) )
		order.append( ", VID" );
	else if( qorder2 == ORDERBYTYPE && !(qorder == ORDERBYTYPE) )
		order.append( ", Qtype" );
	else if( qorder2 == ORDERBYALPHA && !(qorder == ORDERBYALPHA)  )
		order.append( ", Qsort" );

	return( order );
}

QString MainWindowImpl::BookName( int id )
{
	return( booknames[id] );
}

QString MainWindowImpl::AbbrevName( int id )
{
	return( bookabbrev[id] );
}

int MainWindowImpl::BookCount()
{
	return( numbooks );
}

int MainWindowImpl::ChapterCount( int id )
{
	return( chapters[id] );
}

int MainWindowImpl::VerseCount( int book, int chap )
{
	return( verses[book][chap] );
}

int MainWindowImpl::QuestCount()
{
	return( numquest );
}

int MainWindowImpl::CodeCount()
{
	return( numcodes );
}

void MainWindowImpl::setVrange( int book1, int chap1, int verse1, int book2, int chap2, int verse2 )
{
	booklimits[0] = book1;
	booklimits[1] = book2;
	chapterlimits[0] = chap1;
	chapterlimits[1] = chap2;
	verselimits[0] = verse1;
	verselimits[1] = verse2;
	setVID();
	UpdateQuestEdit();
	return;
}

void MainWindowImpl::getVrange( int *start, int *end )
{
	*start = VID[0];
	*end = VID[1];
	return;
}

void MainWindowImpl::Err( QString msg )
{
	errmsg dlg( this );
	
	dlg.message->setText( msg );
	dlg.exec();
}

int MainWindowImpl::TypeCount()
{
	return( numtypes );
}

QString MainWindowImpl::TypeName( int id )
{
	return( qtypename[id] );
}

void MainWindowImpl::SelectTypes( bool *ID )
{
	int i, j, k;
	QString selected;
	
	for( k=0; k<numcodes; k++ )
		codeselected[k] = false;
	
	selected.clear();
	for( i=j=0; i<TypeCount(); i++ )
	{
		typeselected[i] = ID[i];
		if( ID[i] )
		{
			for( k=0; k<numcodes; k++ )
				if( (ctypelist[k] == qtypenumber[i]) && codeshow[k] )
					codeselected[k] = true;
		
			if( selected.length() < 120 )
			{
				if( !selected.isEmpty() )
					selected.append( "s, " );
				selected.append( qtypename[i] );
			}
			else
			{
				selected.append( "s ..." );
			}
		}
		else
			j = 1;
	}

	if( j == 0 )
		questiontypes->setText( tr("All") );
	else if( selected.isEmpty() )
	{
		questiontypes->setText( tr("All") );
		for( i=0; i<TypeCount(); i++ )
			typeselected[i] = true;
	}
	else
	{
		selected.append( "s" );
		questiontypes->setText( selected );
	}
	UpdateQuestEdit();
}

void MainWindowImpl::SetCode( int code, bool value )
{
	codeselected[code] = value;
}

bool MainWindowImpl::IsSelected( int ID )
{
	return( typeselected[ID] );
}

int MainWindowImpl::IsCodeShown( int ID )
{
	return( codeshow[ID] );
}

void MainWindowImpl::setOrder( int ID1, int ID2 )
{
	switch( qorder = ID1 )
	{
		case ORDERBYVERSE :
			switch( qorder2 = ID2 )
			{
				case ORDERBYVERSE :
				questionorder->setText( tr("Verse Order") );
				break;
				case ORDERBYTYPE :
				questionorder->setText( tr("By Verse Then Type") );
				break;
				case ORDERBYALPHA :
				questionorder->setText( tr("By Verse Then Alpha") );
				break;
			}
			break;
		case ORDERBYTYPE :
			switch( qorder2 = ID2 )
			{
				case ORDERBYVERSE :
				questionorder->setText( tr("By Type Then Verse") );
				break;
				case ORDERBYTYPE :
				questionorder->setText( tr("Type Order") );
				break;
				case ORDERBYALPHA :
				questionorder->setText( tr("By Type, Then Alpha") );
				break;
			}
			break;
		case ORDERBYALPHA :
			qorder2 = ID2;
			questionorder->setText( tr("Alpha Order") );
			break;
	}
	UpdateQuestEdit();
}

void MainWindowImpl::getOrder( int *q1, int *q2 )
{
	*q1 = qorder;
	*q2 = qorder2;
	return;
}

void MainWindowImpl::setFormat( int ID )
{
	switch( qform = ID )
	{
		case TWOCOLUMN :
		questionformat->setText( tr("2 Columns") );
		break;
		case FRONTTOBACK :
		questionformat->setText( tr("Front-to-Back") );
		break;
		case SIDEBYSIDE :
		questionformat->setText( tr("Side-by-Side") );
		break;
		case NOANSWER :
		questionformat->setText( tr("No Answers") );
		break;
	}
}

int MainWindowImpl::getFormat()
{
	return( qform );
}

bool MainWindowImpl::IsFinish( QString code )
{
	int i;
	
	for( i=0; i<CodeCount(); i++ )
		if( codelist[i] == code )
			break;
	return( ( i < CodeCount() && finishlist[i] ) ? true : false );
}
	
QString MainWindowImpl::GetCode( int id )
{
	return( codelist[id] );
}

QString MainWindowImpl::GetCodeDescription( int id )
{
	int i;

	for( i=0; i<numtypes; i++ )
		if( ctypelist[id] == qtypenumber[i] )
			return( qtypename[i] );
	return( QString( "" ) );
}

void MainWindowImpl::ShowCode( int ID )
{
	QSqlQuery query;
	
	query.exec( QString( "UPDATE Codes SET Show = 1 WHERE Code = \'%1\'" ).arg(codelist[ID]) );
	if( query.lastError().isValid() )
	{
		Err( query.lastError().text() );
		return;
	}
	codeshow[ID] = true;
	return;
}

void MainWindowImpl::HideCode( int ID )
{
	QSqlQuery query;
	
	query.exec( QString( "UPDATE Codes SET Show = 0 WHERE Code = \'%1\'" ).arg(codelist[ID]) );
	if( query.lastError().isValid() )
	{
		Err( query.lastError().text() );
		return;
	}
	codeshow[ID] = false;
	return;
}

void MainWindowImpl::createMenu()
{
	insertCopyAct = new QAction(tr("Insert &Copy"), this);
	insertCopyAct->setShortcut(tr("Ctrl+C"));
	insertCopyAct->setStatusTip(tr("Insert a new question as a copy of the current one"));
	connect(insertCopyAct, SIGNAL(triggered()), this, SLOT(insertCopy()));
	
	insertBlankAct = new QAction(tr("Insert &Blank"), this);
	insertBlankAct->setShortcut(tr("Ctrl+V"));
	insertBlankAct->setStatusTip(tr("Insert a blank new question"));
	connect(insertBlankAct, SIGNAL(triggered()), this, SLOT(insertBlank()));
	
	deleteAct = new QAction(tr("&Delete Question"), this);
	deleteAct->setShortcut(tr("Ctrl+X"));
	deleteAct->setStatusTip(tr("Delete this question"));
	connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteRow()));
}

void MainWindowImpl::deleteRow()
{
//	Err(tr("Invoked <b>Edit|Cut</b>"));
	qvmodel->deleteRow( /*QuestEdit, */qselected );
//	qvmodel->deleteRow( vheader, qselected );
}

void MainWindowImpl::insertCopy()
{
//	Err(tr("Invoked <b>Edit|Copy</b>"));
	qvmodel->insertRow( /*QuestEdit, */qselected, true );
//	qvmodel->insertRow( vheader, qselected, true );
}

void MainWindowImpl::insertBlank()
{
//	Err(tr("Invoked <b>Edit|Paste</b>"));
	qvmodel->insertRow( /*QuestEdit, */qselected, false );
//	qvmodel->insertRow( vheader, qselected, false );
}

void MainWindowImpl::qedit( int index )
{
	QMenu menu(this);
	qselected = qvmodel->index(index,0).data().toInt();
//	Err( QString( "QID=%1").arg(qselected) );
	menu.addAction(insertCopyAct);
	menu.addAction(insertBlankAct);
	menu.addAction(deleteAct);
	menu.exec(QCursor::pos());
}

bool MainWindowImpl::parseRef( const QString ref, int *book, int *chap, int *verse, int *verses )
{
	int j, ccount, vcount;
	
	for( j=0; j<BookCount(); j++ )
		if( ref.startsWith( AbbrevName(j) ) )
		{
			*book = j+1;
			break;
		}
	if( j == BookCount() )
		return false;
		
	ccount = ( ref.at( 5 ) == QChar( ':' ) ) ? 1 : 2;
	*chap = ref.mid( 4, ccount ).toInt();
	
	if( ref.length() > 7+ccount )
	{
		vcount = ( ref.at( 6+ccount ) == QChar( '-' ) ) ? 1 : 2;
		*verse = ref.mid( 5+ccount, vcount ).toInt();
		*verses = ref.mid( 6+ccount+vcount ).toInt()-(*verse);
	}
	else
	{
		*verse = ref.mid( 5+ccount ).toInt();
		*verses = 0;
	}
	return true;
}
