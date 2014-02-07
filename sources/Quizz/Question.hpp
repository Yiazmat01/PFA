#ifndef QUESTION_HPP
#define QUESTION_HPP


#include <QString>
#include <QStringList>
#include <QDebug>

using namespace std;

namespace musik
{
  
  class Question
  {
  private:
    int _id;
    QString _question;
    QStringList _answer;
    int _n_answer;
    QString _explanation;
    int _id_correct_answer;
    int _correct_answer;
    int _difficulty;
    int _id_theme;
    int _year;
    

    
    
  public:
    Question(QString, QStringList&, int, QString, int, int, int, int);
    bool isRight(int) const;
    QString explanation() const;
    QString answer(int) const;
    QString question() const;
    int correctAnswer() const;
    int nbAnswer() const;
    int difficulty() const;
    int theme() const;
    int year() const;
    int id() const;
    int id_correct_answer() const;
    void debug() const;

    void set_question(QString*);
    void set_explanation(QString*);
    void set_answer(QString*, int);
    void set_id(int);
    void set_id_correct_answer(int);
    void set_difficulty(int);
    void set_id_theme(int);
    void set_year(int);

    void addAnswer(QString *);
    void deleteAnswer(int);
  };
}

#endif
