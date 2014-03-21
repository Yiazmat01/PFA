#ifndef MODIFYCOMMENTWIDGET_H
#define MODIFYCOMMENTWIDGET_H

#include <QWidget>

class QLineEdit;

class ModifyCommentWidget : public QWidget
{
    Q_OBJECT

    private:
        bool _new_comment;
        int _comment_id;
        QLineEdit *_comment;
        bool _is_positive;
        QWidget *_caller;


    public:
        explicit ModifyCommentWidget(bool new_comment, bool is_positive, QString comment, QWidget *caller);
        ~ModifyCommentWidget();

    private:
        void buildWidget(QString comment);

    private slots:
        void save();
};

#endif // MODIFYCOMMENTWIDGET_H
