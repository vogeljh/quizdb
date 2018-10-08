#ifndef QUIZ_H
#define QUIZ_H
//
#define MAXSECTIONS 4
#define MAXQUESTIONS 20
#define MAXQUIZZES 10
#define MAXQUIZDATA 30
#define MAXNAMELENGTH 16
//
#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include "ui_quizdlg.h"
#include "mainwindowimpl.h"
//
class quiz : public QWidget, public Ui::quizdlg
{
Q_OBJECT
public:
	quiz( QWidget * parent = 0, Qt::WFlags f = 0 );
//
	int sectionCount();
	int questionCount( int );
	int qzPageBreak( int );
	QString* SectionTitle( int );
	QString* GetGeneral( int );
	int GetKey( int );
	int GetSection( int );
	int GetEarliest( int );
	int GetLatest( int );
	int GetFewest( int );
	int GetMost( int );
	QString GetCodes( int );
	int GetQuizEntries();
	void SetEdited( bool );
	bool GetEdited();
	void LoadQuizData();
	void Err( QString );
	QSqlDatabase* GetDb();
	void reviewOK( int );
	bool replaceQuestion( int, int, int );

public slots:
	virtual void OkButton_clicked();
	virtual void editquizbutton_clicked();

protected:
	MainWindowImpl* pwin;
	bool edited;
	int numquizzes;
	int numsections;
	int qzdatarows;
	int qzformatrows;
	QString secTitle[MAXSECTIONS];
	int qCount[MAXSECTIONS];
	QString general[MAXSECTIONS];
	int qzBreak[MAXSECTIONS];
	int key[MAXQUIZDATA];
	int sectionnum[MAXQUIZDATA];
	int earliest[MAXQUIZDATA];
	int latest[MAXQUIZDATA];
	int fewest[MAXQUIZDATA];
	int most[MAXQUIZDATA];
	QString quizcodes[MAXQUIZDATA];
	QString LaTeXQuizQuest( int );
	void MakeQuiz( int );
	void ReviewQuiz( int );
	int ChooseQuest( QSqlQueryModel *, const int, const int, const int, const int, const int );
	int GetQuizIntData( const QString, const QString, const QString, int[] );
	void printQuizzes();
	int GetQuizStringData( const QString, const QString, const QString, QString[] );
	int quizQuery( QString, QSqlQueryModel * );
};
#endif

