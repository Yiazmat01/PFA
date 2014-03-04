#include "ModifyQuestionWidget.h"
#include "Database.h"
#include "Quizz/Question.hpp"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QDesktopWidget>

ModifyQuestionWidget::ModifyQuestionWidget(bool new_question)
{
    this->buildWidget(new_question);
    this->setWindowModality(Qt::ApplicationModal);
    this->resize(600, 450);

    // Calculate coordinates of center of the screen
    QDesktopWidget desktop;
    int x = (desktop.screenGeometry().width() - this->width()) / 2;
    int y = (desktop.screenGeometry().height() - this->height()) / 2;

    // Move widget on center of the screen and show it
    this->move(x, y);
    this->show();
}

ModifyQuestionWidget::~ModifyQuestionWidget()
{
    #ifndef QT_NO_DEBUG
        qDebug() << "~ModifyQuestionWidget()";
    #endif
}

void ModifyQuestionWidget::buildWidget(bool new_question)
{
    #define MUSIK_BUTTON_STYLE "QPushButton img { width:200%; } QPushButton { margin: 10px; font: bold 20px; font-family: trebuchet ms; color: #FFF;" \
                               "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00aaf2, stop: 1 #005676);" \
                               "border-style: outset; border-radius: 10px; padding: 5px; }" \
                               "QPushButton:hover { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00ccf2, stop: 1 #007876); }"

    #define MUSIK_LABEL_STYLE "QLabel { font: bold 20px; font-family: trebuchet ms; color: #57E; margin: 0 auto; }"

    // Create label for title
    QLabel *title_label;

    if (new_question)
        title_label = new QLabel(tr("New question"));
    else
        title_label = new QLabel(tr("Modify question"));

    title_label->setStyleSheet(MUSIK_LABEL_STYLE);

    // Create form
    _theme = new QLineEdit;
    _question = new QLineEdit;
    _explanation = new QTextEdit;

    for (int i = 0; i < 4; i++)
        _answers << new QLineEdit;

    // Create validate and cancel buttons
    QPushButton *add_button = new QPushButton(QIcon(":/images/backward.png"), tr("Add"));
    QPushButton *cancel_button = new QPushButton(QIcon(":/images/backward.png"), tr("Cancel"));

    connect(add_button, SIGNAL(clicked()), this, SLOT(save()));
    connect(cancel_button, SIGNAL(clicked()), this, SLOT(close()));

    add_button->setStyleSheet(MUSIK_BUTTON_STYLE);
    cancel_button->setStyleSheet(MUSIK_BUTTON_STYLE);
    add_button->setIconSize(QSize(25, 25));
    cancel_button->setIconSize(QSize(25, 25));

    // Add widgets
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title_label);
    layout->addWidget(new QLabel(tr("Theme")));
    layout->addWidget(_theme);
    layout->addWidget(new QLabel(tr("Question")));
    layout->addWidget(_question);

    for (int i = 0; i < 4; i++)
    {
        layout->addWidget(new QLabel(tr("Answer")));
        layout->addWidget(_answers[i]);
    }

    layout->addWidget(new QLabel(tr("Explaination")));
    layout->addWidget(_explanation);

    // Buttons layout
    QHBoxLayout *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(add_button);
    buttons_layout->addWidget(cancel_button);
    layout->addLayout(buttons_layout);
}

void ModifyQuestionWidget::save()
{
    QStringList answers;

    for (int i = 0; i < 4; i++)
    {
        if (_answers[i]->text().size() > 0)
            answers << _answers[i]->text();
    }

    Question question(-1, _question->text(), answers, _explanation->toPlainText(), 1, 2014, 1);
    Database db;
    db.insertQuestion(&question);
    this->close();
}
