#ifndef MAPTILE_H
#define MAPTILE_H

#include <vector>

#include "Utilities/defines.h"
#include "Render/sprite.h"

class MapTile{
public:
    MapTile(Sprite *tileset, int index = 0);

    void setTileRow(int r){ _tileRow = r; }
    void setTileCell(int c){ _tileCell = c; }
    int  getTileRow(){ return _tileRow; }
    int  getTileCell(){ return _tileCell; }

    void setPosition(b2Vec2 pos){ _position = pos; _basePosition = pos; }
    void setPosition(GLfloat x, GLfloat y){ setPosition(b2Vec2(x, y)); }
    b2Vec2 getPosition(){ return _position; }
    b2Vec2 getBasePosition(){ return _basePosition; }

    void setSelected(bool s = true, int mode = 0){ _selected = s; _selectionMode = mode; }

    void setCursorPosition(b2Vec2 mousePosition);
    void cursorClicked(b2Vec2 mousePosition, bool pressed);
    bool onPoint(){ return (int)_tilePointOn != -1; }
    bool IsConvex();

    vector<b2Vec2> getPoints(){ return _points; }
    void setPoints(vector<b2Vec2> pts){ _points = pts; }
    void addPoint(GLfloat x, GLfloat y){ _points.push_back(b2Vec2(x, y)); }
    void clearPoints(){ _points.clear(); }

    void draw();
    void update();

    void setDestructible(bool d){ _isDestructible = d; }
    bool isDestructible(){ return _isDestructible; }

    void setClimbable(bool c){ _isClimbable = c; }
    bool isClimbable(){ return _isClimbable; }

    void setSlippery(bool s){ _isSlippery = s; }
    bool isSlippery(){ return _isSlippery; }

    void setDeadly(bool d){ _isDeadly = d; }
    bool isDeadly(){ return _isDeadly; }

    void setHorizontalMove(bool move, GLfloat speed = 0.0f, GLfloat max = 0.0f);
    bool getHorizontalMove(){ return _horizontalMove; }
    GLfloat getHorizontalMoveSpeed(){ return _horizontalMoveSpeed; }
    GLfloat getHorizontalMoveMax(){ return _horizontalMoveMax; }

    size_t getTilesetIndex(){ return _index; }

private:
    Sprite *_tileSet;
    int     _tileRow, _tileCell;
    b2Vec2  _position, _basePosition;

    size_t _index;

    bool _selected, _draggingPoint;

    size_t _tilePointOn;
    int _selectionMode;

    bool _isDestructible, _isClimbable, _isSlippery, _isDeadly;

    bool _horizontalMove;
    GLfloat _horizontalMoveSpeed, _horizontalMoveMax;

    vector<b2Vec2> _points;
};

#endif // MAPTILE_H
