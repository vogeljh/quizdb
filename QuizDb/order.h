#ifndef ORDER_H
#define ORDER_H
//
#include <QWidget>
#include "ui_orderdlg.h"
#include "mainwindow.h"
//
class order : public QWidget, public Ui::orderdlg
{
Q_OBJECT
public:
	order( QWidget * parent = 0, Qt::WindowFlags f = 0 );

public slots:
	virtual void OK_clicked();

private:
    MainWindow* pwin;
};
#endif





