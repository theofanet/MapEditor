#include "jeton.h"

Jeton::Jeton(string name, b2Vec2 position) : Object(name, position){
    _type = OBJECT_TYPE_JETON;

    _sprite = new Sprite(imagesDirPath() + "tileJetons.png", 85, 85);
    Animation *anim = new Animation(0, 3, 10);
    anim->setRow(0);
    anim->play();
    _sprite->setDrawSize(2, 2);
    _sprite->setAnimation(anim);
}

Jeton::~Jeton(){
    delete_obj(_sprite);
}

void Jeton::update(GLfloat){
    if(_sprite)
        _sprite->update();
}

void Jeton::draw(){
    if(_sprite)
        _sprite->draw(_position.x, _position.y);
}
