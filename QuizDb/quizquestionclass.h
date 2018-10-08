#ifndef QUIZQUESTIONCLASS_H
#define QUIZQUESTIONCLASS_H
//
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include <QChar>
#include "questclass.h"
//
class quizQuestionClass  
{

public:
    quizQuestionClass( int quiznum, int sectionnum, int questionnum, int printformat=1 );
	virtual ~quizQuestionClass();
	//
	void Err( QString );
	int verseIndex();
	QString bookAbbrev();
	QString bookChapter();
	int chapter();
	int verse();
	int numVerses();
	int questCode();// Questions Qtype: "1-9"
	QString preface();// Qtext header: "Situation Question: Who said it?" 
	QString question();// Qtext qtext: "According to Heb 10:25, Let us what?" 
	QString answer();
	QString crossRef();
	int used();
	QString reference();
	int quiznum();
	int secnum();
	int questnum();
	int qid();
	int vid();
	int key();
    void setLaTeX( bool );
    void setHighlight( bool );
    void showQuestion( bool );
	void showAnswer( bool );
	void showKeyWords( bool );
	void showPreface( bool );
	void shiftFtv( bool );
	bool isRefq();
	bool isSitq();
	bool isFtvq();
    QString formatted( int number=0 );
	void setQuestion( int qid, int key, int vid );

protected:
	questClass *quest;
    int qQCprintformat;
    int qQCquizID;
	int qQCsecID;
	int qQCquestID;
	int qQCqid;
	int qQCvid;
	int qQCkey;
};
#endif
