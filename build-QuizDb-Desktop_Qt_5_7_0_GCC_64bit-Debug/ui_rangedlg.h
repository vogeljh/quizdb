/********************************************************************************
** Form generated from reading UI file 'rangedlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANGEDLG_H
#define UI_RANGEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rangedlg
{
public:
    QPushButton *cancel;
    QPushButton *ok;
    QGroupBox *fromBox;
    QSpinBox *verse1;
    QComboBox *book1;
    QSpinBox *chapter1;
    QGroupBox *ToBox;
    QSpinBox *verse2;
    QComboBox *book2;
    QSpinBox *chapter2;

    void setupUi(QWidget *rangedlg)
    {
        if (rangedlg->objectName().isEmpty())
            rangedlg->setObjectName(QStringLiteral("rangedlg"));
        rangedlg->resize(340, 160);
        rangedlg->setMinimumSize(QSize(340, 160));
        cancel = new QPushButton(rangedlg);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setGeometry(QRect(262, 130, 60, 24));
        ok = new QPushButton(rangedlg);
        ok->setObjectName(QStringLiteral("ok"));
        ok->setGeometry(QRect(200, 130, 50, 24));
        fromBox = new QGroupBox(rangedlg);
        fromBox->setObjectName(QStringLiteral("fromBox"));
        fromBox->setGeometry(QRect(0, 0, 331, 51));
        verse1 = new QSpinBox(fromBox);
        verse1->setObjectName(QStringLiteral("verse1"));
        verse1->setGeometry(QRect(270, 20, 50, 22));
        verse1->setMinimum(1);
        book1 = new QComboBox(fromBox);
        book1->setObjectName(QStringLiteral("book1"));
        book1->setGeometry(QRect(20, 20, 180, 22));
        chapter1 = new QSpinBox(fromBox);
        chapter1->setObjectName(QStringLiteral("chapter1"));
        chapter1->setGeometry(QRect(210, 20, 50, 22));
        chapter1->setMinimum(1);
        ToBox = new QGroupBox(rangedlg);
        ToBox->setObjectName(QStringLiteral("ToBox"));
        ToBox->setGeometry(QRect(0, 60, 331, 51));
        verse2 = new QSpinBox(ToBox);
        verse2->setObjectName(QStringLiteral("verse2"));
        verse2->setGeometry(QRect(270, 20, 50, 22));
        verse2->setMinimum(1);
        book2 = new QComboBox(ToBox);
        book2->setObjectName(QStringLiteral("book2"));
        book2->setGeometry(QRect(20, 20, 180, 22));
        chapter2 = new QSpinBox(ToBox);
        chapter2->setObjectName(QStringLiteral("chapter2"));
        chapter2->setGeometry(QRect(210, 20, 50, 22));
        chapter2->setMinimum(1);

        retranslateUi(rangedlg);
        QObject::connect(ok, SIGNAL(clicked()), rangedlg, SLOT(rangedlg_ok()));
        QObject::connect(cancel, SIGNAL(clicked()), rangedlg, SLOT(close()));
        QObject::connect(book1, SIGNAL(activated(int)), rangedlg, SLOT(book1selected(int)));
        QObject::connect(chapter1, SIGNAL(valueChanged(int)), rangedlg, SLOT(chapter1selected(int)));
        QObject::connect(book2, SIGNAL(activated(int)), rangedlg, SLOT(book2selected(int)));
        QObject::connect(chapter2, SIGNAL(valueChanged(int)), rangedlg, SLOT(chapter2selected(int)));

        QMetaObject::connectSlotsByName(rangedlg);
    } // setupUi

    void retranslateUi(QWidget *rangedlg)
    {
        rangedlg->setWindowTitle(QApplication::translate("rangedlg", "Set Verse Range", 0));
        cancel->setText(QApplication::translate("rangedlg", "Cancel", 0));
        ok->setText(QApplication::translate("rangedlg", "OK", 0));
        fromBox->setTitle(QApplication::translate("rangedlg", "From:", 0));
        ToBox->setTitle(QApplication::translate("rangedlg", "To:", 0));
    } // retranslateUi

};

namespace Ui {
    class rangedlg: public Ui_rangedlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANGEDLG_H
