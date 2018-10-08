#ifndef BIBLE_H
#define BIBLE_H

#include <QApplication>
#include <QSqlQueryModel>
#include <QTableView>
#include "mainwindow.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class bible : public QWidget
{
Q_OBJECT
public:
	bible ( QWidget* parent = 0, Qt::WindowFlags fl = 0 );

	void setSearchModel( QSqlQueryModel * );

public slots:
	virtual void verseCopy( const QModelIndex & );
//	virtual void OK_clicked();

private slots:
	void copyVerse();

protected:
    MainWindow *pwin;
	QTableView *sview;
//	QPushButton *ok, *cancel;
	void closeEvent( QCloseEvent * );
	void createMenu();
	QAction *insertCopyAct;
	QString vselected;
};

#endif
