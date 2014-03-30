#include "ModifyQuestionWidget.h"
#include "../Database.h"
#include "../quizz/Question.hpp"
#include "AdminQuizzWidget.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QDesktopWidget>
#include <QComboBox>

ModifyQuestionWidget::ModifyQuestionWidget(bool new_question, Question *question, QWidget *caller)
    : _new_question(new_question), _current_question(question), _caller(caller)
{
    this->buildWidget();
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

void ModifyQuestionWidget::buildWidget()
{
    #define MUSIK_BUTTON_STYLE "QPushButton img { width:200%; } QPushButton { margin: 10px; font: bold 20px; font-family: trebuchet ms; color: #FFF;" \
                               "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00aaf2, stop: 1 #005676);" \
                               "border-style: outset; border-radius: 10px; padding: 5px; }" \
                               "QPushButton:hover { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00ccf2, stop: 1 #007876); }"

    #define MUSIK_LABEL_STYLE "QLabel { font: bold 20px; font-family: trebuchet ms; color: #57E; margin: 0 auto; }"

    // Create label for title
    QLabel *title_label;

    if (_new_question)
        title_label = new QLabel(tr("New question"));
    else
        title_label = new QLabel(tr("Modify question"));

    title_label->setStyleSheet(MUSIK_LABEL_STYLE);

    // Create form
    _theme = new QComboBox;
    _difficulty = new QComboBox;
    _year = new QLineEdit;
    _question = new QLineEdit;
    _explanation = new QTextEdit;

    for (int i = 0; i < 4; i++)
        _answers << new QLineEdit;

    Database db;
    _theme->addItems(db.loadThemes());

    QStringList difficulties;
    difficulties << "1" << "2" << "3";
    _difficulty->addItems(difficulties);

    // Create validate and cancel buttons
    QPushButton *add_button;

    if (_new_question)
        add_button = new QPushButton(QIcon(":/images/backward.png"), tr("Add"));
    else
        add_button = new QPushButton(QIcon(":/images/backward.png"), tr("Modify"));

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
    layout->addWidget(new QLabel(tr("Difficulty")));
    layout->addWidget(_difficulty);
    layout->addWidget(new QLabel(tr("Year")));
    layout->addWidget(_year);
    layout->addWidget(new QLabel(tr("Question")));
    layout->addWidget(_question);

    for (int i = 0; i < 4; i++)
    {
        QString help;

        if (i == 0)
            help = tr(" (the good answer)");

        layout->addWidget(new QLabel(tr("Answer ") + QString::number(i+1) + help));
        layout->addWidget(_answers[i]);
    }

    layout->addWidget(new QLabel(tr("Explanation")));
    layout->addWidget(_explanation);

    // Pre-fill some fields
    if ( ! _new_question)
    {
        //_theme->setCurrentText(db.theme(_current_question->theme()));
        _year->setText(QString::number(_current_question->year()));
        _difficulty->setCurrentIndex(_current_question->difficulty() - 1);
        _question->setText(_current_question->question());

        for (int i = 0; i < 4; i++)
            _answers.at(i)->setText(_current_question->answer(i));

        _explanation->setText(_current_question->explanation());
    }

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

    Database db;
    int theme_id = db.theme_id(_theme->currentText());

    if (_new_question)
    {
        Question question(-1, _question->text(), answers, _explanation->toPlainText(), _difficulty->currentText().toInt(), _year->text().toInt(), theme_id);
        db.insertQuestion(&question);
    }

    else
    {
         Question question(_current_question->id(), _question->text(), answers, _explanation->toPlainText(), _difficulty->currentText().toInt(), _year->text().toInt(), theme_id);
         db.updateQuestion(&question);
    }

    dynamic_cast<AdminQuizzWidget*>(_caller)->reloadTab();
    this->close();
}
