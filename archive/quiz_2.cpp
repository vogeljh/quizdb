#include "quiz.h"
#include "quizedit.h"
#include "quizview.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTextStream>
#include <QProcess>
#include <QList>
#include <time.h>
//
quiz::quiz( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
	pwin = (MainWindowImpl *)parent; 
	LoadQuizData();
//	connect( EditButton, SIGNAL(clicked()), this, SLOT(editquizbutton_clicked()) );
//	connect( OkButton, SIGNAL(clicked()), this, SLOT(OkButton_clicked()) );
//	connect( CancelButton, SIGNAL(clicked()), this, SLOT(close()) );
}
//
/*$SPECIALIZATION$*/
void quiz::LoadQuizData()
{
	qzformatrows = GetQuizStringData( tr("Name"), tr("QuizFormat"), tr("ID"), secTitle );
	qzformatrows = GetQuizIntData( tr("count"), tr("QuizFormat"), tr("ID"), qCount );
	qzformatrows = GetQuizStringData( tr("general"), tr("QuizFormat"), tr("ID"), general );
	qzformatrows = GetQuizIntData( tr("break"), tr("QuizFormat"), tr("ID"), qzBreak );
	
	qzdatarows = GetQuizIntData( tr("Key"), tr("QuizData"), tr("Section"), key );
	qzdatarows = GetQuizIntData( tr("Section"), tr("QuizData"), tr("Section"), sectionnum );
	qzdatarows = GetQuizIntData( tr("earliest"), tr("QuizData"), tr("Section"), earliest );
	qzdatarows = GetQuizIntData( tr("latest"), tr("QuizData"), tr("Section"), latest );
	qzdatarows = GetQuizIntData( tr("fewest"), tr("QuizData"), tr("Section"), fewest );
	qzdatarows = GetQuizIntData( tr("most"), tr("QuizData"), tr("Section"), most );
	qzdatarows = GetQuizStringData( tr("codes"), tr("QuizData"), tr("Section"), quizcodes );
}

void quiz::OkButton_clicked()
{
	int quiznum;
	QSqlQuery query;
	
	if( TimesUsedCheckBox->isChecked() )
	{
		query.exec( QString( "UPDATE Questions SET Used = 0" ) );
		if( query.lastError().isValid() )
		{
			pwin->Err( query.lastError().text() );
			return;
		}
	}
	
	numquizzes = QuizSpinBox->value();
	query.exec( QString( "DELETE FROM Quiz" ) );
	
	for( quiznum=0; quiznum<numquizzes; quiznum++ )
	{
		MakeQuiz( quiznum );
//		ReviewQuiz( quiznum );
	}
	ReviewQuiz( 0 ); // all quizzes reviewed - pseudo-recursively
}

void quiz::printQuizzes()
{
	int section, questnum, quiznum;
	QString filename;
	QString sql;
	QSqlQueryModel qzmodel;
	QString program;
	QStringList arguments;
	QProcess *pdflatex;
	QProcess *pdf;
	
	filename = pwin->GetdbFiledialog();
//	filename.append( QString( "/quiz%1.tex" ).arg( quiznum+1 ) );
	filename.append( QString( "/quiz.tex" ) );
	QFile file( filename );
	if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
	{
		pwin->Err( QString( "Can't open %1 for writing" ).arg( filename ) );
		return;
	}
	QTextStream out( &file );

	out << "\\documentclass{article}\n";
	out << "\\usepackage{quiz}\n";
	out << "\\begin{document}\n";
	
	for( quiznum=0; quiznum<numquizzes; quiznum++ )
	{
		out << "\\quiz{Quiz \\#" << quiznum+1 << "}\n";
		for( section=0; section<4; section++ )
		{
			if( section )
			{
				if( section < 4 && qzBreak[section] )
					out << "\\pagebreak\n";
				out << "\\subsubsection*{Quiz \\#" << quiznum+1 << " " << secTitle[section] << " Questions}\n";
			}
			out << "\\begin{qnumlist}\n";
	
			sql = QString( "SELECT qid, key, vid FROM Quiz WHERE quiznum=%1 AND section=%2 ORDER BY qnum" )
					.arg( quiznum ).arg( section );
			qzmodel.setQuery( sql );
			if( qzmodel.lastError().isValid() )
			{
				pwin->Err( qzmodel.lastError().text() );
				return;
			}
		
			for( questnum=0; questnum<qzmodel.rowCount(); questnum++ )
				out << LaTeXQuizQuest( qzmodel.record( questnum ).value( "qid" ).toInt() );
			out << "\\end{qnumlist}\n";
		}
	}
	
	out << "\\end{document}\n";
	file.close();
	pdflatex = new QProcess( this );
	pdflatex->setWorkingDirectory( pwin->GetdbFiledialog() );
	program = QString( "pdflatex" );
	arguments.clear();
	arguments << QString( "quiz" );
	pdflatex->start( program, arguments );
	if( !pdflatex->waitForFinished( 5000 ) )
	{
		pwin->Err( pdflatex->errorString() );
 		return;
	}
	pdf = new QProcess( this );
	pdf->setWorkingDirectory( pwin->GetdbFiledialog() );
	program = QString( "kpdf" );
	arguments.clear();
	arguments << QString( "quiz.pdf" );
	pdf->start( program, arguments );
}

