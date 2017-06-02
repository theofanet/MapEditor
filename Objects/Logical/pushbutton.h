#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "Objects/object.h"

class PushButton : public Object{
public:
    PushButton(string name, b2Vec2 pos);
    ~PushButton();

    Json::Value getJsonData();
    static PushButton* fromJsonData(Json::Value data, int index, string basefilepath);

    void connect(Object *obj, string cmd);
    vector<pair<Object*, string>> getConnexions(){ return _connected; }

    void push();

    void draw();

    void handleCmd(string cmd, bool state);

    void addConnexionToCreate(pair<string, string> co){ _connexionToCreate.push_back(co); }
    vector<pair<string, string>> getConnexionsToCreate(){ return _connexionToCreate; }

public slots:
    void targetRemoved(Object *target);

protected:
    vector<pair<Object*, string>> _connected;
    vector<pair<string, string>> _connexionToCreate;

    Image *_img;
};

#endif // PUSHBUTTON_H
