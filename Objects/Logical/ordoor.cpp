#include "ordoor.h"

OrDoor::OrDoor(string name, b2Vec2 pos) : Object(name, pos){
    _type = OBJECT_TYPE_OR_DOOR;

    _entries[0] = false;
    _entries[1] = false;
    _out = false;

    _cmdList.push_back("entry_a");
    _cmdList.push_back("entry_b");
}

OrDoor::~OrDoor(){

}

Json::Value OrDoor::getJsonData(){
    Json::Value data = Object::getJsonData();

    data["entry_a"] = _entries[0];
    data["entry_b"] = _entries[1];
    int i = 0;
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
        data["connexion"][i]["object"] = it->first->getName();
        data["connexion"][i]["cmd"]    = it->second;
        i++;
    }

    return data;
}

OrDoor* OrDoor::fromJsonData(Json::Value data, int index, string){
    string name = "ordoor_" + QString::number(index).toStdString();
    if(data.isMember("name"))
        name = data["name"].asString();

    OrDoor *t = new OrDoor(name, b2Vec2(data["position"]["x"].asDouble(), data["position"]["y"].asDouble()));

    t->setEntryA(data["entry_a"].asBool());
    t->setEntryB(data["entry_b"].asBool());
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

void OrDoor::setEntry(int index, bool b){
    if(index == 0 || index == 1){
        _entries[index] = b;
        bool oldOut = _out;
        _out = _entries[0] || _entries[1];
        if(oldOut != _out){
            notifyConnexions();
            outChanged.trigger(_out);
        }
    }
}

void OrDoor::connect(Object *obj, string cmd){
    _connected.push_back(make_pair(obj, cmd));
    obj->removed.connect(bind(&OrDoor::targetRemoved, this, _1));
    obj->handleCmd(cmd, _out);
}

void OrDoor::targetRemoved(Object *target){
    vector<pair<Object*, string>> newLinks;
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it){
        if(it->first && it->first != target)
            newLinks.push_back(*it);
    }
    _connected = newLinks;
}

void OrDoor::notifyConnexions(){
    for(vector<pair<Object*, string>>::iterator it = _connected.begin(); it != _connected.end(); ++it)
        it->first->handleCmd(it->second, _out);
}

void OrDoor::handleCmd(string cmd, bool state){
    if(cmd == "entry_a")
        setEntryA(state);
    else if(cmd == "entry_b")
        setEntryB(state);
}

void OrDoor::draw(){
    glPushMatrix();
    glTranslatef(_position.x, _position.y, 0);

    if(_out)
        glColor4f(0.0, 1.0, 0.0, 1.0);
    else
        glColor4f(1.0, 0.0, 0.0, 1.0);

    const float32 k_segments = 16.0f;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;
    glBegin(GL_POLYGON);
    for (int32 i = 0; i < k_segments; ++i)
    {
        b2Vec2 v = (1.0 / 2) * b2Vec2(cosf(theta), sinf(theta));
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

