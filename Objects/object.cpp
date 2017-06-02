#include "object.h"

Object::Object(string name, b2Vec2 pos){
    _position  = pos;

    _name = name;

    _mouseOver = false;
    _selected  = false;

    _dim       = b2Vec2(2.0f, 2.0f);

    _selectionColor[0] = 0.9f;
    _selectionColor[1] = 0.9f;
    _selectionColor[2] = 0.0f;

    _type = OBJECT_TYPE_NONE;
}

Object::~Object(){
    removed.trigger(this);
}

void Object::handleCmd(string, bool){

}

void Object::draw(){
    if(_mouseOver || _selected){
        BBox rect = getRectBox();

        glPushMatrix();
        glLineWidth(5.0);
        glColor4f(_selectionColor[0], _selectionColor[1], _selectionColor[2], 1.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(rect.x[0], rect.y[0]);
        glVertex2f(rect.x[1], rect.y[1]);
        glVertex2f(rect.x[2], rect.y[2]);
        glVertex2f(rect.x[3], rect.y[3]);
        glEnd();
        glLineWidth(1.0);
        glPopMatrix();
    }
}

BBox Object::getRectBox(){
    Rect rect;

    rect.min.x = -_dim.x / 2.0f;
    rect.min.y = -_dim.y / 2.0f;
    rect.max.x = _dim.x / 2.0f;
    rect.max.y = _dim.y / 2.0f;

    rect.min += _position;
    rect.max += _position;

    BBox box;

    box.x[0] = rect.min.x;
    box.y[0] = rect.min.y;
    box.x[1] = rect.min.x;
    box.y[1] = rect.max.y;
    box.x[2] = rect.max.x;
    box.y[2] = rect.max.y;
    box.x[3] = rect.max.x;
    box.y[3] = rect.min.y;

    return box;
}

void Object::update(GLfloat){
}

bool Object::checkIfMouseOver(b2Vec2 point){
    BBox box = getRectBox();
    int i, j, c = 0;
    for (i = 0, j = 3; i < 4; j = i++) {
      if ( ((box.y[i]>point.y) != (box.y[j]>point.y)) &&
       (point.x < (box.x[j]-box.x[i]) * (point.y-box.y[i]) / (box.y[j]-box.y[i]) + box.x[i]) )
         c = !c;
    }

    _mouseOver = c;
    return c;
}
