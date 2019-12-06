#include "board.h"
#include <QVector>
#include "tile.h"
#include <iostream>

void Board::selectPiece() {
    Tile* s = static_cast<Tile*>(sender());
    if (selectedPiece != nullptr) {
        Tile* oldTile = board[selectedPiece->first][selectedPiece->second];
        oldTile->clickTile();
        if (*selectedPiece != s->getPos()
                && s->getValid()) {
            char piece = oldTile->getPiece().at(1).toLatin1();
            s->setPiece(oldTile->whitePiece(), piece);
            oldTile->setPiece(false, 'e');
            selectedPiece = new QPair<int,int>{s->getPos()};
            std::cout << " " << static_cast<char>(selectedPiece->second + 65) << (selectedPiece->first - 8) * -1;
        }
        deSelectPiece();
        return;
    }
    if(s->getPiece().length() > 1) {
        s->clickTile();
        validMoves(s->getPiece(), s->getPos());
        selectedPiece = new QPair<int,int>{s->getPos()};
        std::cout << static_cast<char>(selectedPiece->second + 65) << (selectedPiece->first - 8) * -1 << std::flush;
    }
}

void Board::deSelectPiece()
{
    if (selectedPiece != nullptr) {
        std::cout << std::endl;
        free(selectedPiece);
        selectedPiece = nullptr;
    }
    clearMoves();
}

void Board::validMoves(QString const& p, QPair<int, int> pos)
{
    clearMoves();
    int y = pos.first;
    int x = pos.second;
    bool w = board[y][x]->whitePiece();
    const char q = p.at(1).toLatin1();
    int yvector = w?-1:1;

    switch (q) {
    case 'p':
        if (y + yvector > 7
                || y + yvector < 0) {
            break;
        }
        if (board[y+yvector][x]->getPiece().length() < 2) {
            moves.push_back({y+yvector,x});
            if(!w){
                if (y == 1) {
                    if(board[y+2][x]->getPiece().length() < 2) {
                        moves.push_back({y+2,x});
                    }
                }
            } else {
                if (y == 6) {
                    if (board[y-2][x]->getPiece().length() < 2) {
                        moves.push_back({y-2,x});
                    }
                }
            }
        }
        if (x < 7
                && (board[y+yvector][x+1]->getPiece().length() > 1)
                && (board[y+yvector][x+1]->whitePiece() != w)) {
            moves.push_back({y+yvector, x+1});
        }
        if (x > 0
                && (board[y+yvector][x-1]->getPiece().length() > 1)
                && (board[y+yvector][x-1]->whitePiece() != w))
        {
            moves.push_back({y+yvector, x-1});
        }
        break;
    case 'r':
        movesLooper(board[y][x], -1, 0);
        movesLooper(board[y][x], 1, 0);
        movesLooper(board[y][x], 0, -1);
        movesLooper(board[y][x], 0, 1);
        break;
    case 'h':
        moveValid(board[y][x], 2, 1);
        moveValid(board[y][x], -2, 1);
        moveValid(board[y][x], 2, -1);
        moveValid(board[y][x], -2, -1);
        moveValid(board[y][x], 1, 2);
        moveValid(board[y][x], 1, -2);
        moveValid(board[y][x], -1, 2);
        moveValid(board[y][x], -1, -2);
        break;
    case 'b':
        movesLooper(board[y][x], 1, 1);
        movesLooper(board[y][x], 1, -1);
        movesLooper(board[y][x], -1, 1);
        movesLooper(board[y][x], -1, -1);
        break;
    case 'q':
        movesLooper(board[y][x], 1, 1);
        movesLooper(board[y][x], 1, -1);
        movesLooper(board[y][x], -1, 1);
        movesLooper(board[y][x], -1, -1);
        movesLooper(board[y][x], -1, 0);
        movesLooper(board[y][x], 1, 0);
        movesLooper(board[y][x], 0, -1);
        movesLooper(board[y][x], 0, 1);
        break;
    case 'k':
        moveValid(board[y][x], -1, 1);
        moveValid(board[y][x], 1, 1);
        moveValid(board[y][x], 1, -1);
        moveValid(board[y][x], -1, -1);
        moveValid(board[y][x], 0, 1);
        moveValid(board[y][x], 1, 0);
        moveValid(board[y][x], 0, -1);
        moveValid(board[y][x], -1, 0);
        break;
    default:
        break;
    }
    for (auto q: moves) {
        board[q.first][q.second]->setValid(true);
    }
}

void Board::clearMoves()
{
    for (auto q: moves) {
        board[q.first][q.second]->setValid(false);
    }
    moves.clear();
}

void Board::movesLooper(Tile *t, int x, int y)
{
    for (int i = 1; i < 8; ++i) {
        if (!moveValid(t, x*i, y*i)) {
            break;
        }
    }
}

bool Board::moveValid(Tile *t, int x, int y)
{
    int ty = t->getPos().first;
    int tx = t->getPos().second;
    if ((ty + y) > 7
            || (ty + y) < 0
            || (tx + x) > 7
            || (tx + x) < 0) {
        return false;
    }
    if (board[ty + (y)][tx + (x)]->getPiece().length() < 2) {
        moves.push_back({ty + (y), tx + (x)});
    } else if (board[ty + (y)][tx + (x)]->whitePiece() != t->whitePiece()) {
        moves.push_back({ty + (y), tx + (x)});
        return false;
    } else {
        return false;
    }
    return true;
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
            connect(board[i][j], &Tile::rightClicked, this, &Board::deSelectPiece);
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
