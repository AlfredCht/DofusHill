#include "croca.h"
#include <QTimer>
#include <QGraphicsScene>
#include "bouledefeu.h"
#include <cmath>
#include "perso.h"
#include "game.h"
#include "tir.h"
#include<typeinfo>

//Ennemi de la vague 2, le Crocabulia, même principe que le bouftou royal on change juste sa vitesse
XCroca::XCroca(Perso* perso, int y_coor, Game* param_game){
    target = perso;
    game = param_game;

    QTimer* coor_timer = new QTimer;
    connect(coor_timer, SIGNAL(timeout()), this, SLOT(set_coor()));
    coor_timer->start(40);

    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(randomize()));
    timer->start((rand() % 3001) + 2000);

    setPos((rand() % 557) + 100, y_coor);

    direction = rand() % 2;
//Cette fois il va plus vite
    speed = (rand() % 3) + 4;

    setPixmap(QPixmap(":/Images/croca.png"));

    QTimer* moving_timer = new QTimer;
    connect(moving_timer, SIGNAL(timeout()), this, SLOT(move_and_shoot()));
    moving_timer->start(40);
}


void XCroca::set_coor(){
    target_x = target->x() + 10;
    target_y = target->y();
}


void XCroca::randomize()
{

    if (rand() % 2 == 0)
        direction = (direction + 1) % 2;
}


void XCroca::move_and_shoot()
{

    if (y() == -10) move_and_shoot_down();
    else move_and_shoot_up();
}


void XCroca::move_and_shoot_down()
{

    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
        if (typeid(*(colliding_items[i])) == typeid(Tir)){
            --game->enemy_count;
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }

    if (abs(x()-target_x) <= 8){
        Bouledefeu* beam2 = new Bouledefeu(1, game);
        beam2->setPos(x() + 10, y());
        scene()->addItem(beam2);
    }

    if (direction == 1)
        setPos(x() + speed, y());
        if (x() > 615)
            direction = 0;
    if (direction == 0)
        setPos(x() - speed, y());
        if (x() < 100)
            direction = 1;
}


void XCroca::move_and_shoot_up()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
        if (typeid(*(colliding_items[i])) == typeid(Tir)){
            --game->enemy_count;
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }

    if (abs(x()-target_x) <= 8){
        Bouledefeu* beam2 = new Bouledefeu(2, game);
        beam2->setPos(x() + 10, y() + 20);
        scene()->addItem(beam2);
    }

    if (direction == 1)
        setPos(x() + speed, y());
        if (x() > 615)
            direction = 0;
    if (direction == 0)
        setPos(x() - speed, y());
        if (x() < 100)
            direction = 1;
}


YCroca::YCroca(Perso* perso, int x_coor, Game* param_game){

    target = perso;
    game = param_game;

    QTimer* coor_timer = new QTimer;
    connect(coor_timer, SIGNAL(timeout()), this, SLOT(set_coor()));
    coor_timer->start(40);

    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(randomize()));
    timer->start((rand() % 3001) + 2000);

    setPos(x_coor, (rand() % 390) + 150);

    direction = rand() % 2;

    speed = (rand() % 3) + 3;

    setPixmap(QPixmap(":/Images/croca.png"));

    QTimer* moving_timer = new QTimer;
    connect(moving_timer, SIGNAL(timeout()), this, SLOT(move_and_shoot()));
    moving_timer->start(40);
}


void YCroca::set_coor(){
    target_x = target->x();
    target_y = target->y();
}


void YCroca::randomize()
{
    if (rand() % 2 == 0)
        direction = (direction + 1) % 2;
}

void YCroca::move_and_shoot()
{
    if (x() == 60) move_and_shoot_right();
    else move_and_shoot_left();
}


void YCroca::move_and_shoot_right()
{

    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
        if (typeid(*(colliding_items[i])) == typeid(Tir)){
            --game->enemy_count;
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }

    if (abs(y()-target_y) <= 8){
        Bouledefeu* beam2 = new Bouledefeu(3, game);
        beam2->setPos(x(), y() + 20);
        scene()->addItem(beam2);
    }

    if (direction == 1)
        setPos(x(), y() - speed);
        if (y() < 40)
            direction = 0;
    if (direction == 0)
        setPos(x(), y() + speed);
        if (y() > 530)
            direction = 1;
}


void YCroca::move_and_shoot_left()
{

    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
        if (typeid(*(colliding_items[i])) == typeid(Tir)){
            --game->enemy_count;
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            delete colliding_items[i];
            delete this;
            return;
        }

    if (abs(y()-target_y) <= 8){
        Bouledefeu* beam2 = new Bouledefeu(4, game);
        beam2->setPos(x(), y() + 20);
        scene()->addItem(beam2);
    }

    if (direction == 1)
        setPos(x(), y() - speed);
        if (y() < 40)
            direction = 0;
    if (direction == 0)
        setPos(x(), y() + speed);
        if (y() > 530)
            direction = 1;
}

