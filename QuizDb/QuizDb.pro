#-------------------------------------------------
#
# Project created by QtCreator 2012-09-29T11:38:38
#
#-------------------------------------------------

QT       += core gui sql widgets printsupport

TARGET = QuizDb
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vrange.cpp \
    errmsg.cpp \
    range.cpp \
    quizview.cpp \
    quizsectionclass.cpp \
    quizreview.cpp \
    quizquestionclass.cpp \
    quizmodel.cpp \
    quizload.cpp \
    quizedit.cpp \
    quizclass.cpp \
    quiz.cpp \
    questmodel.cpp \
    questclass.cpp \
    print.cpp \
    order.cpp \
    keyview.cpp \
    codes.cpp \
    bible.cpp \
    types.cpp \
    quizquestmodel.cpp \
    quizquesteditview.cpp

HEADERS  += mainwindow.h \
    errmsg.h \
    vrange.h \
    quizview.h \
    quizsectionclass.h \
    quizreview.h \
    quizquestionclass.h \
    quizmodel.h \
    quizload.h \
    quizedit.h \
    quizclass.h \
    quiz.h \
    questmodel.h \
    questclass.h \
    print.h \
    order.h \
    keyview.h \
    codes.h \
    bible.h \
    types.h \
    range.h \
    quizquestmodel.h \
    quizquesteditview.h

FORMS += \
    errdlg.ui \
    quizdlg.ui \
    printdlg.ui \
    orderdlg.ui \
    mainwindow.ui \
    rangedlg.ui

OTHER_FILES += \
    QuizDb.pro.user
