#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "perso.h"

// contient le menu principal, la carte de jeu, le menu de défaite et de victoire
class Game : public QWidget {
    Q_OBJECT
public:
    Game(QWidget* parent=0);
    int enemy_count;
    int wave_count;
    int character;
    int difficulty;
    QGraphicsView* view;
    QGraphicsScene* scene;
    void game_over();
    Perso* perso;
    bool speed_out;
    bool burst_out;
    QTimer* check_powerups_timer;
    QTimer* powerup_speed_timer;
    QTimer* powerup_burst_timer;
    bool player_dead;
public slots:
    void iop_set();
    void cra_set();
    void sacri_set();
    void easy_set();
    void medium_set();
    void hard_set();
    void start_battle();
    void show_instructions();
    void new_wave_or_win();
    void check_powerups();
    void spawn_speed_powerup();
    void spawn_burst_powerup();
};

#endif // MAINMENU
