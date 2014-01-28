#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <string>
namespace musik
{

  class Question
  {
  private:
    const string _question;
    const string [4] _answer;
    const int _n_answer;
    const string _explaination;
    const int _time;
    const int _correct_answer;


  public:
    Question(const string, const string[4], const int, const string, const int);
    bool isRight(int);
    const string explaination();
    const string answer(int);
    const string question();
    int correctAnswer();
  };
}

#endif
