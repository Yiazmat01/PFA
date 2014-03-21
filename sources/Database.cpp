#include "Database.h"
#include "quizz/Question.hpp"

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
               "    id          INTEGER PRIMARY KEY AUTOINCREMENT,"
               "    is_positive INTEGER(1),"
               "    comment     TEXT"
               ")";

    bool result = true;

    // Execute each query
    foreach (QString query, queries)
    {
        if ( ! this->exec(query))
        {
            this->clear();
            result = false;
            break;
        }
        this->clear();
    }

    if ( ! result)
        QMessageBox::critical(NULL, QObject::tr("Error during database creation"), _error);
}

//--------------------------------------------------------------------
//        Questions
//--------------------------------------------------------------------
void Database::insertQuestion(Question *question)
{
    // Insert question
    QVariantList vars;
    vars << question->question() << question->explanation() << question->difficulty() << question->year() << question->nbAnswer() << question->theme();

    if ( ! this->exec("INSERT INTO Questions(question, explanation, difficulty, year, nb_answers, id_theme) VALUES(?, ?, ?, ?, ?, ?)", vars))
    {
        this->clear();
        return ;
    }

    // Get question id
    question->set_id(_query->lastInsertId().toInt());
    this->clear();

    // Insert answers (first one is the good answer)
    for (int i = 0; i < question->nbAnswer(); i++)
    {
        vars.clear();
        vars << question->answer(i) << question->id();

        if ( ! (this->exec("INSERT INTO Answers(answer, id_question) VALUES(?, ?)", vars)))
        {
            this->clear();
            return;
        }
        this->clear();
    }
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
    this->clear();
    return questions;
}

void Database::updateQuestion(Question *question)
{
    if (question != NULL)
    {
        this->deleteQuestion(question);
        this->insertQuestion(question);
    }
}

void Database::deleteQuestion(Question *question)
{
    if (question == NULL)
        return;

    // Create vars list for prepared query
    QVariantList vars;
    vars << question->id();

    // Delete question
    this->exec("DELETE FROM Questions WHERE id = ?", vars);
    this->clear();
    this->exec("DELETE FROM Answers WHERE id_question = ?", vars);
    this->clear();
}

//--------------------------------------------------------------------
//        Themes
//--------------------------------------------------------------------
int Database::theme_id(QString theme)
{
    // Create vars list for prepared query
    QVariantList vars;
    vars << theme;
    int theme_id = 0;

    // Select themes
    if (this->exec("SELECT id FROM Themes WHERE theme = ?", vars))
    {
        _query->next();
        theme_id = _query->value(0).toInt();
    }

    this->clear();
    return theme_id;
}

void Database::insertTheme(QString theme)
{
    // Create vars list for prepared query
    QVariantList vars;
    vars << theme;

    // Insert theme
    this->exec("INSERT INTO Themes(theme) VALUES(?)", vars);
    this->clear();
}

void Database::updateTheme(int theme_id, QString theme)
{
    // Create vars list for prepared query
    QVariantList vars;
    vars << theme << theme_id;

    // Update theme
    this->exec("UPDATE Themes SET theme = ? WHERE id = ?", vars);
    this->clear();
}

QStringList Database::loadThemes()
{
    QStringList themes;

    // Select themes
    if (this->exec("SELECT theme FROM Themes ORDER BY theme"))
    {
        while (_query->next())
            themes << _query->value(0).toString();
    }
    this->clear();
    return themes;
}

void Database::deleteTheme(QString theme)
{
    if (theme == NULL)
        return;

    // Create vars list for prepared query
    QVariantList vars;
    vars << theme;

    // Delete theme
    this->exec("DELETE FROM Themes WHERE theme = ?", vars);
    this->clear();

}

//--------------------------------------------------------------------
//        Comments
//--------------------------------------------------------------------
int Database::comment_id(bool positive, QString comment)
{
    // Create vars list for prepared query
    QVariantList vars;
    vars << positive << comment;
    int comment_id = 0;

    // Select comment
    if (this->exec("SELECT id FROM Comments WHERE is_positive = ? AND comment = ?", vars))
    {
        _query->next();
        comment_id = _query->value(0).toInt();
    }

    this->clear();
    return comment_id;
}

void Database::insertComment(QString comment, bool is_positive)
{
    // Create vars list for prepared query
    QVariantList vars;
    vars << comment << is_positive;

    // Insert comment
    this->exec("INSERT INTO Comments(comment, is_positive) VALUES(?, ?)", vars);
    this->clear();
}

QStringList Database::loadComments(bool positive)
{
    // Create vars list for prepared query
    QVariantList vars;
    vars << positive;

    QStringList comments;

    // Select themes
    if (this->exec("SELECT comment FROM Comments WHERE is_positive = ? ORDER BY comment", vars))
    {
        while (_query->next())
            comments << _query->value(0).toString();
    }

    this->clear();
    return comments;
}

void Database::updateComment(int comment_id, bool positive, QString comment)
{
    // Create vars list for prepared query
    QVariantList vars;
    vars << comment << positive << comment_id;

    // Update theme
    this->exec("UPDATE Comments SET comment = ? WHERE is_positive = ? AND id = ?", vars);
    this->clear();
}

void Database::deleteComment(QString comment)
{
    if (comment == NULL)
        return ;

    // Create vars list for prepared query
    QVariantList vars;
    vars << comment;

    // Delete comment
    this->exec("DELETE FROM Comments WHERE comment = ?", vars);
    this->clear();
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
