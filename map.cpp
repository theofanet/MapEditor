#include "map.h"


Map::Map(QString name, int w, int h){
    _size  = b2Vec2(w, h);
    _realSize = 2 * b2Vec2(_size.x, _size.y);
    _name  = name;
    _draw_borders = true;
    _cursorPosition = b2Vec2();
    _selectedTileCell = 0;
    _selectedTileRow  = 0;
    _selectedTilesetIndex = 0;
    _selectedTile = NULL;
    _lastPositionAdded = b2Vec2(-1, -1);
    _addingMode = false;
    _eraseMode = false;

    _showBackLayer   = true;
    _showFrontLayer  = true;
    _showMiddleLayer = true;
    _selectionMode   = false;

    _startPosition = b2Vec2(0, 0);
    _endPosition = b2Vec2(_realSize.x - 2, _realSize.y - 2);

    _selectionModeStartPosition = b2Vec2();
    _selectionModeEndPosition   = b2Vec2();

    _layerIndex = 1;
    _nbSelected = 0;

    _editionMode = EDIT_MODE_ADD_TILE;

    _flagIcon = new Checkpoint();

    _startImg = new Image(imagesDirPath()+"Start_Item.png");
    _startImg->setScale(0.02);

    _endImg = new Image(imagesDirPath()+"EndItem.png");
    _endImg->setScale(0.02);

    for(int l = 0; l < 3; l++){
        for(int r = 0; r < _realSize.y; r++){
            for(int c = 0; c < _realSize.x; c++)
                _tiles[l][make_pair(c,r)] = NULL;
        }
    }

    _addingLaser = new Laser("laser_0", b2Vec2(10, 10), 5.0f);
    _addingLaser->setColor(0.90588235294118f, 0.29803921568627f, 0.23529411764706f);

    _addingJeton = new Jeton("jeton_0", b2Vec2(0.0, 0.0));

    _addingParticule = new ParticleEmitter("emitter_0", b2Vec2(10, 10), -90);
    _addingParticule->setAndleDist(0);
    _addingParticule->setSpeed(10.0);
    _addingParticule->setSize(1.0f);
    _addingParticule->lunch(500);

    _addingPlatform = new Platform("platform_0", b2Vec2(0, 0));

    _addingSwitch = new Switch("switch_0", b2Vec2(0, 0));
    _addingPushButton = new PushButton("pushbutton_0", b2Vec2(0, 0));
    _addingAndDoor = new AndDoor("anddoor_0", b2Vec2(0, 0));
    _addingOrDoor = new OrDoor("ordoor_0", b2Vec2(0, 0));
    _addingNoDoor = new NoDoor("nodoor_0", b2Vec2(0, 0));

    _backgroundColor[0] = 0.2;
    _backgroundColor[1] = 0.2;
    _backgroundColor[2] = 0.2;

    _selectedObject = NULL;
    _overObject     = NULL;

    for(int i = 0; i < 100; i++)
        _nbObjectType[i] = 0;
}

