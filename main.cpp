#include <QApplication>
#include "perso.h"
#include "game.h"
#include <ctime>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //initalise rand pour que chaque spawn d'ennemi soit différent à chaque lancement du jeu
    srand(time(NULL));

    //creation du menu de jeu et affichage
    Game* game = new Game;
    game->show();

    return a.exec();
}
