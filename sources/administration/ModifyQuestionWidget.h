#ifndef MODIFYQUESTIONWIDGET_H
#define MODIFYQUESTIONWIDGET_H

#include <QWidget>

class QLineEdit;
class QTextEdit;
class QComboBox;
class Question;

class ModifyQuestionWidget : public QWidget
{
    Q_OBJECT

    private:
        bool _new_question;
        Question *_current_question;
        QWidget *_caller;

        QComboBox *_theme;
        QComboBox *_difficulty;
        QLineEdit *_question;
        QLineEdit *_year;
        QList<QLineEdit*> _answers;
        QTextEdit *_explanation;

    public:
        explicit ModifyQuestionWidget(bool new_question, Question *question, QWidget *caller);
        ~ModifyQuestionWidget();

    private:
        void buildWidget();

    private slots:
        void save();
};

#endif // MODIFYQUESTIONWIDGET_H
