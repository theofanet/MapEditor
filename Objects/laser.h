#ifndef LASER_H
#define LASER_H

#include "object.h"

class Laser : public Object{
public:

    Laser(string name, b2Vec2 pos, float power = 5.0f);
    ~Laser();

    Json::Value getJsonData();
    static Laser* fromJsonData(Json::Value data, int index, string basefilepath);

    void draw();

    void setColor(GLfloat r, GLfloat g, GLfloat b){
        _color[0] = r;
        _color[1] = g;
        _color[2] = b;  
        _selectionColor[0] = r;
        _selectionColor[1] = g;
        _selectionColor[2] = b;
        _backColor[0] = (r - 0.3 < 0.0 ? 0.0 : r - 0.3);
        _backColor[1] = (g - 0.3 < 0.0 ? 0.0 : g - 0.3);
        _backColor[2] = (b - 0.3 < 0.0 ? 0.0 : b - 0.3);
    }

    void setColor(int index, GLfloat c){
        if(index >= 0 && index <= 2){
            _color[index]     = c;
            _selectionColor[index] = c;
            _backColor[index] = (c - 0.3 < 0.0 ? 0.0 : c - 0.3);
        }
    }

    GLfloat getColor(int index){
        if(index >= 0 && index <= 2)
            return _color[index];
        return 0.0f;
    }

    void setAngle(GLfloat angle){
        _angle = angle;
        if(_angle > 360)
            _angle = 0;
    }
    GLfloat getAngle(){ return _angle; }

    void setPower(GLfloat power){ _power = power; }
    GLfloat getPower(){ return _power; }

    void setAutoRoatation(bool autoRot){ _autoRotation = autoRot; }
    void setAutoRotationStartAngle(GLfloat angle){ _autoStartAngle = angle; }
    void setAutoRotationEndAngle(GLfloat angle){ _autoEndAngle = angle; }
    void setAutoRotationStep(GLfloat step){ _autoStepAngle = step; }
    GLfloat getAutoRotationStep(){ return _autoStepAngle; }
    GLfloat getAutoRotationStartAngle(){ return _autoStartAngle; }
    GLfloat getAutoRotationEndAngle(){ return _autoEndAngle; }
    bool getAutoRotation(){ return _autoRotation; }

    void handleCmd(string cmd, bool state);

protected:
    GLfloat        _power, _angle;

    GLfloat        _color[3], _backColor[3];

    bool _autoRotation, _isOn;
    GLfloat _autoStartAngle, _autoEndAngle, _autoStepAngle;

    GLfloat        _animation, _lifeTimeOfLaser, _totalTimeOfLaser;
    Image         *_texture[2][3], *_overlay, *_baseTexture;
};

#endif // LASER_H
