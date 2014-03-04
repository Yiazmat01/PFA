#ifndef QUIZZ_HPP
#define QUIZZ_HPP

#include "Question.hpp"
#include "Score.hpp"
#include "QTime"

class Quizz
{
    private:
        QList<Question*> _questions;
        Score _current_score;
        int _combo; // number of correct answers in a row
        QTime _time; //time when the question began
        int _current_question;

    public:
        Quizz(QList<Question*>);
        Question* nextQuestion();
        bool isFinished();
        void refreshScore(int); // the argument of refreshScore is the number of the answer that has been chosen
        int combo();
        QTime time();

};

#endif

