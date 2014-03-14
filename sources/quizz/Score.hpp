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
    int score() const;
    QString name() const;
    void setName(QString);
    void add(int);

};

#endif
