#include "switch.h"

Switch::Switch(string name, b2Vec2 pos) : Object(name, pos){
    _state = false;

    _type = OBJECT_TYPE_SWITCH;

    _img = new Image(imagesDirPath() + "Switch.png");
    _img->setDrawSize(b2Vec2(2, 2));

    _cmdList.push_back("turn_on");
}

Switch::~Switch(){
    delete_obj(_img);
}

Json::Value Switch::getJsonData(){
    Json::Value data = Object::getJsonData();

    data["state"] = _state;
    int i = 0;
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
        data["connexion"][i]["object"] = it->first->getName();
        data["connexion"][i]["cmd"]    = it->second;
        i++;
    }

    return data;
}

Switch* Switch::fromJsonData(Json::Value data, int index, string){
    string name = "switch_" + QString::number(index).toStdString();
    if(data.isMember("name"))
        name = data["name"].asString();

    Switch *t = new Switch(name, b2Vec2(data["position"]["x"].asDouble(), data["position"]["y"].asDouble()));

    t->setState(data["state"].asBool());
    if(data.isMember("connexion")){
        //_connexionToCreate
        int i = 0;
        Json::Value tdata = data["connexion"][i++];
        while ( !tdata.isNull() ) {
            t->addConnexionToCreate(make_pair(tdata["object"].asString(), tdata["cmd"].asString()));
            tdata = data["connexion"][i++];
        }
    }

    return t;
}

void Switch::connect(Object *obj, string cmd){
    _connected.push_back(make_pair(obj, cmd));
    obj->removed.connect(bind(&Switch::targetRemoved, this, _1));
    obj->handleCmd(cmd, _state);
}

void Switch::clicked(){
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
        it->first->handleCmd(it->second, _state);
    }
}

void Switch::targetRemoved(Object *target){
    vector<pair<Object*, string>> newLinks;
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
        if(it->first && it->first != target)
            newLinks.push_back(*it);
    }
    _connected = newLinks;
}

void Switch::draw(){
    if(_state)
        _img->setColor(0.0, 1.0, 0.0f);
    else
        _img->setColor(1.0, 0.0, 0.0);

    _img->setPosition(_position);
    _img->draw();

    Object::draw();

    if(_selected){
        for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
            if(it->first){
                glLineWidth(3.0);
                if(_state)
                    glColor4f(0.0, 1.0, 0.0, 1.0);
                else
                    glColor4f(1.0, 0.0, 0.0, 1.0);
                glLineStipple(1, 0xFF0F);
                glEnable(GL_LINE_STIPPLE);
                glBegin(GL_LINES);
                glVertex2f(_position.x, _position.y);
                glVertex2f(it->first->getPosition().x, it->first->getPosition().y);
                glEnd();
                glLineWidth(1.0);
                glDisable(GL_LINE_STIPPLE);
            }
        }
    }
}

void Switch::handleCmd(string cmd, bool state){
    if(cmd == "turn_on"){
        _state = state;
        clicked();
    }
}
