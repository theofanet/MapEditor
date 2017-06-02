#ifndef QTILE_H
#define QTILE_H

#include <QLabel>
#include <QImage>
#include <QPixmap>

class QTile : public QLabel{
    Q_OBJECT

public:
    QTile(QImage img, int row, int cell, int spriteIndex = 0, QWidget* parent = 0);
    void mousePressEvent(QMouseEvent* event);

    int getRow(){ return _row; }
    int getCell(){ return _cell; }
    int getTilesetIndex(){ return _spriteIndex; }

    bool isSelected(){ return _selected; }

    QImage getImage(){ return _image; }

public slots:
    void setSelected(bool s = true);

signals:
    void clicked(QTile* tile);

private:
    int _row, _cell;
    QImage _image;
    QPixmap _pix;

    int _spriteIndex;

    bool _selected;
};

#endif // QTILE_H
