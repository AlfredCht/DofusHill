#include "bouftouroyal.h"
#include <QTimer>
#include <QGraphicsScene>
#include "boufton.h"
#include <cmath>
#include "perso.h"
#include "game.h"
#include "tir.h"
#include<typeinfo>


//Ennemi de la vague 1, le bouftou royal
XBouftouroyal::XBouftouroyal(Perso* perso, int y_coor, Game* param_game){

    target = perso; //accede au joueur
    game = param_game;//accede au nombre d'ennemi

    //on stock les coordonnées du joueur
    QTimer* coor_timer = new QTimer;
    connect(coor_timer, SIGNAL(timeout()), this, SLOT(set_coor()));
    coor_timer->start(40);

    //toute le 2 à 5 sec, le boufton change de direction de facon random
    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(randomize()));
    timer->start((rand() % 3001) + 2000);

    //set une position random sur le bord
    setPos((rand() % 557) + 100, y_coor);

    //on determine une direction random dans laquelle le bouftou royalva partir
    direction = rand() % 2;

    //on determine la vitesse du bouftou royal
    speed = (rand() % 3) + 3;

    //image du bouftou royal
    setPixmap(QPixmap(":/Images/bouftouroyal.png"));

    QTimer* moving_timer = new QTimer;
    connect(moving_timer, SIGNAL(timeout()), this, SLOT(move_and_shoot()));
    moving_timer->start(40);
}

//coordonnée
void XBouftouroyal::set_coor(){
    target_x = target->x() + 10;
    target_y = target->y();
}

//direction
void XBouftouroyal::randomize()
{
    if (rand() % 2 == 0)
        direction = (direction + 1) % 2;
}

void XBouftouroyal::move_and_shoot()
{
    //depending on the edge enemy is on, they will shoot in a certain direction
    if (y() == -10) move_and_shoot_down();
    else move_and_shoot_up();
}

void XBouftouroyal::move_and_shoot_down()
{
    //Si on touche le bouftou royal avec un tir, on supprime le bouftou et le tir
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
        if (typeid(*(colliding_items[i])) == typeid(Tir)){
            --game->enemy_count;
            scene()->removeItem(colliding_items[i]); //supprime le tir
            scene()->removeItem(this); //supprime le bouftou royal

            delete colliding_items[i];
            delete this;

            return;
        }


    if (abs(x()-target_x) <= 8){

        Boufton* beam = new Boufton(1, game);
        beam->setPos(x() + 10, y());
        scene()->addItem(beam);
    }

    //tant que le br n'atteint pas la limite à gauche, le bouftou royal va a droite
    if (direction == 1)
        setPos(x() + speed, y());
        if (x() > 615)
            direction = 0;
    //tant que le br n'atteint pas la limite à droite, le bouftou royal va a gauche
    if (direction == 0)
        setPos(x() - speed, y());
        if (x() < 100)
            direction = 1;
}

//même principe qu'avant
void XBouftouroyal::move_and_shoot_up()
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
        Boufton* beam = new Boufton(2, game);
        beam->setPos(x() + 10, y() + 20);
        scene()->addItem(beam);
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


YBouftouroyal::YBouftouroyal(Perso* perso, int x_coor, Game* param_game){
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

    setPixmap(QPixmap(":/Images/bouftouroyal.png"));

    QTimer* moving_timer = new QTimer;
    connect(moving_timer, SIGNAL(timeout()), this, SLOT(move_and_shoot()));
    moving_timer->start(40);
}

void YBouftouroyal::set_coor(){
    target_x = target->x();
    target_y = target->y();
}


void YBouftouroyal::randomize()
{
    if (rand() % 2 == 0)
        direction = (direction + 1) % 2;
}


void YBouftouroyal::move_and_shoot()
{
    if (x() == 60) move_and_shoot_right();
    else move_and_shoot_left();
}


void YBouftouroyal::move_and_shoot_right()
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
        Boufton* beam = new Boufton(3, game);
        beam->setPos(x(), y() + 20);
        scene()->addItem(beam);
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


void YBouftouroyal::move_and_shoot_left()
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
        Boufton* beam = new Boufton(4, game);
        beam->setPos(x(), y() + 20);
        scene()->addItem(beam);
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
