#ifndef TIR_H
#define TIR_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

//on tir quand on appuye sur espace
class Tir : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Tir(int value);
    int direction;
public slots:
    void move();
};

#endif // Tir
