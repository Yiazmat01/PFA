#ifndef QUIZZWIDGET_H
#define QUIZZWIDGET_H

#include <QWidget>

class MainWindow;
class QPushButton;
class QLabel;
class QRadioButton;
class QVBoxLayout;
class Quizz;
class QTextEdit;
class QTimer;

class QuizzWidget : public QWidget
{
    Q_OBJECT

    private:
        // Question layout
        QVBoxLayout *_question_layout;

        // Question labels
        QLabel *_question_label;
        QTextEdit *_explanation_label;

        // Answers radio buttons
        QList<QRadioButton*> _answers_radio_buttons;

        // Control buttons and back button
        QPushButton *_answer_button;
        QPushButton *_next_question_button;
        QPushButton *_back_button;

        Quizz *_quizz;
        int _position_correct_answer;

        QStringList _positive_comments;
        QStringList _negative_comments;

        QTimer *_timer;
        QLabel *_time_left;

    public:
        explicit QuizzWidget(QWidget *parent = 0);
        ~QuizzWidget();

    private:
        void buildWidget(MainWindow *main_window);
        QStringList shuffleAnswers(QStringList answers);

    private slots:
        void answer();
        void showQuestion();
        void verify_timeout();
};

#endif // QUIZZWIDGET_H
