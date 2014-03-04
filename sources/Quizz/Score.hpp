#ifndef SCORE_HPP
#define SCORE_HPP

#include <QString>

class Score
{
  private:
    int _score;
    QString _name;

  public:
    Score();
    int score();
    QString name();
    void setName(QString);
    void add(int);

};

#endif