void quiz::reviewOK( int quiznum )
{
	quiznum++;
	if( quiznum < numquizzes )
	{
		ReviewQuiz( quiznum );
	}
	else
	{
		close();
		printQuizzes();		
	}
}

QString quiz::LaTeXQuizQuest( int ID )
{
	QSqlQueryModel qmodel;
	QString q;
	QString sql;
	int i, words;
	
 	sql = QString( "SELECT q, Qtype FROM Quest WHERE QID=%1" ).arg( ID );
	qmodel.setQuery( sql );
	if( qmodel.lastError().isValid() )
	{
		pwin->Err( qmodel.lastError().text() );
		return( QString( "" ) );
	}

	q = qmodel.record( 0 ).value( "q" ).toString();
	if( pwin->IsFinish( qmodel.record( 0 ).value( "Qtype" ).toString() ) ) 
	{ // FTV: move a few words from the answer into the question
		for( words=0, i=21; i<100; i++ )
		{
			if( q.at(i) == QChar( ' ' ) )
				words++;
			else if( q.at(i) == QChar( '}' ) && q.at(i+1) == QChar( '{' ) )
			{
				q.remove( i, 2 );
				q.insert( i, QChar( ' ' ) );
				for( i+=2; i<100; i++ )
				{
					if( q.at(i) == QChar( ' ' ) )
					{
						words++;
						if( words > 3 )
							break;
					}
				}
				q.remove( i, 1 );
				q.insert( i, QString( "}{" ) );
				break;
			}
		}
	}
	return( pwin->LatexQFormat( q ) );
}

