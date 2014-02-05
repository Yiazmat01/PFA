#include <iostream>
#include "Question.hpp"

namespace musik
{
  Question::Question(const int id,const QString q,const QStringList &tab, const int nb, const QString e, int id_a, const int t, const int c_a):
      _id(id), _question(q),_n_answer(nb),_explanation(e),
      _id_correct_answer(id_a), _time(t), _answer(tab), _correct_answer(c_a)
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

  int Question::time()
  {
    return _time;
  }
  

  }
