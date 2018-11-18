#include "perso.h"
#include <QKeyEvent>
#include "tir.h"
#include <QGraphicsScene>
#include "stdlib.h"
#include <QPixmap>
#include "bouftouroyal.h"
#include <QTimer>
#include "boufton.h"
#include <QList>
#include "powerups.h"
#include<typeinfo>


Perso::Perso(int value, QGraphicsPixmapItem* shoot_indicator)
{
    character = value;
    shoot_cooldown = true;
    left = false;
    right = false;
    up = false;
    down = false;
    space = false;

    shoot_ready = shoot_indicator;

    speed = 6;
    burst_fire = 0;

    if (character == 2){
        setPixmap(QPixmap(":/Images/iopjeu.png"));
        //spawn pour iop
        this->setPos(360, 270);
    }

    else if (character == 3){
        //spawn pour sacrieur
            setPixmap(QPixmap(":/Images/sacrijeu.png"));
            this->setPos(360, 270);
   }

    else {
        setPixmap(QPixmap(":/Images/crajeu.png"));
        //spawn pour cra
        this->setPos(360, 270);
    }


    QTimer* indicator_follow = new QTimer;
    connect(indicator_follow, SIGNAL(timeout()), this, SLOT(indicator_follow()));
    indicator_follow->start(10);


    QTimer* smooth_timer = new QTimer;
    connect(smooth_timer, SIGNAL(timeout()), this, SLOT(check_keys()));
    smooth_timer->start(45);

    //2 sec apres avoir tirer le joueur peut tirer à nouveau
    shoot_timer = new QTimer;
    connect(shoot_timer, SIGNAL(timeout()), this, SLOT(shoot_cooled_down()));

}

//definit les evenements a faire quand on appuye sur different bouton
void Perso::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        left = true;
    }
    else if (event->key() == Qt::Key_Right){
        right = true;
    }
    else if (event->key() == Qt::Key_Up){
        up = true;
    }
    else if (event->key() == Qt::Key_Down){
        down = true;
    }
    else if (event->key() == Qt::Key_Space){
        space = true;
    }
}

//definit les evenements a faire quand on relache different bouton
void Perso::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        left = false;
    }
    else if (event->key() == Qt::Key_Right){
        right = false;
    }
    else if (event->key() == Qt::Key_Up){
        up = false;
    }
    else if (event->key() == Qt::Key_Down){
        down = false;
    }
    else if (event->key() == Qt::Key_Space){
        space = false;
    }
}

//autorise le joueur à tirer
void Perso::shoot_cooled_down()
{
    shoot_timer->stop();
    shoot_cooldown = true;
}


