#ifndef QUIZZWIDGET_H
#define QUIZZWIDGET_H

#include <QWidget>

class MainWindow;

class QuizzWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit QuizzWidget(QWidget *parent = 0);
        ~QuizzWidget();

    private:
        void buildWidget(MainWindow *main_window);

};

#endif // QUIZZWIDGET_H
