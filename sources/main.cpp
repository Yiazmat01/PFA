#include "MainWindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QFile>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // The application name here is used by the system to correctly manage processus
    app.setApplicationName("MuSIK : Musical Software Instrument for Kids");

    // Translation
    QLocale locale;
    QString lang = QString(locale.name()).mid(0, 2);
    QString filename = QApplication::applicationDirPath() + "/lang/musik_" + lang + ".qm";
    QTranslator translator;

    // If locale traduction file exists
    if (QFile::exists(filename))
    {
        translator.load(filename);
        app.installTranslator(&translator);
    }

    MainWindow window;

    // Resize then show window
    QDesktopWidget desktop;

    int screenWidth = desktop.screenGeometry().width();
    int screenHeight = desktop.screenGeometry().height();

    window.resize(700, 450);
    window.move((screenWidth - window.width()) / 2, (screenHeight - window.height()) / 2);
    window.show();

    return app.exec();
}
