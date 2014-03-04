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
        QList<QLineEdit*> _answers;
        QTextEdit *_explanation;

    public:
        explicit ModifyQuestionWidget(bool new_question);
        ~ModifyQuestionWidget();

    private:
        void buildWidget(bool new_question);

    private slots:
        void save();
};

#endif // MODIFYQUESTIONWIDGET_H
