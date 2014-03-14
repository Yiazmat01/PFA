#ifndef ADMINQUIZZWIDGET_H
#define ADMINQUIZZWIDGET_H

#include <QWidget>
#include <QHash>

class MainWindow;
class QGridLayout;
class QScrollArea;
class QVBoxLayout;

class AdminQuizzWidget : public QWidget
{
    Q_OBJECT
    private:
        QGridLayout *_grid_layout;
        QScrollArea *_scroll_area;

        QVBoxLayout *_admin_questions_layout;
        QVBoxLayout *_admin_themes_layout;
        QVBoxLayout *_admin_good_answers_layout;
        QVBoxLayout *_admin_bad_answers_layout;

        int _position_current_widget;
        QHash<QObject*, int> _buttons_links;

    public:
        explicit AdminQuizzWidget(QWidget *parent = 0);
        ~AdminQuizzWidget();

    private:
        void buildWidget(MainWindow *main_window);

    private slots:
        void switchWidget(int index);
        void new_question();
        void new_theme();
        void new_good_comment();
        void new_bad_comment();
        void modify_item();
        void delete_item();
    public slots:
        void reloadTab();
};

#endif // ADMINQUIZZWIDGET_H
