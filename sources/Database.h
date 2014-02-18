/**
 * Class to manage database
 *
 * @date April 2011
 * @author Jean-Luc Migot (jean-luc.migot@filmskollection.org)
 *
 *
 * Copyright (C) 2011 Jean-Luc Migot
 *
 * This file is part of FilmsKollection.
 *
 * FilmsKollection is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FilmsKollection is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QSqlDatabase>
#include <QVariant>
#include "Quizz/Question.hpp"

using namespace musik;

class Film;
class Utils;

class Database
{
    private:
        Utils*        _utils;
        QSqlDatabase  _db;
        QSqlQuery*    _query;
        QString       _error;

    public:
        //Database(Utils *utils);
        Database();
        ~Database();

        bool       compact();
        bool       create();

        // Get
        QString error()  const;
        QString dbname() const;

        // Set
        void setDatabaseName(const QString &name);
        bool insertQuestion(musik::Question *question);
        bool insertTheme(QString theme);
        QList<Question*> loadQuestions();
        QList<QString> loadTheme();
        bool updateQuestion(Question * question);
        bool deleteQuestion(Question * question);
        bool deleteTheme(QString theme);
        int theme2id(QString theme);
    private:
        bool open();
        bool exec(const QString &query);
        bool exec(const QString &query, const QVariantList &vars);
        void clear();
        int findGoodAnswerPos(const QList<int>& idListAnswer, const int & id_good_answer);
};

#endif
