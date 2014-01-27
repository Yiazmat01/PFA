#include <iostream>
#include <string>
#include "Question.hpp"

namespace musik
{
  Question::Question(const string q, const string[4] tab, const int nb, const string e, const int ok)
  {
    _queston = q;
    for (int i = 0; i < _n_answer; i++){
      _answer[i] = tab[i];
    }
    _explanation = e;
    _correct_answer = ok;  
  }

  bool Question::isRight(int i)
  {
    return (i == _correct_answer);
  }

  const string Question::explaination()
  {
    return _explaination;
  }

  const string Question::answer(int i)
  {
    if ((i > _n_answer -1) && i < 0)
      throw "Index out of bounds"
    return _answer[i];
  }

  const string Question::question()
  {
    return _question;
  }

  int Question::correctAnswer()
  {
    return _correct_answser;
  }

}
