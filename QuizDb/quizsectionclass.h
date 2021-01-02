#ifndef QUIZSECTIONCLASS_H
#define QUIZSECTIONCLASS_H
//
#include <QString>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include <QChar>
#define MAXQUIZDATA 10
#define MAXQUESTIONS 25
#include "quizquestionclass.h"
//
class quizSectionClass  
{

public:
    quizSectionClass( int quiznum, int sectionnum, int questcount, int printformat=1 );
	virtual ~quizSectionClass();
	//
	void Err( QString );
	quizQuestionClass *question( int questnum );
	int makeSection();
	bool replaceQuestion( int );
	bool isBreak();
	QString sectionTitle();
	int questCount();

protected:
	quizQuestionClass *qSCquest[MAXQUESTIONS];
	int qSCquiznum;
	int qSCsecnum;
	int qzdatarows;
	QString secTitle;
	int qCount;
	int gentype;
	QString genqual;
	bool qzBreak;
	int earliest[MAXQUIZDATA];
	int latest[MAXQUIZDATA];
	int fewest[MAXQUIZDATA];
	int most[MAXQUIZDATA];
	int qtype[MAXQUIZDATA];
	QString quality[MAXQUIZDATA];
	int key[MAXQUIZDATA];
	void loadQuizFormat();
    int quizQuery( int, QString, QSqlQueryModel *, int * );
	int ChooseQuest( QSqlQueryModel *, const int, 
            const int, const int, int * );
//	void getVrange();
//	vRange quizRange;
};
#endif
