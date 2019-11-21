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
public:
    Board(QLayout* l, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
public slots:
    void selectPiece();
};

#endif // BOARD_H
