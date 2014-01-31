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
    _db.setUserName("root");
    _db.setPassword("");
    qDebug() << "open ? " << _db.isOpen();
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
    bool result = this->exec("CREATE TABLE IF NOT EXISTS Questions("
                             "id             INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "text          TEXT,"
                             "explaination  TEXT,"
                             "duration      INTEGER DEFAULT 30,"
                             "score         INTEGER DEFAULT 0)"); //we may change default value
/*
                             "CREATE TABLE IF NOT EXISTS Answer("
                             "id             INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "text          TEXT);"

                             "CREATE TABLE IF NOT EXISTS Quizz("
                             "id             INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "title          TEXT,"
                             "highscore      INTEGER DEFAULT 0)"

                             "CREATE TABLE IF NOT EXISTS Contains("
                             "FOREIGN Key(id_question) REFERENCES Question(id),"
                             "FOREIGN Key(id_quizz)   REFERENCES Quizz(id));"

                             "CREATE TABLE IF NOT EXISTS GoodAnswer("
                             "FOREIGN Key(id_question) REFERENCES Question(id),"
                             "FOREIGN Key(id_answer)   REFERENCES Answer(id));"

                             "CREATE TABLE IF NOT EXISTS BadAnswer("
                             "FOREIGN Key(id_question) REFERENCES Question(id),"
                             "FOREIGN Key(id_answer)   REFERENCES Answer(id));"
                             );
  */
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
    QVariantList vars;
    vars << question->question() << question->explaination() << 30;

    // Insert question
    if (this->exec("INSERT INTO Questions(text, explaination, duration) VALUES(?, ?, ?)", vars))
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

bool Database::loadQuestions()
{
    bool result = false;


    // Select all questions
    if (this->exec("SELECT * FROM Questions"))
    {

        // Browse all results
        while (_query->next())
        {

            qDebug() << _query->value(0).toInt() << _query->value(1).toString()
                << _query->value(2).toString()
                << _query->value(3).toInt()
                << _query->value(4).toInt();

        }

        result = true;
    }

    qDebug() <<"recoucou";
    this->clear();
    return result;
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
