#ifndef __QUIZVIEW_H__
#define __QUIZVIEW_H__

#include <QWidget>
#include <QTabWidget>
#include <QTableView>
#include <QLineEdit>
#include <QLabel>
#include <QSqlDatabase>
#include <QHeaderView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "quizclass.h"
#include "quizreview.h"
#include "quizquestmodel.h"
#include "quizquesteditview.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class quizview : public QWidget
{
Q_OBJECT
public:
    quizview ( quizClass *quiz, QWidget* parent = 0, Qt::WindowFlags fl = 0 );

	void Err( QString );
	bool replaceQuestion( int, int );
    QString *GetQuestQuery();
    void updateQuizModel( int tab );
    void sizeQuizEditView();
    void updateQuestion( int qnum );
//    void cancelEdit();

public slots:
	virtual void OK_clicked();

protected:
	void contextMenuEvent(QContextMenuEvent *event);

private slots:
	void replace();
	void moveUp();
	void moveDown();
    void editQuestion();
    void editQuestionCopy();

private:
	quizreview *pwin;
	quizClass *viewquiz;
    quizQuestModel *quizQuestEditModel;
    class quizQuestEditView *quizQuestEdit;
    QTabWidget *tabwidget;
    void editQuizQuestion( int copy );
    QString quizEditQuestQuery;
	QPushButton *ok, *cancel;
	int section;
	int qselected;
    bool editquestioncopied;
    int copied_qid;
	QSpinBox *Sequence;
	QLineEdit *ref[MAXSECTIONS];
	QLineEdit *header[MAXSECTIONS];
	QLineEdit *quest[MAXSECTIONS];
	QLineEdit *answer[MAXSECTIONS];
	QHeaderView *vheader[MAXSECTIONS];
	void createMenu();
	QAction *replaceAct;
	QAction *moveUpAct;
	QAction *moveDownAct;
    QAction *editQuestionAct;
    QAction *editQuestionCopyAct;
};

#endif // __QUIZVIEW_H__
