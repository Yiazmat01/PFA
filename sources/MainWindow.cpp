#include "MainWindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Build main widget
    _main_widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(_main_widget);

    QPushButton *tools_button = new QPushButton(QIcon(":/images/tools.png"), tr("Tools"));
    QPushButton *quizz_button = new QPushButton(QIcon(":/images/quizz.png"), tr("Quizz"));
    QPushButton *game_button = new QPushButton(QIcon(":/images/notes_exploder.png"), tr("NotesExploder"));

    layout->addWidget(tools_button);
    layout->addWidget(quizz_button);
    layout->addWidget(game_button);

    connect(tools_button, SIGNAL(clicked()), this, SLOT(launch_tools()));
    connect(quizz_button, SIGNAL(clicked()), this, SLOT(launch_quizz()));
    connect(game_button, SIGNAL(clicked()), this, SLOT(launch_game()));

    // Add main widget to the window
    this->setCentralWidget(_main_widget);

    // Title
    this->setWindowTitle("MuSIK : Musical Software Instrument for Kids");

    // Menu
    QMenu *fileMenu(this->menuBar()->addMenu(tr("File")));
    fileMenu->addAction(QIcon(":/images/quit.png"), tr("Quit"), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::launch_tools()
{

}

void MainWindow::launch_quizz()
{
}

void MainWindow::launch_game()
{
}
