#ifndef POWERUPS_H
#define POWERUPS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include "game.h"
#include <QTimer>

//on augente la vitesse quand on prend le dofawa
class SpeedUp : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    SpeedUp(Game* game_arg);
    Game* game;
    bool has_died;

public slots:
    void begone();
    void check_player();
};

//on augmente la cadence de tir quand on prend le dofus turquoise
class Burst : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Burst(Game* game_arg);
    Game* game;
    bool has_died;
public slots:
    void begone();
    void check_player();

};

#endif // POWERUPS
