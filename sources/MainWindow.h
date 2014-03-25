#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        QWidget* _main_widget;

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

   private:
        void buildWidget();

    private slots:
        void launch_tools();
        void launch_quizz(QStringList theme);
        void launch_quizz_selection();
        void back();
        void launch_admin_quizz();
};

#endif // MAINWINDOW_H
