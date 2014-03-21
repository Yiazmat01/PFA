#ifndef MODIFYTHEMEWIDGET_H
#define MODIFYTHEMEWIDGET_H

#include <QWidget>

class QLineEdit;

class ModifyThemeWidget : public QWidget
{
    Q_OBJECT

    private:
        QLineEdit *_theme;
        bool _new_theme;
        int _theme_id;
        QWidget *_caller;

    public:
        explicit ModifyThemeWidget(bool new_theme, QString theme, QWidget *caller);
        ~ModifyThemeWidget();

    private:
        void buildWidget(QString theme);

    private slots:
        void save();
};

#endif // MODIFYTHEMEWIDGET_H
