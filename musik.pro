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
        sources/quizz/Question.hpp \
        sources/quizz/Score.hpp \
        sources/quizz/Quizz.hpp \
        sources/administration/AdminQuizzWidget.h \
        sources/administration/ModifyQuestionWidget.h \
        sources/administration/ModifyThemeWidget.h \
        sources/administration/ModifyCommentWidget.h

SOURCES += \
	sources/MainWindow.cpp \
	sources/main.cpp \
	sources/ToolsWidget.cpp \
	sources/QuizzWidget.cpp \
	sources/NotesExploderWidget.cpp \
	sources/Database.cpp \
        sources/quizz/Question.cpp \
        sources/quizz/Score.cpp \
        sources/quizz/Quizz.cpp \
        sources/administration/AdminQuizzWidget.cpp \
        sources/administration/ModifyQuestionWidget.cpp \
        sources/administration/ModifyThemeWidget.cpp \
        sources/administration/ModifyCommentWidget.cpp

#LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

RESOURCES += \
	resources.qrc

TRANSLATIONS = lang/musik_fr.ts

OTHER_FILES +=
