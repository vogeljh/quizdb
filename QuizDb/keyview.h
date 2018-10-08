#ifndef KEYVIEW_H
#define KEYVIEW_H
//
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include "mainwindow.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class keyView : public QWidget
{
Q_OBJECT
public:
	keyView( QWidget *parent, Qt::WindowFlags fl );
	
	void setSearchModel( QStandardItemModel * );
	void sizeKeyView( int );

public slots:

private slots:

protected:
    MainWindow *pwin;
	QTableView *kView;
};
//
#endif
