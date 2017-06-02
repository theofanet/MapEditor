#ifndef SCENE_H
#define SCENE_H

#include <QWidget>

#include "Utilities/defines.h"
#include "map.h"
#include "Render/sprite.h"

class Scene : public QWidget{
Q_OBJECT

public:
    Scene(QWidget *parent = 0);
    ~Scene();

    virtual void draw();
    virtual void update(GLfloat dt);

    Settings* settings(){ return _settings; }
    void      set_settings(Settings *s){ _settings = s; }
    Map* getMap(){ return _map; }
    void setMap(Map* m);
    void setMousePosition(b2Vec2 p);
    void setMousePosition(GLfloat x, GLfloat y){ setMousePosition(b2Vec2(x, y)); }

signals:
    void objectSelect(Object *obj);

private slots:
    void objectSelectSlot(Object* obj);

protected:
    Settings *_settings;
    b2Vec2 _mousePosition;
    Map *_map;
};

#endif // SCENE_H
