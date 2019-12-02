#ifndef BOARD_H
#define BOARD_H

#include <QLayout>
#include <QWidget>
#include <QVector>
#include <QPair>
#include "tile.h"

class Board : public QWidget
{
    Q_OBJECT
private:
    QVector<QVector<Tile*>> board;
    QPair<int, int> *selectedPiece;
    QVector<QPair<int,int>> moves;

    void validMoves(QString const& p, QPair<int,int> pos);
    void clearMoves();
    void movesLooper(Tile* t, int x, int y);
    bool moveValid(Tile* t, int x, int y);
public:
    Board(QLayout* l, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
public slots:
    void selectPiece();
    void deSelectPiece();
};

#endif // BOARD_H
