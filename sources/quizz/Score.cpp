#include "Score.hpp"

Score::Score(): _score(0)
{
}

int Score::score() const
{
    return _score;
}

QString Score::name() const
{
    return _name;
}

void Score::setName(QString newname)
{
    _name = newname;
}

void Score::add(int i)
{
    _score += i;
}

