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
        Question* currentQuestion();
        bool isFinished();
        void refreshScore(bool); // true if good answer
        int combo() const;
        int score() const;
        int timeLeft() const;
        bool timeOut() const;

};

#endif

