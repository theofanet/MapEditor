#include "nodoor.h"

NoDoor::NoDoor(string name, b2Vec2 pos) : Object(name, pos){
    _type = OBJECT_TYPE_NO_DOOR;

    _out = true;
    _in  = false;

    _cmdList.push_back("entry");
}

NoDoor::~NoDoor(){

}

Json::Value NoDoor::getJsonData(){
    Json::Value data = Object::getJsonData();

    data["in"] = _in;
    int i = 0;
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
        data["connexion"][i]["object"] = it->first->getName();
        data["connexion"][i]["cmd"]    = it->second;
        i++;
    }

    return data;
}

NoDoor* NoDoor::fromJsonData(Json::Value data, int index, string){
    string name = "nodoor_" + QString::number(index).toStdString();
    if(data.isMember("name"))
        name = data["name"].asString();

    NoDoor *t = new NoDoor(name, b2Vec2(data["position"]["x"].asDouble(), data["position"]["y"].asDouble()));

    t->setEntry(data["in"].asBool());
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

void NoDoor::setEntry(bool b){
    _in = b;
    bool oldOut = _out;
    _out = !_in;
    if(oldOut != _out){
        notifyConnexions();
        outChanged.trigger(_out);
    }
}

void NoDoor::connect(Object *obj, string cmd){
    _connected.push_back(make_pair(obj, cmd));
    obj->removed.connect(bind(&NoDoor::targetRemoved, this, _1));
    obj->handleCmd(cmd, _out);
}

void NoDoor::targetRemoved(Object *target){
    vector<pair<Object*, string>> newLinks;
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
        if(it->first && it->first != target)
            newLinks.push_back(*it);
    }
    _connected = newLinks;
}

void NoDoor::notifyConnexions(){
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it)
        it->first->handleCmd(it->second, _out);
}

void NoDoor::handleCmd(string cmd, bool state){
    if(cmd == "entry")
        setEntry(state);
}

void NoDoor::draw(){
    glPushMatrix();
    glTranslatef(_position.x, _position.y + 0.5, 0);

    if(_out)
        glColor4f(0.0, 1.0, 0.0, 1.0);
    else
        glColor4f(1.0, 0.0, 0.0, 1.0);

    glBegin(GL_QUADS);
    glVertex2f(-0.15, -0.5);
    glVertex2f(-0.15, 0.5);
    glVertex2f(0.15, 0.5);
    glVertex2f(0.15, -0.5);
    glEnd();

    glTranslatef(0, -1.25, 0);

    const float32 k_segments = 16.0f;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;
    glBegin(GL_POLYGON);
    for (int32 i = 0; i < k_segments; ++i)
    {
        b2Vec2 v = (0.5 / 2) * b2Vec2(cosf(theta), sinf(theta));
        glVertex2f(v.x, v.y);
        theta += k_increment;
    }
    glEnd();

    glPopMatrix();

    Object::draw();

    if(_selected){
        for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
            glLineWidth(3.0);
            if(_out)
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
