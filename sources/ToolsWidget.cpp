#include "ToolsWidget.h"
#include "MainWindow.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QProcess>
#include <QApplication>
#include <QMessageBox>

ToolsWidget::ToolsWidget(QWidget *parent) :
    QWidget(parent)
{
    this->buildWidget(dynamic_cast<MainWindow*>(parent));
}

ToolsWidget::~ToolsWidget()
{
    #ifndef QT_NO_DEBUG
        qDebug() << "~ToolsWidget()";
    #endif
}

void ToolsWidget::buildWidget(MainWindow *main_window)
{
    #define MUSIK_BUTTON_STYLE "QPushButton img { width:200%; } QPushButton { margin: 10px; font: bold 20px; font-family: trebuchet ms; color: #FFF;" \
                               "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00aaf2, stop: 1 #005676);" \
                               "border-style: outset; border-radius: 10px; padding: 5px; }" \
                               "QPushButton:hover { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00ccf2, stop: 1 #007876); }"

    #define MUSIK_TOOLS_BUTTON_STYLE "QPushButton { margin: 10px; font: bold 20px; font-family: trebuchet ms; color: #FFF;" \
                                     "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ba2232, stop: 1 #560011);" \
                                     "border-style: outset; border-radius: 10px; padding: 20px; }" \
                                     "QPushButton:hover { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e52232, stop: 1 #890011); }"

    #define MUSIK_LABEL_STYLE "QLabel { font: bold 20px; font-family: trebuchet ms; color: #57E; margin: 0 auto; }"

    // Create label for title
    QLabel *title_label = new QLabel("Musical tools availables");
    title_label->setStyleSheet(MUSIK_LABEL_STYLE);

    // Create tools buttons and back button
    QPushButton *tool1_button = new QPushButton(QIcon(":/images/tool_vlc.png"), tr("VLC"));
    QPushButton *tool2_button = new QPushButton(QIcon(":/images/tool_audacity.png"), tr("Audacity"));
    QPushButton *tool3_button = new QPushButton(QIcon(":/images/tools.png"), tr("Metronimix"));
    QPushButton *back_button = new QPushButton(QIcon(":/images/backward.png"), tr("Back"));

    connect(tool1_button, SIGNAL(clicked()), this, SLOT(launch_tool1()));
    connect(tool2_button, SIGNAL(clicked()), this, SLOT(launch_tool2()));
    connect(tool3_button, SIGNAL(clicked()), this, SLOT(launch_tool3()));
    connect(back_button, SIGNAL(clicked()), main_window, SLOT(back()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(close()));

    tool1_button->setStyleSheet(MUSIK_TOOLS_BUTTON_STYLE);
    tool2_button->setStyleSheet(MUSIK_TOOLS_BUTTON_STYLE);
    tool3_button->setStyleSheet(MUSIK_TOOLS_BUTTON_STYLE);
    back_button->setStyleSheet(MUSIK_BUTTON_STYLE);

    tool1_button->setIconSize(QSize(50, 50));
    tool2_button->setIconSize(QSize(50, 50));
    tool3_button->setIconSize(QSize(50, 50));
    back_button->setIconSize(QSize(25, 25));

    // Add widgets
    QHBoxLayout *tools_layout = new QHBoxLayout;
    tools_layout->addWidget(tool1_button);
    tools_layout->addWidget(tool2_button);
    tools_layout->addWidget(tool3_button);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title_label);
    layout->addLayout(tools_layout);
    layout->addWidget(back_button);
}

void ToolsWidget::launch(QString executable_name) const
{
    if ( ! QProcess::startDetached(QApplication::applicationDirPath() + "/tools/" + executable_name))
        QMessageBox::critical(NULL, tr("Error"), tr("Error while trying to start this tool"));
}

void ToolsWidget::launch_tool1() const
{
    // Windows
    #if defined(Q_OS_WIN32)
        this->launch("vlc_win/vlc.exe");

    // Unix
    #elif defined(Q_OS_LINUX)
        this->launch("vlc");

    // Mac
    #elif defined(Q_OS_MAC)
        this->launch("vlc");

    // Others operating systems
    #else
        QMessageBox::critical(NULL, tr("Error"), tr("We are sorry, this program is not available on your system"));
    #endif
}

void ToolsWidget::launch_tool2() const
{
    // Windows
    #if defined(Q_OS_WIN32)
        this->launch("audacity_win/audacity.exe");

    // Unix
    #elif defined(Q_OS_LINUX)
        this->launch("audacity");

    // Mac
    #elif defined(Q_OS_MAC)
        this->launch("audacity");

    // Others operating systems
    #else
        QMessageBox::critical(NULL, tr("Error"), tr("We are sorry, this program is not available on your system"));
    #endif
}

void ToolsWidget::launch_tool3() const
{
    // Windows
    #if defined(Q_OS_WIN32)
        this->launch("audacity_win/audacity.exe");

    // Unix
    #elif defined(Q_OS_LINUX)
        this->launch("audacity");

    // Mac
    #elif defined(Q_OS_MAC)
        this->launch("audacity");

    // Others operating systems
    #else
        QMessageBox::critical(NULL, tr("Error"), tr("We are sorry, this program is not available on your system"));
    #endif
}
