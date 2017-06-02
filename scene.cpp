#include "scene.h"

Scene::Scene(QWidget *parent) : QWidget(parent){
    _settings = new Settings();
    _map = NULL;
}

Scene::~Scene(){
    delete_obj(_settings);
    if(_map)
        delete_obj(_map);
}

void Scene::setMap(Map* m){
    if(_map)
        delete_obj(_map);

    _map = m;
    if(_map){
        _settings->cameraPosition = _map->getSize();
        connect(_map, SIGNAL(objectSelected(Object*)), this, SLOT(objectSelectSlot(Object*)));
    }
}

void Scene::objectSelectSlot(Object *obj){
    if(obj)
        emit objectSelect(obj);
}

void Scene::draw(){
    /*if(_map)
        glClearColor(_map->getBackgroundColor(0), _map->getBackgroundColor(1), _map->getBackgroundColor(2), 1);
    else
        glClearColor(0.2, 0.2, 0.2, 1.0);*/
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glScalef(_settings->cameraZoom, _settings->cameraZoom, _settings->cameraZoom);
    glTranslatef(-_settings->cameraPosition.x, -_settings->cameraPosition.y, 0.0f);

    if(_map)
        _map->draw();

    glPopMatrix();
}

void Scene::update(GLfloat dt){
    if(_map){
        _map->update(dt);
        _map->setDrawPosition(_settings->cameraPosition, _settings->cameraZoom);
    }
}

void Scene::setMousePosition(b2Vec2 p){
    _mousePosition = (p / _settings->cameraZoom) + _settings->cameraPosition;
    if(_map)
        _map->setCursorPosition(_mousePosition);
}
