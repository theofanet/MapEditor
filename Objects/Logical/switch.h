#ifndef SWITCH_H
#define SWITCH_H

#include "Utilities/defines.h"
#include "Utilities/Listener.h"

#include "Objects/object.h"

class Switch : public Object{
public:
    Switch(string name, b2Vec2 pos);
    ~Switch();

    Json::Value getJsonData();
    static Switch* fromJsonData(Json::Value data, int index, string basefilepath);

    void connect(Object *obj, string cmd);
    vector<pair<Object*, string>> getConnexions(){ return _connected; }

    void clicked();

    bool isOn(){ return _state; }
    bool getState(){ return isOn(); }
    void setState(bool s){ _state = s; clicked(); }
    void toggle(){ _state = !_state; clicked(); }

    void draw();

    void handleCmd(string cmd, bool state);

    void addConnexionToCreate(pair<string, string> co){ _connexionToCreate.push_back(co); }
    vector<pair<string, string>> getConnexionsToCreate(){ return _connexionToCreate; }

public slots:
    void targetRemoved(Object *target);

protected:
    bool _state;

    vector<pair<Object*, string>> _connected;
    vector<pair<string, string>> _connexionToCreate;

    Image *_img;
};

#endif // SWITCH_H
