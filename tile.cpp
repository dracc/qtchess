#include "tile.h"
#include <QMouseEvent>
#include <iostream>

Tile::Tile(QWidget* parent, int x, int y, bool white, Qt::WindowFlags q)
    : QLabel (parent, q), x(x), y(y)
{
    if (white) {
        setStyleSheet("QLabel {margin: 0px; padding: 0px; background-color: rgb(80, 80, 80); font-size: 48px;}:hover{background-color: rgb(170,85,127);}");
    } else {
        setStyleSheet("QLabel {margin: 0px; padding: 0px; background-color: rgb(245, 245, 245); font-size: 48px;}:hover{background-color: rgb(170,85,127);}");
    }
}


void Tile::setPiece(bool white, char q) {
    p = q;
    w = white;
    if (white) {
        switch (q) {
        case 'p':
            setPixmap(QPixmap(":/pics/pics/wp.png"));
            break;
        case 'r':
            setPixmap(QPixmap(":/pics/pics/wr.png"));
            break;
        case 'h':
            setPixmap(QPixmap(":/pics/pics/wh.png"));
            break;
        case 'b':
            setPixmap(QPixmap(":/pics/pics/wb.png"));
            break;
        case 'q':
            setPixmap(QPixmap(":/pics/pics/wq.png"));
            break;
        case 'k':
            setPixmap(QPixmap(":/pics/pics/wk.png"));
            break;
        default:
            setText("");
        }
    } else {
        switch (q) {
        case 'p':
            setPixmap(QPixmap(":/pics/pics/bp.png"));
            break;
        case 'r':
            setPixmap(QPixmap(":/pics/pics/br.png"));
            break;
        case 'h':
            setPixmap(QPixmap(":/pics/pics/bh.png"));
            break;
        case 'b':
            setPixmap(QPixmap(":/pics/pics/bb.png"));
            break;
        case 'q':
            setPixmap(QPixmap(":/pics/pics/bq.png"));
            break;
        case 'k':
            setPixmap(QPixmap(":/pics/pics/bk.png"));
            break;
        default:
            setText("");
        }
    }
    emit leftClicked();
}

void Tile::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        std::cout << ((p.length()==0)?" ":p.toStdString()) << " " << x << " "
                  << y << std::endl;
        emit leftClicked();
        QLabel::enterEvent(event);
    }
}
