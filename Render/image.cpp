#include "image.h"

Image::Image(QString filename){
    LoadGLTexture(filename);

    _filepath = filename;

    _position = b2Vec2(0, 0);
    _scale    = 1;
    _rotate   = 0;
    _repeat_x = 1;
    _repeat_y = 1;

    _color[0] = 1.0f;
    _color[1] = 1.0f;
    _color[2] = 1.0f;
    _color[3] = 1.0f;

    _drawSize = b2Vec2(0, 0);

    _blendFunc = GL_ONE_MINUS_SRC_ALPHA;
}

void Image::draw(GLfloat x, GLfloat y){

    glPushMatrix();
    glTranslatef(_position.x, _position.y, 0);
    glScaled(_scale, _scale, _scale);
    glRotated(_rotate, 0, 0, 1);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, _blendFunc);

    glColor4f(_color[0], _color[1], _color[2], _color[3]);

    glBindTexture(GL_TEXTURE_2D, _texture);

    if(_repeat_x > 1 || _repeat_y > 1){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    GLfloat bind_x_min = x*_repeat_x;
    GLfloat bind_x_max = (1 + x)*_repeat_x;
    GLfloat bind_y_min = y*_repeat_y;
    GLfloat bind_y_max = (1 + y)*_repeat_y;

    // Draw a textured quad
    GLfloat dw = _width*_repeat_x;
    GLfloat dh = _height*_repeat_y;
    if(_drawSize.x && _drawSize.y){
        dw = _drawSize.x;
        dh = _drawSize.y;
    }

    glBegin(GL_QUADS);
    glTexCoord2f(bind_x_min, bind_y_min); glVertex2f(-dw/2, -dh/2);
    glTexCoord2f(bind_x_min, bind_y_max); glVertex2f(-dw/2, dh/2);
    glTexCoord2f(bind_x_max, bind_y_max); glVertex2f(dw/2, dh/2);
    glTexCoord2f(bind_x_max, bind_y_min); glVertex2f(dw/2, -dh/2);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Image::LoadGLTexture(QString name){
    QImage t;

    if ( !_QImg.load( name ) )
    {
        cout << "Didn't found the image : " << name.toStdString() << endl;
        _QImg = QImage( 16, 16, QImage::Format_ARGB32  );
        _QImg.fill( 1 );
    }

    t = QGLWidget::convertToGLFormat( _QImg );
    //t = _QImg;

    int miplevel = 0;
    glGenTextures( 1, &_texture );
    //_texture = QGLWidget::bindTexture( _QImg );

    glBindTexture( GL_TEXTURE_2D, _texture );

    int w, h;

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, 0);

    _width  = w;
    _height = h;
}
