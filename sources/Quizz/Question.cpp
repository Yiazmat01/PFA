#include <iostream>
#include "Question.hpp"

Question::Question(int id, QString question, QStringList &answers, QString explanation, int difficulty, int year, int id_theme)
    : _id(id), _question(question), _answers(answers), _explanation(explanation), _difficulty(difficulty), _year(year), _id_theme(id_theme)
{
}

bool Question::isRight(int i) const
{
    return i == 0;
}

QString Question::explanation() const
{
    return _explanation;
}

QString Question::answer(int i) const
{
    return _answers.at(i);
}

QStringList Question::answers() const
{
    return _answers;
}

QString Question::question() const
{
    return _question;
}

int Question::nbAnswer() const
{
    return _answers.size();
}

int Question::difficulty() const
{
    return _difficulty;
}

int Question::theme() const
{
    return _id_theme;
}

int Question::year() const
{
    return _year;
}

void Question::set_id(int i)
{
    _id = i;
}

int Question::id() const
{
  return _id;
}

void Question::debug() const
{
  qDebug() << endl
           << "id :"<< _id << endl
           << "question :"<< _question << endl
           << "answer :"<< _answers << endl
           << "explanation :"<< _explanation << endl
           << "id_theme :"<< _id_theme << endl
           << "year :"<< _year << endl;
}

void Question::set_question(QString s)
{
    _question = s;
}

void Question::set_explanation(QString s)
{
    _explanation = s;
}

void Question::set_difficulty(int i)
{
    _difficulty = i;
}

void Question::set_id_theme(int i)
{
    _id_theme = i;
}

void Question::set_year(int i)
{
    _year = i;
}
