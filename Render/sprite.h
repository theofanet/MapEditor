#ifndef SPRITE_H
#define SPRITE_H

#include <QWidget>
#include "image.h"
#include "animation.h"

class Sprite{
public:
    Sprite(QString filename, GLfloat w, GLfloat h);
    ~Sprite();

    void setScale(GLfloat s){ _scale = s; }
    void setRotation(GLfloat r){ _rotate = r; }
    void setRow(int row);
    void setCell(int cell);
    void setDrawSize(b2Vec2 s){ _drawSize = s; }
    void setDrawSize(GLfloat x, GLfloat y){ setDrawSize(b2Vec2(x, y)); }

    Image*  getImage(){ return _image; }
    GLfloat getScale(){ return _scale; }
    GLfloat getRotation(){ return _rotate; }
    GLfloat getRowWidth(){ return _width; }
    GLfloat getRowHeight(){ return _height; }
    QImage  getQImageTile(int cell, int row);
    int     getNbCell(){ return _nbCell; }
    int     getNbRow(){ return _nbRow; }
    int     getNbTiles(){ return _nbTiles; }
    int     getRow(){ return _row; }
    int     getCell(){ return _cell; }

    bool hasAnimation(string key);
    void removeAnimation(string key);
    void addAnimation(string key, AnimationAbstract *anim);
    void setAnimation(AnimationAbstract *anim);
    void activateAnimation(string key, bool reset = true);
    AnimationAbstract *animation();
    AnimationAbstract *getAnimation(string key);

    void draw(GLfloat x, GLfloat y, bool flip = false);
    void update();

private:
    Image *_image;

    int _row, _cell;

    GLfloat _width, _height;
    GLfloat _scale, _rotate;

    int _nbRow, _nbCell, _nbTiles;

    b2Vec2  _drawSize;

    AnimationAbstract                   *_animation;
    map<std::string, AnimationAbstract*> _animations;
};

#endif // SPRITE_H
