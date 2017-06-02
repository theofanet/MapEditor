#ifndef MAP_H
#define MAP_H

#include <QWidget>

#include <stdio.h>
#include <string>

#include "Utilities/defines.h"
#include "Render/sprite.h"
#include "maptile.h"
#include "Objects/checkpoint.h"
#include "Objects/laser.h"
#include "Objects/jeton.h"
#include "Objects/ParticleEmitter.h"
#include "Objects/platform.h"
#include "Objects/Logical/switch.h"
#include "Objects/Logical/pushbutton.h"
#include "Objects/Logical/anddoor.h"
#include "Objects/Logical/ordoor.h"
#include "Objects/Logical/nodoor.h"

#define NB_CASE_UP    14
#define NB_CASE_RIGHT 18

#define NB_BORDER_UP    36
#define NB_BORDER_RIGHT 36

using namespace std;

class Map : public QWidget{
    Q_OBJECT
public:
    Map(QString name, int w, int h);
    ~Map();

    int addTileset(QString filename, int w, int h){
        Sprite* t = new Sprite(filename, w, h);
        t->setDrawSize(2, 2);
        _tileSets.push_back(t);
        return _tileSets.size()-1;
    }
    int loadTileset(QString filename, int w, int h){ return addTileset(filename, w, h); }
    void setSize(b2Vec2 s){ _size = s; }
    void setSize(GLfloat w, GLfloat h){ _size = b2Vec2(w, h); }
    void setDrawBorders(bool d){ _draw_borders = d; }
    void toggleDrawBorders(){ _draw_borders = !_draw_borders; }
    void setCursorPosition(b2Vec2 pos);
    void setSelectedTileRow(int r){ _selectedTileRow = r; }
    void setSelectedTileCell(int c){ _selectedTileCell = c; }
    void setSelectedTilesetIndex(size_t i){ ((i < _tileSets.size()) ? _selectedTilesetIndex = i : _selectedTilesetIndex = 0); }

    b2Vec2 getSize(){ return _size; }
    Sprite* getTileset(size_t i = 0){ return ((i < _tileSets.size()) ? _tileSets.at(i) : NULL); }
    QString getName(){ return _name; }
    map<pair<int, int>, MapTile*> getTiles(int index = 1){ return _tiles[index]; }
    map<pair<int, int>, Checkpoint*> getCheckpoints(){ return _checkpoints; }

    void draw();
    void update(GLfloat dt);

    void setEditionMode(editionMode m);
    editionMode getEditionMode(){ return _editionMode; }

    void cursorClicked(b2Vec2 pos, bool pressed, bool rightClick = false);
    void addSelectedTileAtPosition();
    void paintBrushSelectedTileFromPosition();
    void addRecursivePaintBrushAtPosition(b2Vec2 position, MapTile *toReplace = NULL);
    void addFlagAtPosition();
    void removeFlagAtPosition();
    void addTile(MapTile *t, int layer = 1);
    void addCheckpoint(Checkpoint *t);

    void setLayerIndex(int index);

    MapTile *getTileAtClickedPosition();
    void setSelectedTile(MapTile *t);

    void toggleFrontLayer(){ _showFrontLayer = !_showFrontLayer; }
    void toggleBackLayer(){ _showBackLayer = !_showBackLayer; }
    void toggleMiddleLayer(){ _showMiddleLayer = !_showMiddleLayer; }

    void showFrontLayer(bool s){ _showFrontLayer = s; }
    void showBackLayer(bool s){ _showBackLayer = s; }
    void showMiddleLayer(bool s){ _showMiddleLayer = s; }

    bool showingMiddleLayer(){ return _showMiddleLayer; }
    bool showingFrontLayer(){ return _showFrontLayer; }
    bool showingBackLayer(){ return _showBackLayer; }

    int getNbObjectSelected(){ return _nbSelected; }

    void resetTilesSelection();
    vector<MapTile*> getSelectedTiles(){ return _selectedTiles; }

    void setStartPosition(b2Vec2 pos){ _startPosition = pos; }
    b2Vec2 getStartPosition(){ return _startPosition; }

    void setEndPosition(b2Vec2 pos){ _endPosition = pos; }
    b2Vec2 getEndPosition(){ return _endPosition; }

    vector<Sprite *> getTilsets(){ return _tileSets; }

    void setDrawPosition(b2Vec2 pos, GLfloat zoom = 1.0f){ _drawPosition = pos; _drawZoom = zoom; }

    GLfloat getBackgroundColor(int index){
        if(index >= 0 && index <= 2)
            return _backgroundColor[index];
        return 0.0f;
    }

    void setBackgroundColor(int index, GLfloat c){
        if(index >= 0 && index <= 2)
            _backgroundColor[index] = c;
    }

    std::map<string, Object*> getObjects(){ return _objects; }
    void addObject(Object *obj){
        _nbObjectType[obj->getType()]++;
        _objects[obj->getName()] = obj;
    }
    void removeObject(Object *obj){ removeObject(obj->getName()); }
    void removeObject(string name);
    Object* getObject(string name);
    int getNbObjectOfType(int type){
        if(type < 100 && type >= 0)
            return _nbObjectType[type];
        return 0;
    }

    void addFileToCopy(pair<string, string> c){ _filesToCopy.push_back(c); }
    void addFileToCopy(string from, string to){ addFileToCopy(make_pair(from, to)); }
    vector<pair<string, string>> getFilesToCopy(){ return _filesToCopy; }

signals:
    void laserSelected(Laser *laser);
    void emitterSelected(ParticleEmitter *p);
    void objectSelected(Object *obj);
    void switchTargetSelected(Object *obj);
    void pushButtonTargetSelected(Object *obj);
    void andDoorTargetSelected(Object *obj);
    void orDoorTargetSelected(Object *obj);
    void noDoorTargetSelected(Object *obj);
    void platformPointAdded(b2Vec2 p);

public slots:
    void objectNameUpdated(Object *obj, string oldName, string newName);

protected:
    QString _name;
    b2Vec2  _size, _realSize, _cursorPosition, _selectionPosition, _lastPositionAdded, _lastPositionRemoved;
    b2Vec2  _selectionModeStartPosition, _selectionModeEndPosition;
    b2Vec2  _startPosition, _endPosition;
    b2Vec2  _drawPosition;
    GLfloat _drawZoom;

    GLfloat _backgroundColor[3];

    vector<Sprite *> _tileSets;
    size_t _selectedTilesetIndex;

    bool    _draw_borders, _addingMode, _selectionMode, _eraseMode;
    int     _selectedTileRow, _selectedTileCell;

    map<pair<int, int>, MapTile*>    _tiles[3];
    map<pair<int, int>, Checkpoint*> _checkpoints;

    editionMode _editionMode;

    Checkpoint *_flagIcon;
    Image      *_startImg, *_endImg;

    MapTile *_selectedTile;
    vector<MapTile*> _selectedTiles;

    ParticleEmitter *_addingParticule;
    Jeton           *_addingJeton;
    Laser           *_addingLaser;
    Switch          *_addingSwitch;
    PushButton      *_addingPushButton;
    AndDoor         *_addingAndDoor;
    OrDoor          *_addingOrDoor;
    NoDoor          *_addingNoDoor;
    Platform        *_addingPlatform;

    Object *_overObject, *_selectedObject;
    std::map<string, Object*> _objects;
    int     _nbObjectType[100];

    vector<pair<string, string>> _filesToCopy;

    bool _showBackLayer, _showMiddleLayer, _showFrontLayer;
    int _layerIndex, _nbSelected;
};

#endif // MAP_H
