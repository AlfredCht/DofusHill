#include "game.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QButtonGroup>
#include "perso.h"
#include "bouftouroyal.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QApplication>
#include <QDesktopWidget>
#include "powerups.h"
#include "croca.h"

//on crée le jeu, menu principal, écran de jeu, menu défaite et menu victoire
Game::Game(QWidget*)
{
    //Titre du jeu
    QLabel* heading = new QLabel("<h1>Dofus Hill</h1>");
    heading->setAlignment(Qt::AlignCenter);

    //instructions
    QLabel* pick_char = new QLabel("<h2>Choisissez votre personnage :</h2>");
    pick_char->setAlignment(Qt::AlignCenter);

    //Image des perso
    QLabel* cra_label = new QLabel;
    QString fileName(":/Images/crasel.png");
    QPixmap* cra_image = new QPixmap(fileName);
    cra_label->setPixmap(*cra_image);
    QLabel* iop_label = new QLabel;
    fileName = ":/Images/iopselec.png";
    QPixmap* iop_image = new QPixmap(fileName);
    iop_label->setPixmap(*iop_image);
    QLabel* sacri_label = new QLabel;
    fileName = ":/Images/sacriselec.png";
    QPixmap* sacri_image = new QPixmap(fileName);
    sacri_label->setPixmap(*sacri_image);
    QHBoxLayout* char_images = new QHBoxLayout;
    char_images->addWidget(cra_label);
    char_images->addWidget(iop_label);
    char_images->addWidget(sacri_label);
    char_images->setAlignment(Qt::AlignCenter);

    //Boutons de selection
    QRadioButton* cra_button = new QRadioButton("Cra");
    QRadioButton* iop_button = new QRadioButton("Iop");
    QRadioButton* sacri_button = new QRadioButton("Sacrieur");
    QHBoxLayout* char_buttons = new QHBoxLayout;
    char_buttons->addWidget(cra_button);
    char_buttons->addWidget(iop_button);
    char_buttons->addWidget(sacri_button);
    char_buttons->setAlignment(Qt::AlignCenter);
    QButtonGroup* char_select = new QButtonGroup;
    char_select->addButton(cra_button);
    char_select->addButton(iop_button);
    char_select->addButton(sacri_button);

    //Selection de la difficulté
    QLabel* choose_difficulty = new QLabel("<h2>Choisissez la difficulté :</h2>");
    choose_difficulty->setAlignment(Qt::AlignCenter);

    //Bouton de selection
    QRadioButton* easy = new QRadioButton("Facile");
    QRadioButton* medium = new QRadioButton("Moyen");
    QRadioButton* hard = new QRadioButton("Difficile");
    QVBoxLayout* difficulties = new QVBoxLayout;
    difficulties->addWidget(easy);
    difficulties->addWidget(medium);
    difficulties->addWidget(hard);
    difficulties->setAlignment(Qt::AlignCenter);
    QButtonGroup* difficulty_select = new QButtonGroup;
    difficulty_select->addButton(easy);
    difficulty_select->addButton(medium);
    difficulty_select->addButton(hard);

    //bouton d'instructions
    QPushButton* instructions = new QPushButton("Comment jouer ?");
    QApplication::connect(instructions, SIGNAL(clicked()), this, SLOT(show_instructions()));

    //Bouton pour commencer à jouer
    QPushButton* battle = new QPushButton("Jouez");

    //On organise les éléments verticalement
    QVBoxLayout* vlay = new QVBoxLayout;
    vlay->addWidget(heading);
    vlay->addWidget(pick_char);
    vlay->addLayout(char_images);
    vlay->addLayout(char_buttons);
    vlay->addWidget(choose_difficulty);
    vlay->addLayout(difficulties);
    vlay->addWidget(instructions);
    vlay->addWidget(battle);

    //Set les éléments
    this->setLayout(vlay);

    //set les perso
    QObject::connect(cra_button, SIGNAL(clicked()), this, SLOT(cra_set()));
    QObject::connect(iop_button, SIGNAL(clicked()), this, SLOT(iop_set()));
    QObject::connect(sacri_button, SIGNAL(clicked()), this, SLOT(sacri_set()));
    character = 1; //default

    //set la difficulté
    QObject::connect(easy, SIGNAL(clicked()), this, SLOT(easy_set()));
    QObject::connect(medium, SIGNAL(clicked()), this, SLOT(medium_set()));
    QObject::connect(hard, SIGNAL(clicked()), this, SLOT(hard_set()));
    difficulty = 1;
    wave_count = 0;
    enemy_count = 1;

    //on initialise les timer des power up pour pas en avoir plein sur l'ecran
    speed_out = 0;
    burst_out = 0;
    check_powerups_timer = new QTimer;
    connect(check_powerups_timer, SIGNAL(timeout()), this, SLOT(check_powerups()));
    powerup_speed_timer = new QTimer;

    connect (powerup_speed_timer, SIGNAL(timeout()), this, SLOT(spawn_speed_powerup()));
    powerup_burst_timer = new QTimer;
    connect (powerup_burst_timer, SIGNAL(timeout()), this, SLOT(spawn_burst_powerup()));

    //quand on clique sur jouer le menu est caché et l'ecran de jeu apparait
    //on cache juste le menu, on ne le detruit pas
    QApplication::connect(battle, SIGNAL(clicked()), this, SLOT(hide()));
    QApplication::connect(battle, SIGNAL(clicked()), this, SLOT(start_battle()));
}

