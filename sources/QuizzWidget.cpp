#include "QuizzWidget.h"
#include "MainWindow.h"
#include "quizz/Quizz.hpp"
#include "Database.h"
#include "quizz/Question.hpp"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QTextEdit>
#include <QTimer>

QuizzWidget::QuizzWidget(QWidget *parent, QStringList themes) :
    QWidget(parent)
{
    Database* db = new Database();
    QList<Question*> questions;
    foreach(QString theme, themes)
    {
        questions << db->loadQuestions(theme);
    }
    _quizz = new Quizz(questions);

    _positive_comments = db->loadComments(true);
    _negative_comments = db->loadComments(false);

    if (_positive_comments.size() == 0)
        _positive_comments << tr("Good answer!");

    if (_negative_comments.size() == 0)
        _negative_comments << tr("Bad answer!");

    this->buildWidget(dynamic_cast<MainWindow*>(parent));

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(verify_timeout()));

    this->showQuestion();
}

QuizzWidget::~QuizzWidget()
{
    #ifndef QT_NO_DEBUG
        qDebug() << "~QuizzWidget()";
    #endif
}

void QuizzWidget::buildWidget(MainWindow *main_window)
{
    #define MUSIK_BUTTON_STYLE "QPushButton img { width:200%; } QPushButton { margin: 10px; font: bold 20px; font-family: trebuchet ms; color: #FFF;" \
                               "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00aaf2, stop: 1 #005676);" \
                               "border-style: outset; border-radius: 10px; padding: 5px; }" \
                               "QPushButton:hover { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00ccf2, stop: 1 #007876); }"

    #define MUSIK_CONTROL_BUTTON_STYLE "QPushButton img { width:200%; } QPushButton { margin: 10px; font: bold 15px; font-family: trebuchet ms; color: #FFF;" \
                                       "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00ccf2, stop: 1 #007876);" \
                                       "border-style: outset; border-radius: 5px; padding: 10px; }" \
                                       "QPushButton:hover { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00eef2, stop: 1 #009a76); }"

    // Create label for title
    QLabel *title_label = new QLabel("Quizz for geniuses");
    title_label->setStyleSheet("font: bold 20px; font-family: trebuchet ms; color: #57E; margin: 0 auto;");

    // Question labels
    _question_label = new QLabel;
    _question_label->setStyleSheet("font: bold 15px; font-family: trebuchet ms; color: #573; margin: 0 auto;");

    _time_left = new QLabel;
    _time_left->setStyleSheet("font: bold 16px; font-family: trebuchet ms; color: #597;");

    _explanation_label = new QTextEdit;
    _explanation_label->setDisabled(true);

    // Answers radio buttons
    for (int i = 0; i < 4; i++)
        _answers_radio_buttons.append(new QRadioButton);

    // Create control buttons and back button
    _answer_button = new QPushButton(QIcon(":/images/validate.png"), tr("Validate"));
    _next_question_button = new QPushButton(QIcon(":/images/next.png"), tr("Next question"));
    _back_button = new QPushButton(QIcon(":/images/backward.png"), tr("Back"));

    connect(_answer_button, SIGNAL(clicked()), this, SLOT(answer()));
    connect(_next_question_button, SIGNAL(clicked()), this, SLOT(showQuestion()));
    connect(_back_button, SIGNAL(clicked()), main_window, SLOT(back()));
    connect(_back_button, SIGNAL(clicked()), this, SLOT(close()));

    _answer_button->setStyleSheet(MUSIK_CONTROL_BUTTON_STYLE);
    _answer_button->setIconSize(QSize(25, 25));
    _answer_button->setMaximumWidth(150);
    _next_question_button->setStyleSheet(MUSIK_CONTROL_BUTTON_STYLE);
    _next_question_button->setIconSize(QSize(25, 25));
    _next_question_button->setMaximumWidth(180);
    _back_button->setStyleSheet(MUSIK_BUTTON_STYLE);
    _back_button->setIconSize(QSize(25, 25));

    // Prepare question layout
    QHBoxLayout *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(_answer_button);
    buttons_layout->addWidget(_next_question_button);

    _question_layout = new QVBoxLayout;
    _question_layout->addWidget(_question_label);

    for (int i = 0; i < 4; i++)
        _question_layout->addWidget(_answers_radio_buttons.at(i));

    _question_layout->addWidget(_explanation_label);
    _question_layout->addLayout(buttons_layout);

    this->setStyleSheet("QRadioButton { font: 15px; font-family: trebuchet ms; color: #573; margin-left: 100px }");

    _question_layout->setAlignment(Qt::AlignHCenter);

    // Add widgets
    QHBoxLayout *title_layout = new QHBoxLayout;
    title_layout->addWidget(title_label);
    title_layout->addWidget(_time_left);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(title_layout);
    layout->addLayout(_question_layout);
    layout->addWidget(_back_button);
}

