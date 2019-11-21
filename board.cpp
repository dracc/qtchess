#include "board.h"
#include <QVector>
#include "tile.h"
#include <iostream>

void Board::selectPiece() {
    if (selectedPiece != nullptr) {
        if (*selectedPiece == static_cast<Tile*>(sender())->getPos()) {
            std::cout << std::endl;
            free(selectedPiece);
            selectedPiece = nullptr;
            return;
        } else {
            selectedPiece = new QPair<int,int>{static_cast<Tile*>(sender())->getPos()};
            std::cout << " " << static_cast<char>(selectedPiece->second + 65) << (selectedPiece->first - 8) * -1 << std::endl;
            free(selectedPiece);
            selectedPiece = nullptr;
            return;
        }
    }
    selectedPiece = new QPair<int,int>{static_cast<Tile*>(sender())->getPos()};
    std::cout << static_cast<char>(selectedPiece->second + 65) << (selectedPiece->first - 8) * -1 << std::flush;
}

Board::Board(QLayout* l, QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f), selectedPiece(nullptr)
{
    board = QVector<QVector<Tile*>>(8);
    bool white = true;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j) {
            board[i].push_back(new Tile(this, i, j, white = !white));
            static_cast<QGridLayout*>(l)->addWidget(board[i][j], i, j);
            connect(board[i][j], &Tile::leftClicked, this, &Board::selectPiece);
        }
        white = !white;
    }

    // Place pieces
    QVector<char> pieces{'r','h','b','q','k','b','h','r'};
    for (int i = 0; i < 8; ++i) {
        board[0][i]->setPiece(false, pieces[i]);
        board[1][i]->setPiece(false, 'p');
        board[6][i]->setPiece(true, 'p');
        board[7][i]->setPiece(true, pieces[i]);
    }
}
