#include <iostream>
#include "Question.hpp"

namespace musik
{
  Question::Question(const QString q,const QStringList &tab, const int nb, const QString e,  const int diff, const int c_a, const int th, const int y):
      _id(-1), _question(q),_n_answer(nb),_explanation(e),
      _id_correct_answer(-1), _difficulty(diff), _answer(tab), _correct_answer(c_a),_id_theme(th), _year(y)
  {
    
  }
   
  bool Question::isRight(int i)
  {
    return (i == _correct_answer);
  }

  const QString Question::explanation()
  {
    return _explanation;
  }

  const QString Question::answer(int i)
  {
    if ((i > _n_answer -1) && i < 0)
      throw "Index out of bounds";
    return _answer[i];
  }

  const QString Question::question()
  {
    return _question;
  }

  int Question::correctAnswer()
  {
    return _correct_answer;
  }

  int Question::difficulty()
  {
    return _difficulty;
  }
  
  int Question::theme()
  {
    return _id_theme;
  }

  int Question::year()
  {
    return _year;
  }

}
