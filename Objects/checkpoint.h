#ifndef CHECKPOIN_H
#define CHECKPOIN_H


#include <QWidget>

#include <stdio.h>
#include <string>

#include "Utilities/defines.h"
#include "Render/sprite.h"

class Checkpoint{
public:
    Checkpoint();
    ~Checkpoint();

    void draw();
    void setPosition(b2Vec2 pos){ _position = pos; }
    void setPosition(GLfloat x, GLfloat y){ setPosition(b2Vec2(x, y)); }
    b2Vec2 getPosition(){ return _position; }

protected:
    Image *_img;
    b2Vec2 _position;
};

#endif // CHECKPOIN_H
