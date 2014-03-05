#ifndef QUESTION_HPP
#define QUESTION_HPP


#include <QString>
#include <QStringList>
#include <QDebug>

using namespace std;

class Question
{
    private:
        int _id;
        QString _question;
        QStringList _answers;
        QString _explanation;
        int _difficulty;
        int _year;
        int _id_theme;

    public:
        Question(int id, QString question, QStringList &answers, QString explanation, int difficulty, int year, int id_theme);
        bool isRight(int) const;
        QString explanation() const;
        QStringList answers() const;
        QString answer(int i) const;
        QString question() const;
        int nbAnswer() const;
        int difficulty() const;
        int theme() const;
        int year() const;
        int id() const;
        void debug() const;

        void set_question(QString);
        void set_explanation(QString);
        void set_id(int);
        void set_difficulty(int);
        void set_id_theme(int);
        void set_year(int);
};

#endif
