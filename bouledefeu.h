#ifndef BOULEDEFEU_H
#define BOULEDEFEU_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include "game.h"

// le crocabulia tire les boules de feu uniquement quand nous sommes dans sa ligne de vue
class Bouledefeu : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bouledefeu(int direction, Game* param_game);
public slots:
    void move_down();
    void move_up();
    void move_right();
    void move_left();
private:
    Game* game;
};

#endif // ENEMY_BEAM2
