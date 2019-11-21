#include "board.h"
#include <QVector>
#include "tile.h"
#include <iostream>

void Board::selectPiece() {
    auto p = static_cast<Tile*>(sender())->getPos();
    std::cout << "CLICK " << p.first << p.second << std::endl;
}

Board::Board(QLayout* l, QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    board = QVector<QVector<Tile*>>(8);
    bool white = true;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j) {
            board[i].push_back(new Tile(this, i, j, white = !white));
            static_cast<QGridLayout*>(l)->addWidget(board[i][j], i, j);
            if(!static_cast<bool>(connect(board[i][j], &Tile::leftClicked, this, &Board::selectPiece))) {
                std::cout << "Connection failed!" << std::endl;
            }
        }
        white = !white;
    }

    // Black pieces
    board[0][0]->setPiece(false, 'r');
    board[0][1]->setPiece(false, 'h');
    board[0][2]->setPiece(false, 'b');
    board[0][3]->setPiece(false, 'q');
    board[0][4]->setPiece(false, 'k');
    board[0][5]->setPiece(false, 'b');
    board[0][6]->setPiece(false, 'h');
    board[0][7]->setPiece(false, 'r');
    for (auto &q: board[1]) {
        q->setPiece(false, 'p');
    }
    // White pieces
    for (auto &q: board[6]) {
        q->setPiece(true, 'p');
    }
    board[7][0]->setPiece(true, 'r');
    board[7][1]->setPiece(true, 'h');
    board[7][2]->setPiece(true, 'b');
    board[7][3]->setPiece(true, 'q');
    board[7][4]->setPiece(true, 'k');
    board[7][5]->setPiece(true, 'b');
    board[7][6]->setPiece(true, 'h');
    board[7][7]->setPiece(true, 'r');
}
