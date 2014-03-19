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
#include "quizz/Question.hpp"

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
        void insertQuestion(Question *question);
        QList<Question*> loadQuestions();
        void updateQuestion(Question * question);
        void deleteQuestion(Question * question);

        // Themes
        int theme_id(QString theme);
        void insertTheme(QString theme);
        QStringList loadThemes();
        void deleteTheme(QString theme);

        // Comments
        void insertComment(QString comment, bool is_positive);
        QStringList loadComments(bool positive);
        void deleteComment(QString comment);

    private:
        // Database
        void create();
        bool open();
        bool exec(const QString &query);
        bool exec(const QString &query, const QVariantList &vars);
        void clear();
};

#endif
