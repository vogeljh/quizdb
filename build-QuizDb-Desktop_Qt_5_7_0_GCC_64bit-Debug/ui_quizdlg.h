/********************************************************************************
** Form generated from reading UI file 'quizdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZDLG_H
#define UI_QUIZDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

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
    QGroupBox *formatGroupBox;
    QRadioButton *LaTeXradioButton;
    QRadioButton *RTFradioButton;
    QCheckBox *HighlightKeyCheckBox;

    void setupUi(QWidget *quizdlg)
    {
        if (quizdlg->objectName().isEmpty())
            quizdlg->setObjectName(QStringLiteral("quizdlg"));
        quizdlg->resize(339, 314);
        quizdlg->setMinimumSize(QSize(250, 110));
        TimesUsedCheckBox = new QCheckBox(quizdlg);
        TimesUsedCheckBox->setObjectName(QStringLiteral("TimesUsedCheckBox"));
        TimesUsedCheckBox->setGeometry(QRect(10, 170, 171, 20));
        TimesUsedCheckBox->setChecked(true);
        textLabel1 = new QLabel(quizdlg);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setGeometry(QRect(60, 140, 121, 20));
        textLabel1->setWordWrap(false);
        QuizSpinBox = new QSpinBox(quizdlg);
        QuizSpinBox->setObjectName(QStringLiteral("QuizSpinBox"));
        QuizSpinBox->setGeometry(QRect(10, 140, 50, 22));
        QuizSpinBox->setMinimum(1);
        QuizSpinBox->setMaximum(10);
        layout1 = new QWidget(quizdlg);
        layout1->setObjectName(QStringLiteral("layout1"));
        layout1->setGeometry(QRect(0, 280, 341, 30));
        hboxLayout = new QHBoxLayout(layout1);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        OkButton = new QPushButton(layout1);
        OkButton->setObjectName(QStringLiteral("OkButton"));

        hboxLayout->addWidget(OkButton);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);

        CancelButton = new QPushButton(layout1);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        hboxLayout->addWidget(CancelButton);

        spacerItem2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem2);

        fromBox = new QGroupBox(quizdlg);
        fromBox->setObjectName(QStringLiteral("fromBox"));
        fromBox->setGeometry(QRect(0, 10, 291, 61));
        verse1 = new QSpinBox(fromBox);
        verse1->setObjectName(QStringLiteral("verse1"));
        verse1->setGeometry(QRect(220, 30, 50, 22));
        verse1->setMinimum(1);
        book1 = new QComboBox(fromBox);
        book1->setObjectName(QStringLiteral("book1"));
        book1->setGeometry(QRect(10, 30, 151, 22));
        chapter1 = new QSpinBox(fromBox);
        chapter1->setObjectName(QStringLiteral("chapter1"));
        chapter1->setGeometry(QRect(170, 30, 50, 22));
        chapter1->setMinimum(1);
        ToBox = new QGroupBox(quizdlg);
        ToBox->setObjectName(QStringLiteral("ToBox"));
        ToBox->setGeometry(QRect(0, 70, 291, 61));
        verse2 = new QSpinBox(ToBox);
        verse2->setObjectName(QStringLiteral("verse2"));
        verse2->setGeometry(QRect(220, 30, 50, 22));
        verse2->setMinimum(1);
        book2 = new QComboBox(ToBox);
        book2->setObjectName(QStringLiteral("book2"));
        book2->setGeometry(QRect(10, 30, 151, 22));
        chapter2 = new QSpinBox(ToBox);
        chapter2->setObjectName(QStringLiteral("chapter2"));
        chapter2->setGeometry(QRect(170, 30, 50, 22));
        chapter2->setMinimum(1);
        editQuizButton = new QPushButton(quizdlg);
        editQuizButton->setObjectName(QStringLiteral("editQuizButton"));
        editQuizButton->setGeometry(QRect(190, 140, 141, 51));
        statusLabel = new QLabel(quizdlg);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(170, 200, 171, 20));
        statusLabel->setWordWrap(false);
        formatGroupBox = new QGroupBox(quizdlg);
        formatGroupBox->setObjectName(QStringLiteral("formatGroupBox"));
        formatGroupBox->setGeometry(QRect(10, 230, 171, 41));
        LaTeXradioButton = new QRadioButton(formatGroupBox);
        LaTeXradioButton->setObjectName(QStringLiteral("LaTeXradioButton"));
        LaTeXradioButton->setGeometry(QRect(10, 20, 91, 21));
        LaTeXradioButton->setChecked(true);
        RTFradioButton = new QRadioButton(formatGroupBox);
        RTFradioButton->setObjectName(QStringLiteral("RTFradioButton"));
        RTFradioButton->setGeometry(QRect(110, 20, 61, 21));
        HighlightKeyCheckBox = new QCheckBox(quizdlg);
        HighlightKeyCheckBox->setObjectName(QStringLiteral("HighlightKeyCheckBox"));
        HighlightKeyCheckBox->setGeometry(QRect(10, 200, 151, 20));
        HighlightKeyCheckBox->setChecked(true);

        retranslateUi(quizdlg);
        QObject::connect(OkButton, SIGNAL(clicked()), quizdlg, SLOT(OkButton_clicked()));
        QObject::connect(CancelButton, SIGNAL(clicked()), quizdlg, SLOT(cancel_clicked()));
        QObject::connect(editQuizButton, SIGNAL(clicked()), quizdlg, SLOT(editQuiz_clicked()));

        QMetaObject::connectSlotsByName(quizdlg);
    } // setupUi

    void retranslateUi(QWidget *quizdlg)
    {
        quizdlg->setWindowTitle(QApplication::translate("quizdlg", "Make Quizzes", 0));
        TimesUsedCheckBox->setText(QApplication::translate("quizdlg", "Reset Times Used", 0));
        textLabel1->setText(QApplication::translate("quizdlg", "# of Quizzes", 0));
        OkButton->setText(QApplication::translate("quizdlg", "OK", 0));
        CancelButton->setText(QApplication::translate("quizdlg", "Cancel", 0));
        fromBox->setTitle(QApplication::translate("quizdlg", "Verse range from:", 0));
        ToBox->setTitle(QApplication::translate("quizdlg", "Verse range to:", 0));
        editQuizButton->setText(QApplication::translate("quizdlg", "Edit Quiz Design", 0));
        statusLabel->setText(QString());
        formatGroupBox->setTitle(QApplication::translate("quizdlg", "Print Format", 0));
        LaTeXradioButton->setText(QApplication::translate("quizdlg", "LaTeX", 0));
        RTFradioButton->setText(QApplication::translate("quizdlg", "RTF", 0));
        HighlightKeyCheckBox->setText(QApplication::translate("quizdlg", "Highlight Key", 0));
    } // retranslateUi

};

namespace Ui {
    class quizdlg: public Ui_quizdlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZDLG_H
