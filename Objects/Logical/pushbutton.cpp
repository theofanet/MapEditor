#include "pushbutton.h"

PushButton::PushButton(string name, b2Vec2 pos) : Object(name, pos){
    _type = OBJECT_TYPE_PUSH_BUTTON;

    _img = new Image(imagesDirPath() + "PushButton.png");
    _img->setDrawSize(b2Vec2(2, 2));

    _cmdList.push_back("push");
}

PushButton::~PushButton(){
    delete_obj(_img);
}

Json::Value PushButton::getJsonData(){
    Json::Value data = Object::getJsonData();

    int i = 0;
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
        data["connexion"][i]["object"] = it->first->getName();
        data["connexion"][i]["cmd"]    = it->second;
        i++;
    }

    return data;
}

PushButton* PushButton::fromJsonData(Json::Value data, int index, string){
    string name = "switch_" + QString::number(index).toStdString();
    if(data.isMember("name"))
        name = data["name"].asString();

    PushButton *t = new PushButton(name, b2Vec2(data["position"]["x"].asDouble(), data["position"]["y"].asDouble()));

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

void PushButton::connect(Object *obj, string cmd){
    _connected.push_back(make_pair(obj, cmd));
    obj->removed.connect(bind(&PushButton::targetRemoved, this, _1));
}

void PushButton::push(){
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it)
        it->first->handleCmd(it->second, 1);
}

void PushButton::targetRemoved(Object *target){
    vector<pair<Object*, string>> newLinks;
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
        if(it->first && it->first != target)
            newLinks.push_back(*it);
    }
    _connected = newLinks;
}

void PushButton::draw(){
    _img->setColor(1.0, 1.0, 1.0);
    _img->setPosition(_position);
    _img->draw();

    Object::draw();

    if(_selected){
        for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
            glLineWidth(3.0);
            glColor4f(1.0, 1.0, 1.0, 1.0);
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

void PushButton::handleCmd(string cmd, bool){
    if(cmd == "push"){
        push();
    }
}
