#ifndef MODIFYCOMMENTWIDGET_H
#define MODIFYCOMMENTWIDGET_H

#include <QWidget>

class QLineEdit;

class ModifyCommentWidget : public QWidget
{
    Q_OBJECT

    private:
        QLineEdit *_comment;
        bool _is_positive;
        QWidget *_caller;

    public:
        explicit ModifyCommentWidget(bool new_comment, bool is_positive, QWidget *caller);
        ~ModifyCommentWidget();

    private:
        void buildWidget(bool new_comment);

    private slots:
        void save();
};

#endif // MODIFYCOMMENTWIDGET_H
