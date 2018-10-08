/********************************************************************************
** Form generated from reading UI file 'orderdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERDLG_H
#define UI_ORDERDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_orderdlg
{
public:
    QSplitter *splitter1;
    QPushButton *OK;
    QPushButton *Cancel;
    QGroupBox *groupBox2;
    QRadioButton *alphabutton_2;
    QRadioButton *typebutton_2;
    QRadioButton *versebutton_2;
    QGroupBox *groupBox1;
    QRadioButton *alphabutton;
    QRadioButton *typebutton;
    QRadioButton *versebutton;

    void setupUi(QWidget *orderdlg)
    {
        if (orderdlg->objectName().isEmpty())
            orderdlg->setObjectName(QStringLiteral("orderdlg"));
        orderdlg->resize(270, 161);
        orderdlg->setMinimumSize(QSize(270, 160));
        splitter1 = new QSplitter(orderdlg);
        splitter1->setObjectName(QStringLiteral("splitter1"));
        splitter1->setGeometry(QRect(0, 130, 264, 24));
        splitter1->setOrientation(Qt::Horizontal);
        OK = new QPushButton(splitter1);
        OK->setObjectName(QStringLiteral("OK"));
        splitter1->addWidget(OK);
        Cancel = new QPushButton(splitter1);
        Cancel->setObjectName(QStringLiteral("Cancel"));
        splitter1->addWidget(Cancel);
        groupBox2 = new QGroupBox(orderdlg);
        groupBox2->setObjectName(QStringLiteral("groupBox2"));
        groupBox2->setGeometry(QRect(140, 10, 111, 111));
        alphabutton_2 = new QRadioButton(groupBox2);
        alphabutton_2->setObjectName(QStringLiteral("alphabutton_2"));
        alphabutton_2->setGeometry(QRect(10, 80, 80, 20));
        typebutton_2 = new QRadioButton(groupBox2);
        typebutton_2->setObjectName(QStringLiteral("typebutton_2"));
        typebutton_2->setGeometry(QRect(10, 50, 80, 20));
        versebutton_2 = new QRadioButton(groupBox2);
        versebutton_2->setObjectName(QStringLiteral("versebutton_2"));
        versebutton_2->setGeometry(QRect(10, 20, 80, 20));
        versebutton_2->setChecked(true);
        groupBox1 = new QGroupBox(orderdlg);
        groupBox1->setObjectName(QStringLiteral("groupBox1"));
        groupBox1->setGeometry(QRect(10, 10, 111, 111));
        alphabutton = new QRadioButton(groupBox1);
        alphabutton->setObjectName(QStringLiteral("alphabutton"));
        alphabutton->setGeometry(QRect(10, 80, 80, 20));
        typebutton = new QRadioButton(groupBox1);
        typebutton->setObjectName(QStringLiteral("typebutton"));
        typebutton->setGeometry(QRect(10, 50, 80, 20));
        versebutton = new QRadioButton(groupBox1);
        versebutton->setObjectName(QStringLiteral("versebutton"));
        versebutton->setGeometry(QRect(10, 20, 80, 20));
        versebutton->setChecked(true);

        retranslateUi(orderdlg);
        QObject::connect(OK, SIGNAL(clicked()), orderdlg, SLOT(OK_clicked()));
        QObject::connect(Cancel, SIGNAL(clicked()), orderdlg, SLOT(close()));

        QMetaObject::connectSlotsByName(orderdlg);
    } // setupUi

    void retranslateUi(QWidget *orderdlg)
    {
        orderdlg->setWindowTitle(QApplication::translate("orderdlg", "Select Order", 0));
        OK->setText(QApplication::translate("orderdlg", "OK", 0));
        Cancel->setText(QApplication::translate("orderdlg", "Cancel", 0));
        groupBox2->setTitle(QApplication::translate("orderdlg", "Secondary Sort", 0));
        alphabutton_2->setText(QApplication::translate("orderdlg", "By Alpha", 0));
        typebutton_2->setText(QApplication::translate("orderdlg", "By Type", 0));
        versebutton_2->setText(QApplication::translate("orderdlg", "By Verse", 0));
        groupBox1->setTitle(QApplication::translate("orderdlg", "Primary Sort", 0));
        alphabutton->setText(QApplication::translate("orderdlg", "By Alpha", 0));
        typebutton->setText(QApplication::translate("orderdlg", "By Type", 0));
        versebutton->setText(QApplication::translate("orderdlg", "By Verse", 0));
    } // retranslateUi

};

namespace Ui {
    class orderdlg: public Ui_orderdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERDLG_H
