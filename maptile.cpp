#include "maptile.h"

MapTile::MapTile(Sprite *tileset, int index){
    _tileSet = tileset;
    _selected = false;

    _index = index;

    _tilePointOn = -1;

    _draggingPoint  = false;
    _selectionMode  = 0;
    _isDestructible = false;
    _isClimbable    = false;
    _isSlippery     = false;
    _horizontalMove = false;
    _isDeadly       = false;

    _horizontalMoveMax = 0.0f;
    _horizontalMoveSpeed = 0.0f;

    _basePosition = b2Vec2();

    _points.push_back(b2Vec2(-1.0, -1.0));
    _points.push_back(b2Vec2(-1.0, 1.0));
    _points.push_back(b2Vec2(1.0, 1.0));
    _points.push_back(b2Vec2(1.0, -1.0));
}

void MapTile::draw(){
    _tileSet->setRow(_tileRow);
    _tileSet->setCell(_tileCell);
    _tileSet->draw(_position.x, _position.y);

    if(_selected){
        glPushMatrix();

        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glTranslatef(_position.x, _position.y, 0);

        glColor4f(1, 1, 1, 0.3);

        if(_selectionMode == 0){
            glBegin(GL_QUADS);
            for(size_t i = 0; i < _points.size(); i++)
                glVertex2f(_points.at(i).x, _points.at(i).y);
            glEnd();

            glDisable(GL_BLEND);

            //POints
            const float32 k_segments = 16.0f;
            const float32 k_increment = 2.0f * b2_pi / k_segments;
            float32 theta = 0.0f;
            for(size_t i = 0; i < _points.size(); i++){
                glColor4f(1.0, 1.0, 0.0, 1.0f);
                if(_tilePointOn == i)
                    glColor4f(1.0, 0.0, 0.0, 1.0f);

                glBegin(GL_TRIANGLE_FAN);
                for (int32 j = 0; j < k_segments; ++j){
                    b2Vec2 v = _points.at(i) + 0.1 * b2Vec2(cosf(theta), sinf(theta));
                    glVertex2f(v.x, v.y);
                    theta += k_increment;
                }
                glEnd();
            }
        }
        else{
            glBegin(GL_QUADS);
            glVertex2f(-1.0, -1.0);
            glVertex2f(-1.0, 1.0);
            glVertex2f(1.0, 1.0);
            glVertex2f(1.0, -1.0);
            glEnd();

        }

        glPopMatrix();
    }
}

void MapTile::setCursorPosition(b2Vec2 mousePosition){
    if(_selected){
        if(!_draggingPoint){
            _tilePointOn = -1;
            for(size_t i = 0; i < _points.size(); i++){
                b2Vec2 pts = _points.at(i);
                pts += _position;

                if(mousePosition.x > pts.x - 0.1 && mousePosition.x < pts.x + 0.1
                   && mousePosition.y < pts.y + 0.1 && mousePosition.y > pts.y - 0.1)
                    _tilePointOn = i;
            }
        }
        else{
            b2Vec2 pos = mousePosition - _position;
            b2Vec2 oldPos = _points.at(_tilePointOn);

            if(pos.x > 1)
                pos.x = 1;
            else if(pos.x < -1)
                pos.x = -1;

            if(pos.y > 1)
                pos.y = 1;
            else if(pos.y < -1)
                pos.y = -1;

            _points.at(_tilePointOn) = pos;
            if(!IsConvex())
                _points.at(_tilePointOn) = oldPos;
        }
    }
}

void MapTile::cursorClicked(b2Vec2, bool pressed){
    if(pressed){
        if(_tilePointOn != (size_t)-1)
            _draggingPoint = true;
    }
    else{
        _draggingPoint = false;
    }
}

bool MapTile::IsConvex() {
    bool isPositive = false;
    for (size_t i = 0; i < _points.size(); ++i) {
        size_t lower = (i == 0) ? (_points.size() - 1) : (i - 1);
        size_t middle = i;
        size_t upper = (i == _points.size() - 1) ? (0) : (i + 1);
        float32 dx0 = _points.at(middle).x - _points.at(lower).x;
        float32 dy0 = _points.at(middle).y - _points.at(lower).y;
        float32 dx1 = _points.at(upper).x - _points.at(middle).x;
        float32 dy1 = _points.at(upper).y - _points.at(middle).y;
        float32 cross = dx0 * dy1 - dx1 * dy0;
        // Cross product should have same sign
        // for each vertex if poly is convex.
        bool newIsP = (cross >= 0) ? true : false;
        if (i == 0) {
            isPositive = newIsP;
        }
        else if (isPositive != newIsP) {
            return false;
        }
    }
    return true;
}

void MapTile::setHorizontalMove(bool move, GLfloat speed, GLfloat max){
    _horizontalMove = move;

    if(_horizontalMove){
        _horizontalMoveSpeed = speed;
        _horizontalMoveMax   = max;
    }
    else{
        _horizontalMoveSpeed = 0.0f;
        _horizontalMoveMax   = 0.0f;
        _position            = _basePosition;
    }
}

void MapTile::update(){
    if(_horizontalMove){
        _position.x += _horizontalMoveSpeed / 10;

        if(_horizontalMoveSpeed > 0 && (_position.x - _basePosition.x) > _horizontalMoveMax)
            _horizontalMoveSpeed = -_horizontalMoveSpeed;
        else if(_horizontalMoveSpeed < 0 &&  (_basePosition.x - _position.x) > _horizontalMoveMax)
            _horizontalMoveSpeed = -_horizontalMoveSpeed;

    }
}
