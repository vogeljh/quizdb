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

#ifndef QUIZEDIT_H
#define QUIZEDIT_H

#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QRadioButton>
#include <QPushButton>
#include <QTabWidget>
#include <QString>
#include "quiz.h"

class quizedit : public QWidget
{
Q_OBJECT
public:
	quizedit ( QWidget* parent = 0, Qt::WindowFlags fl = 0 );

public slots:
	virtual void OK_clicked();
	virtual void AddSection_clicked();
//	virtual void AddRow_clicked()[MAXSECTIONS];
    virtual void AddRow0_clicked();
    virtual void AddRow1_clicked();
    virtual void AddRow2_clicked();
    virtual void AddRow3_clicked();
//    virtual void DeleteSection_clicked()[MAXSECTIONS];
    virtual void DeleteSection0_clicked();
    virtual void DeleteSection1_clicked();
    virtual void DeleteSection2_clicked();
    virtual void DeleteSection3_clicked();

protected:
//	MainWindowImpl* pwin;
	quiz* pwin;
	QTabWidget *tabWidget;
	QWidget *sectionWidget[MAXSECTIONS];
	int numsections;
	QRadioButton *cb[MAXCODES];
    QPushButton *ok, *cancel, *addsection;//, *deletesection;
	void Err( QString );

	QSqlQueryModel quizFormat;
	QSqlQueryModel quizData;
	void sectionEditTab( int );
    void AddNewRow( int );
    void DeleteExistingSection( int );
    int updateQuizFormat( int );
	QPushButton *AddRow[MAXSECTIONS];
    QPushButton *DeleteSection[MAXSECTIONS];
    int section, row0, row1;
	QSpinBox *Sequence[MAXSECTIONS];
	QLineEdit *SecName[MAXSECTIONS];
	QSpinBox *qcount[MAXSECTIONS];
//	QSpinBox *GenType[MAXSECTIONS];
	QComboBox *GenType[MAXSECTIONS];
	QLineEdit *GenQual[MAXSECTIONS];
	QCheckBox *SecBreak[MAXSECTIONS];
	QCheckBox *delrow[MAXSECTIONS][MAXQUIZDATA];
	QSpinBox *earliest[MAXSECTIONS][MAXQUIZDATA];
	QSpinBox *latest[MAXSECTIONS][MAXQUIZDATA];
	QSpinBox *fewest[MAXSECTIONS][MAXQUIZDATA];
	QSpinBox *most[MAXSECTIONS][MAXQUIZDATA];
//	QSpinBox *type[MAXSECTIONS][MAXQUIZDATA];
	QComboBox *type[MAXSECTIONS][MAXQUIZDATA];
	QLineEdit *quality[MAXSECTIONS][MAXQUIZDATA];
	int sectionRowCount[MAXSECTIONS];
    bool addnewsection, sectiondeleted;
};

#endif
