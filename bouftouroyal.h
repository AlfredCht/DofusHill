#ifndef BOUFTOUROYAL_H
#define BOUFTOUROYAL_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include "perso.h"
#include "game.h"

// on fait bouger le bouftou royal
class XBouftouroyal : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    XBouftouroyal(Perso* perso, int y_coor, Game* param_game);
    void move_and_shoot_down();
    void move_and_shoot_up();
public slots:
    void set_coor();
    void randomize();
    void move_and_shoot();
private:
    bool direction;
    int speed;
    Perso* target;
    int target_x;
    int target_y;
    Game* game;
};

class YBouftouroyal : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    YBouftouroyal(Perso* perso, int x_coor, Game* param_game);
    void move_and_shoot_right();
    void move_and_shoot_left();
public slots:
    void set_coor();
    void randomize();
    void move_and_shoot();
private:
    bool direction;
    int speed;
    Perso* target;
    int target_x;
    int target_y;
    Game* game;
};

#endif // ENEMY
