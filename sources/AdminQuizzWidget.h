#ifndef ADMINQUIZZWIDGET_H
#define ADMINQUIZZWIDGET_H

#include <QWidget>

class MainWindow;
class QGridLayout;
class QScrollArea;

class AdminQuizzWidget : public QWidget
{
    Q_OBJECT
    private:
        QGridLayout *_grid_layout;
        QScrollArea *_scroll_area;

    public:
        explicit AdminQuizzWidget(QWidget *parent = 0);
        ~AdminQuizzWidget();

    private:
        void buildWidget(MainWindow *main_window);

    private slots:
        void switchWidget(int index);
        void new_question();
};

#endif // ADMINQUIZZWIDGET_H
