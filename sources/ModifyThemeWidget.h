#ifndef MODIFYTHEMEWIDGET_H
#define MODIFYTHEMEWIDGET_H

#include <QWidget>

class QLineEdit;

class ModifyThemeWidget : public QWidget
{
    Q_OBJECT

    private:
        QLineEdit *_theme;
        QWidget *_caller;

    public:
        explicit ModifyThemeWidget(bool new_theme, QWidget *caller);
        ~ModifyThemeWidget();

    private:
        void buildWidget(bool new_theme);

    private slots:
        void save();
};

#endif // MODIFYTHEMEWIDGET_H