//check les bouton pressé et les collisions avec les dofus
void Perso::check_keys()
{
    //si le joueur passe sur dofus il obtient le power up
    //de plus des qu'on prend un dofus on invoque un dopeul à nos côté
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
        if ((typeid(*(colliding_items[i])) == typeid(SpeedUp)  )&& character ==1 ){
            speed = 12;

            setPixmap(QPixmap(":/Images/crajeudeux.png"));
            setPos(x(), y());

        }
        else if ((typeid(*(colliding_items[i]) ) == typeid(Burst)) && character ==1){
            burst_fire = true;
            shoot_cooldown = true;
            setPixmap(QPixmap(":/Images/crajeutrois.png"));
            setPos(x(), y());

        }
        else if((typeid(*(colliding_items[i])) == typeid(SpeedUp) ) && character ==2){
            speed = 12;
            setPixmap(QPixmap(":/Images/iopjeudeux.png"));
            setPos(x(), y());

        }
        else if ((typeid(*(colliding_items[i]) ) == typeid(Burst))&& character ==2){
            burst_fire = true;
            shoot_cooldown = true;
            setPixmap(QPixmap(":/Images/iopjeutrois.png"));
            setPos(x(), y());

        }
        else if((typeid(*(colliding_items[i])) == typeid(SpeedUp) ) && character ==3){ //if type of colliding_items[i] is Player
            speed = 12;
            setPixmap(QPixmap(":/Images/sacrijeudeux.png"));
            setPos(x(), y());

        }
        else if ((typeid(*(colliding_items[i]) ) == typeid(Burst))&& character ==3){
            burst_fire = true;
            shoot_cooldown = true;
            setPixmap(QPixmap(":/Images/sacrijeutrois.png"));
            setPos(x(), y());

        }

    if (character == 1){
//mouvement haut gauche
    if (left && up){
        if (x() > 111 && y() > 70)
            setPos(x() - speed, y() - speed);
    }
//mouvement haut droite
    else if (right && up){
        if (x() < 592 && y() > 70)
            setPos(x() + speed, y() - speed);
    }
//mouvemant bas gauche
    else if (left && down){
        if (x() > 111 && y() < 510)
            setPos(x() - speed, y() + speed);
    }
//mouvement bas droit
    else if (right & down){
        if (x() < 592 && y() < 510)
            setPos(x() + speed, y() + speed);
    }
    //autorise a bouger a gauche tant qu'on atteint pas la limite gauche
    else if (left){
        if (x() > 111)
            setPos(x() - speed, y());
    }
    //autorise a bouger a droite tant qu'on atteint pas la limite droite
    else if (right){
        if (x() < 592)
            setPos(x() + speed, y());
    }
    //autorise a bouger en haut tant qu'on atteint pas la limite haute
    else if (up){
        if (y() > 70)
            setPos(x(), y() - speed);
    }
    //autorise a bouger en bas tant qu'on atteint pas la limite basse
    else if (down){
        if (y() < 510)
            setPos(x(), y() + speed);
    }
    }

    else if (character == 2 || character == 3){
        //mouvement haut gauche
        if (left && up){
            if (x() > 120 && y() > 70)
                setPos(x() - speed, y() - speed);
        }
        //mouvement haut droite
        else if (right && up){
            if (x() < 606 && y() > 70)
                setPos(x() + speed, y() - speed);
        }
        //mouvement bas gauche
        else if (left && down){
            if (x() > 120 && y() < 520)
                setPos(x() - speed, y() + speed);
        }
        //mouvement bas droite
        else if (right & down){
            if (x() < 606 && y() < 520)
                setPos(x() + speed, y() + speed);
        }
        //même principe que precedement coordonnées differentes pour mieux adapter les positions adapté a nos images
        else if (left){
            if (x() > 120)
                setPos(x() - speed, y());
        }
        else if (right){
            if (x() < 606)
                setPos(x() + speed, y());
        }
        else if (up){
            if (y() > 70)
                setPos(x(), y() - speed);
        }
        else if (down){
            if (y() < 520)
                setPos(x(), y() + speed);
        }
    }



    if (up && space)
        shoot(1);
    else if (down && space)
        shoot(2);
    else if (left && space)
        shoot(3);
    else if (right && space)
        shoot(4);
}

// indique le tir cd
void Perso::indicator_follow()
{
    if (character == 1){
        if (shoot_cooldown == true)
            shoot_ready->setPos(x() - 12, y() + 29);

    }
    else if (character == 2){
        if (shoot_cooldown == true)
            shoot_ready->setPos(x() - 25, y() + 29);

    }
    else if (character == 3){
        if (shoot_cooldown == true)
            shoot_ready->setPos(x() - 25, y() + 29);

    }
}


void Perso::shoot(int value)
{
    //creation du tir centrer sur le joueur
    if (shoot_cooldown == true){
        Tir* tir = new Tir(value);
        if (character == 1){
            if (value == 1)
                tir->setPos(x() + 23, y() - 50);
            else if (value == 2)
                tir->setPos(x() + 23, y() + 75);
            else if (value == 3)
                tir->setPos(x() - 40, y() + 30);
            else if (value == 4)
                tir->setPos(x() + 53, y() + 30);
        }
        else if (character == 2 || character == 3){
            if (value == 1)
                tir->setPos(x() + 6, y() - 58);
            else if (value == 2)
                tir->setPos(x() + 6, y() + 83);
            else if (value == 3)
                tir->setPos(x() - 60, y() + 30);
            else if (value == 4)
                tir->setPos(x() + 40, y() + 30);
        }

        scene()->addItem(tir);
        if (!burst_fire){
        shoot_cooldown = false;
        shoot_ready->setPos(0, -200);
        shoot_timer->start(2000);
        }
    }
}
