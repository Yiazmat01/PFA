#include "qsfmlcanvas.h"
#include <SFML/Window.hpp>
QSFMLCanvas::QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime) :
QWidget       (Parent),
myInitialized (false)
{
    //divers flags de rendu dans le widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // pour que le  widget capte les évènements clavier
    setFocusPolicy(Qt::StrongFocus);

    // Placer le widget
     move(Position);
     resize(Size);

     // Préparation du timer
     myTimer.setInterval(FrameTime);
}

#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif
void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!myInitialized)
    {
        // Sous X11, il faut valider les commandes qui ont été envoyées au serveur
        // afin de s'assurer que SFML aura une vision à jour de la fenêtre
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        // On crée la fenêtre SFML avec l'identificateur du widget
        sf::Window::create((HWND)QWidget::winId(), getSettings());

        // Pour initialiser la classe dérivée
        OnInit();

        // On paramètre le timer de sorte qu'il génère un rafraîchissement à la fréquence souhaitée
        connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        myTimer.start();

        myInitialized = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
    // On update la classe dérivée
    OnUpdate();

    // On rafraîchit le widget
    sf::Window::display();
}

