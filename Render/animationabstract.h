#ifndef ANIMATIONABSTRACT_H
#define ANIMATIONABSTRACT_H


#include <stdio.h>
#include <iostream>
#include "time.h"

using namespace std;

enum AnimationState { PLAYING, PAUSE };

class AnimationAbstract;

class AnimationDelegate{
public:
    virtual void AnimationStarted(AnimationAbstract *){}
    virtual void AnimationEnded(AnimationAbstract *){}
    virtual void AnimationPaused(AnimationAbstract *){}
};

class AnimationAbstract{
public:
    AnimationAbstract(int from, int to, int delay);
    ~AnimationAbstract();

    virtual void pause();
    virtual void stop();
    virtual void start();
    virtual void play();

    virtual void reset(bool pause = false);
    virtual void update();
    virtual void redo(bool r);

    virtual void setStartIndex(int i);
    virtual int getIndex();

    void setRow(int row);
    int  getRow();

    void setDelegate(AnimationDelegate *d);

    void setIdentifier(string ident){ _identifier = ident; }
    string identifier(){ return _identifier; }

protected:
    int _from, _to, _delay;

    int _index, _start_index;
    bool _redo;

    int _rowId;

    clock_t _last_time;
    string _identifier;

    AnimationState _current_state;
    AnimationDelegate *_delegate;
};

#endif // ANIMATIONABSTRACT_H
