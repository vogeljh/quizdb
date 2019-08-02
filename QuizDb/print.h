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

#ifndef PRINT_H
#define PRINT_H
//
#include <QWidget>
#include <QTextStream>
#include <QSqlQueryModel>
#include <QString>
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QSqlQueryModel>
#include "ui_printdlg.h"
#include "mainwindow.h"
#include "vrange.h"
//
class print : public QWidget, public Ui::Dialog
{
Q_OBJECT
public:
	print(QWidget *parent=0, Qt::WindowFlags f = 0);

	void printLaTeXQuestions();
	void printRTFQuestions();
	QString MainTitle();
	QString SectionTitle( int, QString );
    void FrontToBack( QTextStream*, int );
    void IndexCard( QTextStream*, int );
    QString selectedTypesTitle();
	QString verseRangeTitle();

public slots:
	virtual void chapter2selected ( int );
	virtual void book2selected( int );
	virtual void chapter1selected ( int );
	virtual void book1selected( int );
	virtual void okClicked();

protected:
    MainWindow* pwin;
	vRange vsRange;
//	QRadioButton *rb[MAXTYPES];
	QCheckBox *cb[MAXTYPES];
	QSqlQueryModel typeModel;
	QSqlQueryModel qmodel;
	QString primary, secondary;
	int printFormat, numQuest, numTypes;
	bool typeChecked[MAXTYPES];
	bool showKey, LaTeX, typesChanged;
};
#endif
