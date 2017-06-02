#include "sprite.h"

Sprite::Sprite(QString filename, GLfloat w, GLfloat h){
    _image  = new Image(filename);

    _width  = w;
    _height = h;

    _nbCell  = _image->getWidth() / _width;
    _nbRow   = _image->getHeight() / _height;
    _nbTiles = _nbCell * _nbRow;

    _scale  = 1;
    _rotate = 0;

    _row  = 0;
    _cell = 0;

    _drawSize = b2Vec2(0, 0);
}

Sprite::~Sprite(){
    delete_obj(_image);
}

void Sprite::setCell(int cell){
    if(cell > _image->getWidth() / _width)
        cell = _image->getWidth() / _width;

    _cell = cell;
}

void Sprite::setRow(int row){
    if(row > _image->getHeight() / _height)
        row = _image->getHeight() / _height;

    _row = row;
}

void Sprite::draw(GLfloat x, GLfloat y, bool flip){
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScaled(_scale, _scale, _scale);

    if(flip)
        glRotated(180, 0, 1, 0);

    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, _image->getTexture());

    GLfloat bind_x_min = (_width*_cell) / _image->getWidth();
    GLfloat bind_x_max = (_width*_cell + _width) / _image->getWidth();
    GLfloat bind_y_min = (_height*_row) / _image->getHeight();
    GLfloat bind_y_max = (_height*_row + _height) / _image->getHeight();

    // Draw a textured quad
    GLfloat dw = _width;
    GLfloat dh = _height;
    if(_drawSize.x && _drawSize.y){
        dw = _drawSize.x;
        dh = _drawSize.y;
    }

    glBegin(GL_QUADS);
    glTexCoord2f(bind_x_min, bind_y_min); glVertex2f(-dw/2, -dh/2);
    glTexCoord2f(bind_x_min, bind_y_max); glVertex2f(-dw/2, dh/2);
    glTexCoord2f(bind_x_max, bind_y_max); glVertex2f(dw/2, dh/2);
    glTexCoord2f(bind_x_max, bind_y_min); glVertex2f(dw/2, -dh/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

QImage Sprite::getQImageTile(int cell, int row){
    QImage image = _image->getQImage();
    QRect rect   = QRect(cell*_width, ((_nbRow - 1) - row)*_height, _width, _height);

    //size_t offset = rect.x() * image.depth() / 8 + rect.y() * image.bytesPerLine();

    return image.copy(rect);//QImage(image.bits() + offset, rect.width(), rect.height(), image.bytesPerLine(), image.format());
}



bool Sprite::hasAnimation(string key){
    return (_animations.find(key) != _animations.end());
}

void Sprite::addAnimation(string key, AnimationAbstract *anim){
    if(!hasAnimation(key)){
        anim->setIdentifier(key);
        _animations[key] = anim;
    }
}

void Sprite::removeAnimation(string key){
    if(hasAnimation(key))
        _animations.erase(key);
}

void Sprite::activateAnimation(string key, bool reset){
    if(hasAnimation(key)){
        setAnimation(_animations[key]);
        if(reset)
            _animation->reset();
    }
}

void Sprite::setAnimation(AnimationAbstract *anim){
    _animation = anim;
    _row       = anim->getRow();
}

AnimationAbstract* Sprite::getAnimation(string key){
    if(hasAnimation(key))
        return _animations[key];

    return NULL;
}

AnimationAbstract* Sprite::animation(){
    return _animation;
}

void Sprite::update(){
    if(_animation){
        _animation->update();
        setCell(_animation->getIndex());
    }
}
