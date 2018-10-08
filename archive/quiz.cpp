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
					.arg( quiznum+1 ).arg( section+1 );
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
//	arguments << QString( "quiz%1" ).arg( quiznum+1 );
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
//	arguments << QString( "quiz%1.pdf" ).arg( quiznum+1 );
	arguments << QString( "quiz.pdf" );
	pdf->start( program, arguments );
}

void quiz::reviewOK( int quiznum )
{
	quiznum++;
	if( quiznum == numquizzes )
	{
		close();
		printQuizzes();		
	}
	else
	{
//		MakeQuiz( quiznum );		
		ReviewQuiz( quiznum );
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
	int i, sec, qnum, rnum, qty, qzquestrows, row;
	
	srand( time( NULL ) );
	for( sec=0; sec<sectionCount(); sec++ )
		for( qnum=0; qnum<questionCount(sec); qnum++ )
			qzData[qznum][sec][qnum].qid = qzData[qznum][sec][qnum].key = 
				qzData[qznum][sec][qnum].vid = 0;
	
	for( row=sec=0; sec<sectionCount(); sec++ )
	{
		for( ; row<=qzdatarows && (sectionnum[row] == sec+1); row++ )
		{
			qzquestrows = quizQuery( quizcodes[row], &qmodel );
			if( qzquestrows > 0 )
			{
				if( most[row] > fewest[row] )/* most > fewest */
					qty = (rand() % most[row] - fewest[row] + 1) + fewest[row];
				else
					qty = most[row];
				for( i=0; i<qty; i++ )
				{
					qnum = GetQnum( qznum, sec, key[row], earliest[row], latest[row] );
					rnum = ChooseQuest( &qmodel, qznum, sec, qnum, qCount[sec], key[row], qzquestrows );
				}
			}
		}
	/* fill in general questions*/
		qzquestrows = quizQuery( general[sec], &qmodel );
		for( qnum=0; qnum<qCount[sec]; qnum++ )
			if( qzData[qznum][sec][qnum].qid == 0 )
				rnum = ChooseQuest( &qmodel, qznum, sec, qnum, qCount[sec], 0, qzquestrows );
	}
}

void quiz::ReviewQuiz( int quiznum )
{
	QSqlQuery query;
	int sec, qnum;
	quizview *qwin = 0;
	
	if( quiznum == 0 )
		query.exec( QString( "DELETE FROM Quiz" ) );
	for( sec=0; sec<sectionCount(); sec++ )
		for( qnum=0; qnum<qCount[sec]; qnum++ )
		{
			query.exec( QString( "INSERT INTO Quiz VALUES (%1, %2, %3, %4, %5, %6)" )
				.arg(quiznum+1).arg(sec+1).arg(qnum+1)
				.arg(qzData[quiznum][sec][qnum].qid)
				.arg(qzData[quiznum][sec][qnum].key)
				.arg(qzData[quiznum][sec][qnum].vid) );
			if( query.lastError().isValid() )
			{
				pwin->Err( query.lastError().text() );
				return;
			}
		}
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

int quiz::GetQnum( const int qznum, const int sec, const int key, const int qmin, const int qmax )
{
	int qnum, i, j;
	bool ok;
	
	for( ok=false, j=0; j<50; j++ )
	{
		qnum = (rand() % (qmax-qmin+1)) + qmin-1;
		if( qzData[qznum][sec][qnum].qid == 0 )
			for( ok=true, i=(qmin>qnum-3?qmin:qnum-3)-1; i<(qmax<qnum+3?qmax:qnum+3); i++ )
				if( qzData[qznum][sec][i].qid>0 && qzData[qznum][sec][i].key==key )
				{
					ok = false;
					break;
				}
		if( ok )
			break;
	}
	if( j==50 )
		pwin->Err( QString( "Unable to find legal question spacing; quiz=%1 sec= %2 key= %3 question num %4.")
			.arg(qznum).arg(sec).arg(key).arg(qnum) );
	return( qnum );
}

int quiz::ChooseQuest( QSqlQueryModel *qmodel, const int qznum, const int sec, 
					const int qnum, const int count, const int key, const int numq )
{
	int i, j, rnum, used;
	qzdata q;
	QSqlQuery query;
	bool ok;

	for( j=0; j<50; j++ )
	{
		rnum = rand() % numq + 1;
		q.qid = qmodel->record( rnum ).value( "QID" ).toInt();
		q.key = key;
		q.vid = qmodel->record( rnum ).value( "VID" ).toInt();
		used = qmodel->record( rnum ).value( "Used" ).toInt();
		if( used == 0 )
		{
			for( ok=true, i=0; i<qnum; i++ )
				if( q.vid == qzData[qznum][sec][i].vid )
				{
					ok = false;
					break;
				}
			if( ok )
				for(i=qnum+1; i<count; i++ )
					if( q.vid == qzData[qznum][sec][i].vid )
					{
						ok = false;
						break;
					}
			if( ok )
				break;
		}
	}
	if( j==50 )
		pwin->Err( QString( "Unable to find legal question spacing; quiz= %1 sec= %2 key= %3 question num %4.")
			.arg(qznum).arg(sec).arg(key).arg(qnum) );
	
	query.exec( QString( "UPDATE Questions SET Used = %1 WHERE QID = %2" )
		.arg(used+1).arg(q.qid) );
	if( query.lastError().isValid() )
	{
		pwin->Err( query.lastError().text() );
	}
	qzData[qznum][sec][qnum] = q;
	
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

bool quiz::replaceQuestion( int qznum0, int sec0, int qnum0 )
{
	QSqlQueryModel qModel;
	QSqlQuery query;
	QString sql;
	int qid0, key0, vid0, i;
	QString replaceCodes;
//	bool ok = true;
		
	sql = QString( "SELECT qid, key, vid FROM Quiz WHERE quiznum=%1 AND section=%2 AND qnum=%3" )
				.arg( qznum0 ).arg( sec0 ).arg( qnum0 );
	qModel.setQuery( sql );
	if( qModel.lastError().isValid() )
	{
		pwin->Err( qModel.lastError().text() );
		return false;
	}
	qid0 = qModel.record( 0 ).value( "qid" ).toInt();
	key0 = qModel.record( 0 ).value( "key" ).toInt();
	vid0 = qModel.record( 0 ).value( "vid" ).toInt();

	if( key0 > 0 )
	{
		for( i=0; i<qzdatarows; i++ )
			if( key[i] == key0 )
				break;
		if( i == qzdatarows )
		{
			pwin->Err( QString( "key %1 not found." ).arg(key0) );
			return false;
		}
		replaceCodes = quizcodes[i];
	}
	else
		replaceCodes = general[sec0];

	int qzquestrows = quizQuery( replaceCodes, &qModel );

	ChooseQuest( &qModel, qznum0, sec0, qnum0, qCount[sec0], key0, qzquestrows );

	sql = QString( "UPDATE Quiz SET qid=%1, vid=%2 WHERE quiznum=%3 AND section=%4 AND qnum=%5" )
				.arg( qzData[qznum0][sec0][qnum0].qid )
				.arg( qzData[qznum0][sec0][qnum0].vid )
				.arg( qznum0 ).arg( sec0 ).arg( qnum0 );
	qModel.setQuery( sql );
	if( query.lastError().isValid() )
	{
		pwin->Err( query.lastError().text() );
		return false;
	}

	return true;
}
