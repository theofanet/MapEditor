#ifndef EDITORTAB_H
#define EDITORTAB_H

#include <QWidget>
#include "openglwidget.h"
#include "qtile.h"
#include "Objects/tileoptionwidget.h"
#include "Objects/laseroptionwidget.h"
#include "Objects/particleemitteroptionwidget.h"
#include "Objects/switchoptionwidget.h"
#include "Objects/anddooroptionwidget.h"
#include "Objects/ordooroptionwidget.h"
#include "Objects/nodooroptionwidget.h"
#include "Objects/plateformoptionwidget.h"
#include "Objects/pushbuttonoptionwidget.h"

class EditorTab : public QWidget{
    Q_OBJECT

public:
    EditorTab(QWidget *parent = 0);
    ~EditorTab();

    Scene* getScene(){ return _glWidget->getScene(); }

    void loadTilesets();

    void toggleFrontLayer(){ _glWidget->getScene()->getMap()->toggleFrontLayer(); }
    void toggleBackLayer(){ _glWidget->getScene()->getMap()->toggleBackLayer(); }
    void toggleMiddleLayer(){ _glWidget->getScene()->getMap()->toggleMiddleLayer(); }

    bool showingMiddleLayer(){ return _glWidget->getScene()->getMap()->showingMiddleLayer(); }
    bool showingFrontLayer(){ return _glWidget->getScene()->getMap()->showingFrontLayer(); }
    bool showingBackLayer(){ return _glWidget->getScene()->getMap()->showingBackLayer(); }

    void setLayerIndex(int index){ _glWidget->getScene()->getMap()->setLayerIndex(index); }

    void setMapMode(editionMode mode);

    void laserSelected(Laser *laser);
    void particuleEmitterSelected(ParticleEmitter *emitter);
    void switchSelected(Switch *s);
    void andDoorSelected(AndDoor *d);
    void orDoorSelected(OrDoor *d);
    void noDoorSelected(NoDoor *d);
    void platformSelected(Platform *p);
    void pushButtonSelected(PushButton *p);

signals:
    void resetSelection(bool s);

public slots:
    void tileClicked(QTile* tile);
    void setSelectedObjects(vector<MapTile*> tiles);
    void objectSelected(Object *obj);

private:
    OpenGLWidget *_glWidget;

    Sprite       *_tileSet;
    QTabWidget   *_tabs;

    TileOptionWidget  *_tileOption;
    LaserOptionWidget *_laserOption;
    ParticleEmitterOptionWidget *_particuleOption;
    SwitchOptionWidget          *_switchOption;
    AndDoorOptionWidget         *_andDoorOption;
    OrDoorOptionWidget          *_orDoorOption;
    NoDoorOptionWidget          *_noDoorOption;
    PlateformOptionWidget       *_platformOption;
    PushButtonOptionWidget      *_pushButtonOption;
};


#endif // EDITORTAB_H
