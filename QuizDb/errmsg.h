#ifndef ERRMSG_H
#define ERRMSG_H
//
#include <QDialog>
#include "ui_errdlg.h"
//
class errmsg : public QDialog, public Ui::errdlg
{
Q_OBJECT
public:
	errmsg( QWidget * parent = 0, Qt::WindowFlags f = 0 );
private slots:
};
#endif





