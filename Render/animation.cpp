#include "animation.h"

Animation::Animation(int from, int to, int delay) : AnimationAbstract(from, to, delay){

}

void Animation::update(){
    if(_current_state != AnimationState::PAUSE){
        _last_time++;
        if((int)_last_time > _delay){
            _last_time = 0;

            int sign = 1;
            if(_from > _to)
                sign = -1;

            _index += sign*1;

            if(_redo && ((sign > 0 && _index > _to) || (sign < 0 && _index < _to)))
                _index = _from;
            else if(!_redo && ((sign > 0 && _index > _to) || (sign < 0 && _index < _to))){
                _index = _to;
                stop();
            }
        }
    }
}
