#ifndef BOUFTON_H
#define BOUFTON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include "game.h"


// le bouftou royal tire les bouftons uniquement quand nous sommes dans sa ligne de vue
class Boufton : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Boufton(int direction, Game* param_game);
public slots:
    void move_down();
    void move_up();
    void move_right();
    void move_left();
private:
    Game* game;
};

#endif // ENEMY_BEAM
