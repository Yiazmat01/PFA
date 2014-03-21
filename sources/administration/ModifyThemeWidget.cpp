#include "ModifyThemeWidget.h"
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

ModifyThemeWidget::ModifyThemeWidget(bool new_theme, QString theme, QWidget *caller)
    : _new_theme(new_theme), _caller(caller)
{
    if ( ! _new_theme)
    {
        Database db;
        _theme_id = db.theme_id(theme);
        qDebug() << _theme_id;
    }

    this->buildWidget(theme);
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

ModifyThemeWidget::~ModifyThemeWidget()
{
    #ifndef QT_NO_DEBUG
        qDebug() << "~ModifyThemeWidget()";
    #endif
}

void ModifyThemeWidget::buildWidget(QString theme)
{
    #define MUSIK_BUTTON_STYLE "QPushButton img { width:200%; } QPushButton { margin: 10px; font: bold 20px; font-family: trebuchet ms; color: #FFF;" \
                               "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00aaf2, stop: 1 #005676);" \
                               "border-style: outset; border-radius: 10px; padding: 5px; }" \
                               "QPushButton:hover { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00ccf2, stop: 1 #007876); }"

    #define MUSIK_LABEL_STYLE "QLabel { font: bold 20px; font-family: trebuchet ms; color: #57E; margin: 0 auto; }"

    // Create label for title
    QLabel *title_label;

    if (_new_theme)
        title_label = new QLabel(tr("New theme"));
    else
        title_label = new QLabel(tr("Modify theme"));

    title_label->setStyleSheet(MUSIK_LABEL_STYLE);

    // Create form
    _theme = new QLineEdit;

    if ( ! _new_theme)
        _theme->setText(theme);

    // Create validate and cancel buttons
    QPushButton *add_button;

    if (_new_theme)
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

    // Buttons layout
    QHBoxLayout *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(add_button);
    buttons_layout->addWidget(cancel_button);
    layout->addLayout(buttons_layout);
}

void ModifyThemeWidget::save()
{
    Database db;

    // Add / modify theme
    if (_new_theme)
        db.insertTheme(_theme->text());

    else
        db.updateTheme(_theme_id, _theme->text());

    dynamic_cast<AdminQuizzWidget*>(_caller)->reloadTab();
    this->close();
}
