//
//  Particle.cpp
//  GameCube
//
//  Created by Theo Fanet on 28/07/16.
//  Copyright © 2016 Theo. All rights reserved.
//

#include "Particle.h"

Particle::Particle(b2Vec2 pos, GLfloat angle, GLfloat speed, GLfloat life){
    _position = pos;
    _life     = life;
    _speed    = speed;
    _angle    = angle;
    _gravity  = b2Vec2(0, 0);
    _time     = 0.0;
    
    _texture = NULL;
    
    rand();
    
    _radius = (double)rand()/RAND_MAX;
    
    _graduateColor = false;
    _color[0] = 0.0f;
    _color[1] = 0.0f;
    _color[2] = 1.0f;
    _color[3] = 1.0f;
    
    _velocity.x = _speed * cos(_angle*DEGTORAD) * 0.5;
    _velocity.y = -_speed * sin(_angle*DEGTORAD) * 0.5;
    
    _originalRadius = _radius;
    _originalLife   = _life;
}

Particle::~Particle(){
    
}

void Particle::update(GLfloat dt){
    if(_life > 0){
        _life -= dt;
        _time += dt;
        
        if(_life > 0){
            _position.x += (_velocity.x + _gravity.x*_time)*dt;
            _position.y += (_velocity.y + _gravity.y*_time)*dt;
            
            if(_graduateColor){
                for(int i = 0; i < 4; i++)
                    _color[i] += _deltaColor[i]*dt;
            }
            
            GLfloat ageRatio = _life / _originalLife;
            if(_updateRadius)
                _radius          = _originalRadius * ageRatio;
            if(_updateAlpha)
                _color[3]        = ageRatio;
        }
        else
            isDead.trigger(this);
    }
}

void Particle::draw(){
    if(_life > 0){
        if(_texture){
            _texture->setBlendFunc(GL_ONE);
            _texture->setDrawSize(b2Vec2(_radius, _radius));
            _texture->setColor(_color[0], _color[1], _color[2], _color[3]);
            _texture->setPosition(_position);
            _texture->draw();
        }
        else{
            glPushMatrix();
            glTranslatef(_position.x, _position.y, 0);
            
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE);
            
            glColor4f(_color[0], _color[1], _color[2], _color[3]);
            
            const float32 k_segments = 16.0f;
            const float32 k_increment = 2.0f * b2_pi / k_segments;
            float32 theta = 0.0f;
            glBegin(GL_POLYGON);
            for (int32 i = 0; i < k_segments; ++i)
            {
                b2Vec2 v = (_radius / 2) * b2Vec2(cosf(theta), sinf(theta));
                glVertex2f(v.x, v.y);
                theta += k_increment;
            }
            glEnd();
            
            glDisable(GL_BLEND);
            
            glPopMatrix();
        }
    }
}
