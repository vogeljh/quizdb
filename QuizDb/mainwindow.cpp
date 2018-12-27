#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QFileDialog>
#include <QProcess>
#include <QtGui>
#include <QVBoxLayout>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QTextBlockFormat>
#include <QTextOption>
#include <QTextCursor>
//#include <QFont>
#include <QPrinter>
#include <QPrintDialog>
#include <QDialog>
#include <QList>
#include "mainwindow.h"
#include "range.h"
#include "types.h"
#include "order.h"
#include "errmsg.h"
#include "quiz.h"
#include "quizload.h"
#include "questmodel.h"
#include "bible.h"
#include "print.h"
//
questModel *qvmodel;
//

MainWindow::MainWindow( QWidget * parent, Qt::WindowFlags f)
    : QMainWindow(parent, f)
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    questEdit = new QTableView;
    questEdit->setMinimumSize(1300, 800);
    colwidth[0] = 0;
    colwidth[1] = -1;
    colwidth[2] = -1;
    colwidth[3] = -1;
    colwidth[4] = 200;
    colwidth[5] = 360;
    colwidth[6] = 400;
    colwidth[7] = 100;
    colwidth[8] = 0;
    colwidth[9] = 0;
    colwidth[10] = 0;
    colwidth[11] = 0;
    questEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//	questEdit->setVerticalScrollMode( QAbstractItemView::ScrollPerPixel );
    QLabel *typeLabel = new QLabel;
    typeLabel->setText( tr("Types: ") );
    verseRangeLabel = new QLabel;
    verseRangeLabel->setMinimumSize(120, 20);
    questionTypesLabel = new QLabel;
    questionTypesLabel->setMinimumSize(40, 20);
//	questionTypesLabel->setWordWrap( true );
    questionTypesLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QLabel *searchLabel = new QLabel;
    searchLabel->setText( tr("Search: ") );
    searchBox = new QLineEdit;
    searchBox->setMinimumSize(120, 20);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->setMargin(5);
    vlayout->addWidget(questEdit);
    widget->setLayout(vlayout);
    statusBar()->addPermanentWidget(verseRangeLabel);
    statusBar()->addPermanentWidget(typeLabel);
    statusBar()->addPermanentWidget(questionTypesLabel);
    statusBar()->addPermanentWidget(searchLabel);
    statusBar()->addPermanentWidget(searchBox);
    createActions();
    createMenus();

    QString message = tr("right click for context menu");
    statusBar()->showMessage(message);
    setWindowTitle(tr("QuizDb"));

    qvmodel = new questModel( this, questEdit );
    questEdit->setModel( qvmodel );
    connect( searchBox, SIGNAL(returnPressed()), this, SLOT(searchText()) );

    dbname.clear();
    dbpath.clear();
    searchOpen = false;
}

//MainWindow::~MainWindow()
//{
//    delete ui;
//}

