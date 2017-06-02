#ifndef MAPJSONDATA_H
#define MAPJSONDATA_H

#include <stdio.h>
#include <iostream>
#include <istream>
#include <fstream>

#include "map.h"
#include "json/json.h"
#include "json.h"

using namespace std;

struct SpriteJsonData{
    SpriteJsonData(string file, GLfloat w, GLfloat h){
        _spritefilename  = file;
        _spriteRowWidth  = w;
        _spriteRowHeight = h;
    }

    Json::Value toJsonValue(){
        Json::Value data;

        data["spriteFileName"] = _spritefilename;
        data["spriteRowWidth"] = _spriteRowWidth;
        data["spriteRowHeight"] = _spriteRowHeight;

        return data;
    }

    string _spritefilename;
    GLfloat _spriteRowWidth, _spriteRowHeight;
};

struct MapCheckpointJsonData{
    MapCheckpointJsonData(Checkpoint *t = NULL){
        if(t)
            _position = t->getPosition();
    }

    Json::Value toJsonValue(){
        Json::Value data;

        data["position"]["x"]   = _position.x;
        data["position"]["y"]   = _position.y;

        return data;
    }

    b2Vec2 _position;
};

struct MapTileJsonData{
    MapTileJsonData(MapTile *t = NULL){
        if(t){
            _is_destructible = t->isDestructible();
            _is_climbable    = t->isClimbable();
            _is_slippery     = t->isSlippery();
            _is_deadly       = t->isDeadly();
            _tileRow  = t->getTileRow();
            _tileCell = t->getTileCell();
            _position = t->getBasePosition();
            _horizontalMove = t->getHorizontalMove();
            _horizontalMoveSpeed = t->getHorizontalMoveSpeed();
            _horizontalMoveMax   = t->getHorizontalMoveMax();
            _tilesetIndex = t->getTilesetIndex();

            for(size_t i = 0; i < t->getPoints().size(); i++)
                _points.push_back(t->getPoints().at(i));
        }
    }

    Json::Value toJsonValue(){
        Json::Value data;

        data["is_destructible"] = _is_destructible;
        data["is_climbable"]    = _is_climbable;
        data["is_slippery"]     = _is_slippery;
        data["is_deadly"]       = _is_deadly;
        data["tileRow"]         = _tileRow;
        data["tileCell"]        = _tileCell;
        data["position"]["x"]   = _position.x;
        data["position"]["y"]   = _position.y;
        data["horizontalMove"]  = _horizontalMove;
        data["horizontalMoveSpeed"] = _horizontalMoveSpeed;
        data["horizontalMoveMax"]   = _horizontalMoveMax;
        data["index"]               = _tilesetIndex;

        for(size_t i = 0; i < _points.size(); i++){
            data["points"][(int)i]["x"] = _points.at(i).x;
            data["points"][(int)i]["y"] = _points.at(i).y;
        }

        return data;
    }

    bool   _is_destructible, _is_climbable, _is_slippery, _is_deadly;
    bool   _horizontalMove;
    GLfloat _horizontalMoveSpeed, _horizontalMoveMax;
    int    _tileRow, _tileCell;
    int _tilesetIndex;
    b2Vec2 _position;
    vector<b2Vec2> _points;
};

class MapJsonData{
public:
    MapJsonData(Map *map = NULL);

    void saveToFile(string filename);
    void loadFromFile(string filename);

    Map *getMap(){ return _map; }

    Json::Value toJsonValue(){
        Json::Value data;

        data["name"] = _name;
        data["start"]["x"] = _startPosition.x;
        data["start"]["y"] = _startPosition.y;
        data["end"]["x"] = _endPosition.x;
        data["end"]["y"] = _endPosition.y;
        data["size"]["x"] = _size.x;
        data["size"]["y"] = _size.y;
        data["backgroundColor"]["r"] = _backgroundColor[0];
        data["backgroundColor"]["g"] = _backgroundColor[1];
        data["backgroundColor"]["b"] = _backgroundColor[2];

        for(int l = 0; l < 3; l++){
            for(size_t i = 0; i < _tiles[l].size(); i++)
                data["tiles"][l][(int)i] = _tiles[l].at(i).toJsonValue();
        }

        for(size_t i = 0; i < _checkpoints.size(); i++)
            data["checkpoints"][(int)i] = _checkpoints.at(i).toJsonValue();

        for(size_t i = 0; i < _tilesets.size(); i++)
            data["sprites"][(int)i] = _tilesets.at(i).toJsonValue();

        size_t i = 0;
        for(std::map<string, Object*>::iterator it = _objects.begin(); it != _objects.end(); ++it){
            if(it->second){
                data["objects"][(int)i] = ObjectToJson(it->second);

                vector<pair<string, string>> filesToCopy = it->second->getFilesToCopy();
                if(filesToCopy.size()){
                    for(vector<pair<string, string>>::iterator iter = filesToCopy.begin(); iter != filesToCopy.end(); ++iter)
                        _map->addFileToCopy(*iter);
                }

                i++;
            }
        }

        return data;
    }

    void fromJsonValue(Json::Value data);

    Json::Value ObjectToJson(Object *obj){
        Json::Value data;

        if(obj){
            switch(obj->getType()){
            case Object::OBJECT_TYPE_LASER:
                data = static_cast<Laser *>(obj)->getJsonData();
                break;
            case Object::OBJECT_TYPE_JETON:
                data = static_cast<Jeton *>(obj)->getJsonData();
                break;
            case Object::OBJECT_TYPE_EMITTER:
                data = static_cast<ParticleEmitter *>(obj)->getJsonData();
                break;
            case Object::OBJECT_TYPE_SWITCH:
                data = static_cast<Switch *>(obj)->getJsonData();
                break;
            case Object::OBJECT_TYPE_AND_DOOR:
                data = static_cast<AndDoor *>(obj)->getJsonData();
                break;
            case Object::OBJECT_TYPE_OR_DOOR:
                data = static_cast<OrDoor *>(obj)->getJsonData();
                break;
            case Object::OBJECT_TYPE_NO_DOOR:
                data = static_cast<NoDoor *>(obj)->getJsonData();
                break;
            case Object::OBJECT_TYPE_PLATFORM:
                data = static_cast<Platform *>(obj)->getJsonData();
                break;
            case Object::OBJECT_TYPE_PUSH_BUTTON:
                data = static_cast<PushButton *>(obj)->getJsonData();
                break;
            default:
                break;
            }
        }

        return data;
    }



private:
    Map    *_map;

    string  _name;
    b2Vec2  _size, _startPosition, _endPosition;

    GLfloat _backgroundColor[3];

    vector<MapTileJsonData> _tiles[3];
    vector<MapCheckpointJsonData> _checkpoints;
    vector<SpriteJsonData> _tilesets;
    std::map<string, Object*> _objects;

    string _filename;
};

#endif // MAPJSONDATA_H
