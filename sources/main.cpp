#include "MainWindow.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // The application name here is used by the system to correctly manage processus
    app.setApplicationName("MuSIK : Musical Software Instrument for Kids");

    MainWindow window;

    // Resize then show window
    QDesktopWidget desktop;

    int screenWidth = desktop.screenGeometry().width();
    int screenHeight = desktop.screenGeometry().height();

    window.resize(700, 400);
    window.move((screenWidth - window.width()) / 2, (screenHeight - window.height()) / 2);
    window.show();

    return app.exec();
}
