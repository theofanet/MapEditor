#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdio.h>
#include <iostream>
#include "time.h"

#include "AnimationAbstract.h"

using namespace std;

class Animation : public AnimationAbstract{
public:
    Animation(int from, int to, int delay);

    void update();
};

#endif // ANIMATION_H
