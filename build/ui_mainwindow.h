/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Jul 8 22:01:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *title;
    QPushButton *RangeButton;
    QPushButton *QuizButton;
    QPushButton *FileButton;
    QPushButton *FormatButton;
    QPushButton *OrderButton;
    QLabel *questionformat;
    QLabel *questionorder;
    QPushButton *TypeButton;
    QPushButton *PrintQuest;
    QLabel *questiontypes;
    QLabel *verserange;
    QTableView *QuestEdit;
    QPushButton *SearchButton;
    QLineEdit *SearchBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(789, 536);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setGeometry(QRect(0, 30, 789, 483));
        title = new QLabel(centralwidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(0, 0, 370, 42));
        QFont font;
        font.setPointSize(24);
        title->setFont(font);
        title->setTextFormat(Qt::RichText);
        title->setAlignment(Qt::AlignCenter);
        title->setWordWrap(true);
        RangeButton = new QPushButton(centralwidget);
        RangeButton->setObjectName(QString::fromUtf8("RangeButton"));
        RangeButton->setGeometry(QRect(0, 50, 50, 30));
        QuizButton = new QPushButton(centralwidget);
        QuizButton->setObjectName(QString::fromUtf8("QuizButton"));
        QuizButton->setGeometry(QRect(360, 130, 112, 24));
        FileButton = new QPushButton(centralwidget);
        FileButton->setObjectName(QString::fromUtf8("FileButton"));
        FileButton->setGeometry(QRect(360, 40, 120, 24));
        FileButton->setAutoDefault(false);
        FileButton->setDefault(false);
        FormatButton = new QPushButton(centralwidget);
        FormatButton->setObjectName(QString::fromUtf8("FormatButton"));
        FormatButton->setGeometry(QRect(0, 170, 50, 30));
        FormatButton->setAutoDefault(false);
        FormatButton->setDefault(false);
        OrderButton = new QPushButton(centralwidget);
        OrderButton->setObjectName(QString::fromUtf8("OrderButton"));
        OrderButton->setGeometry(QRect(0, 130, 50, 30));
        questionformat = new QLabel(centralwidget);
        questionformat->setObjectName(QString::fromUtf8("questionformat"));
        questionformat->setGeometry(QRect(60, 170, 220, 30));
        questionformat->setWordWrap(false);
        questionorder = new QLabel(centralwidget);
        questionorder->setObjectName(QString::fromUtf8("questionorder"));
        questionorder->setGeometry(QRect(60, 130, 220, 30));
        questionorder->setWordWrap(false);
        TypeButton = new QPushButton(centralwidget);
        TypeButton->setObjectName(QString::fromUtf8("TypeButton"));
        TypeButton->setGeometry(QRect(0, 90, 50, 30));
        PrintQuest = new QPushButton(centralwidget);
        PrintQuest->setObjectName(QString::fromUtf8("PrintQuest"));
        PrintQuest->setGeometry(QRect(0, 210, 50, 30));
        PrintQuest->setMinimumSize(QSize(50, 30));
        questiontypes = new QLabel(centralwidget);
        questiontypes->setObjectName(QString::fromUtf8("questiontypes"));
        questiontypes->setGeometry(QRect(60, 80, 420, 50));
        questiontypes->setAlignment(Qt::AlignVCenter);
        questiontypes->setWordWrap(true);
        verserange = new QLabel(centralwidget);
        verserange->setObjectName(QString::fromUtf8("verserange"));
        verserange->setGeometry(QRect(60, 50, 220, 30));
        verserange->setWordWrap(false);
        QuestEdit = new QTableView(centralwidget);
        QuestEdit->setObjectName(QString::fromUtf8("QuestEdit"));
        QuestEdit->setGeometry(QRect(0, 250, 781, 261));
        SearchButton = new QPushButton(centralwidget);
        SearchButton->setObjectName(QString::fromUtf8("SearchButton"));
        SearchButton->setGeometry(QRect(360, 210, 75, 28));
        SearchBox = new QLineEdit(centralwidget);
        SearchBox->setObjectName(QString::fromUtf8("SearchBox"));
        SearchBox->setGeometry(QRect(130, 210, 211, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 789, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setGeometry(QRect(0, 513, 789, 23));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        title->setText(QApplication::translate("MainWindow", "Quizzing Database", 0, QApplication::UnicodeUTF8));
        RangeButton->setText(QApplication::translate("MainWindow", "Range:", 0, QApplication::UnicodeUTF8));
        QuizButton->setText(QApplication::translate("MainWindow", "Make Quiz", 0, QApplication::UnicodeUTF8));
        FileButton->setText(QApplication::translate("MainWindow", "Change Database", 0, QApplication::UnicodeUTF8));
        FormatButton->setText(QApplication::translate("MainWindow", "Format:", 0, QApplication::UnicodeUTF8));
        OrderButton->setText(QApplication::translate("MainWindow", "Order:", 0, QApplication::UnicodeUTF8));
        questionformat->setText(QString());
        questionorder->setText(QString());
        TypeButton->setText(QApplication::translate("MainWindow", "Types:", 0, QApplication::UnicodeUTF8));
        PrintQuest->setText(QApplication::translate("MainWindow", "Print", 0, QApplication::UnicodeUTF8));
        questiontypes->setText(QString());
        verserange->setText(QString());
        SearchButton->setText(QApplication::translate("MainWindow", "Search", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
