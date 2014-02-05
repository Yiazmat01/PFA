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
    const int _id;
    const QString _question;
    const QStringList _answer;
    const int _n_answer;
    const QString _explanation;
    int _id_correct_answer;
    const int _correct_answer;
    const int _time;

    
    
  public:
    Question(const int, const QString, const QStringList&, const int, const QString, int, const int, const int);
    bool isRight(int);
    const QString explanation();
    const QString answer(int);
    const QString question();
    int correctAnswer();
    int time();
  };
}

#endif
