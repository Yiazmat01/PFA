#include "ThemeSelectionWidget.h"
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
#include <QSignalMapper>
#include <QScrollArea>
#include <QGridLayout>
#include <QCheckBox>

ThemeSelectionWidget::ThemeSelectionWidget(QWidget *parent) :
    QWidget(parent)
{
  Database* db = new Database();
  _themes = db->loadThemes();
  this->buildWidget(dynamic_cast<MainWindow*>(parent));        
  this->showTheme(_themes);
}

void ThemeSelectionWidget::buildWidget(MainWindow *main_window)
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

    //Create label for description
    _theme_label = new QLabel("Select a theme : ");
    _theme_label->setStyleSheet("QLabel { font: 14px; font-family: trebuchet ms; margin: 0 auto; }");
  
    // Themes radio buttons
    foreach (QString theme, _themes)
    {
        _themes_check_boxes.append(new QCheckBox);
    }

    // Create scrollable area
    _scroll_area = new QScrollArea;
    QWidget *grid_widget = new QWidget;
    _scroll_area->setWidget(grid_widget);
    _grid_layout = new QGridLayout(grid_widget);

    _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _scroll_area->setWidgetResizable(true);

    // Create control buttons and back button
    _theme_button = new QPushButton(QIcon(":/images/validate.png"), tr("Validate"));
    _next_button = new QPushButton(QIcon(":/images/next.png"), tr("Next "));
    _back_button = new QPushButton(QIcon(":/images/backward.png"), tr("Back"));

    connect(_theme_button, SIGNAL(clicked()), this, SLOT(theme()));
    connect(this, SIGNAL(choiceDone(const QStringList &)), main_window, SLOT(launch_quizz(const QStringList &)));
    connect(_theme_button, SIGNAL(clicked()), this, SLOT(close()));
    connect(_back_button, SIGNAL(clicked()), main_window, SLOT(back()));
    connect(_back_button, SIGNAL(clicked()), this, SLOT(close()));

    _theme_button->setStyleSheet(MUSIK_CONTROL_BUTTON_STYLE);
    _theme_button->setIconSize(QSize(25, 25));
    _theme_button->setMaximumWidth(150);
    _next_button->setStyleSheet(MUSIK_CONTROL_BUTTON_STYLE);
    _next_button->setIconSize(QSize(25, 25));
    _next_button->setMaximumWidth(180);
    _back_button->setStyleSheet(MUSIK_BUTTON_STYLE);
    _back_button->setIconSize(QSize(25, 25));

    // Prepare theme layout
    QHBoxLayout *buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(_theme_button);
    buttons_layout->addWidget(_next_button);

    _theme_layout = new QVBoxLayout;
    _theme_layout->addWidget(_theme_label);
    _theme_layout->addWidget(_scroll_area);

    int i = 0;
    foreach (QString theme, _themes)
    {
        _grid_layout->addWidget(_themes_check_boxes.at(i));
        i++;
    }

    _theme_layout->addLayout(buttons_layout);

    this->setStyleSheet("QCheckBox { font: 15px; font-family: trebuchet ms; color: #573; margin-left: 100px }");


    _theme_layout->setAlignment(Qt::AlignHCenter);

    // Add widgets
    QHBoxLayout *title_layout = new QHBoxLayout;
    title_layout->addWidget(title_label);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(title_layout);
    layout->addLayout(_theme_layout);
    layout->addWidget(_back_button);
}

void ThemeSelectionWidget::showTheme(QStringList themes)
{
    // Themes
    int i = 0;
    foreach (QString theme, themes)
    {
        if(i == 0)
            _themes_check_boxes.at(i)->setChecked(true);
        _themes_check_boxes.at(i)->setText(themes.at(i));
        _themes_check_boxes.at(i)->setCheckable(true);
        _themes_check_boxes.at(i)->setStyleSheet("font-weight: normal; color: #573;");
        _themes_check_boxes.at(i)->show();
        i++;

    }


    // Control buttons
    _theme_button->setVisible(true);
    _next_button->setVisible(false);

}

ThemeSelectionWidget::~ThemeSelectionWidget()
{
    #ifndef QT_NO_DEBUG
        qDebug() << "~ThemeSelectionWidget()";
    #endif
}


void ThemeSelectionWidget::theme()
{
    int i = 0;
    foreach (QString theme, _themes)
    {
        //selected theme
        if (_themes_check_boxes.at(i)->isChecked())
            _themes_chosen << theme;
        i++;
    }
    emit choiceDone(_themes_chosen);
}
