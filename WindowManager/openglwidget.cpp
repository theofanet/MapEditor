#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QGLWidget(parent){
    glInit();

    setMouseTracking(true);

    int framesPerSecond = 60;
    int seconde = 1000; // 1 seconde = 1000 ms
    int timerInterval = seconde / framesPerSecond;
    t_Timer = new QTimer(this);
    connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
    t_Timer->start( timerInterval );

    _asleep = false;
    _movingCamera = false;
    _movingCameraPosition = b2Vec2();
    _mousePosition = b2Vec2();

    _scene = new Scene();
}

b2Vec2 OpenGLWidget::ConvertScreenToWorld(int x, int y){
    float u = x / float(_width);
    float v = (_height - y) / float(_height);

    float ratio = float(_width) / float(_height);
    b2Vec2 extents(ratio * _scene->settings()->viewSize, _scene->settings()->viewSize);
    extents *= _scene->settings()->viewZoom;

    b2Vec2 lower = _scene->settings()->viewCenter - extents;
    b2Vec2 upper = _scene->settings()->viewCenter + extents;

    b2Vec2 p;
    p.x = (1.0f - u) * lower.x + u * upper.x;
    p.y = (1.0f - v) * lower.y + v * upper.y;

    return p;
}

void OpenGLWidget::initializeGL(){
    //OPENGL INIT
    glClearColor(.2, .2, .2, .5);
    glShadeModel(GL_FLAT);
    glAlphaFunc(GL_GREATER, 0); //For alpha
    glEnable(GL_ALPHA_TEST);  //Same
    glEnable(GL_BLEND); //Same
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Same
}

void OpenGLWidget::resizeGL(int, int){
    _width  = size().width();
    _height = size().height();

    glViewport(0, 0, _width, _height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratio = float(_width) / float(_height);

    b2Vec2 extents(ratio * _scene->settings()->viewSize, _scene->settings()->viewSize);
    extents *= _scene->settings()->viewZoom;

    b2Vec2 lower = _scene->settings()->viewCenter - extents;
    b2Vec2 upper = _scene->settings()->viewCenter + extents;

    _scene->settings()->lower  = lower;
    _scene->settings()->upper  = upper;
    _scene->settings()->height = _height;
    _scene->settings()->width  = _width;

    gluOrtho2D(lower.x, upper.x, lower.y, upper.y);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWidget::paintGL(){
    _scene->draw();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent  *event){
    _mousePosition = ConvertScreenToWorld(event->x(), event->y());

    _scene->setMousePosition(_mousePosition);
    if(_scene->getMap() && _scene->getMap()->getEditionMode() == EDIT_MODE_SELECTION_TILE)
        emit objectSelected(_scene->getMap()->getSelectedTiles());

    if(_movingCamera){
        b2Vec2 p = _movingCameraPosition - _mousePosition;
        _scene->settings()->cameraPosition += b2Vec2(p.x, p.y);
        _movingCameraPosition = _mousePosition;
    }
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event){
    if(event->type() == QEvent::MouseButtonRelease){
        if(event->button() == Qt::RightButton){
            _movingCamera = false;
        }
        else if(_scene->getMap())
            _scene->getMap()->cursorClicked(_mousePosition, false);
    }

}

void OpenGLWidget::mousePressEvent(QMouseEvent  *event){
    if(event->type() == QEvent::MouseButtonPress){
        if(event->button() == Qt::RightButton){
            _movingCamera = true;
            _movingCameraPosition = ConvertScreenToWorld(event->x(), event->y());
        }

        if(_scene->getMap())
            _scene->getMap()->cursorClicked(_mousePosition, true, (event->button() == Qt::RightButton));
    }

}

void OpenGLWidget::wheelEvent(QWheelEvent *event){
    switch(event->orientation()){
        case Qt::Horizontal:
            break;
        case Qt::Vertical:
            if(event->delta() < 0)
                _scene->settings()->cameraZoom = min((float32)(1.0f + MOUSE_WHEEL_SENSIBILTY) * _scene->settings()->cameraZoom, 4.0f);
            else
                _scene->settings()->cameraZoom = max((float32)(1.0f - MOUSE_WHEEL_SENSIBILTY) * _scene->settings()->cameraZoom, 0.10f);
            break;
    }
}
