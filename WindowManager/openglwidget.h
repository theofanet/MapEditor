#ifndef OPENGLTAB_H
#define OPENGLTAB_H

#include <iostream>

#include <QGLWidget>
#include <QtOpenGL>
#ifdef _WIN32

#include <GL/glext.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#else
#include <GLUT/glut.h>
#endif

#include "Utilities/defines.h"
#include "scene.h"

using namespace std;

class OpenGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);

    b2Vec2 ConvertScreenToWorld(int x, int y);

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    bool getAsleep(){ return _asleep; }
    void setAsleep(bool s = true){ _asleep = s; }
    void toogleAsleep(){ _asleep = !_asleep; }

    void mouseMoveEvent(QMouseEvent  *event);
    void mousePressEvent(QMouseEvent  *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    Scene* getScene(){ return _scene; }

public slots:
    virtual void timeOutSlot(){
        if(!_asleep) {
            updateGL();
            _scene->update((double)t_Timer->interval() / 1000.0);
        }
    }

signals:
    void objectSelected(vector<MapTile*> tiles);

private:
    QTimer *t_Timer;
    bool    _asleep;
    int     _width, _height;

    bool   _movingCamera;
    b2Vec2 _movingCameraPosition, _mousePosition;

    Scene   *_scene;
};

#endif // OPENGLTAB_H
