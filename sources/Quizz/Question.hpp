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
    int _id;
    const QString _question;
    const QStringList _answer;
    const int _n_answer;
    const QString _explanation;
    int _id_correct_answer;
    const int _correct_answer;
    const int _difficulty;
    const int _id_theme;
    const int _year;
    

    
    
  public:
    Question(const QString, const QStringList&, const int, const QString, const int, const int, const int, const int);
    bool isRight(int);
    const QString explanation();
    const QString answer(int);
    const QString question();
    int correctAnswer();
    int difficulty();
    int theme();
    int year();
  };
}

#endif
