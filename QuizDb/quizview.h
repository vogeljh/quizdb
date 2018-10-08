#ifndef __QUIZVIEW_H__
#define __QUIZVIEW_H__

#include <QWidget>
#include <QTabWidget>
#include <QLineEdit>
#include <QLabel>
#include <QSqlDatabase>
#include <QHeaderView>
#include <QMenu>
#include <QContextMenuEvent>
#include "quizclass.h"
#include "quizreview.h"

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

public slots:
	virtual void OK_clicked();

protected:
	void contextMenuEvent(QContextMenuEvent *event);

private slots:
	void replace();
	void moveUp();
	void moveDown();

private:
	quizreview *pwin;
	quizClass *viewquiz;
	QTabWidget *tabwidget;
	QPushButton *ok, *cancel;
//	int quiznum;
	int section;
	int qselected;
	QSpinBox *Sequence;
	QLineEdit *ref[MAXSECTIONS];
	QLineEdit *header[MAXSECTIONS];
	QLineEdit *quest[MAXSECTIONS];
	QLineEdit *answer[MAXSECTIONS];
	QHeaderView *vheader[MAXSECTIONS];
//	QHeaderView *vheader;
	void createMenu();
	QAction *replaceAct;
	QAction *moveUpAct;
	QAction *moveDownAct;
};

#endif // __QUIZVIEW_H__
