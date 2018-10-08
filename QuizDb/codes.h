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

#ifndef CODES_H
#define CODES_H

#include <QCheckBox>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QSqlQueryModel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mainwindow.h"
#define MAXQUALITYLEVELS 5

class codes : public QWidget
{
Q_OBJECT
public:
	codes ( QWidget* parent = 0, Qt::WindowFlags f = 0 );

	void Err( QString );

public slots:
	virtual void OK_clicked();
	virtual void Cancel_clicked();

protected:
	int buildLayout();
    MainWindow* pwin;
	QSqlQueryModel qualityModel, typeModel;
	QCheckBox *cb[MAXTYPES][MAXQUALITYLEVELS];
	QLabel *qlbl[MAXQUALITYLEVELS];
	QLabel *tlbl[MAXTYPES];
	QPushButton *ok, *cancel;
	int numtypes;
	QVBoxLayout *box;
};

#endif
