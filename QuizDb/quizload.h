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

#ifndef QUIZLOAD_H
#define QUIZLOAD_H

#define MAXSAVEDQUIZZES 10
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "quiz.h"
#include "quizclass.h"

class quizload : public QWidget
{
Q_OBJECT
public:
	quizload ( QWidget* parent=0, Qt::WindowFlags fl=0, QSqlQueryModel *tables=0 );

public slots:
	virtual void OK_clicked();
	virtual void cancel_clicked();

protected:
    MainWindow* pwin;
	int quizcount;
	quizClass *qCquiz[MAXQUIZZES];
	QRadioButton *cb[MAXSAVEDQUIZZES];
	QPushButton *ok, *cancel;
	void Err( QString );
	QSqlQueryModel saveTypeModel;
	QSqlQueryModel saveQualityModel;
	bool loaded;
    QRadioButton *LaTeXbutton;
    QRadioButton *RTFbutton;
};

#endif
