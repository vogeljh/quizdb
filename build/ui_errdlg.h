/********************************************************************************
** Form generated from reading UI file 'errdlg.ui'
**
** Created: Sun Jul 8 22:01:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRDLG_H
#define UI_ERRDLG_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

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
            errdlg->setObjectName(QString::fromUtf8("errdlg"));
        errdlg->resize(281, 109);
        errdlg->setMinimumSize(QSize(250, 90));
        errdlg->setModal(true);
        gridLayout = new QGridLayout(errdlg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        message = new QLabel(errdlg);
        message->setObjectName(QString::fromUtf8("message"));
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
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem2);

        ok = new QPushButton(errdlg);
        ok->setObjectName(QString::fromUtf8("ok"));

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
        errdlg->setWindowTitle(QApplication::translate("errdlg", "Error", 0, QApplication::UnicodeUTF8));
        message->setText(QString());
        ok->setText(QApplication::translate("errdlg", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class errdlg: public Ui_errdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRDLG_H
