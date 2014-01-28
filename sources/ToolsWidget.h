#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <QWidget>

class MainWindow;

class ToolsWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit ToolsWidget(QWidget *parent = 0);
        ~ToolsWidget();

    private:
        void buildWidget(MainWindow *main_window);
        void launch(QString executable_name) const;

    private slots:
        void launch_tool1() const;
        void launch_tool2() const;
        void launch_tool3() const;
};

#endif // TOOLSWIDGET_H
