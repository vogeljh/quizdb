#ifndef QUIZCLASS_H
#define QUIZCLASS_H
//
#include <QString>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include <QChar>
#define MAXSECTIONS 4
#include "quizsectionclass.h"
//
class quizClass  
{

public:
    quizClass( int quiznum, int sectioncount, int questioncount[], int printformat=1, QString viewer=0 );
	virtual ~quizClass();
	//
	void Err( QString );
	quizSectionClass *section( int secnum );
	int makeQuiz();
    int quizNumber();
    int sectionCount();
    int questionCount( int section );
    void setPrintFormat( int format );
    int getPrintFormat();
    void setViewer( QString qzviewer );
    QString getViewer();

protected:
	quizSectionClass *qCsection[MAXSECTIONS];
    int qCquiznum;
    int qCsectioncount;
    int qCquestioncount[MAXSECTIONS];
    int qCprintformat;
    QString qCviewer;
};
#endif
