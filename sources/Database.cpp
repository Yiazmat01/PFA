#include "Database.h"
#include "Quizz/Question.hpp"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

using namespace musik;
/*--------------------------------------------------------------------*\
        Public
\*--------------------------------------------------------------------*/

/*Database::Database(Utils *utils)
    : _utils(utils)
{
    // Load SQLite driver
    _db    = QSqlDatabase::addDatabase("QSQLITE");
    _query = NULL;
}
*/
Database::Database()
{
    // Load SQLite driver
    _db    = QSqlDatabase::addDatabase("QSQLITE");
    _db.setHostName("localhost");
    _db.setDatabaseName("base");
    _query = NULL;
}

Database::~Database()
{
    #ifndef QT_NO_DEBUG
        qDebug() << "~Database()";
    #endif

    // Close connection
    this->clear();
}

bool Database::compact()
{
    // Clean erased data from database (which remains on disk when deleted)
    bool result = this->exec("VACUUM");
    this->clear();
    return result;
}

bool Database::create()
{
    // Create table questions if not exists
    bool result;

    if (!(result = this->exec("CREATE TABLE IF NOT EXISTS Answer("
                                 "id          INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "text        TEXT);")))
        qDebug() << "Problem with Answer creation.";
    this->clear();

    if (!(result = this->exec("CREATE TABLE IF NOT EXISTS Theme("
                                 "id          INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "text        TEXT);")))
        qDebug() << "Problem with Theme creation.";
    this->clear();

    if(!( result = this->exec("CREATE TABLE IF NOT EXISTS Questions("
                             "id               INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "text             TEXT,"
                             "explanation     TEXT,"
                             "id_good_answer   INTEGER,"
                             "id_theme         INTEGER,"
                             "score            INTEGER DEFAULT 0,"
                             "FOREIGN KEY (id_good_answer)   REFERENCES Answer(id),"
                             "FOREIGN KEY (id_theme)         REFERENCES Theme(id));"
                               )))
        qDebug() << "Problem with Questions creation";
    this->clear();

    if(!(result = this->exec("CREATE TABLE IF NOT EXISTS AnswerList("
                             "id_question INTEGER,"
                             "id_answer INTEGER,"
                             "FOREIGN Key(id_question) REFERENCES Questions(id),"
                             "FOREIGN Key(id_answer)   REFERENCES Answer(id));"
                             )))
        qDebug() << "Problem with AnswerList creation";

    this->clear();
    qDebug() << "base created ?" << result;
    return result;
}

// Get
QString Database::error() const
{
    return _error;
}

QString Database::dbname() const
{
    return _db.databaseName();
}

// Set
void Database::setDatabaseName(const QString &filename)
{
    this->clear();
    _db.setDatabaseName(filename);
}

bool Database::insertQuestion(musik::Question *question)
{
    bool result = false;

    // Create vars list for prepared query
    int i, id_good_answer;
    QVariantList vars_q, vars_a;
    // We should use a QList
    for(i = 0; i < 4; i++) {
        vars_a << question->answer(i);
        if (i = question->correctAnswer()) {
            id_good_answer = i;
        }
    }

    // Insert Answer
    if (this->exec("INSERT INTO Answers(text, explanation, duration, id_good_answer) VALUES(?, ?, ?, ?)", vars_q))
    {
        QVariant id(_query->lastInsertId());

        if (id.isValid())
        {
            //question->setId(id.toInt());
            result = true;
        }
    }

    this->clear();

    vars_q << question->question()
           << question->explanation()
           << id_good_answer;//<< question->theme() << question->score();

    // Insert question
    if (this->exec("INSERT INTO Questions(text, explanation, duration, id_good_answer) VALUES(?, ?, ?, ?)", vars_q))
    {
        QVariant id(_query->lastInsertId());

        if (id.isValid())
        {
            //question->setId(id.toInt());
            result = true;
        }
    }

    this->clear();
    return result;
}

QList<Question*> Database::loadQuestions()
{
    bool result = false;
    QList<Question*> questionList;
    Question * question;
    QList<int> idList;
    int good_answer, current_id=1, nb_questions=0;
    // Select all questions

    if (this->exec("SELECT id FROM Questions;"))
    {
        while(_query->next()) {
            idList << _query->value(0).toInt();
        }
        this->clear();
    }

    foreach(int id, idList) {
        QVariantList vars;
        bool stocked = false;
        QString statement, explanation;
        int id_question, id_good_answer, id_theme;
        vars << id;
        QString query("Select q.*, a.*\
                       from Questions as q, Answer as a, AnswerList as l\
                       where l.id_question = ?\
                       and q.id=l.id_question\
                       and l.id_answer = a.id");
        if(this->exec(query,vars)){
        QStringList answers;
        QList<int> idListAnswer;
        while (_query->next()){
            if(!stocked) {
                stocked = true;
                id_question =_query->value(0).toInt();
                statement = _query->value(1).toString();
                explanation = _query->value(2).toString();
                id_good_answer = _query->value(3).toInt();
                id_theme = _query->value(5).toInt();
            }
            answers << _query->value(7).toString();
            idListAnswer << _query->value(6).toInt();
        }
        good_answer = findGoodAnswerPos(idListAnswer,id_good_answer);
        qDebug() << answers;
        question = new Question(statement,
                                answers,
                                answers.length(), // nb_answers
                                explanation,
                                42, // difficulty
                                good_answer, //
                                id_theme,
                                2014); // time but soon score
        question->set_id(id_question); //id
        question->set_id_correct_answer(id_good_answer);
        this->clear();
  }
}
 /*       {
        // Browse all results

        {


            //get answerslist from current question
            //do{
             while(current_id == _query->value(0).toInt()) {
              qDebug() << current_id;

              _query->next();
            }
            qDebug() << answers ;

            /* il faut choisir aléatoirement la bonne réponse (tu vois ce que jveux dire)  */
            /*question = new Question( _query->value(1).toString(),
                                     answers,
                                     4, // nb_answers
                                     _query->value(2).toString(), // explanation
                                     42, // difficulty
                                     good_answer, //
                                     _query->value(5).toInt(), // id_theme
                                     2014); // time but soon score
            // _query->value(0).toInt() //id
            // _query->value(3).toInt(), // id_good_answer
            questionList.append(question);
*/

   /*         current_id = _query->value(0).toInt();
        }*/
        result = true;


    qDebug() << _db.lastError();
    this->clear();
    return questionList;
}

bool Database::updateQuestion(Question * question)
{
    // Create vars list for prepared query
    QVariantList vars_q, vars_a;
    vars_q << question->question()
         << question->explanation();
         //<< id_good_answer;
       //<< question->theme()
       //<< question->score();

    // Update Question
    QString query_q("UPDATE Questions SET"
                  "text = ?,"
                  "explanation = ?,"
                  "id_good_answer = ?,"
                  "id_theme = ?,"
                  "score = ?"
                  "WHERE id = ?");

    // faire le lien avec la table answerList
    /*
    for(i = 0; i < 4; i++) {
        vars_a << question->answer(i) << question->answer(i);
        if (i = question->correctAnswer()) {
            id_good_answer = i;
        }
    }
    QString query_a("UPDATE Answer SET "
                    "text = ?,"
                    "WHERE text = ?");
    */
    // Execute query
    QString query_a;
    bool result = this->exec(query_q, vars_q);
    this->clear();

    bool result2 = this->exec(query_a, vars_a);
    this->clear();
    return result && result2;
}



/*--------------------------------------------------------------------*\
        Private
\*--------------------------------------------------------------------*/
bool Database::open()
{
    _error.clear();

    // If db is already opened, close connection
    if (_db.isOpen())
        this->clear();

    // Try opening db
    if ( ! _db.open())
    {
        _error = _db.lastError().text();
        qDebug() << "failure";
        return false;
    }

    return true;
}

bool Database::exec(const QString &query)
{
    if (this->open())
    {
        _query = new QSqlQuery;

        // This is very important for select queries
        _query->setForwardOnly(true);

        // Exec query
        if (_query->exec(query))
            return true;

        _error = _query->lastError().text();
    }

    return false;
}

bool Database::exec(const QString &query, const QVariantList &vars)
{
    if (this->open())
    {
        _query = new QSqlQuery;

        // This is very important for select queries
        _query->setForwardOnly(true);

        // Prepare query
        if ( ! _query->prepare(query))
            _error = _query->lastError().text();

        else
        {
            // Bind vars
            foreach (QVariant var, vars)
                _query->addBindValue(var);

            // Exec query
            if (_query->exec())
                return true;

            _error = _query->lastError().text();
        }
    }

    return false;
}

void Database::clear()
{
    if (_query != NULL)
    {
        // Clear and finish query
        _query->finish();
        _query->clear();

        // Delete query and set it to NULL for further comparaisons
        delete _query;
        _query = NULL;
    }

    _db.close();
}

int Database::findGoodAnswerPos(const QList<int>& idListAnswer, const int & id_good_answer)
{
    int i=0;
    foreach(int id, idListAnswer) {
        if (id == id_good_answer)
            return i;
        i++;
    }
    return -1;
}
