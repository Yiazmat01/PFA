#include "MainWindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // The application name here is used by the system to correctly manage processus
    app.setApplicationName("MuSIK : Musical Software Instrument for Kids");

    // QString must be in UTF-8 format (all code is written in UTF-8)
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    MainWindow window;

    // Resize then show window
    QDesktopWidget desktop;

    int screenWidth = desktop.screenGeometry().width();
    int screenHeight = desktop.screenGeometry().height();

    // If screen is too small, we show application in maximized mode
    if (screenWidth <= 1024 || screenHeight <= 768)
        window.showMaximized();

    // Else application takes 2/3 of screen
    else
    {
        window.resize(screenWidth * 2 / 3, screenHeight * 2 / 3);
        window.move((screenWidth - window.width()) / 2, (screenHeight - window.height()) / 2);
        window.show();
    }

    window.show();
    
    return app.exec();
}
