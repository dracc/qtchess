#ifndef TILE_H
#define TILE_H

#include <QLabel>
#include <QPair>

class Tile : public QLabel
{
    Q_OBJECT
private:
    QString p = "";
    bool w = false;
    int x = 0;
    int y = 0;
signals:
    void leftClicked();
public:
    Tile(QWidget* parent = nullptr, int x=0, int y=0, bool white = false,
         Qt::WindowFlags f = Qt::WindowFlags());
    void setPiece(bool white, char q);
    QString getPiece() {return p;}
    QPair<int,int> getPos() {return {x,y};}
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // TILE_H
