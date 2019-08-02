#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//
#define MAXPATH 256
#define MAXBOOKS 5
#define MAXCHAPTERS 32
#define MAXTYPES 10
#define MAXCODES 36
#define ORDERBYVERSE 0
#define ORDERBYTYPE 1
#define ORDERBYALPHA 2
#define TWOCOLUMN 0
#define FRONTTOBACK 1
#define SIDEBYSIDE 2
#define NOANSWER 3
#define INDEX 4
#define NEWDB 0
#define CHANGEDB 1
#define HIGHLIGHT 2
#define LATEX 1
#define RTF 0
#define QUESTCOLUMNS 12
//
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QTextStream>
#include <QTableView>
#include <QLabel>
#include <QLineEdit>
#include "vrange.h"
//
class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow( QWidget * parent = 0, Qt::WindowFlags f = 0 );
//
//    explicit MainWindow(QWidget *parent = 0);
//    ~MainWindow();
//
    int LoadDb();
    QString BookName( int );
    QString AbbrevName( int );
    int BookCount();
    int ChapterCount( int );
    int VerseCount( int, int );
    int QuestCount();
    QString TypeName( int );
    void setVrange();
    vRange* getVrange();
    void setOrder( QString, QString );
    QString getPrimaryOrder();
    QString getSecondaryOrder();
    void setSelectionTitle( QSqlQueryModel * );
    void Err( QString );
    QString GetdbPath();
    QString GetdbFiledialog();
    void SetDb( QSqlDatabase * );
    QSqlDatabase* GetDb();
    QString SQLOrder();
    int GetDatabase( int );
    void UpdateQuestEdit();
    int GetBookData();
    int GetTypeData();
    void SetSelections();
    QString *GetQuestQuery();
    void SetQuestEditColumns();
    void SetQuestEditColumnWidth( int column, int width );
    void searchClosed();
    bool parseRef( const QString ref, int *book, int *chap, int *verse, int *verses );
    bool getConfig();
    QString getViewer( int format );
    QString getVerseRangeLabel();
    QString getQuestionTypesLabel();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void openDatabase();
    void printQuestions();
    void selectRange();
    void selectTypes();
    void setQuestionOrder();
    void loadQuiz();
    void prepareQuizzes();
    void about();
    void searchText();
    void insertCopy();
    void insertBlank();
    void deleteRow();
    void showKey();

private:
    QMenu *fileMenu;
    QMenu *questionsMenu;
    QMenu *quizMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QAction *rangeAct;
    QAction *typesAct;
    QAction *orderAct;
    QAction *printAct;
    QAction *makeQuizAct;
    QAction *loadQuizAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *deleteAct;
    QAction *insertBlankAct;
    QAction *insertCopyAct;
    QAction *showKeywordsAct;
    QString dbname;
    QString dbpath;
    QString LaTeXViewer;
    QString RTFViewer;
    int numquest;
    int numbooks;
    int numtypes;
    int OutputMode;
    QSqlDatabase *db;
    vRange displayRange;
    QString booknames[MAXBOOKS];
    QString bookabbrev[MAXBOOKS];
    int chapters[MAXBOOKS];
    int verses[MAXBOOKS][MAXCHAPTERS];
    QString qtypename[MAXTYPES];
    int qtypenumber[MAXTYPES];
    bool typeselected[MAXTYPES];
    QString qorder1;
    QString qorder2;
    QString dbfiledialog;
    QString QuestQuery;
    bool copied;
    QSqlQueryModel bibleModel;
    bool searchOpen;
    QTableView *questEdit;
    QLabel *verseRangeLabel;
    QLabel *questionTypesLabel;
    QLineEdit *searchBox;
    void createActions();
    void createMenus();
    int colwidth[QUESTCOLUMNS];
};
#endif // MAINWINDOW_H
