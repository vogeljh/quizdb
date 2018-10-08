#ifndef QUESTCLASS_H
#define QUESTCLASS_H
//
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include <QChar>
//
class questClass  
{

public:
	questClass( QSqlRecord );
	virtual ~questClass();
	//
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

protected:
	int qCverseIndex;
	QString qCbookAbbrev;
	QString qCbookChapter;
	int qCchapter;
	int qCverse;
	int qCnumVerses;
	int qCquestCode;// Questions Qtype: 1-9
	QString qCpreface;// Qtext header: "Situation Question: Who said it?" 
	QString qCquestion;// Qtext qtext: "According to Heb 10:25, Let us what?" 
	QString qCanswer;
	QString qCcrossRef;
	int qCused;
	QString qCreference;
	QString qCformatted;
	bool qCshowQuestion;
	bool qCshowAnswer;
	bool qCshowKeyWords;
	bool qCshowPreface;
	bool qCrefq;
	bool qCsitq;
	bool qCftvq;
	bool qCshiftFtv;
    bool qCLaTeX;
    QSqlQueryModel kModel;
	QSqlQueryModel aModel;
	bool isSameWord( QString, int );
	QString LaTeXformatted();
    QString RTFformatted( int number=0 );
	QString LaTeXkey( QString );
	QString RTFkey( QString );
	QString fixQuotes( QString );
	QString fixRefCapitalization( QString );
};
#endif
