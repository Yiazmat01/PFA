#include "NotesExploderWidget.h"
#include "MainWindow.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

NotesExploderWidget::NotesExploderWidget(QWidget *parent) :
    QWidget(parent)
{
    this->buildWidget(dynamic_cast<MainWindow*>(parent));
}

NotesExploderWidget::~NotesExploderWidget()
{
    #ifndef QT_NO_DEBUG
        qDebug() << "~NotesExploderWidget()";
    #endif
}

void NotesExploderWidget::buildWidget(MainWindow *main_window)
{
    #define MUSIK_BUTTON_STYLE "QPushButton img { width:200%; } QPushButton { margin: 10px; font: bold 20px; font-family: trebuchet ms; color: #FFF;" \
                               "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00aaf2, stop: 1 #005676);" \
                               "border-style: outset; border-radius: 10px; padding: 5px; }" \
                               "QPushButton:hover { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00ccf2, stop: 1 #007876); }"

    #define MUSIK_LABEL_STYLE "QLabel { font: bold 20px; font-family: trebuchet ms; color: #57E; margin: 0 auto; }"

    // Create label for title
    QLabel *title_label = new QLabel("Quizz for geniuses");
    title_label->setStyleSheet(MUSIK_LABEL_STYLE);

    // Create tools buttons and back button
    QPushButton *back_button = new QPushButton(QIcon(":/images/tools.png"), tr("Back"));

    connect(back_button, SIGNAL(clicked()), main_window, SLOT(back()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(close()));

    back_button->setStyleSheet(MUSIK_BUTTON_STYLE);

    // Add widgets
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title_label);
    layout->addWidget(back_button);
}
