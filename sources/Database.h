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

#include <QSqlDatabase>
#include <QVariant>
#include "Quizz/Question.hpp"

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
        Database();
        ~Database();

        // Questions
        bool insertQuestion(Question *question);
        QList<Question*> loadQuestions();
        bool updateQuestion(Question * question);
        bool deleteQuestion(Question * question);

        // Themes
        bool insertTheme(QString theme);
        QStringList loadThemes();
        bool deleteTheme(QString theme);

    private:
        // Database
        void create();
        bool open();
        bool exec(const QString &query);
        bool exec(const QString &query, const QVariantList &vars);
        void clear();
};

#endif
