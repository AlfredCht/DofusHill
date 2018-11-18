#ifndef CROCA_H
#define CROCA_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include "perso.h"
#include "game.h"

//on fait bouger le crocabulia
class XCroca : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    XCroca(Perso* perso, int y_coor, Game* param_game);
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

/**
 * @brief Enemy that only changes on y-coordinates (left and right)
 */
class YCroca : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    YCroca(Perso* perso, int x_coor, Game* param_game);
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

#endif // Croca
