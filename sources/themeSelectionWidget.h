#ifndef THEMESELECTIONWIDGET_H
#define THEMESELECTIONWIDGET_H

#include <QWidget>
#include <QSignalMapper>

class MainWindow;
class QPushButton;
class QLabel;
class QRadioButton;
class QCheckBox;
class QVBoxLayout;
class Quizz;
class QTextEdit;
class QScrollArea;
class QGridLayout;

class ThemeSelectionWidget : public QWidget
{
  Q_OBJECT
    private:
    // Themes list
    QStringList _themes;

    //Selected theme
    QString _theme;

    // Theme layout
    QVBoxLayout *_theme_layout;
    QGridLayout *_grid_layout;
  
    //Scroll area
    QScrollArea *_scroll_area;

    // Theme labels
    QLabel *_theme_label;

    // Themes radio buttons
    QList<QRadioButton*> _themes_radio_buttons;
    
    //Themes check boxes
    //QList<QCheckBox*> _themes_check_boxes;

    // Control buttons and back button
    QPushButton *_theme_button;
    QPushButton *_next_button;
    QPushButton *_back_button;

    // Mapper to send theme as parameter
    QSignalMapper *_mapper;
    
 public:
    explicit ThemeSelectionWidget(QWidget *parent = 0);
    void launch_quizz();
    ~ThemeSelectionWidget();

 private : 
    void buildWidget(MainWindow *main_window);


 signals:
    void choiceDone();
    private slots:
    void showTheme(QStringList themes);
    void theme();
    
};

#endif // THEMESELECTIONWIDGET_H
