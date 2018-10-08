/********************************************************************************
** Form generated from reading UI file 'printdlg.ui'
**
** Created: Sun Jul 8 22:01:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINTDLG_H
#define UI_PRINTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

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
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(459, 418);
        OkBox = new QDialogButtonBox(Dialog);
        OkBox->setObjectName(QString::fromUtf8("OkBox"));
        OkBox->setGeometry(QRect(290, 380, 161, 32));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OkBox->sizePolicy().hasHeightForWidth());
        OkBox->setSizePolicy(sizePolicy);
        OkBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        fromBox = new QGroupBox(Dialog);
        fromBox->setObjectName(QString::fromUtf8("fromBox"));
        fromBox->setGeometry(QRect(0, 10, 281, 61));
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
        ToBox = new QGroupBox(Dialog);
        ToBox->setObjectName(QString::fromUtf8("ToBox"));
        ToBox->setGeometry(QRect(0, 70, 281, 61));
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
        formatBox = new QGroupBox(Dialog);
        formatBox->setObjectName(QString::fromUtf8("formatBox"));
        formatBox->setGeometry(QRect(0, 260, 141, 151));
        formatBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        noanswerbutton = new QRadioButton(formatBox);
        noanswerbutton->setObjectName(QString::fromUtf8("noanswerbutton"));
        noanswerbutton->setGeometry(QRect(20, 120, 107, 20));
        sidebysidebutton = new QRadioButton(formatBox);
        sidebysidebutton->setObjectName(QString::fromUtf8("sidebysidebutton"));
        sidebysidebutton->setGeometry(QRect(20, 90, 110, 20));
        fronttobackbutton = new QRadioButton(formatBox);
        fronttobackbutton->setObjectName(QString::fromUtf8("fronttobackbutton"));
        fronttobackbutton->setGeometry(QRect(20, 60, 110, 20));
        twocolumnbutton = new QRadioButton(formatBox);
        twocolumnbutton->setObjectName(QString::fromUtf8("twocolumnbutton"));
        twocolumnbutton->setGeometry(QRect(20, 30, 90, 20));
        twocolumnbutton->setChecked(true);
        sortBox1 = new QGroupBox(Dialog);
        sortBox1->setObjectName(QString::fromUtf8("sortBox1"));
        sortBox1->setGeometry(QRect(0, 130, 141, 121));
        alphabutton = new QRadioButton(sortBox1);
        alphabutton->setObjectName(QString::fromUtf8("alphabutton"));
        alphabutton->setGeometry(QRect(10, 90, 80, 20));
        typebutton = new QRadioButton(sortBox1);
        typebutton->setObjectName(QString::fromUtf8("typebutton"));
        typebutton->setGeometry(QRect(10, 60, 80, 20));
        versebutton = new QRadioButton(sortBox1);
        versebutton->setObjectName(QString::fromUtf8("versebutton"));
        versebutton->setGeometry(QRect(10, 30, 80, 20));
        versebutton->setChecked(true);
        sortBox2 = new QGroupBox(Dialog);
        sortBox2->setObjectName(QString::fromUtf8("sortBox2"));
        sortBox2->setGeometry(QRect(140, 130, 141, 121));
        alphabutton2 = new QRadioButton(sortBox2);
        alphabutton2->setObjectName(QString::fromUtf8("alphabutton2"));
        alphabutton2->setGeometry(QRect(10, 90, 80, 20));
        typebutton2 = new QRadioButton(sortBox2);
        typebutton2->setObjectName(QString::fromUtf8("typebutton2"));
        typebutton2->setGeometry(QRect(10, 60, 80, 20));
        versebutton2 = new QRadioButton(sortBox2);
        versebutton2->setObjectName(QString::fromUtf8("versebutton2"));
        versebutton2->setGeometry(QRect(10, 30, 80, 20));
        versebutton2->setChecked(true);
        outputBox = new QGroupBox(Dialog);
        outputBox->setObjectName(QString::fromUtf8("outputBox"));
        outputBox->setGeometry(QRect(140, 260, 141, 91));
        LaTeXButton = new QRadioButton(outputBox);
        LaTeXButton->setObjectName(QString::fromUtf8("LaTeXButton"));
        LaTeXButton->setGeometry(QRect(10, 30, 103, 21));
        LaTeXButton->setChecked(true);
        RTFButton = new QRadioButton(outputBox);
        RTFButton->setObjectName(QString::fromUtf8("RTFButton"));
        RTFButton->setGeometry(QRect(10, 50, 103, 31));
        KeyWordBox = new QGroupBox(Dialog);
        KeyWordBox->setObjectName(QString::fromUtf8("KeyWordBox"));
        KeyWordBox->setGeometry(QRect(140, 350, 141, 61));
        KeyWordButton = new QRadioButton(KeyWordBox);
        KeyWordButton->setObjectName(QString::fromUtf8("KeyWordButton"));
        KeyWordButton->setGeometry(QRect(10, 30, 101, 21));
        KeyWordButton->setChecked(true);
        verticalLayoutWidget = new QWidget(Dialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(290, 60, 161, 271));
        TypeBox = new QVBoxLayout(verticalLayoutWidget);
        TypeBox->setObjectName(QString::fromUtf8("TypeBox"));
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
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        fromBox->setTitle(QApplication::translate("Dialog", "Verse range from:", 0, QApplication::UnicodeUTF8));
        ToBox->setTitle(QApplication::translate("Dialog", "Verse range to:", 0, QApplication::UnicodeUTF8));
        formatBox->setTitle(QApplication::translate("Dialog", "Choose Format", 0, QApplication::UnicodeUTF8));
        noanswerbutton->setText(QApplication::translate("Dialog", "No Answers", 0, QApplication::UnicodeUTF8));
        sidebysidebutton->setText(QApplication::translate("Dialog", "Side-by-Side", 0, QApplication::UnicodeUTF8));
        fronttobackbutton->setText(QApplication::translate("Dialog", "Front-to-Back", 0, QApplication::UnicodeUTF8));
        twocolumnbutton->setText(QApplication::translate("Dialog", "2 columns", 0, QApplication::UnicodeUTF8));
        sortBox1->setTitle(QApplication::translate("Dialog", "Primary Sort", 0, QApplication::UnicodeUTF8));
        alphabutton->setText(QApplication::translate("Dialog", "By Alpha", 0, QApplication::UnicodeUTF8));
        typebutton->setText(QApplication::translate("Dialog", "By Type", 0, QApplication::UnicodeUTF8));
        versebutton->setText(QApplication::translate("Dialog", "By Verse", 0, QApplication::UnicodeUTF8));
        sortBox2->setTitle(QApplication::translate("Dialog", "Secondary Sort", 0, QApplication::UnicodeUTF8));
        alphabutton2->setText(QApplication::translate("Dialog", "By Alpha", 0, QApplication::UnicodeUTF8));
        typebutton2->setText(QApplication::translate("Dialog", "By Type", 0, QApplication::UnicodeUTF8));
        versebutton2->setText(QApplication::translate("Dialog", "By Verse", 0, QApplication::UnicodeUTF8));
        outputBox->setTitle(QApplication::translate("Dialog", "Select Output", 0, QApplication::UnicodeUTF8));
        LaTeXButton->setText(QApplication::translate("Dialog", "LaTeX", 0, QApplication::UnicodeUTF8));
        RTFButton->setText(QApplication::translate("Dialog", "Rich Text", 0, QApplication::UnicodeUTF8));
        KeyWordBox->setTitle(QApplication::translate("Dialog", "Key Words", 0, QApplication::UnicodeUTF8));
        KeyWordButton->setText(QApplication::translate("Dialog", "Highlight", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINTDLG_H
