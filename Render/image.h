#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <iostream>
#include "Utilities/defines.h"

using namespace std;

class Image
{
public:
    Image(QString filename);

    void draw(GLfloat x = 0.0f, GLfloat y = 0.0f);

    void setPosition(b2Vec2 p){ _position = p; }
    void setPosition(GLfloat x, GLfloat y){ setPosition(b2Vec2(x, y)); }
    void setRotation(GLfloat r){ _rotate = r; }
    void setScale(GLfloat s){ _scale = s; }
    void setRepeat(int x = 1.0f, int y = 1.0f){ _repeat_x = x; _repeat_y = y; }
    void setWidth(GLfloat width){ _width = width; }
    void setHeight(GLfloat height){ _height = height; }

    GLfloat getWidth(){ return _width; }
    GLfloat getHeight(){ return _height; }
    GLuint  getTexture(){ return _texture; }

    QString getFilePath(){ return _filepath; }
    QImage getQImage(){ return _QImg; }

    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f){
        _color[0] = r;
        _color[1] = g;
        _color[2] = b;
        _color[3] = a;
    }

    void setBlendFunc(GLenum func){ _blendFunc = func; }

    void setDrawSize(b2Vec2 s){ _drawSize = s; }
    void setDrawSize(GLfloat x, GLfloat y){ setDrawSize(b2Vec2(x, y)); }

private:
    void LoadGLTexture(QString name);
    QImage _QImg;

    QString _filepath;
    GLuint  _texture;
    GLfloat _width, _height;
    GLfloat _color[4];

    GLenum _blendFunc;

    b2Vec2  _position, _drawSize;
    GLfloat _rotate, _scale;
    int     _repeat_x, _repeat_y;
};

#endif // IMAGE_H