Map::~Map(){
    for(size_t i = 0; i < _tileSets.size(); i++)
        delete_obj(_tileSets.at(i));

    for(int l = 0; l < 3; l++){
        for(int r = 0; r < _size.y; r++){
            for(int c = 0; c < _size.x; c++)
                delete_obj(_tiles[l][make_pair(c,r)]);
        }
    }

    delete_obj(_flagIcon);
    delete_obj(_startImg);
    delete_obj(_endImg);
    delete_obj(_addingLaser);
    delete_obj(_addingJeton);
    delete_obj(_addingParticule);
    delete_obj(_addingPushButton);
    delete_obj(_addingSwitch);
    delete_obj(_addingAndDoor);
    delete_obj(_addingOrDoor);
    delete_obj(_addingNoDoor);

    for(map<string, Object*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
        delete_obj(it->second);
}

void Map::draw(){
    glPushMatrix();
    glScaled(2, 2, 2);

    int width  = (NB_BORDER_RIGHT)/_drawZoom;
    int height = (NB_BORDER_UP)/_drawZoom;

    if(_draw_borders){
        for(size_t x = max(0.0f, _drawPosition.x/2 - width); x < min(_size.x + 1, _drawPosition.x/2 + width); x += 1){
            glPushMatrix();

            glTranslatef(x - 0.5f, max(-0.5f, _drawPosition.y/2 - height), 0);

            glColor3f(1, 1, 1);

            glBegin(GL_LINES);
            glVertex2f(0, 0);
            glVertex2f(0, min(_size.y, (float)height*2));
            glEnd();

            glPopMatrix();
        }

        for(size_t y = max(0.0f, _drawPosition.y/2 - height); y < min(_size.y + 1, _drawPosition.y/2 + height); y += 1){
            glPushMatrix();

            glTranslatef(max(-0.5f, _drawPosition.x/2 - width), y - 0.5f, 0);

            glColor3f(1, 1, 1);

            glBegin(GL_LINES);
            glVertex2f(0, 0);
            glVertex2f(min(_size.x, (float)width*2), 0);
            glEnd();

            glPopMatrix();
        }
    }

    glPopMatrix();

    width  = (NB_CASE_RIGHT*2)/_drawZoom;
    height = (NB_CASE_UP*2)/_drawZoom;

    //Back
    if(_showBackLayer){
        for(int r = _drawPosition.x - width; r < _drawPosition.x + width; r++){
            for(int c = _drawPosition.y - height; c < _drawPosition.y + height; c++){
                MapTile *t = _tiles[0][make_pair(r, c)];
                if(t)
                    t->draw();
            }
        }
    }

    //Middle
    if(_showMiddleLayer){
        for(int r = _drawPosition.x - width; r < _drawPosition.x + width; r++){
            for(int c = _drawPosition.y - height; c < _drawPosition.y + height; c++){
                MapTile *t = _tiles[1][make_pair(r, c)];
                if(t && t != _selectedTile)
                    t->draw();
            }
        }

        for(int r = _drawPosition.x - width; r < _drawPosition.x + width; r++){
            for(int c = _drawPosition.y - height; c < _drawPosition.y + height; c++){
                Checkpoint *t = _checkpoints[make_pair(r, c)];
                if(t)
                    t->draw();
            }
        }

        if(_selectedTile)
            _selectedTile->draw();
    }

    for(map<string, Object*>::iterator it = _objects.begin(); it != _objects.end(); ++it){
        if(it->second)
            it->second->draw();
    }

    _startImg->setPosition(_startPosition);
    _startImg->draw();

    _endImg->setPosition(_endPosition);
    _endImg->draw();

    if(_tileSets.size()){
        if((_editionMode == EDIT_MODE_ADD_TILE || _editionMode == EDIT_MODE_ADD_PAINT_BUCKET_TILE) && _selectedTilesetIndex < _tileSets.size()){
            _tileSets.at(_selectedTilesetIndex)->setRow(_selectedTileRow);
            _tileSets.at(_selectedTilesetIndex)->setCell(_selectedTileCell);
            _tileSets.at(_selectedTilesetIndex)->draw(_selectionPosition.x, _selectionPosition.y);
        }
    }

    if(_editionMode == EDIT_MODE_FLAG){
        _flagIcon->setPosition(_selectionPosition.x, _selectionPosition.y);
        _flagIcon->draw();
    }
    else if(_editionMode == EDIT_MODE_START_POSITION){
        _startImg->setPosition(_selectionPosition.x, _selectionPosition.y);
        _startImg->draw();
    }
    else if(_editionMode == EDIT_MODE_END_POSITION){
        _endImg->setPosition(_selectionPosition.x, _selectionPosition.y);
        _endImg->draw();
    }
    else if(_editionMode == EDIT_MODE_ADD_LASER)
        _addingLaser->draw();
    else if(_editionMode == EDIT_MODE_ADD_JETON)
        _addingJeton->draw();
    else if(_editionMode == EDIT_MODE_ADD_EMITTER)
        _addingParticule->draw();
    else if(_editionMode == EDIT_MODE_ADD_SWITCH)
        _addingSwitch->draw();
    else if(_editionMode == EDIT_MODE_ADD_AND_DOOR)
        _addingAndDoor->draw();
    else if(_editionMode == EDIT_MODE_ADD_OR_DOOR)
        _addingOrDoor->draw();
    else if(_editionMode == EDIT_MODE_ADD_NO_DOOR)
        _addingNoDoor->draw();
    else if(_editionMode == EDIT_MODE_ADD_PLATFORM)
        _addingPlatform->draw();
    else if(_editionMode == EDIT_MODE_ADD_PUSH_BUTTON)
        _addingPushButton->draw();
    else if(_editionMode == EDIT_MODE_SELECTION_TILE && _selectionMode){
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(1, 0.7, 0, 0.1);
        // Draw a textured quad
        glBegin(GL_QUADS);
        glVertex2f(_selectionModeStartPosition.x, _selectionModeStartPosition.y);
        glVertex2f(_selectionModeStartPosition.x, _selectionModeEndPosition.y);
        glVertex2f(_selectionModeEndPosition.x, _selectionModeEndPosition.y);
        glVertex2f(_selectionModeEndPosition.x, _selectionModeStartPosition.y);
        glEnd();

        glLineWidth(3.0);
        glColor4f(1, 0.7, 0, 1);
        glLineStipple(1, 0xFF0F);
        glEnable(GL_LINE_STIPPLE);
        // Draw a textured quad
        glBegin(GL_LINE_LOOP);
        glVertex2f(_selectionModeStartPosition.x, _selectionModeStartPosition.y);
        glVertex2f(_selectionModeStartPosition.x, _selectionModeEndPosition.y);
        glVertex2f(_selectionModeEndPosition.x, _selectionModeEndPosition.y);
        glVertex2f(_selectionModeEndPosition.x, _selectionModeStartPosition.y);
        glEnd();
        glLineWidth(1.0);
        glDisable(GL_LINE_STIPPLE);

        glDisable(GL_BLEND);
    }
    else if(_editionMode == EDIT_MODE_SWITCH_SELECT_TARGET || _editionMode == EDIT_MODE_AND_DOOR_SELECT_TARGET
            || _editionMode == EDIT_MODE_OR_DOOR_SELECT_TARGET || _editionMode == EDIT_MODE_NO_DOOR_SELECT_TARGET
            || _editionMode == EDIT_MODE_PUSH_BUTTON_SELECT_TARGET){
        glLineWidth(3.0);
        if(_overObject)
            glColor3f(0.0f, 1.0f, 0.0f);
        else
            glColor3f(1, 0.7, 0);
        glLineStipple(1, 0xFF0F);
        glEnable(GL_LINE_STIPPLE);
        // Draw a textured quad
        glBegin(GL_LINES);
        glVertex2f(_selectedObject->getPosition().x, _selectedObject->getPosition().y);
        glVertex2f(_cursorPosition.x, _cursorPosition.y);
        glEnd();
        glLineWidth(1.0);
        glDisable(GL_LINE_STIPPLE);
    }
    else if(_editionMode == EDIT_MODE_PLATFORM_ADD_POINT){
        Platform *p = static_cast<Platform *>(_selectedObject);
        p->drawAddingPoint(_cursorPosition);
    }

    //Front
    if(_showFrontLayer){
        for(int r = _drawPosition.x - width; r < _drawPosition.x + width; r++){
            for(int c = _drawPosition.y - height; c < _drawPosition.y + height; c++){
                MapTile *t = _tiles[2][make_pair(r, c)];
                if(t)
                    t->draw();
            }
        }
    }
}

void Map::setLayerIndex(int index){
    if(index < 0)
        index = 0;
    else if(index > 2)
        index = 2;

    _layerIndex = index;
}

void Map::update(GLfloat dt){
    _selectionPosition = _cursorPosition;

    int x = floor(_cursorPosition.x);
    if(x % 2 != 0)
        x += 1;
    _selectionPosition.x = x;

    if(_selectionPosition.x < 0)
        _selectionPosition.x = 0;
    else if(_selectionPosition.x > _realSize.x - 2)
        _selectionPosition.x = _realSize.x - 2;

    int y = floor(_cursorPosition.y);
    if(y % 2 != 0)
        y += 1;
    _selectionPosition.y = y;

    if(_selectionPosition.y < 0)
        _selectionPosition.y = 0;
    else if(_selectionPosition.y > _realSize.y - 2)
        _selectionPosition.y = _realSize.y - 2;

    if(_editionMode == EDIT_MODE_ADD_LASER)
        _addingLaser->setPosition(_cursorPosition);
    else if(_editionMode == EDIT_MODE_ADD_JETON)
        _addingJeton->setPosition(_cursorPosition);
    else if(_editionMode == EDIT_MODE_ADD_EMITTER){
        _addingParticule->setPosition(_cursorPosition);
        _addingParticule->update(dt);
    }
    else if(_editionMode == EDIT_MODE_ADD_SWITCH)
        _addingSwitch->setPosition(_cursorPosition);
    else if(_editionMode == EDIT_MODE_ADD_AND_DOOR)
        _addingAndDoor->setPosition(_cursorPosition);
    else if(_editionMode == EDIT_MODE_ADD_OR_DOOR)
        _addingOrDoor->setPosition(_cursorPosition);
    else if(_editionMode == EDIT_MODE_ADD_NO_DOOR)
        _addingNoDoor->setPosition(_cursorPosition);
    else if(_editionMode == EDIT_MODE_ADD_PLATFORM){
        _addingPlatform->setPosition(_cursorPosition);
        _addingPlatform->update(dt);
    }
    else if(_editionMode == EDIT_MODE_ADD_PUSH_BUTTON)
        _addingPushButton->setPosition(_cursorPosition);

    _overObject = NULL;
    for(map<string, Object*>::iterator it = _objects.begin(); it != _objects.end(); ++it){
        if(it->second)
            it->second->update(dt);

        if(_editionMode == EDIT_MODE_SELECT_OBJECT || _editionMode == EDIT_MODE_REMOVE_OBJECT || _editionMode == EDIT_MODE_SWITCH_SELECT_TARGET
                || _editionMode == EDIT_MODE_AND_DOOR_SELECT_TARGET || _editionMode == EDIT_MODE_OR_DOOR_SELECT_TARGET || _editionMode == EDIT_MODE_NO_DOOR_SELECT_TARGET
                || _editionMode == EDIT_MODE_PUSH_BUTTON_SELECT_TARGET ){
            if(it->second->checkIfMouseOver(_cursorPosition))
                _overObject = it->second;
        }
    }
}

void Map::addSelectedTileAtPosition(){
    if(_selectedTilesetIndex < _tileSets.size()){
        if(_lastPositionAdded.x != _selectionPosition.x || _lastPositionAdded.y != _selectionPosition.y){
            _lastPositionAdded = _selectionPosition;
            delete_obj(_tiles[_layerIndex][make_pair(_selectionPosition.x, _selectionPosition.y)]);
            MapTile *t = new MapTile(_tileSets.at(_selectedTilesetIndex), _selectedTilesetIndex);
            t->setTileRow(_selectedTileRow);
            t->setTileCell(_selectedTileCell);
            t->setPosition(_selectionPosition);
            _tiles[_layerIndex][make_pair(_selectionPosition.x, _selectionPosition.y)] = t;
        }
    }
}

void Map::addRecursivePaintBrushAtPosition(b2Vec2 position, MapTile *toReplace){
    MapTile *oldTile = _tiles[_layerIndex][make_pair(position.x, position.y)];

    int nbStep = 2;

    if((oldTile == NULL && toReplace == NULL)
            || (toReplace != NULL && oldTile != NULL
                && oldTile->getTileCell() == toReplace->getTileCell()
                && oldTile->getTileRow() == toReplace->getTileRow()
                && oldTile->getTilesetIndex() == toReplace->getTilesetIndex())){

        bool same = false;
        if(oldTile){
            if(oldTile->getTilesetIndex() == _selectedTilesetIndex){
                if(oldTile->getTileCell() == _selectedTileCell && oldTile->getTileRow() == _selectedTileRow)
                    same = true;
            }
        }

        if(!same){
            MapTile *t = new MapTile(_tileSets.at(_selectedTilesetIndex), _selectedTilesetIndex);
            t->setTileRow(_selectedTileRow);
            t->setTileCell(_selectedTileCell);
            t->setPosition(position);
            delete_obj(oldTile);
            _tiles[_layerIndex][make_pair(position.x, position.y)] = t;

            if(position.x - nbStep >= 0 && position.x - nbStep <= _realSize.x - 2)
                addRecursivePaintBrushAtPosition(b2Vec2(position.x - nbStep, position.y), toReplace);
            if(position.x + nbStep >= 0 && position.x + nbStep <= _realSize.x - 2)
                addRecursivePaintBrushAtPosition(b2Vec2(position.x + nbStep, position.y), toReplace);
            if(position.y + nbStep >= 0 && position.y + nbStep <= _realSize.y - 2)
                addRecursivePaintBrushAtPosition(b2Vec2(position.x, position.y + nbStep), toReplace);
            if(position.y - nbStep >= 0 && position.y - nbStep <= _realSize.y - 2)
                addRecursivePaintBrushAtPosition(b2Vec2(position.x, position.y - nbStep), toReplace);
        }
    }
}

void Map::paintBrushSelectedTileFromPosition(){
    if(_selectedTilesetIndex < _tileSets.size()){
        MapTile *actual = _tiles[_layerIndex][make_pair(_selectionPosition.x, _selectionPosition.y)];
        MapTile *copy   = NULL;
        if(actual)
            copy = new MapTile(*actual);

        addRecursivePaintBrushAtPosition(_selectionPosition, copy);

        delete_obj(copy);
    }
}

void Map::addFlagAtPosition(){
    delete_obj(_checkpoints[make_pair(_selectionPosition.x, _selectionPosition.y)]);
    Checkpoint *t = new Checkpoint();
    t->setPosition(_selectionPosition);
    _checkpoints[make_pair(_selectionPosition.x, _selectionPosition.y)] = t;
}

void Map::removeFlagAtPosition(){
    delete_obj(_checkpoints[make_pair(_selectionPosition.x, _selectionPosition.y)]);
}

MapTile* Map::getTileAtClickedPosition(){
    MapTile *t = _tiles[1][make_pair(_selectionPosition.x, _selectionPosition.y)];
    return t;
}

void Map::setCursorPosition(b2Vec2 pos){
    _cursorPosition = pos;

    if(_editionMode == EDIT_MODE_EDIT_TILE && _selectedTile)
        _selectedTile->setCursorPosition(_cursorPosition);
    else if(_editionMode == EDIT_MODE_ADD_TILE && _addingMode)
        addSelectedTileAtPosition();
    else if(_editionMode == EDIT_MODE_ERASE_TILE && _eraseMode)
        delete_obj(_tiles[_layerIndex][make_pair(_selectionPosition.x, _selectionPosition.y)]);
    else if(_editionMode == EDIT_MODE_SELECTION_TILE && _selectionMode){
        _selectionModeEndPosition = pos;

        b2Vec2 start, end;
        start.x = min(_selectionModeStartPosition.x, _selectionModeEndPosition.x);
        start.y = min(_selectionModeStartPosition.y, _selectionModeEndPosition.y);
        end.x   = max(_selectionModeStartPosition.x, _selectionModeEndPosition.x);
        end.y   = max(_selectionModeStartPosition.y, _selectionModeEndPosition.y);

        resetTilesSelection();
        _nbSelected = 0;
        for(int y = start.y; y < end.y; y++){
            for(int x = start.x; x < end.x; x++){
                MapTile *t = _tiles[1][make_pair(x, y)];
                if(t){
                    _nbSelected++;
                    t->setSelected(true, 1);
                    _selectedTiles.push_back(t);
                }
            }
        }
    }
}

void Map::cursorClicked(b2Vec2 pos, bool pressed, bool rightClick){
    if(!rightClick){
        if(pressed){
            if(_editionMode == EDIT_MODE_ADD_TILE){
                _addingMode = true;
                addSelectedTileAtPosition();
            }
            else if(_editionMode == EDIT_MODE_ADD_PAINT_BUCKET_TILE){
                paintBrushSelectedTileFromPosition();
            }
            else if(_editionMode == EDIT_MODE_FLAG){
                addFlagAtPosition();
            }
            else if(_editionMode == EDIT_MODE_START_POSITION){
                _startPosition = _selectionPosition;
            }
            else if(_editionMode == EDIT_MODE_END_POSITION){
                _endPosition = _selectionPosition;
            }
            else if(_editionMode == EDIT_MODE_ADD_LASER){
                Laser *laser = new Laser(QString("laser_" + QString::number(_nbObjectType[Object::OBJECT_TYPE_LASER] + 1)).toStdString(), _cursorPosition, 5.0f);
                laser->setColor(0.90588235294118f, 0.29803921568627f, 0.23529411764706f);
                addObject(laser);
            }
            else if(_editionMode == EDIT_MODE_ADD_JETON){
                Jeton *jeton = new Jeton(QString("jeton_" + QString::number(_nbObjectType[Object::OBJECT_TYPE_JETON] + 1)).toStdString(), _addingJeton->getPosition());
                addObject(jeton);
            }
            else if(_editionMode == EDIT_MODE_ADD_EMITTER){
                ParticleEmitter *e = new ParticleEmitter(QString("emitter_" + QString::number(_nbObjectType[Object::OBJECT_TYPE_EMITTER] + 1)).toStdString(), _addingParticule->getPosition(), _addingParticule->getAngle());

                e->setAndleDist(0);
                e->setSpeed(10.0);
                e->setSize(1.0f);
                e->lunch(500);

                addObject(e);
            }
            else if(_editionMode == EDIT_MODE_ADD_PLATFORM){
                Platform *p = new Platform(QString("platform_" + QString::number(_nbObjectType[Object::OBJECT_TYPE_PLATFORM] + 1)).toStdString(), _cursorPosition);
                addObject(p);
            }
            else if(_editionMode == EDIT_MODE_ADD_SWITCH){
                Switch *s = new Switch(QString("switch_" + QString::number(_nbObjectType[Object::OBJECT_TYPE_SWITCH] + 1)).toStdString(), _cursorPosition);
                addObject(s);
            }
            else if(_editionMode == EDIT_MODE_ADD_PUSH_BUTTON){
                PushButton *s = new PushButton(QString("pushbutton_" + QString::number(_nbObjectType[Object::OBJECT_TYPE_PUSH_BUTTON] + 1)).toStdString(), _cursorPosition);
                addObject(s);
            }
            else if(_editionMode == EDIT_MODE_ADD_AND_DOOR){
                AndDoor *d = new AndDoor(QString("anddoor_" + QString::number(_nbObjectType[Object::OBJECT_TYPE_AND_DOOR] + 1)).toStdString(), _cursorPosition);
                addObject(d);
            }
            else if(_editionMode == EDIT_MODE_ADD_OR_DOOR){
                OrDoor *d = new OrDoor(QString("ordoor_" + QString::number(_nbObjectType[Object::OBJECT_TYPE_OR_DOOR] + 1)).toStdString(), _cursorPosition);
                addObject(d);
            }
            else if(_editionMode == EDIT_MODE_ADD_NO_DOOR){
                NoDoor *d = new NoDoor(QString("nodoor_" + QString::number(_nbObjectType[Object::OBJECT_TYPE_NO_DOOR] + 1)).toStdString(), _cursorPosition);
                addObject(d);
            }
            else if(_editionMode == EDIT_MODE_REMOVE_OBJECT){
                if(_overObject){
                    removeObject(_overObject);
                    _overObject = NULL;
                }
            }
            else if(_editionMode == EDIT_MODE_SWITCH_SELECT_TARGET){
                if(_overObject){
                    _editionMode = EDIT_MODE_SELECT_OBJECT;
                    emit switchTargetSelected(_overObject);
                }
            }
            else if(_editionMode == EDIT_MODE_AND_DOOR_SELECT_TARGET){
                if(_overObject){
                    _editionMode = EDIT_MODE_SELECT_OBJECT;
                    emit andDoorTargetSelected(_overObject);
                }
            }
            else if(_editionMode == EDIT_MODE_OR_DOOR_SELECT_TARGET){
                if(_overObject){
                    _editionMode = EDIT_MODE_SELECT_OBJECT;
                    emit orDoorTargetSelected(_overObject);
                }
            }
            else if(_editionMode == EDIT_MODE_NO_DOOR_SELECT_TARGET){
                if(_overObject){
                    _editionMode = EDIT_MODE_SELECT_OBJECT;
                    emit noDoorTargetSelected(_overObject);
                }
            }
            else if(_editionMode == EDIT_MODE_PUSH_BUTTON_SELECT_TARGET){
                if(_overObject){
                    _editionMode = EDIT_MODE_SELECT_OBJECT;
                    emit pushButtonTargetSelected(_overObject);
                }
            }
            else if(_editionMode == EDIT_MODE_PLATFORM_ADD_POINT){
                emit platformPointAdded(_cursorPosition);
            }
            else if(_editionMode == EDIT_MODE_SELECT_OBJECT){
                if(_overObject){
                    if(_selectedObject)
                        _selectedObject->setSelected(false);
                    _overObject->setSelected(true);
                    _selectedObject = _overObject;
                    emit objectSelected(_selectedObject);
                }
            }
            else if(_editionMode == EDIT_MODE_SELECTION_TILE){
                _selectionModeStartPosition = _cursorPosition;
                _selectionModeEndPosition   = _cursorPosition;
                _selectionMode = true;
                resetTilesSelection();
            }
            else if(_editionMode == EDIT_MODE_ERASE_TILE){
                delete_obj(_tiles[_layerIndex][make_pair(_selectionPosition.x, _selectionPosition.y)]);
                _lastPositionRemoved = _selectionPosition;
                _eraseMode = true;
            }
        }
        else if(!pressed){
            if(_editionMode == EDIT_MODE_ADD_TILE){
                _addingMode = false;
                _lastPositionAdded = b2Vec2(-1, -1);
            }
            else if(_editionMode == EDIT_MODE_ERASE_TILE){
                _eraseMode = false;
                _lastPositionRemoved = b2Vec2(-1, -1);
            }
            else if(_editionMode == EDIT_MODE_SELECTION_TILE){
                _selectionMode = false;
            }
        }

        if(_editionMode == EDIT_MODE_EDIT_TILE){
            if(_selectedTile && _selectedTile->onPoint())
                _selectedTile->cursorClicked(pos, pressed);
            else{
                MapTile *t = getTileAtClickedPosition();

                if(pressed && t)
                    setSelectedTile(t);
                else if(pressed && _selectedTile){
                    _tiles[1][make_pair(_selectedTile->getPosition().x, _selectedTile->getPosition().y)] = NULL;
                    _selectedTile->setPosition(_selectionPosition);
                    _tiles[1][make_pair(_selectionPosition.x, _selectionPosition.y)] = _selectedTile;
                }
            }
        }
    }
    else{
        if(pressed){
            if(_editionMode == EDIT_MODE_FLAG){
                removeFlagAtPosition();
            }
        }
    }
}

void Map::addTile(MapTile *t, int layer){
    if(t){
        MapTile *old = _tiles[layer][make_pair(t->getPosition().x, t->getPosition().y)];
        delete_obj(old);
        _tiles[layer][make_pair(t->getPosition().x, t->getPosition().y)] = t;
    }
}

void Map::addCheckpoint(Checkpoint *t){
    if(t){
        Checkpoint *old = _checkpoints[make_pair(t->getPosition().x, t->getPosition().y)];
        delete_obj(old);
        _checkpoints[make_pair(t->getPosition().x, t->getPosition().y)] = t;
    }
}

void Map::setSelectedTile(MapTile *t){
    if(_selectedTile)
        _selectedTile->setSelected(false);
    _selectedTile = t;
    if(_selectedTile)
        _selectedTile->setSelected();
}

void Map::setEditionMode(editionMode m){
    editionMode oldMode = _editionMode;
    _editionMode = m;

    setSelectedTile(NULL);
    if(_editionMode != EDIT_MODE_SWITCH_SELECT_TARGET && oldMode != EDIT_MODE_SWITCH_SELECT_TARGET
            && _editionMode != EDIT_MODE_AND_DOOR_SELECT_TARGET && oldMode != EDIT_MODE_AND_DOOR_SELECT_TARGET
            && _editionMode != EDIT_MODE_OR_DOOR_SELECT_TARGET && oldMode != EDIT_MODE_OR_DOOR_SELECT_TARGET
            && _editionMode != EDIT_MODE_NO_DOOR_SELECT_TARGET && oldMode != EDIT_MODE_NO_DOOR_SELECT_TARGET
            && _editionMode != EDIT_MODE_PUSH_BUTTON_SELECT_TARGET && oldMode != EDIT_MODE_PUSH_BUTTON_SELECT_TARGET
            && _editionMode != EDIT_MODE_PLATFORM_ADD_POINT && oldMode != EDIT_MODE_PLATFORM_ADD_POINT){
        if(_selectedObject)
            _selectedObject->setSelected(false);
        _selectedObject = NULL;
    }
}

void Map::resetTilesSelection(){
    for(size_t i = 0; i < _selectedTiles.size(); i++)
        _selectedTiles.at(i)->setSelected(false);
    _selectedTiles.clear();
}

void Map::objectNameUpdated(Object *obj, string oldName, string newName){
    map<string, Object*>::iterator it = _objects.find(oldName);
    if(it != _objects.end()){
        _objects.erase(it);
        _objects[newName] = obj;
    }
}

void Map::removeObject(string name){
    map<string, Object*>::iterator it = _objects.find(name);
    if(it != _objects.end()){
        delete_obj(it->second);
        _objects.erase(it);
    }
}

Object* Map::getObject(string name){
    map<string, Object*>::iterator it = _objects.find(name);
    if(it != _objects.end())
        return it->second;

    return NULL;
}
