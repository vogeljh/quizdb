/********************************************************************************
** Form generated from reading UI file 'printdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINTDLG_H
#define UI_PRINTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *OkBox;
    QGroupBox *fromBox;
    QSpinBox *verse1;
    QComboBox *book1;
    QSpinBox *chapter1;
    QGroupBox *ToBox;
    QSpinBox *verse2;
    QComboBox *book2;
    QSpinBox *chapter2;
    QGroupBox *formatBox;
    QRadioButton *noanswerbutton;
    QRadioButton *sidebysidebutton;
    QRadioButton *fronttobackbutton;
    QRadioButton *twocolumnbutton;
    QRadioButton *indexbutton;
    QGroupBox *sortBox1;
    QRadioButton *alphabutton;
    QRadioButton *typebutton;
    QRadioButton *versebutton;
    QGroupBox *sortBox2;
    QRadioButton *alphabutton2;
    QRadioButton *typebutton2;
    QRadioButton *versebutton2;
    QGroupBox *outputBox;
    QRadioButton *LaTeXButton;
    QRadioButton *RTFButton;
    QGroupBox *KeyWordBox;
    QRadioButton *KeyWordButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *TypeBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(559, 453);
        OkBox = new QDialogButtonBox(Dialog);
        OkBox->setObjectName(QStringLiteral("OkBox"));
        OkBox->setGeometry(QRect(320, 410, 161, 32));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OkBox->sizePolicy().hasHeightForWidth());
        OkBox->setSizePolicy(sizePolicy);
        OkBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        fromBox = new QGroupBox(Dialog);
        fromBox->setObjectName(QStringLiteral("fromBox"));
        fromBox->setGeometry(QRect(0, 10, 281, 61));
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
        ToBox = new QGroupBox(Dialog);
        ToBox->setObjectName(QStringLiteral("ToBox"));
        ToBox->setGeometry(QRect(0, 70, 281, 61));
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
        formatBox = new QGroupBox(Dialog);
        formatBox->setObjectName(QStringLiteral("formatBox"));
        formatBox->setGeometry(QRect(0, 260, 161, 181));
        formatBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        noanswerbutton = new QRadioButton(formatBox);
        noanswerbutton->setObjectName(QStringLiteral("noanswerbutton"));
        noanswerbutton->setGeometry(QRect(20, 120, 131, 20));
        sidebysidebutton = new QRadioButton(formatBox);
        sidebysidebutton->setObjectName(QStringLiteral("sidebysidebutton"));
        sidebysidebutton->setGeometry(QRect(20, 90, 131, 20));
        fronttobackbutton = new QRadioButton(formatBox);
        fronttobackbutton->setObjectName(QStringLiteral("fronttobackbutton"));
        fronttobackbutton->setGeometry(QRect(20, 60, 131, 20));
        twocolumnbutton = new QRadioButton(formatBox);
        twocolumnbutton->setObjectName(QStringLiteral("twocolumnbutton"));
        twocolumnbutton->setGeometry(QRect(20, 30, 131, 20));
        twocolumnbutton->setChecked(true);
        indexbutton = new QRadioButton(formatBox);
        indexbutton->setObjectName(QStringLiteral("indexbutton"));
        indexbutton->setGeometry(QRect(20, 150, 131, 21));
        sortBox1 = new QGroupBox(Dialog);
        sortBox1->setObjectName(QStringLiteral("sortBox1"));
        sortBox1->setGeometry(QRect(0, 130, 161, 121));
        alphabutton = new QRadioButton(sortBox1);
        alphabutton->setObjectName(QStringLiteral("alphabutton"));
        alphabutton->setGeometry(QRect(10, 90, 131, 20));
        typebutton = new QRadioButton(sortBox1);
        typebutton->setObjectName(QStringLiteral("typebutton"));
        typebutton->setGeometry(QRect(10, 60, 131, 20));
        versebutton = new QRadioButton(sortBox1);
        versebutton->setObjectName(QStringLiteral("versebutton"));
        versebutton->setGeometry(QRect(10, 30, 121, 20));
        versebutton->setChecked(true);
        sortBox2 = new QGroupBox(Dialog);
        sortBox2->setObjectName(QStringLiteral("sortBox2"));
        sortBox2->setGeometry(QRect(160, 130, 161, 121));
        alphabutton2 = new QRadioButton(sortBox2);
        alphabutton2->setObjectName(QStringLiteral("alphabutton2"));
        alphabutton2->setGeometry(QRect(10, 90, 80, 20));
        typebutton2 = new QRadioButton(sortBox2);
        typebutton2->setObjectName(QStringLiteral("typebutton2"));
        typebutton2->setGeometry(QRect(10, 60, 80, 20));
        versebutton2 = new QRadioButton(sortBox2);
        versebutton2->setObjectName(QStringLiteral("versebutton2"));
        versebutton2->setGeometry(QRect(10, 30, 80, 20));
        versebutton2->setChecked(true);
        outputBox = new QGroupBox(Dialog);
        outputBox->setObjectName(QStringLiteral("outputBox"));
        outputBox->setGeometry(QRect(160, 260, 161, 91));
        LaTeXButton = new QRadioButton(outputBox);
        LaTeXButton->setObjectName(QStringLiteral("LaTeXButton"));
        LaTeXButton->setGeometry(QRect(10, 30, 103, 21));
        LaTeXButton->setChecked(true);
        RTFButton = new QRadioButton(outputBox);
        RTFButton->setObjectName(QStringLiteral("RTFButton"));
        RTFButton->setGeometry(QRect(10, 50, 103, 31));
        KeyWordBox = new QGroupBox(Dialog);
        KeyWordBox->setObjectName(QStringLiteral("KeyWordBox"));
        KeyWordBox->setGeometry(QRect(160, 350, 161, 61));
        KeyWordButton = new QRadioButton(KeyWordBox);
        KeyWordButton->setObjectName(QStringLiteral("KeyWordButton"));
        KeyWordButton->setGeometry(QRect(10, 30, 101, 21));
        KeyWordButton->setChecked(true);
        verticalLayoutWidget = new QWidget(Dialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(320, 60, 231, 271));
        TypeBox = new QVBoxLayout(verticalLayoutWidget);
        TypeBox->setObjectName(QStringLiteral("TypeBox"));
        TypeBox->setContentsMargins(0, 0, 0, 0);
        QWidget::setTabOrder(book1, chapter1);
        QWidget::setTabOrder(chapter1, verse1);
        QWidget::setTabOrder(verse1, book2);
        QWidget::setTabOrder(book2, chapter2);
        QWidget::setTabOrder(chapter2, verse2);
        QWidget::setTabOrder(verse2, versebutton);
        QWidget::setTabOrder(versebutton, typebutton);
        QWidget::setTabOrder(typebutton, alphabutton);
        QWidget::setTabOrder(alphabutton, versebutton2);
        QWidget::setTabOrder(versebutton2, typebutton2);
        QWidget::setTabOrder(typebutton2, alphabutton2);
        QWidget::setTabOrder(alphabutton2, twocolumnbutton);
        QWidget::setTabOrder(twocolumnbutton, fronttobackbutton);
        QWidget::setTabOrder(fronttobackbutton, sidebysidebutton);
        QWidget::setTabOrder(sidebysidebutton, noanswerbutton);
        QWidget::setTabOrder(noanswerbutton, LaTeXButton);
        QWidget::setTabOrder(LaTeXButton, RTFButton);
        QWidget::setTabOrder(RTFButton, OkBox);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        fromBox->setTitle(QApplication::translate("Dialog", "Verse range from:", 0));
        ToBox->setTitle(QApplication::translate("Dialog", "Verse range to:", 0));
        formatBox->setTitle(QApplication::translate("Dialog", "Choose Format", 0));
        noanswerbutton->setText(QApplication::translate("Dialog", "No Answers", 0));
        sidebysidebutton->setText(QApplication::translate("Dialog", "Side-by-Side", 0));
        fronttobackbutton->setText(QApplication::translate("Dialog", "Front-to-Back", 0));
        twocolumnbutton->setText(QApplication::translate("Dialog", "2 columns", 0));
        indexbutton->setText(QApplication::translate("Dialog", "Index cards", 0));
        sortBox1->setTitle(QApplication::translate("Dialog", "Primary Sort", 0));
        alphabutton->setText(QApplication::translate("Dialog", "By Alpha", 0));
        typebutton->setText(QApplication::translate("Dialog", "By Type", 0));
        versebutton->setText(QApplication::translate("Dialog", "By Verse", 0));
        sortBox2->setTitle(QApplication::translate("Dialog", "Secondary Sort", 0));
        alphabutton2->setText(QApplication::translate("Dialog", "By Alpha", 0));
        typebutton2->setText(QApplication::translate("Dialog", "By Type", 0));
        versebutton2->setText(QApplication::translate("Dialog", "By Verse", 0));
        outputBox->setTitle(QApplication::translate("Dialog", "Select Output", 0));
        LaTeXButton->setText(QApplication::translate("Dialog", "LaTeX", 0));
        RTFButton->setText(QApplication::translate("Dialog", "Rich Text", 0));
        KeyWordBox->setTitle(QApplication::translate("Dialog", "Key Words", 0));
        KeyWordButton->setText(QApplication::translate("Dialog", "Highlight", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINTDLG_H
