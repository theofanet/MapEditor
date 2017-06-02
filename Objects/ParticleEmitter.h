//
//  ParticleEmitter.hpp
//  GameCube
//
//  Created by Theo Fanet on 28/07/16.
//  Copyright © 2016 Theo. All rights reserved.
//

#ifndef ParticleEmitter_hpp
#define ParticleEmitter_hpp

#include <stdio.h>
#include "Particle.h"
#include "object.h"

class ParticleEmitter : public Object{
public:
    ParticleEmitter(string name, b2Vec2 pos, GLfloat angle);
    ~ParticleEmitter();

    Json::Value getJsonData();
    static ParticleEmitter* fromJsonData(Json::Value data, int index, string basefilepath);
    
    void setSpeed(GLfloat speed){ _speed = speed; }
    void setSize(GLfloat size){ _radius = size; }
    void setPosition(b2Vec2 pos){ _position = pos; }
    void setAngle(GLfloat angle){ _angle = angle; }
    void setAndleDist(GLfloat angleD){ _angleDist = angleD; }
    void setLife(GLfloat life){ _life = life; }
    
    void draw();
    void update(GLfloat dt);
    
    void lunch(int nb);
    
    void setUpdateAlpha(bool a){ _updateAlpha = a; }
    void setUpdateRadius(bool r){ _updateRadius = r; }
    void setBaseLife(GLfloat l){ _life = l; }
    void setRadiusMult(GLfloat r){ _radius = r; }
    void setGravity(b2Vec2 g){ _gravity = g; }
    
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
    }

    void setColor(int index, GLfloat c){
        if(index >= 0 && index <= 2)
            _color[index]     = c;
    }

    void setEndColor(int index, GLfloat c){
        if(index >= 0 && index <= 2)
            _endColor[index]     = c;
    }

    GLfloat getColor(int index){
        if(index >= 0 && index <= 2)
            return _color[index];
        return 0.0f;
    }

    GLfloat getEndColor(int index){
        if(index >= 0 && index <= 2)
            return _endColor[index];
        return 0.0f;
    }

    GLfloat getLife(){ return _life; }
    GLfloat getSize(){ return _radius; }
    GLfloat getSpeed(){ return _speed; }
    GLfloat getAngle(){ return _angle; }
    GLfloat getAngleDelta(){ return _angleDist; }
    bool getUpdateAlpha(){ return _updateAlpha; }
    bool getUpdateRadius(){ return _updateRadius; }
    bool isEndColorActive(){ return _graduateColor; }
    void setEndColorActive(bool a){ _graduateColor = a; }
    b2Vec2 getGravity(){ return _gravity; }
    void setEmitteSize(b2Vec2 size){ _emitSize = size; }
    b2Vec2 getEmitteSize(){ return _emitSize; }

    void setNbParticules(int nb){
        _nbParticule = nb;
        lunch(nb);
    }
    int getNbParticules(){ return _nbParticule; }

    bool isShowingTexture(){ return _showTexture; }
    void setShowingTexture(bool s){ _showTexture = s; }

    void setOpen(bool o){ _open = o; }
    bool isOpen(){ return _open; }

    void handleCmd(string cmd, bool state);

public slots:
    void particleDead(Particle *p);
    
protected:
    vector<Particle *> _particles;
    vector<Particle *> _toErease;

    b2Vec2  _gravity, _emitSize;
    
    GLfloat _angle, _angleDist;
    GLfloat _speed;
    GLfloat _radius;
    GLfloat _life;
    
    Image *_particleTexture;

    int _nbParticule;
    
    bool    _graduateColor, _updateRadius, _updateAlpha, _showTexture;
    GLfloat _color[4], _endColor[4];

    bool _open;
    
    bool _isEmitting;
};

#endif /* ParticleEmitter_hpp */
