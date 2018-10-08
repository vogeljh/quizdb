#include <QApplication>
#include <QSqlDatabase>
#include <QFont>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app( argc, argv );
    QSqlDatabase db;
    MainWindow win;

    QFont sansFont("Helvetica [Cronyx]", 12);
    app.setFont( sansFont );
    db = QSqlDatabase::addDatabase("QSQLITE");
    win.SetDb( &db );
    win.LoadDb();
    win.show();
    app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
    return app.exec();
}
