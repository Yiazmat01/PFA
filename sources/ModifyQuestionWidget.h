#ifndef MODIFYQUESTIONWIDGET_H
#define MODIFYQUESTIONWIDGET_H

#include <QWidget>

class QLineEdit;
class QTextEdit;

class ModifyQuestionWidget : public QWidget
{
    Q_OBJECT

    private:
        QLineEdit *_theme;
        QLineEdit *_question;
        QLineEdit *_answer1;
        QLineEdit *_answer2;
        QLineEdit *_answer3;
        QLineEdit *_answer4;
        QTextEdit *_explaination;

    public:
        explicit ModifyQuestionWidget(bool new_question);
        ~ModifyQuestionWidget();

    private:
        void buildWidget(bool new_question);

    private slots:
        void save();
};

#endif // MODIFYQUESTIONWIDGET_H
