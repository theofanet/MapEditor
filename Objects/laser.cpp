#include "laser.h"

Laser::Laser(string name, b2Vec2 pos, GLfloat power) : Object(name, pos){
    _angle        = 0.0f;
    _power        = power;
    _isOn         = true;

    _type = OBJECT_TYPE_LASER;

    _autoRotation = false;
    _autoStartAngle = 0.0f;
    _autoEndAngle   = 360.0f;
    _autoStepAngle  = 0.1f;

    _texture[0][0] = new Image(imagesDirPath()+"laser_start_back.png");
    _texture[0][0]->setPosition(0, 0.01);
    _texture[0][0]->setScale(0.02);
    _texture[0][0]->setBlendFunc(GL_ONE);

    _texture[0][1] = new Image(imagesDirPath()+"laser_mid_back.png");
    _texture[0][1]->setRepeat(1, 100);
    _texture[0][1]->setScale(0.02);
    _texture[0][1]->setBlendFunc(GL_ONE);

    _texture[0][2] = new Image(imagesDirPath()+"laser_end_back.png");
    _texture[0][2]->setScale(0.02);
    _texture[0][2]->setBlendFunc(GL_ONE);

    _texture[1][0] = new Image(imagesDirPath()+"laser_start_front.png");
    _texture[1][0]->setPosition(0, 0.01);
    _texture[1][0]->setScale(0.02);
    _texture[1][0]->setBlendFunc(GL_ONE);

    _texture[1][1] = new Image(imagesDirPath()+"laser_mid_front.png");
    _texture[1][1]->setRepeat(1, 100);
    _texture[1][1]->setScale(0.02);
    _texture[1][1]->setBlendFunc(GL_ONE);

    _texture[1][2] = new Image(imagesDirPath()+"laser_end_front.png");
    _texture[1][2]->setScale(0.02);
    _texture[1][2]->setBlendFunc(GL_ONE);

    _overlay = new Image(imagesDirPath()+"laser_overlay.png");
    _overlay->setRepeat(1, 100);
    _overlay->setScale(0.02);
    _overlay->setBlendFunc(GL_ONE);

    _baseTexture = new Image(imagesDirPath()+"laserBase.png");
    _baseTexture->setScale(0.002);

    _color[0] = 1.0f;
    _color[1] = 0.0f;
    _color[2] = 0.0f;

    _animation = 100;

    _cmdList.push_back("turn_on");
}

Laser::~Laser(){
    for(int layer = 0; layer < 2; layer++)
        for(int part = 0; part < 3; part++)
            delete_obj(_texture[layer][part]);
    delete_obj(_overlay);
    delete_obj(_baseTexture);
}

Json::Value Laser::getJsonData(){
    Json::Value data = Object::getJsonData();

    data["power"] = _power;
    data["angle"] = _angle;
    data["color"]["r"] = _color[0];
    data["color"]["g"] = _color[1];
    data["color"]["b"] = _color[2];
    data["autoRotation"] = _autoRotation;
    data["autoRotationStartAngle"] = _autoStartAngle;
    data["autoRotationEndAngle"] = _autoEndAngle;
    data["autoRotationStep"] = _autoStepAngle;

    return data;
}

Laser* Laser::fromJsonData(Json::Value data, int index, string){
    string name = "laser_" + QString::number(index).toStdString();
    if(data.isMember("name"))
        name = data["name"].asString();

    Laser *t = new Laser(name, b2Vec2(data["position"]["x"].asDouble(), data["position"]["y"].asDouble()), data["power"].asDouble());

    t->setAngle(data["angle"].asDouble());
    t->setAutoRoatation(data["autoRotation"].asBool());

    if(data.isMember("autoRotationMaxAngle"))
        t->setAutoRotationStartAngle(data["autoRotationMaxAngle"].asDouble());
    else if(data.isMember("autoRotationStartAngle"))
        t->setAutoRotationStartAngle(data["autoRotationStartAngle"].asDouble());

    if(data.isMember("autoRotationMinAngle"))
        t->setAutoRotationEndAngle(data["autoRotationMinAngle"].asDouble());
    else if(data.isMember("autoRotationEndAngle"))
        t->setAutoRotationEndAngle(data["autoRotationEndAngle"].asDouble());

    if(data.isMember("autoRotationSpeed"))
        t->setAutoRotationStep(data["autoRotationSpeed"].asDouble());
    else if(data.isMember("autoRotationStep"))
        t->setAutoRotationStep(data["autoRotationStep"].asDouble());

    t->setColor(data["color"]["r"].asDouble(), data["color"]["g"].asDouble(), data["color"]["b"].asDouble());

    return t;
}

void Laser::draw(){
    glPushMatrix();

    glTranslatef(_position.x, _position.y, 0.0);
    glRotatef(_angle, 0, 0, 1);

    _baseTexture->draw();

    if(_isOn){
        float r = 0.6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.4)));

        for(int layer = 0; layer < 2; layer++){
            for(int part = 0; part < 3; part++){
                _texture[layer][part]->setColor(
                            (layer == 0 ? _backColor[0] : _color[0]),
                            (layer == 0 ? _backColor[1] : _color[1]),
                            (layer == 0 ? _backColor[2] : _color[2]),
                            (layer == 0 ? 0.8 : 1.0)*r
                        );

                if(part == 1){
                    _texture[layer][part]->setPosition(0, _power + (_texture[layer][0]->getHeight()*0.02)/2);
                    _texture[layer][part]->setHeight(_power);
                }
                else if(part == 2)
                    _texture[layer][part]->setPosition(0, _power*2 + (_texture[layer][0]->getHeight()*0.02));

                _texture[layer][part]->draw();

            }
        }

        _overlay->setColor(_backColor[0], _backColor[1], _backColor[2],  .7f * r);
        _overlay->setPosition(-0.02, (_power + (_texture[1][0]->getHeight()*0.02)/1.6));
        _overlay->setHeight(_power + (_texture[1][0]->getHeight()*0.014));
        _overlay->draw(0, _animation);
        _animation -= 0.0008;
        if(_animation < 0)
            _animation = 100;
    }

    glPopMatrix();

    if(_autoRotation && _isOn){
        _angle += _autoStepAngle;
        if(_angle > 360)
            _angle = 0;
        else if(_angle < 0)
            _angle = 360;

        if(_autoStepAngle > 0){
            if(_angle > _autoEndAngle){
                if(_autoStartAngle < _autoEndAngle || _angle < _autoStartAngle)
                    _angle = _autoStartAngle;
            }
        }
        else if(_autoStepAngle < 0){
            if(_angle < _autoEndAngle){
                if(_autoStartAngle > _autoEndAngle || _angle > _autoStartAngle)
                    _angle = _autoStartAngle;
            }
        }
    }

    Object::draw();
}

void Laser::handleCmd(string cmd, bool state){
    if(cmd == "turn_on")
        _isOn = state;
}
