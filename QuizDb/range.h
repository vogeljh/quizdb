#ifndef RANGE_H
#define RANGE_H
//
#include <QWidget>
#include "ui_rangedlg.h"
#include "mainwindow.h"
//
class range : public QWidget, public Ui::rangedlg
{
Q_OBJECT
public:
	range( QWidget * parent = 0, Qt::WindowFlags f = 0 );

public slots:
	virtual void chapter2selected ( int );
	virtual void book2selected( int );
	virtual void chapter1selected ( int );
	virtual void book1selected( int );
	virtual void rangedlg_ok();

protected:
    MainWindow* pwin;
	vRange *vsRange;

};
#endif
