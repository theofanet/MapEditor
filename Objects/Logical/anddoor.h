#ifndef ANDDOOR_H
#define ANDDOOR_H

#include "Objects/object.h"


class AndDoor : public Object{
public:
    AndDoor(string name, b2Vec2 pos);
    ~AndDoor();

    Json::Value getJsonData();
    static AndDoor* fromJsonData(Json::Value data, int index, string basefilepath);

    void setEntry(int index, bool b);
    void setEntryA(bool b){ setEntry(0, b); }
    void setEntryB(bool b){ setEntry(1, b); }

    bool getEntryA(){ return _entries[0]; }
    bool getEntryB(){ return _entries[1]; }
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
    bool _entries[2];
    bool _out;

    vector<pair<Object*, string>> _connected;
    vector<pair<string, string>> _connexionToCreate;
};

#endif // ANDDOOR_H
