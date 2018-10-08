#ifndef QUIZ_H
#define QUIZ_H
//
//#define MAXSECTIONS 4
//#define MAXQUESTIONS 20
#define MAXQUIZZES 20
//#define MAXQUIZDATA 30
//#define MAXNAMELENGTH 16
//
#include <QWidget>
#include <QSqlQueryModel>
//#include <QSqlDatabase>
#include "ui_quizdlg.h"
#include "mainwindow.h"
#include "vrange.h"
#include "quizclass.h"
//
class quiz : public QWidget, public Ui::quizdlg
{
Q_OBJECT
public:
	quiz( QWidget * parent = 0, Qt::WindowFlags f = 0 );
//
	quizClass *quizzes( int quiznum );
	void Err( QString );
//	QSqlDatabase* GetDb();
//	void reviewOK( int );

public slots:
	virtual void OkButton_clicked();
	virtual void cancel_clicked();
	virtual void editQuiz_clicked();
	virtual void chapter2selected ( int );
	virtual void book2selected( int );
	virtual void chapter1selected ( int );
	virtual void book1selected( int );

protected:
    MainWindow* pwin;
	quizClass *qCquiz[MAXQUIZZES];
	int numquizzes;
//	void ReviewQuiz( int );
	QSqlQueryModel saveTypeModel;
	QSqlQueryModel saveQualityModel;
	vRange vsRange;
	bool prepared;
};
#endif

