#ifndef TILEOPTIONWIDGET_H
#define TILEOPTIONWIDGET_H

#include <stdio.h>
#include <stdlib.h>

#include <QWidget>
#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <string>

#include <vector>

#include <iostream>

#include "Utilities/defines.h"
#include "maptile.h"

using namespace std;

class TileOptionWidget : public QWidget{
Q_OBJECT
public:
    TileOptionWidget(QWidget *parent = 0);

    void setSelectedObjects(vector<MapTile*> tiles);
    void update();

    void clearTiles(){ _tiles.clear(); update(); }

private slots:
    void setDestructibleData(bool d);
    void setClimbableData(bool c);
    void setSlipperyData(bool s);
    void setDeadlyData(bool d);
    void setHorizontalMoveData(bool h = true);

private:
    QCheckBox *_destructible, *_climbable, *_slippery, *_deadly;

    QCheckBox *_horizontalMove;
    QLineEdit *_horizontalMoveSpeed, *_horizontalMoveMax;

    QLabel *_labelNbSelected, *_labelMultipleValue;

    vector<MapTile *> _tiles;
};

#endif // TILEOPTIONWIDGET_H
