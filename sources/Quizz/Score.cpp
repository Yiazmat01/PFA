#include "Score.hpp"


namespace musik
{

Score::Score(): _score(0)
    {

    }

int Score::score()
{
        return _score;
}

QString Score::name()
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

}
