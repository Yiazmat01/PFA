#include "MainWindow.h"
#include "NotesExploderWidget.h"
#include "QuizzWidget.h"
#include "ToolsWidget.h"
#include "Database.h"

#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Build menu
    QMenu *fileMenu(this->menuBar()->addMenu(tr("File")));
    fileMenu->addAction(QIcon(":/images/quit.png"), tr("Quit"), this, SLOT(close()));

    // Build main widget
    this->buildWidget();

    // Add main widget to the window
    this->setCentralWidget(_main_widget);

    // Set title
    this->setWindowTitle("MuSIK : Musical Software Instrument for Kids");

    // Create database
    Database* db = new Database();
    db->create();

}

MainWindow::~MainWindow()
{
    #ifndef QT_NO_DEBUG
        qDebug() << "~MainWindow()";
    #endif
}

void MainWindow::buildWidget()
{
    #define MUSIK_BUTTON_STYLE "QPushButton { margin: 10px; font: bold 20px; font-family: trebuchet ms; color: #FFF;" \
                               "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00aaf2, stop: 1 #005676);" \
                               "border-style: outset; border-radius: 10px; padding: 15px; }" \
                               "QPushButton:hover { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00ccf2, stop: 1 #007876); }"

    // Create label for title
    QLabel *title_label = new QLabel("MuSIK : Musical Software Instrument for Kids");
    QLabel *description_label = new QLabel(tr("Welcome in MuSIK! You can try out some musical tools like VLC or Audacity,<br>"
                                           "you can test your knowledge with the musical quizz or play NotesExploder to<br> "
                                           "see if you are able to survive among many notes"));
    title_label->setStyleSheet("QLabel { font: bold 20px; font-family: trebuchet ms; color: #57E; margin: 0 auto; }");
    description_label->setStyleSheet("QLabel { font: 14px; font-family: trebuchet ms; margin: 0 auto; }");

    // Create main window buttons
    QPushButton *tools_button = new QPushButton(QIcon(":/images/tools.png"), tr("Tools"));
    QPushButton *quizz_button = new QPushButton(QIcon(":/images/quizz.png"), tr("Quizz"));
    QPushButton *game_button = new QPushButton(QIcon(":/images/notes_exploder.png"), tr("NotesExploder"));

    connect(tools_button, SIGNAL(clicked()), this, SLOT(launch_tools()));
    connect(quizz_button, SIGNAL(clicked()), this, SLOT(launch_quizz()));
    connect(game_button, SIGNAL(clicked()), this, SLOT(launch_game()));

    tools_button->setStyleSheet(MUSIK_BUTTON_STYLE);
    quizz_button->setStyleSheet(MUSIK_BUTTON_STYLE);
    game_button->setStyleSheet(MUSIK_BUTTON_STYLE);

    tools_button->setIconSize(QSize(25, 25));
    quizz_button->setIconSize(QSize(25, 25));
    game_button->setIconSize(QSize(25, 25));

    // Add widgets
    _main_widget = new QWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(_main_widget);
    layout->addWidget(title_label);
    layout->addWidget(description_label);
    layout->addWidget(tools_button);
    layout->addWidget(quizz_button);
    layout->addWidget(game_button);
}

void MainWindow::launch_tools()
{
    this->setCentralWidget(new ToolsWidget(this));
}

void MainWindow::launch_quizz()
{
    this->setCentralWidget(new QuizzWidget(this));
}

void MainWindow::launch_game()
{
    this->setCentralWidget(new NotesExploderWidget(this));
}

void MainWindow::back()
{
    this->buildWidget();
    this->setCentralWidget(_main_widget);
}
