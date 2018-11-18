#include "powerups.h"
#include "QGraphicsPixmapItem"
#include "game.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>


//creation du power up vitesse avec le dofawa
SpeedUp::SpeedUp(Game* game_arg)
{
    has_died = 0;

    game = game_arg;
    game->speed_out = 1;
    setPixmap(QPixmap(":/Images/Dofawa.png"));
    setPos(rand() % (570 - 130) + 130, rand() % (520 - 80) + 80);

    QTimer* duration = new QTimer;
    connect(duration, SIGNAL(timeout()), this, SLOT(begone()));
    duration->start(4000);

    QTimer* check_life_timer = new QTimer;
    connect(check_life_timer, SIGNAL(timeout()), this, SLOT(check_player()));

    check_life_timer->start(1);

}

//timer pour enlever le dofawa
void SpeedUp::begone()
{
    if (has_died)
        game->speed_out = 0;
    game->powerup_speed_timer->start(20000);
    scene()->removeItem(this);
    delete this;

}

//check si le joueur est mort
void SpeedUp::check_player()
{
    if (game->player_dead)
        has_died = 1;
}

// creation du power up enlevant le coldown des tir, le dofus turquoise
Burst::Burst(Game* game_arg)
{
    game = game_arg;
    game->burst_out = 1;
    setPixmap(QPixmap(":/Images/turquoise.png"));
    setPos(rand() % (570 - 130) + 130, rand() % (520 - 80) + 80);
    QTimer* duration = new QTimer;
    connect(duration, SIGNAL(timeout()), this, SLOT(begone()));
    duration->start(2000);

    QTimer* check_life_timer = new QTimer;
    connect(check_life_timer, SIGNAL(timeout()), this, SLOT(check_player()));
    check_life_timer->start(1);
}

//enlever le dofus turquoise au bou d'un certain temps
void Burst::begone()
{
    if (!has_died)
        game->burst_out = 0;
    game->powerup_burst_timer->start(20000);
    scene()->removeItem(this);
    delete this;
}


//check si joueur mort
void Burst::check_player()
{
    if (game->player_dead)
        has_died = 1;
}
