#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QWidget>
#include <SFML/Graphics.hpp>
#include <QTimer>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
public:

    QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);
    /*constructeur pour les proprietes des widgets. Le dernier parametres sert a rafraichir la fenetre*/

    virtual ~QSFMLCanvas() = 0;

private:

       virtual void OnInit() = 0;

       virtual void OnUpdate() = 0;

       virtual QPaintEngine* paintEngine() const;

       virtual void showEvent(QShowEvent*);//pour definir la fenetre sfml

       virtual void paintEvent(QPaintEvent*);//pour rafraichir la fenetre sfml

       QTimer myTimer;
       bool   myInitialized;

signals:

public slots:

};

#endif // QSFMLCANVAS_H
