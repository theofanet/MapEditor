#ifndef NODOOR_H
#define NODOOR_H

#include "Objects/object.h"

class NoDoor : public Object{
public:
    NoDoor(string name, b2Vec2 pos);
    ~NoDoor();

    Json::Value getJsonData();
    static NoDoor* fromJsonData(Json::Value data, int index, string basefilepath);

    void setEntry(bool b);
    bool getEntry(){ return _in; }
    bool getOut(){ return _out; }

    void connect(Object *obj, string cmd);
    vector<pair<Object*, string>> getConnexions(){ return _connected; }
    void notifyConnexions();

    void handleCmd(string cmd, bool state);

    void draw();

    void addConnexionToCreate(pair<string, string> co){ _connexionToCreate.push_back(co); }
    vector<pair<string, string>> getConnexionsToCreate(){ return _connexionToCreate; }

signals:
    Signal<void(bool)> outChanged;

public slots:
    void targetRemoved(Object *target);

protected:
    bool _out, _in;

    vector<pair<Object*, string>> _connected;
    vector<pair<string, string>> _connexionToCreate;
};

#endif // NODOOR_H
