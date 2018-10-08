/********************************************************************************
** Form generated from reading UI file 'quizdlg.ui'
**
** Created: Sun Jul 8 22:01:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZDLG_H
#define UI_QUIZDLG_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_quizdlg
{
public:
    QCheckBox *TimesUsedCheckBox;
    QLabel *textLabel1;
    QSpinBox *QuizSpinBox;
    QWidget *layout1;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *OkButton;
    QSpacerItem *spacerItem1;
    QPushButton *CancelButton;
    QSpacerItem *spacerItem2;
    QGroupBox *fromBox;
    QSpinBox *verse1;
    QComboBox *book1;
    QSpinBox *chapter1;
    QGroupBox *ToBox;
    QSpinBox *verse2;
    QComboBox *book2;
    QSpinBox *chapter2;
    QPushButton *editQuizButton;
    QLabel *statusLabel;

    void setupUi(QWidget *quizdlg)
    {
        if (quizdlg->objectName().isEmpty())
            quizdlg->setObjectName(QString::fromUtf8("quizdlg"));
        quizdlg->resize(293, 260);
        quizdlg->setMinimumSize(QSize(250, 110));
        TimesUsedCheckBox = new QCheckBox(quizdlg);
        TimesUsedCheckBox->setObjectName(QString::fromUtf8("TimesUsedCheckBox"));
        TimesUsedCheckBox->setGeometry(QRect(10, 170, 141, 20));
        TimesUsedCheckBox->setChecked(true);
        textLabel1 = new QLabel(quizdlg);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setGeometry(QRect(60, 140, 81, 20));
        textLabel1->setWordWrap(false);
        QuizSpinBox = new QSpinBox(quizdlg);
        QuizSpinBox->setObjectName(QString::fromUtf8("QuizSpinBox"));
        QuizSpinBox->setGeometry(QRect(10, 140, 50, 22));
        QuizSpinBox->setMinimum(1);
        QuizSpinBox->setMaximum(10);
        layout1 = new QWidget(quizdlg);
        layout1->setObjectName(QString::fromUtf8("layout1"));
        layout1->setGeometry(QRect(0, 220, 291, 30));
        hboxLayout = new QHBoxLayout(layout1);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        OkButton = new QPushButton(layout1);
        OkButton->setObjectName(QString::fromUtf8("OkButton"));

        hboxLayout->addWidget(OkButton);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);

        CancelButton = new QPushButton(layout1);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

        hboxLayout->addWidget(CancelButton);

        spacerItem2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem2);

        fromBox = new QGroupBox(quizdlg);
        fromBox->setObjectName(QString::fromUtf8("fromBox"));
        fromBox->setGeometry(QRect(0, 10, 291, 61));
        verse1 = new QSpinBox(fromBox);
        verse1->setObjectName(QString::fromUtf8("verse1"));
        verse1->setGeometry(QRect(220, 30, 50, 22));
        verse1->setMinimum(1);
        book1 = new QComboBox(fromBox);
        book1->setObjectName(QString::fromUtf8("book1"));
        book1->setGeometry(QRect(10, 30, 151, 22));
        chapter1 = new QSpinBox(fromBox);
        chapter1->setObjectName(QString::fromUtf8("chapter1"));
        chapter1->setGeometry(QRect(170, 30, 50, 22));
        chapter1->setMinimum(1);
        ToBox = new QGroupBox(quizdlg);
        ToBox->setObjectName(QString::fromUtf8("ToBox"));
        ToBox->setGeometry(QRect(0, 70, 291, 61));
        verse2 = new QSpinBox(ToBox);
        verse2->setObjectName(QString::fromUtf8("verse2"));
        verse2->setGeometry(QRect(220, 30, 50, 22));
        verse2->setMinimum(1);
        book2 = new QComboBox(ToBox);
        book2->setObjectName(QString::fromUtf8("book2"));
        book2->setGeometry(QRect(10, 30, 151, 22));
        chapter2 = new QSpinBox(ToBox);
        chapter2->setObjectName(QString::fromUtf8("chapter2"));
        chapter2->setGeometry(QRect(170, 30, 50, 22));
        chapter2->setMinimum(1);
        editQuizButton = new QPushButton(quizdlg);
        editQuizButton->setObjectName(QString::fromUtf8("editQuizButton"));
        editQuizButton->setGeometry(QRect(160, 140, 131, 51));
        statusLabel = new QLabel(quizdlg);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(80, 200, 111, 20));
        statusLabel->setWordWrap(false);

        retranslateUi(quizdlg);
        QObject::connect(OkButton, SIGNAL(clicked()), quizdlg, SLOT(OkButton_clicked()));
        QObject::connect(CancelButton, SIGNAL(clicked()), quizdlg, SLOT(cancel_clicked()));
        QObject::connect(editQuizButton, SIGNAL(clicked()), quizdlg, SLOT(editQuiz_clicked()));

        QMetaObject::connectSlotsByName(quizdlg);
    } // setupUi

    void retranslateUi(QWidget *quizdlg)
    {
        quizdlg->setWindowTitle(QApplication::translate("quizdlg", "Make Quizzes", 0, QApplication::UnicodeUTF8));
        TimesUsedCheckBox->setText(QApplication::translate("quizdlg", "Reset Times Used", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("quizdlg", "# of Quizzes", 0, QApplication::UnicodeUTF8));
        OkButton->setText(QApplication::translate("quizdlg", "OK", 0, QApplication::UnicodeUTF8));
        CancelButton->setText(QApplication::translate("quizdlg", "Cancel", 0, QApplication::UnicodeUTF8));
        fromBox->setTitle(QApplication::translate("quizdlg", "Verse range from:", 0, QApplication::UnicodeUTF8));
        ToBox->setTitle(QApplication::translate("quizdlg", "Verse range to:", 0, QApplication::UnicodeUTF8));
        editQuizButton->setText(QApplication::translate("quizdlg", "Edit Quiz Design", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class quizdlg: public Ui_quizdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZDLG_H
