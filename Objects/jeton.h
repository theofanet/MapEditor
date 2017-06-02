#ifndef JETON_H
#define JETON_H

#include "object.h"

class Jeton : public Object{
public:
    Jeton(string name, b2Vec2 _position);
    ~Jeton();

    void update(GLfloat dt);
    void draw();

    static Jeton* fromJsonData(Json::Value data, int index, string){
        string name = "jeton_" + QString::number(index).toStdString();
        if(data.isMember("name"))
            name = data["name"].asString();

        b2Vec2 pos = b2Vec2(0.0, 0.0);
        if(data.isMember("position"))
            pos = b2Vec2(data["position"]["x"].asDouble(), data["position"]["y"].asDouble());

        Jeton* o = new Jeton(name, pos);
        return o;
    }

protected:
    Sprite *_sprite;
};


#endif // JETON_H
