#include "boufton.h"
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

//on crée le boufton dans toutes les directions, bas, haut, droite, et gauche
Boufton::Boufton(int direction, Game* param_game)
{
    game = param_game; // pour avoir acces au perso et au nombre d'ennemi

    //creation du boufton
    if (direction == 1 || direction == 2)
        setPixmap(QPixmap(":/Images/bouftonNoir.png"));
    else
        setPixmap(QPixmap(":/Images/bouftonNoir.png"));

    QTimer* timer = new QTimer;

    //si 1 ennemi vient du haut, donc le boufton va vers le bas
    if (direction == 1){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_down()));
        timer->start(40);
    }
    //si 2 ennemi vient du bas, donc le boufton va vers le haut
    else if (direction == 2){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_up()));
        timer->start(40);
    }

    //si 3 ennemi vient de gauche, donc le boufton va vers la droite
    else if (direction == 3){
        connect(timer, SIGNAL(timeout()), this, SLOT(move_right()));
        timer->start(40);
    }
    // sinon le boufton va vers la gauche
    else {
        connect(timer, SIGNAL(timeout()), this, SLOT(move_left()));
        timer->start(40);
    }
}

// boufton se deplacant en bas, si il touch le joueur, le joueur meurt
void Boufton::move_down(){
    //si le boufton touche, lui et le joueur sont détruit
    //liste de ce que le boufton peut toucher
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
        if (typeid(*(colliding_items[i])) == typeid(Perso) && game->enemy_count != 9000){
            QGraphicsPixmapItem* tombstone = new QGraphicsPixmapItem(QPixmap(":/Images/tombstone.png"));
            tombstone->setPos(colliding_items[i]->x(), colliding_items[i]->y());
            game->player_dead = 1;
            scene()->removeItem(game->perso->shoot_ready);
            scene()->addItem(tombstone);
            scene()->removeItem(colliding_items[i]); //supprime le joueur
            scene()->removeItem(this); //supprime le boufton

            delete this;

            game->game_over();

            return;
        }

    //le boufton va moins vite que le joueur
    setPos(x(), y() + 4);
    //quand il quitte la scène on le détruit
    if (y() > 660){
        scene()->removeItem(this);
        delete this;
    }
}
//même principe que précédement mais ici le boufton va en haut
void Boufton::move_up(){

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

//même principe que précédement mais ici le boufton va à droite
void Boufton::move_right()
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

//même principe que précédement mais ici le boufton va en haut
void Boufton::move_left()
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
