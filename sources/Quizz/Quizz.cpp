#include "Quizz.hpp"

/* After each nextQuestion() the score has to be updated with refreshScore()
 * Before each nextQuestion() the list has to be tested with isFinished()
 * If the list is finished, the score has to be compared and potentially added
 * to the highscore table
 */

namespace musik{

Quizz::Quizz(QList<Question>): _current_score(Score()), _combo(0),_time(QTime()), _current_question(-1)
    {

    }


    Question Quizz::nextQuestion()
    {
        _time = QTime::currentTime();
        return _questions.at(++_current_question);
    }

    bool Quizz::isFinished()
    {
        return (_questions.size() -1 == _current_question);
    }

    void Quizz::refreshScore(int i)
    {
        int answer_time = _time.secsTo(QTime::currentTime());
        if (_questions[_current_question].isRight(i))
        {
            _combo++;
            _current_score.add((1+_combo)* _questions[_current_question].difficulty() / answer_time);

        }
        _combo = 0;
    }


    int Quizz::combo()
    {
        return _combo;
    }

    QTime Quizz::time()
    {
        return _time;
    }
}
