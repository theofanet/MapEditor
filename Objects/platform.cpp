#include "platform.h"

Platform::Platform(string name, b2Vec2 pos) : Object(name, pos){
    _isMoving = false;

    _type = OBJECT_TYPE_PLATFORM;
    _dim = b2Vec2(10.0, 2.0);

    _nextIndex = 0;

    _actualPosition = _position;

    _actualDirection    = true;
    _oneStepMove        = false;
    _normalizeDirection = true;
    _movingCircle       = false;
    _speed = 5.0f;

    _texture = NULL;
    _showTexture = false;

    _cmdList.push_back("power");
    _cmdList.push_back("one_step_front");
    _cmdList.push_back("one_step_back");
    _cmdList.push_back("setDirection");
    _cmdList.push_back("toggleDirection");
    _cmdList.push_back("resetPosition");
}

Platform::~Platform(){
    delete_obj(_texture);
}

Json::Value Platform::getJsonData(){
    Json::Value data = Object::getJsonData();

    data["isMoving"] = _isMoving;
    data["movingCircle"] = _movingCircle;
    data["direction"] = _actualDirection;
    data["normalizeDirection"] = _normalizeDirection;
    data["speed"] = _speed;
    data["size"]["x"] = _dim.x;
    data["size"]["y"] = _dim.y;
    data["showTexture"] = _showTexture;
    if(_showTexture){
        QFileInfo fileinfo(_texture->getFilePath());
        data["textureFilename"] = "Objects/" + fileinfo.fileName().toStdString();
        _filesToCopy.push_back(make_pair(_texture->getFilePath().toStdString(), "Objects/" + fileinfo.fileName().toStdString()));
    }
    else
        data["textureFilename"] = "";

    int i = 0;
    for(vector<b2Vec2>::iterator it = _points.begin(); it != _points.end(); ++it){
        b2Vec2 pts = *it;
        data["points"][i]["x"] = pts.x;
        data["points"][i]["y"] = pts.y;
        i++;
    }

    return data;
}

Platform* Platform::fromJsonData(Json::Value data, int index, string basefilepath){
    string name = "laser_" + QString::number(index).toStdString();
    if(data.isMember("name"))
        name = data["name"].asString();

    Platform *t = new Platform(name, b2Vec2(data["position"]["x"].asDouble(), data["position"]["y"].asDouble()));

    t->setIsMoving(data["isMoving"].asBool());
    t->setMovingCircle(data["movingCircle"].asBool());
    t->setDirection(data["direction"].asBool());
    t->setNormalizeDirection(data["normalizeDirection"].asBool());
    t->setSpeed(data["speed"].asDouble());
    t->setSize(data["size"]["x"].asDouble(), data["size"]["y"].asDouble());
    if(data.isMember("showTexture")){
        t->showTexture(data["showTexture"].asBool());
        if(t->isShowingTexture())
            t->setTexture(basefilepath + data["textureFilename"].asString());
    }

    if(data.isMember("points")){
        int i = 0;
        Json::Value tdata = data["points"][i++];
        while ( !tdata.isNull() ) {
            t->addPoint(tdata["x"].asDouble(), tdata["y"].asDouble());
            tdata = data["points"][i++];
        }
    }

    return t;
}

void Platform::setTexture(string filename){
    if(!filename.empty()){
        if(_texture)
            delete_obj(_texture);

        _texture = new Image(QString::fromStdString(filename));
        _texture->setDrawSize(_dim);
        _filename = filename;
    }
}

void Platform::handleCmd(string cmd, bool state){
    if(cmd == "power")
        _isMoving = state;
    else if(cmd == "setDirection")
        _actualDirection = state;
    else if(cmd == "toggleDirection")
        _actualDirection = !_actualDirection;
    else if(cmd == "one_step_front"){
        _oneStepMove = true;
        _isMoving    = true;
    }
    else if(cmd == "resetPosition"){
        _actualPosition = _position;
        _nextIndex = (_actualDirection ? 0 : _points.size()-1);
    }
    else if(cmd == "one_step_back"){
        _nextIndex -= 2;
        if(_nextIndex <= -2){
            if(_movingCircle)
                _nextIndex = (_actualDirection ? _points.size()-1 : -1);
            else{
                _actualDirection = !_actualDirection;
                _nextIndex = (_actualDirection ? _points.size()-1 : 0);
            }
        }
        _oneStepMove = true;
        _isMoving    = true;
    }
}

void Platform::setIsMoving(bool b){
    _isMoving = b;
}