void MainWindow::createActions()
{
    openAct = new QAction(tr("Open &Database"), this);
    openAct->setShortcut(tr("Ctrl+D"));
    openAct->setStatusTip(tr("Open a database"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openDatabase()));

    rangeAct = new QAction(tr("Set &Range"), this);
    rangeAct->setShortcut(tr("Ctrl+R"));
    rangeAct->setStatusTip(tr("Set verse range for questions, quizzes"));
    connect(rangeAct, SIGNAL(triggered()), this, SLOT(selectRange()));

    typesAct = new QAction(tr("Choose &Types"), this);
    typesAct->setShortcut(tr("Ctrl+T"));
    typesAct->setStatusTip(tr("Select question types"));
    connect(typesAct, SIGNAL(triggered()), this, SLOT(selectTypes()));

    orderAct = new QAction(tr("Set &Order"), this);
    orderAct->setShortcut(tr("Ctrl+O"));
    orderAct->setStatusTip(tr("Set question order"));
    connect(orderAct, SIGNAL(triggered()), this, SLOT(setQuestionOrder()));

    printAct = new QAction(tr("&Print Questions"), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setStatusTip(tr("Print selected practice questions"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(printQuestions()));

    loadQuizAct = new QAction(tr("&Load Quiz"), this);
    loadQuizAct->setShortcut(tr("Ctrl+L"));
    loadQuizAct->setStatusTip(tr("Load previously saved quiz"));
    connect(loadQuizAct, SIGNAL(triggered()), this, SLOT(loadQuiz()));

    makeQuizAct = new QAction(tr("Prepare &Quizzes"), this);
    makeQuizAct->setShortcut(tr("Ctrl+Q"));
    makeQuizAct->setStatusTip(tr("Make quizzes on selected verse range"));
    connect(makeQuizAct, SIGNAL(triggered()), this, SLOT(prepareQuizzes()));

    aboutAct = new QAction(tr("&About QuizDb"), this);
    aboutAct->setShortcut(tr("Ctrl+A"));
    aboutAct->setStatusTip(tr("About QuizDb"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+X"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    insertCopyAct = new QAction(tr("Insert &Copy"), this);
    insertCopyAct->setShortcut(tr("Ctrl+C"));
    insertCopyAct->setStatusTip(tr("Insert new question as a copy"));
    connect(insertCopyAct, SIGNAL(triggered()), this, SLOT(insertCopy()));

    insertBlankAct = new QAction(tr("Insert &Blank"), this);
    insertBlankAct->setShortcut(tr("Ctrl+V"));
    insertBlankAct->setStatusTip(tr("Insert a blank new question"));
    connect(insertBlankAct, SIGNAL(triggered()), this, SLOT(insertBlank()));

    deleteAct = new QAction(tr("&Delete Question"), this);
    deleteAct->setShortcut(tr("Ctrl+X"));
    deleteAct->setStatusTip(tr("Delete this question"));
    connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteRow()));

    showKeywordsAct = new QAction(tr("Show &Key Words"), this);
    showKeywordsAct->setShortcut(tr("Ctrl+K"));
    showKeywordsAct->setStatusTip(tr("List key, almost key words"));
    connect(showKeywordsAct, SIGNAL(triggered()), this, SLOT(showKey()));
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    menu.addAction(insertCopyAct);
    menu.addAction(insertBlankAct);
    menu.addAction(deleteAct);
    menu.addAction(showKeywordsAct);
    menu.exec(event->globalPos());
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    questionsMenu = menuBar()->addMenu(tr("&Questions"));
    questionsMenu->addAction(rangeAct);
    questionsMenu->addAction(typesAct);
    questionsMenu->addAction(orderAct);

    quizMenu = menuBar()->addMenu(tr("&Quiz"));
    quizMenu->addAction(loadQuizAct);
    quizMenu->addAction(makeQuizAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

/*$SPECIALIZATION$*/
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Menu"),
        tr("QuizDb version 1.00 released 07Oct2008."));
}

void MainWindow::SetDb( QSqlDatabase *database )
{
    db = database;
}

QSqlDatabase * MainWindow::GetDb()
{
    return( db );
}

int MainWindow::LoadDb()
{

    dbpath.append( getenv( "QUIZZING" ) );
    if( dbpath.isEmpty() )
    {
        Err( tr( "QUIZZING environment variable not defined." ) );
        return( -1 );
    }

    dbfiledialog = dbpath;
    OutputMode = RTF;
    if( !dbname.isEmpty() )
    {
        dbpath = dbname;
        db->setDatabaseName( dbpath );
        if( !db->open() )
        {
            Err( QString( "Can't open database: %1, database path: %2" ).arg( db->lastError().text(), dbpath ) );
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
        if( getConfig() > 0 )
        {
            db->setDatabaseName( dbpath );
            if( !db->open() )
            {
                Err( QString( "Database name is empty, can't open database: %1" ).arg( db->lastError().text() ) );
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

bool MainWindow::getConfig()
{
    QList<QByteArray> config, args;

    dbpath.append( "/Quizzing.cfg" );
    QFile file( dbpath );
    if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        Err( QString( "Can't find %1" ).arg( dbpath ) );
        dbpath.clear();
        if( GetDatabase( NEWDB ) )
        {
            close();
            return( false );
        }
    }
    else
    {
        QByteArray line = file.readLine();
        while( line.length() > 0 )
        {
            if( line.at( line.length()-1 ) == '\n' )
                line.chop( 1 );
            config = line.split( '=' );
            if( !(config.size() == 2) )
            {
                Err( QString( "Invalid Quizzing.cfg file: entry reads %1!" ).arg( line.data() ) );
                return( false );
            }
            if( config[0] == QByteArray( "DBPATH" ) )
            {
                dbpath = config[1];
            }
            else if( config[0] == QByteArray( "HOME" ) )
            {
                dbfiledialog = config[1];
            }
            else if( config[0] == QByteArray( "OUTPUT" ) )
            {
                if( config[1] == "LaTeX" )
                    OutputMode = LATEX;
                else
                    OutputMode = RTF;
            }
            else if( config[0] == QByteArray( "LATEXVIEWER" ) )
            {
                args = config[1].split( ' ' );
                LaTeXViewer = args[0];
//				if( args.size() > 1 )
//					ViewArgs = args[1];
//				else
//					ViewArgs = QString( "" );
            }
            else if( config[0] == QByteArray( "RTFVIEWER" ) )
            {
                args = config[1].split( ' ' );
                RTFViewer = args[0];
//				if( args.size() > 1 )
//					ViewArgs = args[1];
//				else
//					ViewArgs = QString( "" );
            }
            else
                Err( QString( "Unknown config entry" ) );
            line = file.readLine();
        }
        file.close();
        return( true );
    }
    return( false );
}

int MainWindow::GetDatabase( int dbmode )
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
        Err( QString( "Database name set successfully, but unable to open it: %1, database path: %2" ).arg( db->lastError().text(), dbpath ) );
        db->close();
        dbpath.clear();
        return( -1 );
    }

    return( 0 );
}

QString MainWindow::GetdbPath()
{
    return( dbpath );
}

QString MainWindow::GetdbFiledialog()
{
    return( dbfiledialog );
}

int MainWindow::GetBookData()
{
    int i, j, k;
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
//	numchaps = vmodel.rowCount();
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

int MainWindow::GetTypeData()
{
    int i;
    QSqlQueryModel tmodel;
    QSqlQueryModel cmodel;

    tmodel.setQuery( "SELECT Questtype,QName,Show FROM Types" );
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
    setSelectionTitle( &tmodel );
    return( 0 );
}

void MainWindow::SetSelections()
{
    QSqlQueryModel filterModel;
    QString order;

    filterModel.setQuery( "SELECT ORDER1,ORDER2,VID1,VID2 FROM Qfilter" );
    if( filterModel.lastError().isValid() )
    {
        Err( filterModel.lastError().text() );
        return;
    }
    qorder1 = filterModel.record( 0 ).value( "ORDER1" ).toString();
    qorder2 = filterModel.record( 0 ).value( "ORDER2" ).toString();
    displayRange.setStartIndex( filterModel.record( 0 ).value( "VID1" ).toInt() );
    displayRange.setEndIndex( filterModel.record( 0 ).value( "VID2" ).toInt() );
    setVrange();
}

void MainWindow::selectRange()
{
    range *dlg = 0;

    dlg = new range( this, Qt::Window );
    dlg->show();
}

void MainWindow::selectTypes()
{
    types *dlg = 0;

    dlg = new types( this, Qt::Window );
    dlg->show();
}

void MainWindow::setQuestionOrder()
{
    order *dlg = 0;

    dlg = new order( this, Qt::Window );
    dlg->show();
}

void MainWindow::openDatabase()
{
    QSqlQueryModel filterModel;
    QSqlQuery VIDQuery;

    GetDatabase(CHANGEDB);
    GetBookData();

    filterModel.setQuery( "SELECT ORDER1,ORDER2,VID1,VID2 FROM Qfilter" );
    if( filterModel.lastError().isValid() )
    {
        Err( filterModel.lastError().text() );
        return;
    }
    qorder1 = filterModel.record( 0 ).value( "ORDER1" ).toString();
    qorder2 = filterModel.record( 0 ).value( "ORDER2" ).toString();
    if( filterModel.record( 0 ).value( "VID1" ).toInt() < 0 )
        displayRange.setStartIndex( 0 );
    else
        displayRange.setStartIndex( filterModel.record( 0 ).value( "VID1" ).toInt() );
    if( filterModel.record( 0 ).value( "VID2" ).toInt() >
            (BookCount()-1)*4096+(ChapterCount(BookCount()-1)-1)*128 +
            VerseCount(BookCount()-1, ChapterCount(BookCount()-1)-1))
        displayRange.setEndIndex( (BookCount()-1)*4096+(ChapterCount(BookCount()-1)
                -1)*128+VerseCount(BookCount()-1, ChapterCount(BookCount()-1)-1) );
    else
        displayRange.setEndIndex( filterModel.record( 0 ).value( "VID2" ).toInt() );
    setVrange();

    GetTypeData();
    UpdateQuestEdit();

    return;
}

void MainWindow::loadQuiz()
{
    QSqlQueryModel tableNameModel;
    quizload *dlgload = 0;

    tableNameModel.setQuery( QString("SELECT name FROM sqlite_master WHERE " )
            .append( "type=\'table\' AND name LIKE \'Qz%\' " ) );
    if( tableNameModel.lastError().isValid() )
    {
        Err( tableNameModel.lastError().text() );
        return;
    }
    if( tableNameModel.rowCount() < 1 )
    {
        Err( "No Saved Quizzes." );
        return;
    }
    else if( tableNameModel.rowCount() )
    {
        dlgload = new quizload( this, Qt::Window, &tableNameModel );
        dlgload->show();
    }
}

void MainWindow::prepareQuizzes()
{
    quiz *dlg = 0;

    dlg = new quiz( this, Qt::Window );
    dlg->show();
}

void MainWindow::searchText()
{
    static bible *bview = 0;
    QString search;
    QString BibleQuery;
    QString where;
    int i, numverses, book, chap, verse, verses, searchvid[2];

    search = searchBox->text();
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
                else if( search.at( i ) == '\'' )
                {
                    search.insert( i, tr("'") );
                    i+=1;
                }
            }
            search.append( tr("\%',Contents)") );
            BibleQuery = QString(
            "SELECT Ref,Contents FROM Bible WHERE %1 AND VID>%2 AND VID<%3" )
                .arg(search).arg(displayRange.startIndex())
                .arg(displayRange.endIndex()+2);
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

void MainWindow::searchClosed()
{
    searchOpen = false;
}


QString *MainWindow::GetQuestQuery()
{
    return( &QuestQuery );
}

void MainWindow::SetQuestEditColumns()
{
    int col;

    for( col=0; col<QUESTCOLUMNS; col++ )
    {
        if( colwidth[col] < 0 )
            questEdit->resizeColumnToContents( col );
        else if( colwidth[col] == 0 )
            questEdit->hideColumn( col );
        else
            questEdit->setColumnWidth( col, colwidth[col] );
    }
    questEdit->resizeRowsToContents();
}

void MainWindow::SetQuestEditColumnWidth( int column, int width )
{
    colwidth[column] = width;
}

void MainWindow::UpdateQuestEdit()
{
    QuestQuery = QString( "SELECT QID,Ref,Tabbrev,Quality,Preface,Question,Answer,CR,Used,Qsort,VID,Verses FROM Quest" );
    QuestQuery.append( SQLOrder() );

    qvmodel->setQuery( QuestQuery );
    while( qvmodel->canFetchMore() )
        qvmodel->fetchMore();
    if( qvmodel->lastError().isValid() )
    {
        Err( qvmodel->lastError().text() );
        Err( QuestQuery );
        return;
    }
    numquest = qvmodel->rowCount();
    qvmodel->setHeaderData( 2, Qt::Horizontal, tr( "Type" ) );
    qvmodel->setHeaderData( 3, Qt::Horizontal, tr( "Qual" ) );
    SetQuestEditColumns();
}

void MainWindow::printQuestions()
{
    print *dlg = 0;

    dlg = new print( this, Qt::Window );
    dlg->show();
}

QString MainWindow::SQLOrder()
{
    QString order;
    QSqlQueryModel filterModel;

    filterModel.setQuery( "SELECT ORDER1, ORDER2 FROM Qfilter" );
    if( filterModel.lastError().isValid() )
    {
        Err( filterModel.lastError().text() );
        return( QString( "" ) );
    }
    order = QString( " ORDER BY %1, %2, QID" )
        .arg( filterModel.record( 0 ).value( "ORDER1" ).toString() )
        .arg( filterModel.record( 0 ).value( "ORDER2" ).toString() );

    return( order );
}

QString MainWindow::BookName( int id )
{
    QSqlQueryModel bmodel;

    bmodel.setQuery( "SELECT BookName FROM Books" );
    if( bmodel.lastError().isValid() )
    {
        Err( bmodel.lastError().text() );
        return( "" );
    }
    return( bmodel.record( id ).value( "BookName" ).toString() );
}

QString MainWindow::AbbrevName( int id )
{
    QSqlQueryModel bmodel;

    bmodel.setQuery( "SELECT Abbrev FROM Books" );
    if( bmodel.lastError().isValid() )
    {
        Err( bmodel.lastError().text() );
        return( "" );
    }
    return( bmodel.record( id ).value( "Abbrev" ).toString() );
}

int MainWindow::BookCount()
{
    QSqlQueryModel bmodel;

    bmodel.setQuery( "SELECT Abbrev FROM Books" );
    if( bmodel.lastError().isValid() )
    {
        Err( bmodel.lastError().text() );
        return( -1 );
    }
    return( bmodel.rowCount() );
}

int MainWindow::ChapterCount( int id )
{
    QSqlQueryModel bmodel;

    bmodel.setQuery( "SELECT Chapters FROM Books" );
    if( bmodel.lastError().isValid() )
    {
        Err( bmodel.lastError().text() );
        return( -1 );
    }
    return( bmodel.record( id ).value( "Chapters" ).toInt() );
}

int MainWindow::VerseCount( int book, int chap )
{
    int i;
    QSqlQueryModel vmodel;

    vmodel.setQuery(
        QString( "SELECT Verses FROM VerseCount WHERE Booknum=%1 AND Chapter=%2" )
            .arg( book+1 ).arg( chap+1 ) );
    if( vmodel.lastError().isValid() )
    {
        Err( vmodel.lastError().text() );
        return( -1 );
    }
    return( i=vmodel.record( 0 ).value( "Verses" ).toInt() );
}

int MainWindow::QuestCount()
{
    QSqlQueryModel qmodel;

    qmodel.setQuery( "SELECT * from Quest" );
    if( qmodel.lastError().isValid() )
    {
        Err( qmodel.lastError().text() );
        return( -1 );
    }
    return( qmodel.rowCount() );
}

vRange* MainWindow::getVrange()
{
    return( &displayRange );
}

void MainWindow::setVrange()
{
    QSqlQuery filterQuery;

    verseRangeLabel->setText( QString( "%1 %2:%3 - %4 %5:%6" )
        .arg( bookabbrev[displayRange.startBook()] )
        .arg( displayRange.startChapter()+1 )
        .arg( displayRange.startVerse()+1 )
        .arg( bookabbrev[displayRange.endBook()] )
        .arg( displayRange.endChapter()+1 )
        .arg( displayRange.endVerse()+1 ) );

    filterQuery.exec( QString( "UPDATE Qfilter SET VID1=\'%1\', VID2=\'%2\'" )
            .arg( displayRange.startIndex() ).arg( displayRange.endIndex() ) );
    if( filterQuery.lastError().isValid() )
        Err( filterQuery.lastError().text() );
    else
        UpdateQuestEdit();

    return;
}

void MainWindow::Err( QString msg )
{
    errmsg dlg( this );

    dlg.message->setText( msg );
    dlg.exec();
}

QString MainWindow::TypeName( int id )
{
    QSqlQueryModel tmodel;

    tmodel.setQuery(
        QString( "SELECT Qname FROM Types WHERE Questtype=%1" )
            .arg( id ) );
    if( tmodel.lastError().isValid() )
    {
        Err( tmodel.lastError().text() );
        return( "" );
    }
    return( tmodel.record( 0 ).value( "Qname" ).toString() );
}

void MainWindow::setSelectionTitle( QSqlQueryModel *model )
{
    int i, j;
    QString selected;

// Show Types
    selected.clear();
    for( i=j=0; i<model->rowCount(); i++ )
    {
        if( model->record(i).value("Show").toString() == QString( "1" ) )
        {
            if( selected.length() < 120 )
            {
                if( !selected.isEmpty() )
                    selected.append( "s, " );
                selected.append( model->record(i).value("Qname").toString() );
            }
            else
                selected.append( "s ..." );
        }
        else
            j = 1;
    }

    if( j == 0 )
        questionTypesLabel->setText( tr("All") );
    else if( selected.isEmpty() )
        questionTypesLabel->setText( tr("All") );
    else
    {
        selected.append( "s" );
        questionTypesLabel->setText( selected );
    }
}

void MainWindow::setOrder( QString order1, QString order2 )
{
    QSqlQuery filterQuery;

    filterQuery.exec( QString( "UPDATE Qfilter SET ORDER1=\'%1\', ORDER2=\'%2\'" )
            .arg( qorder1=order1 ).arg( qorder2=order2 ) );
    if( filterQuery.lastError().isValid() )
    {
        Err( filterQuery.lastError().text() );
    }
    UpdateQuestEdit();
}

void MainWindow::deleteRow()
{
    qvmodel->deleteRow();
}

void MainWindow::insertCopy()
{
    qvmodel->insertRow( true );
}

void MainWindow::insertBlank()
{
    qvmodel->insertRow( false );
}

void MainWindow::showKey()
{
    qvmodel->showKey();
}

bool MainWindow::parseRef( const QString ref, int *book, int *chap, int *verse, int *verses )
{
    int j, ccount, vcount, chaploc;

    for( j=0; j<BookCount(); j++ )
        if( ref.startsWith( AbbrevName(j) ) ||
                ref.startsWith( AbbrevName(j).toLower() ))
        {
            *book = j+1;
            break;
        }
    if( j == BookCount() )
        return false;

    chaploc = ref.indexOf( ' ' ) + 1;
    ccount = ( ref.at( chaploc+1 ) == QChar( ':' ) ) ? 1 : 2;
    *chap = ref.mid( chaploc, ccount ).toInt();
    if( *chap < 1 )
        return false;
    if( *chap > ChapterCount( j ) )
        return false;

    if( ref.length() > chaploc+3+ccount )
    {
        vcount = ( ref.at( chaploc+2+ccount ) == QChar( '-' ) ) ? 1 : 2;
        *verse = ref.mid( chaploc+1+ccount, vcount ).toInt();
        *verses = ref.mid( chaploc+2+ccount+vcount ).toInt()-(*verse);
    }
    else
    {
        *verse = ref.mid( chaploc+1+ccount ).toInt();
        *verses = 0;
    }
    if( *verse < 1 || *verses < 0 )
        return false;
    if( (*verse + *verses) > VerseCount( j, *chap-1 ) )
        return false;

    return true;
}

QString MainWindow::getViewer( int format )
{
    if( format%2 == LATEX )
        return( LaTeXViewer );
    else
        return( RTFViewer );
}

//QString MainWindow::getViewArgs()
//{
//	return( ViewArgs );
//}

QString MainWindow::getVerseRangeLabel()
{
    return( verseRangeLabel->text() );
}

QString MainWindow::getQuestionTypesLabel()
{
    return( questionTypesLabel->text() );
}
