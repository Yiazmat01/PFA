#include "Quizz.hpp"

/* After each nextQuestion() the score has to be updated with refreshScore()
 * Before each nextQuestion() the list has to be tested with isFinished()
 * If the list is finished, the score has to be compared and potentially added
 * to the highscore table
 */

namespace musik{

Quizz::Quizz(QList<Question>): _current_score(Score(0)), _combo(0),_time(QTime()), _current_question(-1)
    {

    }


    Question nextQuestion()
    {
        _time = QTime::currentTime();
        return _qestions.at(++_current_question);
    }

    bool isFinished()
    {
        return (_questions.size() -1 == _current_question);
    }

    void refreshScore(int i)
    {
        QTime answer_time = QTime::secsTo(_time);
        if (_questions.at(_current_question).isRight())
        {
            _combo++;

        }
        _combo = 0;
    }


    int combo()
    {
        return _combo;
    }

    int time()
    {
        return _time;
    }
}
