#ifndef PLATFORM_H
#define PLATFORM_H

#include "object.h"

class Platform : public Object{
public:
    Platform(string name, b2Vec2 pos);
    ~Platform();
    
    Json::Value getJsonData();
    static Platform* fromJsonData(Json::Value data, int index, string basefilepath);

    void draw();
    void drawAddingPoint(b2Vec2 pos);
    void update(GLfloat dt);

    void showTexture(bool s){ _showTexture = s; }
    bool isShowingTexture(){ return _showTexture; }
    void setTexture(string filename);

    void setIsMoving(bool b);
    bool isMoving(){ return _isMoving; }

    void addPoint(b2Vec2 p){ _points.push_back(p); }
    void addPoint(GLfloat x, GLfloat y){ addPoint(b2Vec2(x, y)); }
    vector<b2Vec2> getPoints(){ return _points; }

    void setNormalizeDirection(bool n){ _normalizeDirection = n; }
    bool getNormalizeDirection(){ return _normalizeDirection; }

    void setSpeed(GLfloat s){ _speed = s; }
    GLfloat getSpeed(){ return _speed; }

    void setMovingCircle(bool m){ _movingCircle = m; }
    bool isMovingCircle(){ return _movingCircle; }

    void setDirection(bool d){ _actualDirection = d; }
    bool getDirection(){ return _actualDirection; }

    void setWidth(GLfloat w){ _dim.x = w; }
    void setHeight(GLfloat h){ _dim.y = h; }
    void setSize(b2Vec2 s){ _dim  = s; }
    void setSize(GLfloat w, GLfloat h){ setSize(b2Vec2(w, h)); }
    b2Vec2 getSize(){ return _dim; }


    void handleCmd(string cmd, bool state);

protected:
    bool _isMoving, _movingCircle;

    vector<b2Vec2> _points;

    Image  *_texture;
    bool   _showTexture;
    string _filename;

    b2Vec2  _actualPosition;
    bool    _actualDirection;
    bool    _oneStepMove;
    int     _nextIndex;
    GLfloat _speed;
    bool    _normalizeDirection;
};

#endif // PLATFORM_H
