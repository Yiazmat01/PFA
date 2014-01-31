#include <iostream>
#include "Question.hpp"

namespace musik
{
  Question::Question(const QString q,const QStringList &tab, const int nb, const QString e, const int ok, const int t): _question(q),_n_answer(nb),_explaination(e), _correct_answer(ok), _time(t), _answer(tab)
  {
    
  }
   



  bool Question::isRight(int i)
  {
    return (i == _correct_answer);
  }

  const QString Question::explaination()
  {
    return _explaination;
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