void Platform::draw(){
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    b2Vec2 pos;
    if(!_isMoving && _actualPosition.x == 0 && _actualPosition.y == 0)
        pos = _position;
    else
        pos = _actualPosition;

    if(pos.x != _position.x && pos.y != _position.y){
        if(_showTexture && _texture){
            _texture->setDrawSize(_dim);
            _texture->setPosition(_position);
            _texture->setColor(1.0, 1.0, 1.0, .5);
            _texture->draw();
        }
        else{
            glPushMatrix();
            glTranslated(_position.x, _position.y, 0.0f);

            glColor4f(1.0, 1.0, 1.0, .5);
            glBegin(GL_QUADS);
            glVertex2f(-_dim.x/2, -_dim.y/2);
            glVertex2f(-_dim.x/2, _dim.y/2);
            glVertex2f(_dim.x/2, _dim.y/2);
            glVertex2f(_dim.x/2, -_dim.y/2);
            glEnd();

            glPopMatrix();
        }
    }

    b2Vec2 lastPts = _position;

    size_t i = 0;
    for(vector<b2Vec2>::iterator it = _points.begin(); it != _points.end(); ++it){
        b2Vec2 pts = *it;


        if(_showTexture && _texture){
            _texture->setDrawSize(_dim);
            _texture->setPosition(pts);
            _texture->setColor(1.0, 1.0, 1.0, .5);
            _texture->draw();
        }
        else{
            glPushMatrix();
            glTranslated(pts.x, pts.y, 0.0f);

            glColor4f(1.0, 1.0, 1.0, .5f);

            glBegin(GL_QUADS);
            glVertex2f(-_dim.x/2, -_dim.y/2);
            glVertex2f(-_dim.x/2, _dim.y/2);
            glVertex2f(_dim.x/2, _dim.y/2);
            glVertex2f(_dim.x/2, -_dim.y/2);
            glEnd();

            glPopMatrix();
        }

        glLineWidth(3.0);
        glColor4f(0.0, 1.0, 0.0, 1.0);
        glLineStipple(1, 0xFF0F);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        glVertex2f(lastPts.x, lastPts.y);
        glVertex2f(pts.x, pts.y);
        glEnd();
        glLineWidth(1.0);
        glDisable(GL_LINE_STIPPLE);

        if(_movingCircle && i == _points.size()-1){
            glLineWidth(3.0);
            glColor4f(0.0, 1.0, 0.0, 1.0);
            glLineStipple(1, 0xFF0F);
            glEnable(GL_LINE_STIPPLE);
            glBegin(GL_LINES);
            glVertex2f(pts.x, pts.y);
            glVertex2f(_position.x, _position.y);
            glEnd();
            glLineWidth(1.0);
            glDisable(GL_LINE_STIPPLE);
        }

        lastPts = pts;
        i++;
    }


    if(_showTexture && _texture){
        _texture->setDrawSize(_dim);
        _texture->setPosition(pos);
        _texture->setColor(1.0, 1.0, 1.0, 1.0);
        _texture->draw();
    }
    else{
        glPushMatrix();
        glTranslated(pos.x, pos.y, 0.0f);

        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glVertex2f(-_dim.x/2, -_dim.y/2);
        glVertex2f(-_dim.x/2, _dim.y/2);
        glVertex2f(_dim.x/2, _dim.y/2);
        glVertex2f(_dim.x/2, -_dim.y/2);
        glEnd();

        glPopMatrix();
    }

    glDisable(GL_BLEND);
    Object::draw();
}

void Platform::drawAddingPoint(b2Vec2 pos){
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    if(_showTexture && _texture){
        _texture->setDrawSize(_dim);
        _texture->setPosition(pos);
        _texture->setColor(1.0, 1.0, 1.0, .5);
        _texture->draw();
    }
    else{
        glPushMatrix();
        glTranslated(pos.x, pos.y, 0.0f);

        glColor4f(1.0, 1.0, 1.0, .5f);

        glBegin(GL_QUADS);
        glVertex2f(-_dim.x/2, -_dim.y/2);
        glVertex2f(-_dim.x/2, _dim.y/2);
        glVertex2f(_dim.x/2, _dim.y/2);
        glVertex2f(_dim.x/2, -_dim.y/2);
        glEnd();

        glPopMatrix();
    }

    b2Vec2 from = _position;
    if(_points.size())
        from = _points.at(_points.size() - 1);

    glLineWidth(3.0);
    glColor4f(0.0, 1.0, 0.0, 1.0);
    glLineStipple(1, 0xFF0F);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex2f(from.x, from.y);
    glVertex2f(pos.x, pos.y);
    glEnd();
    glLineWidth(1.0);
    glDisable(GL_LINE_STIPPLE);

    glDisable(GL_BLEND);
}

void Platform::update(GLfloat dt){
    if(_isMoving && _nextIndex < (int)_points.size() && _nextIndex > -2){
        b2Vec2 pos     = _actualPosition;
        b2Vec2 nextPos;
        if(_nextIndex == -1)
            nextPos = _position;
        else
            nextPos = _points.at(_nextIndex);

        GLfloat dist = sqrt(pow(pos.x-nextPos.x, 2) + pow(pos.y-nextPos.y, 2));
        b2Vec2  dir  = nextPos - pos;
        if(_normalizeDirection)
            dir.Normalize();

        if(dist > 0.1)
            _actualPosition += dt * _speed * dir;
        else{
            _nextIndex += (_actualDirection ? 1 : -1);
            _actualPosition = nextPos;

            if(_oneStepMove){
                _oneStepMove = false;
                _isMoving    = false;
            }
        }
    }
    else if(_isMoving){
        if(_movingCircle)
            _nextIndex = (_actualDirection ? -1 : _points.size()-1);
        else{
            _actualDirection = !_actualDirection;
            _nextIndex = (_actualDirection ? 0 : _points.size()-1);
        }
    }
}