void QuizzWidget::verify_timeout()
{
    // If time is over
    if (_quizz->timeOut())
        this->answer();

    // Else, we show time left
    else
        _time_left->setText("00:" + QString::number(_quizz->timeLeft()));
}

QStringList QuizzWidget::shuffleAnswers(QStringList answers)
{
    int random_positions[answers.size()];

    for (int i=0; i<answers.size(); i++)
        random_positions[i] = i;

    // Shuffle
    for (int i=0; i<answers.size(); i++)
    {
        int j = qrand() % answers.size();
        int tmp = random_positions[j];
        random_positions[j] = random_positions[i];
        random_positions[i] = tmp;
    }

    QStringList shuffled_answers;

    for (int i=0; i<answers.size(); i++)
    {
        shuffled_answers << answers.at(random_positions[i]);

        // Good answer
        if (random_positions[i] == 0)
            _position_correct_answer = i;
    }

    return shuffled_answers;
}

void QuizzWidget::showQuestion()
{
    if ( ! _quizz->isFinished())
    {
        Question *question = _quizz->nextQuestion();

        // Question labels
        _question_label->setText(question->question());

        QStringList answers = this->shuffleAnswers(question->answers());

        // Answers
        for (int i = 0; i < 4; i++)
        {
            if (i < question->nbAnswer())
            {
                _answers_radio_buttons.at(i)->setText(answers.at(i));
                _answers_radio_buttons.at(i)->setCheckable(true);
                _answers_radio_buttons.at(i)->setStyleSheet("font-weight: normal; color: #573;");
                _answers_radio_buttons.at(i)->show();
            }

            else
                _answers_radio_buttons.at(i)->hide();
        }

        // Clear explanation
        _explanation_label->setVisible(false);

        // Control buttons
        _answer_button->setVisible(true);
        _next_question_button->setVisible(false);
        _timer->start(500);
    }

    else
    {
        QString score = tr("Your score is: ") + QString::number(_quizz->score());
        QMessageBox::information(this, tr("Quizz finished!"), tr("Quizz is over! ") + score);
    }
}

void QuizzWidget::answer()
{
    _timer->stop();

    // The right answer for the current question
    int selected_answer = -1;

    // Colorize good and bad answer
    for (int i = 0; i < 4; i++)
    {
        // Good answer
        if (i == _position_correct_answer)
            _answers_radio_buttons.at(i)->setStyleSheet("font-weight: bold; color: #0a0;");

        // Bad answer and this is the one given by user
        else if (_answers_radio_buttons.at(i)->isChecked())
            _answers_radio_buttons.at(i)->setStyleSheet("font-weight: bold; color: #f00;");

        // Keep user's answer in memory
        if (_answers_radio_buttons.at(i)->isChecked())
            selected_answer = i;
    }

    // Answers aren't checkable until next question
    for (int i = 0; i < 4; i++)
        _answers_radio_buttons.at(i)->setCheckable(false);

    // Good answer
    if (selected_answer == _position_correct_answer)
    {
        _explanation_label->setText(_positive_comments.at(qrand() % _positive_comments.size()));
        _explanation_label->setStyleSheet("font: bold 14px; font-family: trebuchet ms; color: #0a0; margin: 0 auto;");
    }

    // Bad answer
    else
    {
        _explanation_label->setText(_negative_comments.at(qrand() % _negative_comments.size()));
        _explanation_label->setStyleSheet("font: bold 14px; font-family: trebuchet ms; color: #f00; margin: 0 auto;");
    }

    _quizz->refreshScore(selected_answer == _position_correct_answer);

    // Show explanation
    _explanation_label->setHtml(_explanation_label->toHtml() + "<br>" + _quizz->currentQuestion()->explanation());
    _explanation_label->setVisible(true);
    _explanation_label->setFixedHeight(_explanation_label->document()->size().height());

    // Control buttons
    _answer_button->setVisible(false);
    _next_question_button->setVisible(true);
}
