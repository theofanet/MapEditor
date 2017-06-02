#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <QWidget>
#include <iostream>
#include "Render/sprite.h"
#include "Utilities/defines.h"
#include "Utilities/Listener.h"

#include "Utilities/json/json.h"
#include "Utilities/json.h"

class Object{
public:
    enum ObjectType {
        OBJECT_TYPE_NONE = 0,
        OBJECT_TYPE_LASER,
        OBJECT_TYPE_JETON,
        OBJECT_TYPE_EMITTER,
        OBJECT_TYPE_SWITCH,
        OBJECT_TYPE_AND_DOOR,
        OBJECT_TYPE_OR_DOOR,
        OBJECT_TYPE_NO_DOOR,
        OBJECT_TYPE_PLATFORM,
        OBJECT_TYPE_PUSH_BUTTON
    };

    Object(string name, b2Vec2 pos);
    virtual ~Object();

    void setPosition(b2Vec2 pos){ _position = pos; }
    b2Vec2 getPosition(){ return _position; }

    virtual BBox getRectBox();
    void setMouseOver(bool over){ _mouseOver = over; }
    bool isMouseOver(){ return _mouseOver; }
    virtual bool checkIfMouseOver(b2Vec2 point);

    void setSelected(bool selected){ _selected = selected; }

    virtual void draw();
    virtual void update(GLfloat dt = 0.0);

    ObjectType getType(){ return _type; }

    string getName(){ return _name; }
    void setName(string name){
        string old = _name;
        _name = name;
        nameUpadted.trigger(this, old, _name);
    }

    virtual Json::Value getJsonData(){
        Json::Value data;

        data["name"] = _name;
        data["type"] = _type;
        data["position"]["x"] = _position.x;
        data["position"]["y"] = _position.y;

        return data;
    }

    static Object* fromJsonData(Json::Value data, int index, string){
        string name = "unknow_" + QString::number(index).toStdString();
        if(data.isMember("name"))
            name = data["name"].asString();

        b2Vec2 pos = b2Vec2(0.0, 0.0);
        if(data.isMember("position"))
            pos = b2Vec2(data["position"]["x"].asDouble(), data["position"]["y"].asDouble());

        Object* o = new Object(name, pos);
        return o;
    }

    virtual void handleCmd(string cmd, bool state);
    vector<string> getCmdList(){ return _cmdList; }

    vector<pair<string, string>> getFilesToCopy(){ return _filesToCopy; }

signals:
    Signal<void(Object* , string, string)> nameUpadted;
    Signal<void(Object*)> removed;

protected:
    b2Vec2 _position;
    b2Vec2 _dim;

    ObjectType _type;

    GLfloat _selectionColor[3];

    vector<string> _cmdList;
    vector<pair<string, string>> _filesToCopy;

    bool _mouseOver, _selected;
    string _name;
};

#endif // OBJECT_H
