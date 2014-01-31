#ifndef QUESTION_HPP
#define QUESTION_HPP


#include <QString>
#include <QStringList>

using namespace std;

namespace musik
{
  
  class Question
  {
  private:
    const QString _question;
    const QStringList _answer;
    const int _n_answer;
    const QString _explaination;
    const int _correct_answer;
    const int _time;
    
    
  public:
    Question(const QString, const QStringList&, const int, const QString, const int, const int);
    bool isRight(int);
    const QString explaination();
    const QString answer(int);
    const QString question();
    int correctAnswer();
    int time();
  };
}

#endif
