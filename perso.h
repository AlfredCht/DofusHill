#ifndef PERSO_H
#define PERSO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>


//On fait bouger le personnage
class Perso : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);
    Perso(int value, QGraphicsPixmapItem* shoot_indicator);
    int character;
    QTimer* shoot_timer;
    QGraphicsPixmapItem* shoot_ready;
    bool shoot_cooldown;
    bool left;
    bool right;
    bool up;
    bool down;
    bool space;
    void shoot(int value);
    int speed;
    bool burst_fire;
public slots:
    void shoot_cooled_down();
    void check_keys();
    void indicator_follow();
};



#endif // PLAYER
