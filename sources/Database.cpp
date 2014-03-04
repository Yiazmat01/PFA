#include "Database.h"
#include "Quizz/Question.hpp"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>
#include <QMessageBox>

Database::Database()
{
    // Load SQLite driver
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setHostName("localhost");
    _db.setDatabaseName("db/quizz.db3");
    _query = NULL;

    // Create database
    this->create();
}

Database::~Database()
{
    #ifndef QT_NO_DEBUG
        qDebug() << "~Database()";
    #endif

    // Close connection
    this->clear();
}

void Database::create()
{
    // Make "db" directory
    QDir dir;
    dir.mkdir("db");

    // Construct list of queries
    QStringList queries;

    queries << "CREATE TABLE IF NOT EXISTS Themes("
               "    id          INTEGER PRIMARY KEY AUTOINCREMENT,"
               "    theme       TEXT"
               ")";

    queries << "CREATE TABLE IF NOT EXISTS Questions("
               "    id               INTEGER PRIMARY KEY AUTOINCREMENT,"
               "    question         TEXT,"
               "    explanation      TEXT,"
               "    difficulty       INTEGER,"
               "    year             INTEGER,"
               "    nb_answers       INTEGER,"
               "    id_theme         INTEGER"
               ")";

    queries << "CREATE TABLE IF NOT EXISTS Answers("
               "    id          INTEGER PRIMARY KEY AUTOINCREMENT,"
               "    answer      TEXT,"
               "    id_question INTEGER"
               ")";

    queries << "CREATE TABLE IF NOT EXISTS Comments("
               "    id INTEGER,"
               "    is_positive INTEGER(1),"
               "    comment TEXT"
               ")";

    bool result = true;

    // Execute each query
    foreach (QString query, queries)
    {
        if ( ! this->exec(query))
        {
            result = false;
            break;
        }
    }

    if ( ! result)
        QMessageBox::critical(NULL, QObject::tr("Error during database creation"), _error);
}

//--------------------------------------------------------------------
//        Questions
//--------------------------------------------------------------------
bool Database::insertQuestion(Question *question)
{
    // Insert question
    QVariantList vars;
    vars << question->question() << question->explanation() << question->difficulty() << question->year() << question->nbAnswer() << question->theme();

    if ( ! this->exec("INSERT INTO Questions(question, explanation, difficulty, year, nb_answers, id_theme) VALUES(?, ?, ?, ?, ?, ?)", vars))
        return false;

    // Get question id
    question->set_id(_query->lastInsertId().toInt());

    // Insert answers (first one is the good answer)
    for (int i = 0; i < question->nbAnswer(); i++)
    {
        vars.clear();
        vars << question->answer(i) << question->id();

        if ( ! (this->exec("INSERT INTO Answers(answer, id_question) VALUES(?, ?)", vars)))
             return false;
    }

    return true;
}

QList<Question*> Database::loadQuestions()
{
    QList<Question*> questions;

    // Get questions
    if ( ! this->exec("SELECT q.id, q.question, q.explanation, q.difficulty, q.year, q.nb_answers, q.id_theme, a.answer "
                      "FROM Questions q JOIN Answers a ON a.id_question = q.id "
                      "ORDER BY a.id"))
        return questions;

    QStringList answers;
    int nb_answers_max = 0;

    while (_query->next())
    {
        // New question
        if (nb_answers_max == 0)
        {
            nb_answers_max = _query->value(5).toInt();
            answers.clear();
        }

        // Add current answer to the set
        answers << _query->value(7).toString();

        // All answers are taken, we create the question
        if (answers.size() == nb_answers_max)
        {
            questions << new Question(_query->value(0).toInt(),
                                      _query->value(1).toString(),
                                      answers,
                                      _query->value(2).toString(),
                                      _query->value(3).toInt(),
                                      _query->value(4).toInt(),
                                      _query->value(6).toInt());
            nb_answers_max = 0;
        }
    }

    return questions;
}

bool Database::updateQuestion(Question *question)
{
    return (question != NULL) && this->deleteQuestion(question) && this->insertQuestion(question);
}

bool Database::deleteQuestion(Question *question)
{
    if (question == NULL)
        return false;

    // Create vars list for prepared query
    QVariantList vars;
    vars << question->id();

    // Delete question
    return this->exec("DELETE FROM Questions WHERE id = ?", vars) &&
           this->exec("DELETE FROM Answers WHERE id_question = ?", vars);
}

//--------------------------------------------------------------------
//        Themes
//--------------------------------------------------------------------
bool Database::insertTheme(QString theme)
{
    // Create vars list for prepared query
    QVariantList vars;
    vars << theme;

    // Insert theme
    return this->exec("INSERT INTO Themes(theme) VALUES(?)", vars);
}

QStringList Database::loadThemes()
{
    QStringList themes;

    // Select themes
    if (this->exec("SELECT theme FROM Themes"))
    {
        while (_query->next())
            themes << _query->value(0).toString();
    }

    return themes;
}

bool Database::deleteTheme(QString theme)
{
    if (theme == NULL)
        return false;

    // Create vars list for prepared query
    QVariantList vars;
    vars << theme;

    // Delete theme
    return this->exec("DELETE FROM Theme WHERE theme = ?", vars);
}

//--------------------------------------------------------------------
//        Database
//--------------------------------------------------------------------
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
