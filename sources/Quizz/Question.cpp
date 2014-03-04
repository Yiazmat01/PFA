#include <iostream>
#include "Question.hpp"

Question::Question(int id, QString question, QStringList &answers, QString explanation, int difficulty, int year, int id_theme)
    : _id(id), _question(question), _answer(answers), _n_answer(answers.size()), _explanation(explanation), _difficulty(difficulty), _year(year), _id_theme(id_theme)
{
}

/*Question::Question( QString q, QStringList &tab,  int nb,  QString e,   int diff,  int c_a,  int y, int th):
  _id(-1), _question(q),_n_answer(nb),_explanation(e),
  _id_correct_answer(-1), _difficulty(diff), _answer(tab), _correct_answer(c_a), _year(y), _id_theme(th)
{
  try
  {
    if (_correct_answer > _n_answer || _correct_answer < 0)
    {
        throw "Correct answer out of bounds";
    }
    if (_difficulty > 3 || _difficulty < 1)
    {
        throw "Difficulty out of bounds, has to be between 1 and 3";
    }
    if  (_n_answer != _answer.size())
    {
        throw "the number of answers given differs from the number of answers provided";
    }
  }
  catch (const char * Msg)
  {
      std::cerr << Msg;
  }
}*/

bool Question::isRight(int i) const
{
return (i == _correct_answer);
}

QString Question::explanation() const
{
return _explanation;
}

QString Question::answer(int i) const
{
    try
    {
        if ((i > _n_answer -1) && i < 0)
        {
            throw "Index out of bounds";
        }
    }
    catch (const char * Msg)
    {
        std::cerr << Msg;
    }
    return _answer[i];
}

QString Question::question() const
{
    return _question;
}

int Question::correctAnswer() const
{
    return _correct_answer;
}

int Question::nbAnswer() const
{
    return _n_answer;
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

void Question::set_id_correct_answer(int i)
{
  _id_correct_answer = i;
}

int Question::id_correct_answer() const
{
  return _id_correct_answer;
}

void Question::debug() const
{
  qDebug() << endl
           << "id :"<< _id << endl
           << "question :"<< _question << endl
           << "answer :"<< _answer << endl
           << "explanation :"<< _explanation << endl
           << "correct_answer :"<< _correct_answer << endl
           << "id_theme :"<< _id_theme << endl
           << "year :"<< _year << endl
           << "id_correct_answer :"<< _id_correct_answer << endl;
}

void Question::set_question(QString *s)
{
  _question = *s;
}

void Question::set_explanation(QString *s)
{
  _explanation = *s;
}
void Question::set_answer(QString *s, int i)
{
  try
  {
      if (i < 0 || i > _n_answer)
          throw "index out of bounds";
  }
  catch (const char * Msg)
  {
      std::cerr << Msg;
  }
  _answer.replace(i, *s);
}


void Question::set_difficulty(int i)
{
  try
  {
      if (i < 1 || i > 3)
          throw "difficulty out of bounds";
  }
  catch (const char * Msg)
  {
      std::cerr << Msg;
  }
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

void Question::addAnswer(QString *s)
{
  _answer << *s;
}

void Question::deleteAnswer(int i)
{
  try
  {
      if (i < 0 || i > _n_answer)
          throw "index out of bounds";
  }
  catch (const char * Msg)
  {
      std::cerr << Msg;
  }
  _answer.removeAt(i);
}
