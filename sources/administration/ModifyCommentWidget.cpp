#include "ModifyCommentWidget.h"
#include "../Database.h"
#include "../quizz/Question.hpp"
#include "AdminQuizzWidget.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDesktopWidget>

ModifyCommentWidget::ModifyCommentWidget(bool new_comment, bool is_positive, QString comment, QWidget *caller)
    : _new_comment(new_comment), _is_positive(is_positive), _caller(caller)
{
    if ( ! new_comment)
    {
        Database db;
        _comment_id = db.comment_id(is_positive, comment);
    }

    this->buildWidget(comment);
    this->setWindowModality(Qt::ApplicationModal);
    this->resize(400, 200);

    // Calculate coordinates of center of the screen
    QDesktopWidget desktop;
    int x = (desktop.screenGeometry().width() - this->width()) / 2;
    int y = (desktop.screenGeometry().height() - this->height()) / 2;

    // Move widget on center of the screen and show it
    this->move(x, y);
    this->show();
}

ModifyCommentWidget::~ModifyCommentWidget()
{
    #ifndef QT_NO_DEBUG
        qDebug() << "~ModifyCommentWidget()";
    #endif
}

void ModifyCommentWidget::buildWidget(QString comment)
{
    #define MUSIK_BUTTON_STYLE "QPushButton img { width:200%; } QPushButton { margin: 10px; font: bold 20px; font-family: trebuchet ms; color: #FFF;" \
                               "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00aaf2, stop: 1 #005676);" \
                               "border-style: outset; border-radius: 10px; padding: 5px; }" \
                               "QPushButton:hover { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00ccf2, stop: 1 #007876); }"

    #define MUSIK_LABEL_STYLE "QLabel { font: bold 20px; font-family: trebuchet ms; color: #57E; margin: 0 auto; }"

    // Create label for title
    QLabel *title_label;

    if (_new_comment)
    {
        if (_is_positive)
            title_label = new QLabel(tr("New good comment"));
        else
            title_label = new QLabel(tr("New bad comment"));
    }
    else
    {
        if (_is_positive)
            title_label = new QLabel(tr("Modify good comment"));

        else
            title_label = new QLabel(tr("Modify bad comment"));
    }

    title_label->setStyleSheet(MUSIK_LABEL_STYLE);

    // Create form
    _comment = new QLineEdit;

    if ( ! _new_comment)
        _comment->setText(comment);

    // Create validate and cancel buttons
    QPushButton *add_button;

    if (_new_comment)
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
    layout->addWidget(new QLabel(tr("Comment")));
    layout->addWidget(_comment);

    // Buttons layout
    QHBoxLayout *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(add_button);
    buttons_layout->addWidget(cancel_button);
    layout->addLayout(buttons_layout);
}

void ModifyCommentWidget::save()
{
    Database db;

    if (_new_comment)
        db.insertComment(_comment->text(), _is_positive);

    else
        db.updateComment(_comment_id, _is_positive, _comment->text());

    dynamic_cast<AdminQuizzWidget*>(_caller)->reloadTab();
    this->close();
}