//on reset les parametre du jeu quand la partie est finie
void Game::game_over()
{
    check_powerups_timer->stop();
    powerup_burst_timer->stop();
    powerup_speed_timer->stop();
    speed_out = 0;
    burst_out = 0;

    wave_count = 0;
    if (difficulty == 1)
        enemy_count = 1;
    else if (difficulty == 2)
        enemy_count = 2;
    else if (difficulty == 3)
        enemy_count = 4;

    QWidget* game_over_menu = new QWidget;

    QLabel* you_lose = new QLabel("<h1> Vous êtes mort </h1>");
    you_lose->setAlignment(Qt::AlignCenter);
    QPushButton* restart = new QPushButton("Jouer encore une fois");
    QPushButton* change_options = new QPushButton("Revenir au menu de selection");
    QPushButton* quit = new QPushButton("Partir misérablement");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(you_lose);
    layout->addWidget(restart);
    layout->addWidget(change_options);
    layout->addWidget(quit);

    game_over_menu->setLayout(layout);
    game_over_menu->show();

    connect(restart, SIGNAL(clicked()), view, SLOT(close()));
    connect(restart, SIGNAL(clicked()), game_over_menu, SLOT(close()));
    connect(restart, SIGNAL(clicked()), this, SLOT(start_battle()));

    connect(change_options, SIGNAL(clicked()), view, SLOT(close()));
    connect(change_options, SIGNAL(clicked()), game_over_menu, SLOT(close()));
    connect(change_options, SIGNAL(clicked()), this, SLOT(show()));

    connect(quit, SIGNAL(clicked()), view, SLOT(close()));
    connect(quit, SIGNAL(clicked()), game_over_menu, SLOT(close()));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
}

//liste des instructions
void Game::show_instructions()
{
    QWidget* instruction_window = new QWidget;
    QLabel* instructions1 = new QLabel("<h3> Ramassez les items pour ramener des alliés à votre troupe !</h3>");
    QLabel* instructions2 = new QLabel("<h3>Tuez la vague de Bouftou Royal puis la vague de Crocabulia !</h3>");
    instructions2->setAlignment(Qt::AlignCenter);
    QLabel* instructions3 = new QLabel("<h3> Appuyez sur espace pour tirer !</h3>");
    instructions3->setAlignment(Qt::AlignCenter);
    QLabel* instructions4 = new QLabel("<h3> Vos alliés vous donnent des pouvoirs !</h3>");
    instructions4->setAlignment(Qt::AlignCenter);
    QPushButton* close = new QPushButton("Fermer");

    QVBoxLayout* vlayout = new QVBoxLayout;
    vlayout->addWidget(instructions1);
    vlayout->addWidget(instructions2);
    vlayout->addWidget(instructions3);
    vlayout->addWidget(instructions4);
    vlayout->addWidget(close);
    instruction_window->setLayout(vlayout);
    instruction_window->show();

    QApplication::connect(close, SIGNAL(clicked()), instruction_window, SLOT(close()));
}

