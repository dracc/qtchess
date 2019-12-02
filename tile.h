#ifndef TILE_H
#define TILE_H

#include <QLabel>
#include <QPair>

class Tile : public QLabel
{
    Q_OBJECT
private:
    QString p = "";
    bool wP = false;
    bool wT = false;
    bool selected = false;
    bool validMove = false;
    int x = 0;
    int y = 0;
signals:
    void leftClicked();
    void rightClicked();
public:
    Tile(QWidget* parent = nullptr, int x=0, int y=0, bool white = false,
         Qt::WindowFlags f = Qt::WindowFlags());
    void setPiece(bool white, char q);
    QString getPiece() {return (wP?"w":"b") + p;}
    bool whitePiece() {return wP;}
    QPair<int,int> getPos() {return {x,y};}
    void clickTile();
    void setValid(bool val);
    bool getValid() {return validMove;}
protected:
    void mousePressEvent(QMouseEvent* event);
    void setColor();
};

#endif // TILE_H
