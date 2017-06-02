#include "qtile.h"

QTile::QTile(QImage img, int row, int cell, int spriteIndex, QWidget* parent) : QLabel(parent){
    _row = row;
    _cell = cell;
    _image = img;
    _spriteIndex = spriteIndex;

    _pix = QPixmap::fromImage(_image);
    setPixmap(_pix.scaled(60, 60, Qt::KeepAspectRatio));
    setFixedSize(70, 70);
    setMargin(5);
}

void QTile::mousePressEvent(QMouseEvent*){
    setSelected();
    emit clicked(this);
}

void QTile::setSelected(bool s){
    _selected = s;
    if(_selected)
        setStyleSheet("border: 2px solid");
    else
        setStyleSheet("border: none;");
}
