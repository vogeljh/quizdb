/***************************************************************************
 *   Copyright (C) 2007 by Jeff Vogel   *
 *   vogeljh@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef QUIZREVIEW_H
#define QUIZREVIEW_H

#include <QGroupBox>
#include <QString>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "quizclass.h"
#include "quiz.h"
#include "vrange.h"

class quizreview : public QWidget
{
Q_OBJECT
public:
	quizreview ( quizClass *quizzes[], int numquizzes, QWidget* parent=0, 
                    Qt::WindowFlags fl=0, QString qzpath=0 );

	int sectionCount();
	bool replaceQuestion( int, int, int );
	void Err( QString );

public slots:
	virtual void done_clicked();
	virtual void save_clicked();
	virtual void review_clicked();

protected:
	int quizCount;
//	int qzformatrows, qzdatarows;
//	quizClass *reviewQuiz[];
	quizClass **reviewQuiz;
	QRadioButton *cb[MAXQUIZZES];
	QPushButton *done, *save, *review, *cancel;
    void printLaTeXQuizzes();
    void printRTFQuizzes();
    QString filename;
//	int GetQuizIntData( const QString, const QString, const QString, int[] );
//	int GetQuizStringData( const QString, const QString, const QString, 
//			QString[] );
//	QString LaTeXQuizQuest( int );
//	QString secTitle[MAXSECTIONS];
//	int qCount[MAXSECTIONS];
//	int gentype[MAXSECTIONS];
//	QString genqual[MAXSECTIONS];
//	int qzBreak[MAXSECTIONS];
//	int quiztype[MAXQUIZDATA];
//	int key[MAXQUIZDATA];
//	QString quizquality[MAXQUIZDATA];
//	void loadQuizFormat();
//	int quizQuery( int, QString, QSqlQueryModel * );
//	int ChooseQuest( QSqlQueryModel *, const int, const int, const int, 
//			const int, const int );
//	void getVrange();
//	vRange quizRange;
};

#endif
