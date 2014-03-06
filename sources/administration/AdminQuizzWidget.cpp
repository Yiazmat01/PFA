#include "AdminQuizzWidget.h"
#include "../MainWindow.h"
#include "../quizz/Question.hpp"
#include "../Database.h"
#include "ModifyQuestionWidget.h"
#include "ModifyThemeWidget.h"
#include "ModifyCommentWidget.h"

#include <QDebug>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>

AdminQuizzWidget::AdminQuizzWidget(QWidget *parent) :
    QWidget(parent)
{
    this->buildWidget(dynamic_cast<MainWindow*>(parent));
}

AdminQuizzWidget::~AdminQuizzWidget()
{
    #ifndef QT_NO_DEBUG
        qDebug() << "~AdminQuizzWidget()";
    #endif
}

void AdminQuizzWidget::buildWidget(MainWindow *main_window)
{
    #define MUSIK_BUTTON_STYLE "QPushButton img { width:200%; } QPushButton { margin: 10px; font: bold 20px; font-family: trebuchet ms; color: #FFF;" \
                               "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00aaf2, stop: 1 #005676);" \
                               "border-style: outset; border-radius: 10px; padding: 5px; }" \
                               "QPushButton:hover { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00ccf2, stop: 1 #007876); }"

    #define MUSIK_LABEL_STYLE "QLabel { font: bold 20px; font-family: trebuchet ms; color: #57E; margin: 0 auto; }"

    // Create label for title
    QLabel *title_label = new QLabel(tr("Administration"));
    title_label->setStyleSheet(MUSIK_LABEL_STYLE);

    // Create tab widget
    QTabWidget *tab_widget = new QTabWidget;
    connect(tab_widget, SIGNAL(currentChanged(int)), this, SLOT(switchWidget(int)));

    _scroll_area = new QScrollArea;
    QWidget *grid_widget = new QWidget;
    _scroll_area->setWidget(grid_widget);
    _grid_layout = new QGridLayout(grid_widget);

    _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _scroll_area->setWidgetResizable(true);

    // Create questions widget
    QWidget *admin_questions = new QWidget;
    _admin_questions_layout = new QVBoxLayout;
    QPushButton *add_question_button = new QPushButton(QIcon(":/images/backward.png"), tr("Add new question"));

    connect(add_question_button, SIGNAL(clicked()), this, SLOT(new_question()));

    admin_questions->setLayout(_admin_questions_layout);
    _admin_questions_layout->addWidget(add_question_button);
    _admin_questions_layout->addWidget(_scroll_area);

    // Create themes widget
    QWidget *admin_themes = new QWidget;
    _admin_themes_layout = new QVBoxLayout;
    QPushButton *add_theme_button = new QPushButton(QIcon(":/images/backward.png"), tr("Add new theme"));

    connect(add_theme_button, SIGNAL(clicked()), this, SLOT(new_theme()));

    admin_themes->setLayout(_admin_themes_layout);
    _admin_themes_layout->addWidget(add_theme_button);

    // Create good answers widget
    QWidget *admin_good_answers = new QWidget;
    _admin_good_answers_layout = new QVBoxLayout;
    QPushButton *add_good_answer_button = new QPushButton(QIcon(":/images/backward.png"), tr("Add new good answer"));

    connect(add_good_answer_button, SIGNAL(clicked()), this, SLOT(new_good_comment()));

    admin_good_answers->setLayout(_admin_good_answers_layout);
    _admin_good_answers_layout->addWidget(add_good_answer_button);

    // Create bad answers widget
    QWidget *admin_bad_answers = new QWidget;
    _admin_bad_answers_layout = new QVBoxLayout;
    QPushButton *add_bad_answer_button = new QPushButton(QIcon(":/images/backward.png"), tr("Add new bad answer"));

    connect(add_bad_answer_button, SIGNAL(clicked()), this, SLOT(new_bad_comment()));

    admin_bad_answers->setLayout(_admin_bad_answers_layout);
    _admin_bad_answers_layout->addWidget(add_bad_answer_button);

    // Create back button
    QPushButton *back_button = new QPushButton(QIcon(":/images/backward.png"), tr("Back"));

    connect(back_button, SIGNAL(clicked()), main_window, SLOT(back()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(close()));

    back_button->setStyleSheet(MUSIK_BUTTON_STYLE);
    back_button->setIconSize(QSize(25, 25));

    // Add widgets to tab widget
    tab_widget->addTab(admin_questions, tr("Questions/Answers"));
    tab_widget->addTab(admin_themes, tr("Themes"));
    tab_widget->addTab(admin_good_answers, tr("Good answers"));
    tab_widget->addTab(admin_bad_answers, tr("Bad answers"));

    // Add widgets
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title_label);
    layout->addWidget(tab_widget);
    layout->addWidget(back_button);
}

void AdminQuizzWidget::new_question()
{
    new ModifyQuestionWidget(true, NULL, this);
}

