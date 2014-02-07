#-------------------------------------------------
#
# Project created by QtCreator 2013-12-18T11:15:07
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = musik
TEMPLATE = app

HEADERS += \
	sources/MainWindow.h \
	sources/ToolsWidget.h \
	sources/QuizzWidget.h \
	sources/NotesExploderWidget.h \
    sources/Database.h \
    sources/Quizz/Question.hpp \
    sources/Quizz/Score.hpp \
    sources/Quizz/Quizz.hpp \
    sources/AdminQuizzWidget.h \
    sources/ModifyQuestionWidget.h

SOURCES += \
	sources/MainWindow.cpp \
	sources/main.cpp \
	sources/ToolsWidget.cpp \
	sources/QuizzWidget.cpp \
	sources/NotesExploderWidget.cpp \
    sources/Database.cpp \
    sources/Quizz/Question.cpp \
    sources/Quizz/Score.cpp \
    sources/Quizz/Quizz.cpp \
    sources/Quizz/test.cpp \
    sources/AdminQuizzWidget.cpp \
    sources/ModifyQuestionWidget.cpp

LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

RESOURCES += \
	resources.qrc

TRANSLATIONS = lang/musik_fr.ts

OTHER_FILES += \
    sources/Quizz/Makefile
