#include "animationabstract.h"

AnimationAbstract::AnimationAbstract(int from, int to, int delay){
    _from  = from;
    _to    = to;
    _delay = delay;

    _start_index = from;
    _index       = _start_index;

    _current_state = AnimationState::PAUSE;
    _redo = true;

    _last_time = 0;
    _rowId     = 0;

    _delegate    = NULL;
    _identifier  = "animation_";
    _identifier += rand();
}

AnimationAbstract::~AnimationAbstract(){

}

void AnimationAbstract::setDelegate(AnimationDelegate *d){
    _delegate = d;
}

void AnimationAbstract::redo(bool r){
    _redo = r;
}

void AnimationAbstract::setStartIndex(int i){
    _start_index = i;
    _index       = i;
}

int AnimationAbstract::getIndex(){
    return _index;
}

void AnimationAbstract::start(){
    reset();
}

void AnimationAbstract::pause(){
    _current_state = AnimationState::PAUSE;
    if(_delegate)
        _delegate->AnimationPaused(this);
}

void AnimationAbstract::stop(){
    _current_state = AnimationState::PAUSE;
    if(_delegate)
        _delegate->AnimationEnded(this);
}

void AnimationAbstract::update(){

}

void AnimationAbstract::play(){
    _current_state = AnimationState::PLAYING;
    if(_delegate)
        _delegate->AnimationStarted(this);
}

void AnimationAbstract::reset(bool pause){
    if(pause && _delegate)
        _delegate->AnimationPaused(this);
    else if(_delegate)
        _delegate->AnimationStarted(this);

    _current_state = pause ? AnimationState::PAUSE : AnimationState::PLAYING;
    _index = _start_index;
}

void AnimationAbstract::setRow(int row){
    _rowId = row;
}

int AnimationAbstract::getRow(){
    return _rowId;
}
