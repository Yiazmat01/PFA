#include "Question.hpp"
#include <iostream>

using namespace musik;
using namespace std;

int main (){
  
  QString q = "Quoi qu'est-ce ?";

  QString r1 = "42";
  QString r2 = "Vous pouvez répéter la question ?";
  QString r3 = "Obiwan Kenobi";
  QString r4 = "D, la réponse D";

  QStringList t;
  t << r1 << r2 << r3 << r4;

  int nb = 4;
  QString e = "Parce que, MAIS PARCE QUE !";
  int ok = 3;
  int time = 50;

  Question q1(q, t, nb, e, ok, time);
  qDebug(q1.answer(q1.correctAnswer()).toLatin1());

  return 0;
}
