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

#ifndef TYPES_H
#define TYPES_H

#include <QCheckBox>
#include <QPushButton>
#include "mainwindow.h"

class types : public QWidget
{
Q_OBJECT
public:
	types( QWidget * parent = 0, Qt::WindowFlags f = 0 );

public slots:
	virtual void OK_clicked();
	virtual void EditCodes_clicked();
	virtual void All_clicked();
	virtual void None_clicked();

protected:
    MainWindow* pwin;
	QCheckBox *cb[MAXTYPES];
	QPushButton *ok, *cancel, *editcodes, *all, *none;
	QSqlQueryModel typeModel;

};

#endif
