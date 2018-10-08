#ifndef QUIZCLASS_H
#define QUIZCLASS_H
//
#include <QString>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include <QChar>
#define MAXSECTIONS 5
#include "quizsectionclass.h"
//
class quizClass  
{

public:
    quizClass( int quiznum, int printformat=1, QString viewer=0 );
	virtual ~quizClass();
	//
	void Err( QString );
	quizSectionClass *section( int secnum );
	int makeQuiz();
	int quizNumber();
    int sectionCount();
    void setPrintFormat( int format );
    int getPrintFormat();
    void setViewer( QString qzviewer );
    QString getViewer();

protected:
	quizSectionClass *qCsection[MAXSECTIONS];
	int qCquiznum;
	int qCseccount;
    int qCprintformat;
    QString qCviewer;
};
#endif