void quiz::MakeQuiz( int qznum )
{
	QSqlQueryModel qmodel;
	QSqlQueryModel qzModel;
	int i, j, id, sec, qnum, rnum, qty, qzquestrows, row;
	QList<int> avlbl, unused;
	
	srand( time( NULL ) );
	
	for( row=sec=0; sec<sectionCount(); sec++ )
	{
		unused.clear();
		for( i=0; i<qCount[sec]; i++ )
			unused << i;
		for( ; row<=qzdatarows && (sectionnum[row] == sec+1); row++ )
		{
			qzquestrows = quizQuery( quizcodes[row], &qmodel );
			if( qzquestrows > 0 )
			{
				if( most[row] > fewest[row] )
					qty = (rand() % most[row] - fewest[row] + 1) + fewest[row];
				else
					qty = most[row];
				for( i=0; i<qty; i++ )
				{
					if( earliest[row] == latest[row] )
					{ // typical for replacement questions - only one question # allowed
						avlbl.clear();
						avlbl << latest[row]-1;
					}
					else if( i == 0 )
					{ // set avlbl to all unused questions between earliest and latest
						avlbl = unused;
						for( j=1; j<earliest[row]; j++ )
							if( avlbl.first() < earliest[row]-1 )
								avlbl.removeFirst();
						for( j=qCount[sec]; j>latest[row]; j-- )
							if( avlbl.last() > latest[row]-1 )
								avlbl.removeLast();
					}
					else // remove from avlbl last question # selected plus 3 to either side (if not already used)
					{
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
					{
						pwin->Err( QString( "No suitable question spacing: quiz %1 section %2 key %3." )
								.arg(qznum).arg(sec).arg(key[row]) );
						return;
					}
					if( avlbl.size() < 2 )
						qnum = avlbl.first();
					else
						qnum = avlbl.at( id = rand() % (avlbl.size()) );
					unused.removeOne( qnum );
					rnum = ChooseQuest( &qmodel, qznum, sec, qnum, qzquestrows, key[row] );
				}
			}
			else
			{
				pwin->Err( QString( "No unused questions of type %1." ).arg(key[row]) );
			}
		}
	/* fill in general questions*/
		qzquestrows = quizQuery( general[sec], &qmodel );
		for( i=0; i<unused.size(); i++ )
			rnum = ChooseQuest( &qmodel, qznum, sec, unused.at(i), qzquestrows, 0 );
	}
}

void quiz::ReviewQuiz( int quiznum )
{
	quizview *qwin = 0;

	qwin = new quizview( this, Qt::Window, quiznum );
//	qwin->setWindowModality( Qt::WindowModal );
	qwin->show();
}
	
int quiz::quizQuery( QString codelist, QSqlQueryModel *qmodel )
{
	int i, j, rows;
	QString sql;
	
	for( i=0; i<pwin->CodeCount(); i++ )
		pwin->SetCode( i, false );

	for( j=0; j<codelist.length(); j++ )
		for( i=0; i<pwin->CodeCount(); i++ )
		{
			if( codelist.mid(j,1) == pwin->GetCode(i) )
			{
				pwin->SetCode( i, true );
				break;
			}
		}
	sql = QString( "SELECT QID, VID, Used FROM Quest" );
	sql.append( pwin->SQLFilter() );
	sql.append( pwin->SQLOrder() );
	qmodel->setQuery( sql );
	while( qmodel->canFetchMore() )
		qmodel->fetchMore();
	if( qmodel->lastError().isValid() )
	{
		pwin->Err( qmodel->lastError().text() );
		return( -1 );
	}
	rows = qmodel->rowCount();
	if( rows == 0 )
		pwin->Err( QString( "No questions of type %1.").arg( codelist ) );
	return( rows );
}

int quiz::GetQuizStringData( const QString field, const QString table, const QString sort, QString data[] )
{
	int i;
	QSqlQueryModel qmodel;
	QString sql; 
	
	sql = QString( "SELECT %1 FROM %2 ORDER BY %3" ).arg(field).arg(table).arg(sort);
	qmodel.setQuery( sql );
	if( qmodel.lastError().isValid() )
	{
		pwin->Err( qmodel.lastError().text() );
		return( -1 );
	}
	
	for( i=0; i<qmodel.rowCount(); i++ )
		data[i] = qmodel.record( i ).value( field ).toString();
	
	return( qmodel.rowCount() );
}

int quiz::GetQuizIntData( const QString field, const QString table, const QString sort, int data[] )
{
	int i;
	QSqlQueryModel qmodel;
	QString sql; 
	
	sql = QString( "SELECT %1 FROM %2 ORDER BY %3" ).arg(field).arg(table).arg(sort);
	qmodel.setQuery( sql );
	if( qmodel.lastError().isValid() )
	{
		pwin->Err( qmodel.lastError().text() );
		return( -1 );
	}
	
	for( i=0; i<qmodel.rowCount(); i++ )
		data[i] = qmodel.record( i ).value( field ).toInt();
	
	return( qmodel.rowCount() );
}

int quiz::ChooseQuest( QSqlQueryModel *qmodel, const int qznum, const int sec, 
					const int qnum, const int numq, const int key )
{
	int j, rnum;
	QSqlQuery query;
	QSqlQueryModel qzModel;

	for( j=0; j<50; j++ )
	{
		rnum = rand() % numq;
		if( qmodel->record( rnum ).value( "Used" ).toInt() == 0 )
		{
			qzModel.setQuery( QString( "SELECT qnum FROM Quiz WHERE quiznum=%1 AND section=%2 AND VID=%3" )
						.arg( qznum ).arg( sec ).arg( qmodel->record( rnum ).value( "VID" ).toInt() ) );
			if( qzModel.lastError().isValid() )
			{
				pwin->Err( qzModel.lastError().text() );
				return -1;
			}
			if( qzModel.rowCount() == 0 )
				break;
		}
	}
	if( j==50 )
		pwin->Err( QString( "Unable to find legal question; quiz %1 section %2 question %3.")
			.arg(qznum+1).arg(sec+1).arg(qnum+1) );
	if( qmodel->record( rnum ).value( "QID" ).toInt() == 0 )
	{
		pwin->Err( QString( "Error: QID=0! rnum=%1 numq=%2.")
			.arg(rnum).arg(numq) );
	}

	query.exec( QString( "UPDATE Questions SET Used = Used+1 WHERE QID = %1" )
		.arg(qmodel->record( rnum ).value( "QID" ).toInt()) );
	if( query.lastError().isValid() )
	{
		pwin->Err( query.lastError().text() );
	}

	query.exec( QString( "INSERT INTO Quiz VALUES (%1, %2, %3, %4, %5, %6)" )
		.arg(qznum).arg(sec).arg(qnum).arg(qmodel->record( rnum ).value( "QID" ).toInt())
		.arg(key).arg(qmodel->record( rnum ).value( "VID" ).toInt()) );
	if( query.lastError().isValid() )
	{
		pwin->Err( query.lastError().text() );
	}
	
	return( rnum );
}

void quiz::editquizbutton_clicked()
{
	quizedit *dlg = 0;
	
	dlg = new quizedit( this, Qt::Window );
	dlg->show();
}

int quiz::sectionCount()
{
	return( qzformatrows );
}

QString *quiz::SectionTitle( int secnum )
{
	return( &(secTitle[secnum]) );
}

int quiz::questionCount( int secnum )
{
	return( qCount[secnum] );
}

QString *quiz::GetGeneral( int secnum )
{
	return( &(general[secnum]) );
}

int quiz::qzPageBreak( int secnum )
{
	return( qzBreak[secnum] );
}

int quiz::GetKey( int row )
{
	return( key[row] );
}

int quiz::GetSection( int row )
{
	return( sectionnum[row] );
}

int quiz::GetEarliest( int row )
{
	return( earliest[row] );
}

int quiz::GetLatest( int row )
{
	return( latest[row] );
}

int quiz::GetFewest( int row )
{
	return( fewest[row] );
}

int quiz::GetMost( int row )
{
	return( most[row] );
}

QString quiz::GetCodes( int row )
{
	return( quizcodes[row] );
}

int quiz::GetQuizEntries()
{
	return qzdatarows;
}

void quiz::SetEdited( bool flag )
{
	edited = flag;
}

bool quiz::GetEdited()
{
	return( edited );
}

void quiz::Err( QString msg )
{
	pwin->Err( msg );
}

QSqlDatabase * quiz::GetDb()
{
	return( pwin->GetDb() );
}

bool quiz::replaceQuestion( int qznum, int sec, int qnum )
{
	QSqlQueryModel qModel;
	QSqlQueryModel qzModel;
	QSqlQuery query;
	int qkey, i, qzquestrows;
	QString replaceCodes;
		
	qzModel.setQuery( QString( "SELECT key FROM Quiz WHERE quiznum=%1 AND section=%2 AND qnum=%3" )
				.arg( qznum ).arg( sec ).arg( qnum ) );
	if( qzModel.lastError().isValid() )
	{
		pwin->Err( qzModel.lastError().text() );
		return false;
	}
	else if( qzModel.rowCount() < 1 )
	{
		pwin->Err( QString( "Error replacing quiz %1, section %2, question %3 (Cannnot find it!)")
					.arg(qznum+1).arg(sec+1).arg(qnum+1)  );
		return false;
	}
	qkey = qzModel.data(qzModel.index(0,0)).toInt();

	if( qkey > 0 )
	{
		for( i=0; i<qzdatarows; i++ )
			if( key[i] == qkey )
				break;
		if( i == qzdatarows )
		{
			pwin->Err( QString( "key %1 not found." ).arg(qkey) );
			return false;
		}
		replaceCodes = quizcodes[i];
	}
	else
		replaceCodes = general[sec];

	if( (qzquestrows = quizQuery( replaceCodes, &qModel )) == 0 )
		return false;
	{
		query.exec( QString( "Delete from Quiz WHERE quiznum=%1 AND section=%2 AND qnum=%3" )
				.arg( qznum ).arg( sec ).arg( qnum ) );
		return (ChooseQuest( &qModel, qznum, sec, qnum, qzquestrows, qkey ) >= 0 ? true : false );
	}
}
