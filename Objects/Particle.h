//
//  Particle.hpp
//  GameCube
//
//  Created by Theo Fanet on 28/07/16.
//  Copyright © 2016 Theo. All rights reserved.
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
#include "Utilities/defines.h"
#include "Utilities/Listener.h"
#include "Render/image.h"

class Particle{
public:
    Particle(b2Vec2 pos, GLfloat angle, GLfloat speed, GLfloat life);
    ~Particle();
    
    void update(GLfloat dt);
    void draw();
    
    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0){
        _color[0] = r;
        _color[1] = g;
        _color[2] = b;
        _color[3] = a;
    }
    
    void setEndColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0){
        _graduateColor = true;
        
        _endColor[0] = r;
        _endColor[1] = g;
        _endColor[2] = b;
        _endColor[3] = a;
        
        _deltaColor[0] = (_endColor[0] - _color[0]) / _life;
        _deltaColor[1] = (_endColor[1] - _color[1]) / _life;
        _deltaColor[2] = (_endColor[2] - _color[2]) / _life;
        _deltaColor[3] = (_endColor[3] - _color[3]) / _life;
    }
    
    void setUpdateAlpha(bool a){ _updateAlpha = a; }
    void setUpdateRadius(bool r){ _updateRadius = r; }
    void setRadiusMult(GLfloat r){
        _radius = r + doubRand()*(doubRand() > 0.5 ? 1.0f : -1.0f);
        _originalRadius = _radius;
    }
    
    void setTexture(Image* tex){ _texture = tex; }
    void setGravity(b2Vec2 g){ _gravity = g; }
    
signals:
    Signal<void(Particle*)> isDead;
    
protected:
    b2Vec2 _position;
    b2Vec2 _velocity;
    b2Vec2 _gravity;
    
    Image *_texture;
    
    bool    _graduateColor, _updateRadius, _updateAlpha;
    GLfloat _color[4], _endColor[4], _deltaColor[4];

    GLfloat _life, _originalLife, _time;
    GLfloat _angle, _speed;
    GLfloat _radius, _originalRadius;
};

#endif /* Particle_hpp */
