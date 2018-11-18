#include "bouledefeu.h"
#include <QTimer>
#include <QGraphicsScene>
#include "perso.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "game.h"
#include <QObject>
#include <QApplication>
#include <QList>
#include <QGraphicsPixmapItem>
#include<typeinfo>

//on crée la boule de feu dans toutes les directions, bas, haut, droite, et gauche, même principe que boufton
Bouledefeu::Bouledefeu(int direction, Game* param_game)
{
    game = param_game;

    //image de la boule de feu
    if (direction == 1 || direction == 2)
        setPixmap(QPixmap(":/Images/feu.png"));
    else
        setPixmap(QPixmap(":/Images/feu.png"));

    QTimer* timer = new QTimer;

    if (direction == 1){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_down()));
        timer->start(40);
    }
    else if (direction == 2){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_up()));
        timer->start(40);
    }

    else if (direction == 3){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_right()));
        timer->start(40);
    }

    else {
        connect(timer, SIGNAL(timeout()), this, SLOT(move_left()));
        timer->start(40);
    }
}

void Bouledefeu::move_down(){

    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
        if (typeid(*(colliding_items[i])) == typeid(Perso) && game->enemy_count != 9000){
            QGraphicsPixmapItem* tombstone = new QGraphicsPixmapItem(QPixmap(":/Images/tombstone.png"));
            tombstone->setPos(colliding_items[i]->x(), colliding_items[i]->y());
            game->player_dead = 1;
            scene()->removeItem(game->perso->shoot_ready);
            scene()->addItem(tombstone);
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete this;

            game->game_over();

            return;
        }

    setPos(x(), y() + 4);
    if (y() > 660){
        scene()->removeItem(this);
        delete this;
    }
}


void Bouledefeu::move_up(){

    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
        if (typeid(*(colliding_items[i])) == typeid(Perso) && game->enemy_count != 9000){
            QGraphicsPixmapItem* tombstone = new QGraphicsPixmapItem(QPixmap("C:/Images/tombstone.png"));
            tombstone->setPos(colliding_items[i]->x(), colliding_items[i]->y());
            game->player_dead = 1;
            scene()->removeItem(game->perso->shoot_ready);
            scene()->addItem(tombstone);
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete this;

            game->game_over();

            return;
        }
    setPos(x(), y() - 4);
    if (y() < -50){
        scene()->removeItem(this);
        delete this;
    }
}


void Bouledefeu::move_right()
{

    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
        if (typeid(*(colliding_items[i])) == typeid(Perso) && game->enemy_count != 9000){
            QGraphicsPixmapItem* tombstone = new QGraphicsPixmapItem(QPixmap(":/Images/tombstone.png"));
            tombstone->setPos(colliding_items[i]->x(), colliding_items[i]->y());
            game->player_dead = 1;
            scene()->removeItem(game->perso->shoot_ready);
            scene()->addItem(tombstone);
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete this;

            game->game_over();

            return;
        }
    setPos(x() + 4, y());
    if (x() > 670){
        scene()->removeItem(this);
        delete this;
    }
}


void Bouledefeu::move_left()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
        if (typeid(*(colliding_items[i])) == typeid(Perso) && game->enemy_count != 9000){
            QGraphicsPixmapItem* tombstone = new QGraphicsPixmapItem(QPixmap(":/Images/tombstone.png"));
            tombstone->setPos(colliding_items[i]->x(), colliding_items[i]->y());
            game->player_dead = 1;
            scene()->removeItem(game->perso->shoot_ready);
            scene()->addItem(tombstone);
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete this;

            game->game_over();

            return;
        }
    setPos(x() - 4, y());
    if (x() < 0){
        scene()->removeItem(this);
        delete this;
    }
}
