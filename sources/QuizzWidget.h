#ifndef QUIZZWIDGET_H
#define QUIZZWIDGET_H

#include <QWidget>

class MainWindow;
class QPushButton;
class QLabel;
class QRadioButton;
class QVBoxLayout;

class QuizzWidget : public QWidget
{
    Q_OBJECT

    private:
        // Question layout
        QVBoxLayout *_question_layout;

        // Question labels
        QLabel *_question_label;
        QLabel *_explanation_label;

        // Answers radio buttons
        QList<QRadioButton*> _answers_radio_buttons;

        // Control buttons and back button
        QPushButton *_answer_button;
        QPushButton *_next_question_button;
        QPushButton *_back_button;

    public:
        explicit QuizzWidget(QWidget *parent = 0);
        ~QuizzWidget();

    private:
        void buildWidget(MainWindow *main_window);

    private slots:
        void answer();
        void showQuestion();
};

#endif // QUIZZWIDGET_H
