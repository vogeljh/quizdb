#ifndef QUIZQUESTEDITVIEW_H
#define QUIZQUESTEDITVIEW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include "quizview.h"
#include "quizquestmodel.h"

class quizQuestEditView : public QWidget
{
    Q_OBJECT
public:
    quizQuestEditView( QWidget *parent = 0, int qnum = 0, Qt::WindowFlags fl = 0 );

    void setQuizModel( class quizQuestModel * );
    void sizeQuizQuestEditView( );

signals:

public slots:
    virtual void OK_clicked();
//    virtual void Cancel_clicked();

protected:
    class quizview *pwin;
    QTableView *quizQuestEdit;

private:
    int editqnum;
    quizQuestModel *quizeditmodel;
};

#endif // QUIZQUESTEDITVIEW_H
