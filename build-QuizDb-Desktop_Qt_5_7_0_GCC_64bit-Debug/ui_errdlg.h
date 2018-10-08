/********************************************************************************
** Form generated from reading UI file 'errdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRDLG_H
#define UI_ERRDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_errdlg
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QLabel *message;
    QSpacerItem *spacerItem1;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem2;
    QPushButton *ok;
    QSpacerItem *spacerItem3;

    void setupUi(QDialog *errdlg)
    {
        if (errdlg->objectName().isEmpty())
            errdlg->setObjectName(QStringLiteral("errdlg"));
        errdlg->resize(281, 109);
        errdlg->setMinimumSize(QSize(250, 90));
        errdlg->setModal(true);
        gridLayout = new QGridLayout(errdlg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        message = new QLabel(errdlg);
        message->setObjectName(QStringLiteral("message"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(20);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(message->sizePolicy().hasHeightForWidth());
        message->setSizePolicy(sizePolicy);
        message->setAlignment(Qt::AlignVCenter);
        message->setWordWrap(true);

        hboxLayout->addWidget(message);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);


        gridLayout->addLayout(hboxLayout, 0, 0, 1, 1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem2);

        ok = new QPushButton(errdlg);
        ok->setObjectName(QStringLiteral("ok"));

        hboxLayout1->addWidget(ok);

        spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem3);


        gridLayout->addLayout(hboxLayout1, 1, 0, 1, 1);


        retranslateUi(errdlg);
        QObject::connect(ok, SIGNAL(clicked()), errdlg, SLOT(close()));

        QMetaObject::connectSlotsByName(errdlg);
    } // setupUi

    void retranslateUi(QDialog *errdlg)
    {
        errdlg->setWindowTitle(QApplication::translate("errdlg", "Error", 0));
        message->setText(QString());
        ok->setText(QApplication::translate("errdlg", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class errdlg: public Ui_errdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRDLG_H