//check le nombre d'ennmi et la vague pour faire apparaitre les ennemis et l'ecran de fin correctement connecté au timer
void Game::new_wave_or_win()
{
    if (wave_count == 1 && enemy_count == 0){
        perso->left = false;
        perso->right = false;
        perso->up = false;
        perso->down = false;

        QLabel* winner_label = new QLabel;
        QPixmap* face = new QPixmap(":/Images/dofusocre.png");
        if (character == 1){
            delete face;
            face = new QPixmap(":/Images/dofusocre.png");
        }
        else if (character == 2){
            delete face;
            face = new QPixmap(":/Images/dofusocre.png");
        }
        else if (character == 3){
            delete face;
            face = new QPixmap(":/Images/dofusocre.png");
        }
        winner_label->setPixmap(*face);
        QLabel* you_win = new QLabel("<h1>Victoire</h1>");
        you_win->setAlignment(Qt::AlignCenter);
        QPushButton* close = new QPushButton("A+");

        QVBoxLayout* vlayout = new QVBoxLayout;
        vlayout->addWidget(winner_label);
        vlayout->addWidget(you_win);
        vlayout->addWidget(close);

        QWidget* win_window = new QWidget;
        win_window->setLayout(vlayout);
        win_window->show();

        connect(close, SIGNAL(clicked()), view, SLOT(close()));
        connect(close, SIGNAL(clicked()), win_window, SLOT(close()));

        //avec ca, la fonction ne crée pas des écran en masse
        enemy_count = 10000;
    }
    if (enemy_count == 0 && wave_count == 0){
        ++wave_count;
        XCroca* bottom_enemy1 = new XCroca(perso, 590, this);
        scene->addItem(bottom_enemy1);

        if (difficulty >= 1){
            for (int i = 0; i < wave_count; ++i){

            }
            enemy_count = 1;
        }
        if (difficulty >= 2){
            YCroca* left_enemy1 = new YCroca(perso, 60, this);
            scene->addItem(left_enemy1);

            enemy_count = 2;
        }
        if (difficulty == 3){
            YCroca* right_enemy1 = new YCroca(perso, 655, this);
            scene->addItem(right_enemy1);
            XCroca* another_right_enemy = new XCroca(perso, -10, this);
            scene->addItem(another_right_enemy);
            enemy_count = 4;
        }
    }
}


void Game::cra_set()
{
    character = 1;
}


void Game::iop_set()
{
    character = 2;
}


void Game::sacri_set()
{
    character = 3;
}


void Game::easy_set()
{
    difficulty = 1;
    enemy_count = 1;
}


void Game::medium_set()
{
    difficulty = 2;
    enemy_count = 2;
}


void Game::hard_set()
{
    difficulty = 3;
    enemy_count = 4;
}


void Game::start_battle()
{
    view = new QGraphicsView;
    //creation de la scene
    scene = new QGraphicsScene;
    //set la scene
    view->setScene(scene);

    QGraphicsPixmapItem* shoot_indicator = new QGraphicsPixmapItem(QPixmap (":/Images/fourmiorptitrien.png"));
    scene->addItem(shoot_indicator);

    //on fait passer l'indicateur de cooldown dans le joueur

    perso = new Perso(character, shoot_indicator);
    scene->addItem(perso);
    player_dead = 0;
    perso->setFlag(QGraphicsItem::ItemIsFocusable);
    perso->setFocus();

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->setFixedSize(657, 670);
    scene->setSceneRect(56, 0, 657, 670);

    //map du jeu
    scene->setBackgroundBrush(QBrush(QImage(":/Images/mapdofus.png")));

    //spawn du bouftou royal
    XBouftouroyal* top_enemy1 = new XBouftouroyal(perso, -10, this);
    scene->addItem(top_enemy1);
    if (difficulty == 2){
        YBouftouroyal* left_enemy1 = new YBouftouroyal(perso, 60, this);
        scene->addItem(left_enemy1);
    }
    if (difficulty == 3){
        YBouftouroyal* left_enemy1 = new YBouftouroyal(perso, 60, this);
        scene->addItem(left_enemy1);
        YBouftouroyal* right_enemy1 = new YBouftouroyal(perso, 655, this);
        scene->addItem(right_enemy1);
        XBouftouroyal* bottom_enemy1 = new XBouftouroyal(perso, 590, this);
        scene->addItem(bottom_enemy1);
     }

    QTimer* check_enemynwave = new QTimer;
    connect(check_enemynwave, SIGNAL(timeout()), this, SLOT(new_wave_or_win()));
    check_enemynwave->start(1000);

    powerup_speed_timer->start(2000);
    powerup_burst_timer->start(10000);
    check_powerups_timer->start(5);

    view->show();
}

void Game::check_powerups()
{
    if (speed_out == 1){
        powerup_speed_timer->stop();
    }
    if (burst_out == 1){
        powerup_burst_timer->stop();
    }
}

//spawm du power up vitesse = dofawa
void Game::spawn_speed_powerup()
{
    powerup_speed_timer->stop();
    SpeedUp* speedup = new SpeedUp(this);
    scene->addItem(speedup);

}

//spawm du power up tir = dofus turquoise
void Game::spawn_burst_powerup()
{
    powerup_burst_timer->stop();
    Burst* burst = new Burst(this);
    scene->addItem(burst);
}