void AdminQuizzWidget::new_theme()
{
    new ModifyThemeWidget(true, this);
}

void AdminQuizzWidget::new_good_comment()
{
    new ModifyCommentWidget(true, true, this);
}

void AdminQuizzWidget::new_bad_comment()
{
    new ModifyCommentWidget(true, false, this);
}

void AdminQuizzWidget::modify_item()
{
    QObject *sender = QObject::sender();
    int selected = _buttons_links[sender];
    Database db;

    // Questions
    if (_position_current_widget == 0)
    {
        QList<Question*> questions = db.loadQuestions();
        Question *question = questions.at(selected);

        //new ModifyQuestionWidget(false, question);
    }

    // Themes
    else if (_position_current_widget == 1)
    {

    }

    // Comments
    else if (_position_current_widget == 2 || _position_current_widget == 3)
    {

    }
}

void AdminQuizzWidget::delete_item()
{
    QObject *sender = QObject::sender();
    int selected = _buttons_links[sender];
    Database db;

    // Questions
    if (_position_current_widget == 0)
    {
        QList<Question*> questions = db.loadQuestions();
        Question *question = questions.at(selected);
        db.deleteQuestion(question);
    }

    // Themes
    else if (_position_current_widget == 1)
    {
        QStringList themes = db.loadThemes();
        QString theme = themes.at(selected);
        db.deleteTheme(theme);
    }

    // Comments
    else if (_position_current_widget == 2 || _position_current_widget == 3)
    {
        QStringList comments = db.loadComments(_position_current_widget == 2);
        QString comment = comments.at(selected);
        db.deleteComment(comment);
    }

    this->reloadTab();
}

void AdminQuizzWidget::reloadTab()
{
    this->switchWidget(_position_current_widget);
}

void AdminQuizzWidget::switchWidget(int index)
{
    _position_current_widget = index;
    Database db;

    while (_grid_layout->count() > 0)
    {
        QLayoutItem* item = _grid_layout->takeAt(0);
        delete item->widget();
    }

    _buttons_links.clear();

    // Questions
    if (index == 0)
    {
        QList<Question*> questions = db.loadQuestions();

        for (int i = 0; i < questions.size(); i++)
        {
            QLabel *label = new QLabel(questions.at(i)->question());
            QPushButton *modify_button = new QPushButton(tr("Modify"));
            QPushButton *delete_button = new QPushButton(tr("Delete"));

            connect(modify_button, SIGNAL(clicked()), this, SLOT(modify_item()));
            connect(delete_button, SIGNAL(clicked()), this, SLOT(delete_item()));

            _buttons_links.insert(modify_button, i);
            _buttons_links.insert(delete_button, i);

            _grid_layout->addWidget(label, i, 0);
            _grid_layout->addWidget(modify_button, i, 1);
            _grid_layout->addWidget(delete_button, i, 2);
        }

        _admin_questions_layout->addWidget(_scroll_area);
    }

    // Themes
    else if (index == 1)
    {
        QStringList themes = db.loadThemes();

        for (int i = 0; i < themes.size(); i++)
        {
            QLabel *label = new QLabel(themes.at(i));
            QPushButton *modify_button = new QPushButton(tr("Modify"));
            QPushButton *delete_button = new QPushButton(tr("Delete"));

            connect(modify_button, SIGNAL(clicked()), this, SLOT(modify_item()));
            connect(delete_button, SIGNAL(clicked()), this, SLOT(delete_item()));

            _buttons_links.insert(modify_button, i);
            _buttons_links.insert(delete_button, i);

            _grid_layout->addWidget(label, i, 0);
            _grid_layout->addWidget(modify_button, i, 1);
            _grid_layout->addWidget(delete_button, i, 2);
        }

        _admin_themes_layout->addWidget(_scroll_area);
    }

    // Good/Bad answers
    else if (index == 2 || index == 3)
    {
        // Index == 2 => good answers
        QStringList comments = db.loadComments(index == 2);

        for (int i = 0; i < comments.size(); i++)
        {
            QLabel *label = new QLabel(comments.at(i));
            QPushButton *modify_button = new QPushButton(tr("Modify"));
            QPushButton *delete_button = new QPushButton(tr("Delete"));

            connect(modify_button, SIGNAL(clicked()), this, SLOT(modify_item()));
            connect(delete_button, SIGNAL(clicked()), this, SLOT(delete_item()));

            _buttons_links.insert(modify_button, i);
            _buttons_links.insert(delete_button, i);

            _grid_layout->addWidget(label, i, 0);
            _grid_layout->addWidget(modify_button, i, 1);
            _grid_layout->addWidget(delete_button, i, 2);
        }

        if (index == 2)
            _admin_good_answers_layout->addWidget(_scroll_area);
        else
            _admin_bad_answers_layout->addWidget(_scroll_area);
    }
}
