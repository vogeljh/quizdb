/********************************************************************************
** Form generated from reading UI file 'formatdlg.ui'
**
** Created: Sun Jul 8 22:01:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMATDLG_H
#define UI_FORMATDLG_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSplitter>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formatdlg
{
public:
    QSplitter *splitter1;
    QPushButton *OK;
    QPushButton *Cancel;
    QGroupBox *groupBox;
    QRadioButton *noanswerbutton;
    QRadioButton *sidebysidebutton;
    QRadioButton *fronttobackbutton;
    QRadioButton *twocolumnbutton;

    void setupUi(QWidget *formatdlg)
    {
        if (formatdlg->objectName().isEmpty())
            formatdlg->setObjectName(QString::fromUtf8("formatdlg"));
        formatdlg->resize(280, 207);
        formatdlg->setMinimumSize(QSize(270, 200));
        splitter1 = new QSplitter(formatdlg);
        splitter1->setObjectName(QString::fromUtf8("splitter1"));
        splitter1->setGeometry(QRect(10, 170, 264, 24));
        splitter1->setOrientation(Qt::Horizontal);
        OK = new QPushButton(splitter1);
        OK->setObjectName(QString::fromUtf8("OK"));
        splitter1->addWidget(OK);
        Cancel = new QPushButton(splitter1);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        splitter1->addWidget(Cancel);
        groupBox = new QGroupBox(formatdlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 251, 151));
        noanswerbutton = new QRadioButton(groupBox);
        noanswerbutton->setObjectName(QString::fromUtf8("noanswerbutton"));
        noanswerbutton->setGeometry(QRect(20, 110, 107, 20));
        sidebysidebutton = new QRadioButton(groupBox);
        sidebysidebutton->setObjectName(QString::fromUtf8("sidebysidebutton"));
        sidebysidebutton->setGeometry(QRect(20, 80, 110, 20));
        fronttobackbutton = new QRadioButton(groupBox);
        fronttobackbutton->setObjectName(QString::fromUtf8("fronttobackbutton"));
        fronttobackbutton->setGeometry(QRect(20, 50, 110, 20));
        twocolumnbutton = new QRadioButton(groupBox);
        twocolumnbutton->setObjectName(QString::fromUtf8("twocolumnbutton"));
        twocolumnbutton->setGeometry(QRect(20, 20, 90, 20));
        twocolumnbutton->setChecked(true);

        retranslateUi(formatdlg);
        QObject::connect(OK, SIGNAL(clicked()), formatdlg, SLOT(OK_clicked()));
        QObject::connect(Cancel, SIGNAL(clicked()), formatdlg, SLOT(close()));

        QMetaObject::connectSlotsByName(formatdlg);
    } // setupUi

    void retranslateUi(QWidget *formatdlg)
    {
        formatdlg->setWindowTitle(QApplication::translate("formatdlg", "Print format", 0, QApplication::UnicodeUTF8));
        OK->setText(QApplication::translate("formatdlg", "OK", 0, QApplication::UnicodeUTF8));
        Cancel->setText(QApplication::translate("formatdlg", "Cancel", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("formatdlg", "Format:", 0, QApplication::UnicodeUTF8));
        noanswerbutton->setText(QApplication::translate("formatdlg", "No Answers", 0, QApplication::UnicodeUTF8));
        sidebysidebutton->setText(QApplication::translate("formatdlg", "Side-by-Side", 0, QApplication::UnicodeUTF8));
        fronttobackbutton->setText(QApplication::translate("formatdlg", "Front-to-Back", 0, QApplication::UnicodeUTF8));
        twocolumnbutton->setText(QApplication::translate("formatdlg", "2 columns", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class formatdlg: public Ui_formatdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMATDLG_H
