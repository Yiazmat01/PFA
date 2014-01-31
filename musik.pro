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
    sources/Quizz/Question.hpp

SOURCES += \
	sources/MainWindow.cpp \
	sources/main.cpp \
	sources/ToolsWidget.cpp \
	sources/QuizzWidget.cpp \
	sources/NotesExploderWidget.cpp \
    sources/Database.cpp \
    sources/Quizz/Question.cpp

LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

RESOURCES += \
	resources.qrc

TRANSLATIONS = translate/musik_fr.ts
