#include "tir.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "bouftouroyal.h"

//creation des tir dans toute les directions, 1 si haut 2 si bas 3 si gauche 4 si droite
Tir::Tir(int value){

    direction = value;

    if (value == 1 || value == 2)
        setPixmap(QPixmap(":/Images/up_down3.png"));
    else if (value == 3 || value == 4)
        setPixmap(QPixmap(":/Images/left_right3.png"));

    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(40);
}

//faire bouger les tir selon les directions
void Tir::move()
{
    if (direction == 1){
        //bouge le tir en haut
        setPos(x(), y() - 6);
        //quand le tir quitte la scene il est detruit
        if (y() < -50){
            scene()->removeItem(this);
            delete this;
        }
    }
    else if (direction == 2){
 //meme principe en bas
        setPos(x(), y() + 6);
        if (y() > 660){
            scene()->removeItem(this);
            delete this;
        }
    }
    else if (direction == 3){
        //meme principe a gauche
        setPos(x() - 6, y());
        if (x() < 0){
            scene()->removeItem(this);
            delete this;
        }
    }
    else if (direction == 4){
        //meme principe a droite
        setPos(x() + 6, y());
        if (x() > 670){
            scene()->removeItem(this);
            delete this;
        }
    }
}
