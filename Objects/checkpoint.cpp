#include "checkpoint.h"

Checkpoint::Checkpoint(){
    _img = new Image(imagesDirPath()+"FlagItem.png");
}

Checkpoint::~Checkpoint(){
    delete_obj(_img);
}

void Checkpoint::draw(){
    _img->setPosition(_position.x, _position.y);
    _img->setScale(0.02);
    _img->draw();
}
