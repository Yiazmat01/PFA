#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <string>
namespace musik
{
	
	class Question
	{
		private:
			const string _question;
			const string [4] _answer;
			const int _n_answer;
			const string _explaination;
			const int time;
		
		public:
			Question(const String, const String[4], const int, const String);
			bool isRight(int);
			const string explaination();
			const string answer(int);
			const string question();
			int correctAnswer();
	};
}

#endif
