#include "tile.h"
#include <QMouseEvent>
#include <iostream>

Tile::Tile(QWidget* parent, int x, int y, bool white, Qt::WindowFlags q)
    : QLabel (parent, q), wT(white), x(x), y(y)
{
    setColor();
}


void Tile::setPiece(bool white, char q) {
    p = q;
    wP = white;
    QString colorIdentifier = wP?"w":"b";
    switch (q) {
    case 'p':
        setPixmap(QPixmap(":/pics/pics/" + colorIdentifier + "p.png"));
        break;
    case 'r':
        setPixmap(QPixmap(":/pics/pics/" + colorIdentifier + "r.png"));
        break;
    case 'h':
        setPixmap(QPixmap(":/pics/pics/" + colorIdentifier + "h.png"));
        break;
    case 'b':
        setPixmap(QPixmap(":/pics/pics/" + colorIdentifier + "b.png"));
        break;
    case 'q':
        setPixmap(QPixmap(":/pics/pics/" + colorIdentifier + "q.png"));
        break;
    case 'k':
        setPixmap(QPixmap(":/pics/pics/" + colorIdentifier + "k.png"));
        break;
    default:
        p = "";
        setPixmap(QPixmap(""));
    }
}

void Tile::clickTile()
{
    selected = !selected;
    setColor();
}

void Tile::setValid(bool val)
{
    validMove = val;
    setColor();
}

void Tile::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit leftClicked();
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked();
    }
    QLabel::enterEvent(event);
}

void Tile::setColor()
{
    if (selected) {
        setStyleSheet("QLabel {margin: 0px; padding: 0px; background-color: rgb(245, 245, 80); font-size: 48px;}:hover{background-color: rgb(245,245,127);}");
    } else if (validMove) {
        setStyleSheet("QLabel {margin: 0px; padding: 0px; background-color: rgb(170, 245, 170); font-size: 48px;}:hover{background-color: rgb(127,245,127);}");
    }else if (wT) {
        setStyleSheet("QLabel {margin: 0px; padding: 0px; background-color: rgb(80, 80, 80); font-size: 48px;}:hover{background-color: rgb(170,85,127);}");
    } else {
        setStyleSheet("QLabel {margin: 0px; padding: 0px; background-color: rgb(245, 245, 245); font-size: 48px;}:hover{background-color: rgb(170,85,127);}");
    }
}
