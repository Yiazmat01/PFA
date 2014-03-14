#include "Quizz.hpp"
#include "math.h"

/* After each nextQuestion() the score has to be updated with refreshScore()
 * Before each nextQuestion() the list has to be tested with isFinished()
 * If the list is finished, the score has to be compared and potentially added
 * to the highscore table
 */

Quizz::Quizz(QList<Question*> questions)
    : _questions(questions), _current_score(Score()), _combo(0), _time(QTime()), _current_question(-1)
{
}

Question* Quizz::nextQuestion()
{
    _time = QTime::currentTime();
    return _questions.at(++_current_question);
}

Question* Quizz::currentQuestion()
{
    return _questions.at(_current_question);
}

bool Quizz::isFinished()
{
    return (_questions.size() -1 == _current_question);
}

void Quizz::refreshScore(bool good_answer)
{
    int answer_time = min(1, _time.secsTo(QTime::currentTime()));

    if ( ! good_answer)
        _combo = 0;

    _current_score.add(ceil((_combo * _questions[_current_question]->difficulty() + (int)good_answer) / (answer_time / 10.0)));
    _combo++;
}

int Quizz::combo() const
{
    return _combo;
}

int Quizz::score() const
{
    return _current_score.score();
}

int Quizz::timeLeft() const
{
    return 30 - _time.secsTo(QTime::currentTime());
}

bool Quizz::timeOut() const
{
    return timeLeft() <= 0;
}
