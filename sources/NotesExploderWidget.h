#ifndef NOTESEXPLODERWIDGET_H
#define NOTESEXPLODERWIDGET_H

#include <QWidget>

class MainWindow;

class NotesExploderWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit NotesExploderWidget(QWidget *parent = 0);
        ~NotesExploderWidget();

    private:
        void buildWidget(MainWindow *main_window);
};

#endif // NOTESEXPLODER_H
