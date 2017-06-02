#include "editortab.h"

EditorTab::EditorTab(QWidget *parent) : QWidget(parent){
    _glWidget = new OpenGLWidget(this);
    _tileSet  = NULL;

    QHBoxLayout *mainLayout = new QHBoxLayout;  
    mainLayout->setContentsMargins(0, 0, 0, 0);

    _tabs = new QTabWidget(this);
    _tabs->setTabShape(QTabWidget::Triangular);
    _tabs->setTabsClosable(false);
    _tabs->setStyleSheet(QString("QTabWidget::pane {margin:0;padding:0;border-top:2px solid #fafafa;}"
                                 "QTabWidget::tab-bar {left: 5px;margin:0;padding:0;}"
                                 "QTabBar::tab {"
                                 "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
                                 "border: 1px solid #9B9B9B;"
                                 "border-bottom:0; "
                                 "border-top-left-radius: 2px;"
                                 "border-top-right-radius: 2px;"
                                 "padding: 2px;"
                                 "padding-left: 15px;padding-right: 15px;}"
                                 "QTabBar::tab:selected, QTabBar::tab:hover {"
                                 "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #fafafa, stop: 0.4 #f4f4f4,stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);}"
                                 "QTabBar::tab:selected {border-top:2px solid #2980b9;border-bottom:0;margin-left:-2px;margin-right:-2px;}"
                                 "QTabBar::tab:first:selected {margin-left: 0;}"
                                 "QTabBar::tab:last:selected {margin-right: 0;}"
                                 "QTabBar::tab:only-one {margin: 0; }"));

    _tabs->setFixedWidth(330);
    
    _tileOption = new TileOptionWidget(this);
    _tileOption->hide();

    _laserOption = new LaserOptionWidget(this);
    _laserOption->hide();

    _particuleOption = new ParticleEmitterOptionWidget(this);
    _particuleOption->hide();

    _switchOption = new SwitchOptionWidget(this);
    _switchOption->hide();

    _andDoorOption = new AndDoorOptionWidget(this);
    _andDoorOption->hide();

    _orDoorOption = new OrDoorOptionWidget(this);
    _orDoorOption->hide();

    _noDoorOption = new NoDoorOptionWidget(this);
    _noDoorOption->hide();

    _platformOption = new PlateformOptionWidget(this);
    _platformOption->hide();

    _pushButtonOption = new PushButtonOptionWidget(this);
    _pushButtonOption->hide();

    mainLayout->addWidget(_tabs);
    mainLayout->addWidget(_glWidget);
    mainLayout->addWidget(_tileOption);
    mainLayout->addWidget(_laserOption);
    mainLayout->addWidget(_particuleOption);
    mainLayout->addWidget(_switchOption);
    mainLayout->addWidget(_andDoorOption);
    mainLayout->addWidget(_orDoorOption);
    mainLayout->addWidget(_noDoorOption);
    mainLayout->addWidget(_platformOption);
    mainLayout->addWidget(_pushButtonOption);

    connect(_glWidget, SIGNAL(objectSelected(vector<MapTile*>)), this, SLOT(setSelectedObjects(vector<MapTile*>)));
    connect(_glWidget->getScene(), SIGNAL(objectSelect(Object*)), this, SLOT(objectSelected(Object*)));

    setLayout(mainLayout);
}

EditorTab::~EditorTab(){
    delete_obj(_tabs);
    delete_obj(_glWidget);
    delete_obj(_tileOption);
    delete_obj(_laserOption);
    delete_obj(_particuleOption);
    delete_obj(_switchOption);
    delete_obj(_andDoorOption);
    delete_obj(_orDoorOption);
    delete_obj(_noDoorOption);
    delete_obj(_platformOption);
    delete_obj(_pushButtonOption);
}

void EditorTab::tileClicked(QTile* tile){
    _glWidget->getScene()->getMap()->setSelectedTileCell(tile->getCell());
    _glWidget->getScene()->getMap()->setSelectedTileRow(tile->getRow());
    _glWidget->getScene()->getMap()->setSelectedTilesetIndex(tile->getTilesetIndex());
    emit resetSelection(false);
    tile->setSelected();
}

void EditorTab::loadTilesets(){
    _tabs->clear();

    vector<Sprite *> tilesets = _glWidget->getScene()->getMap()->getTilsets();
    for(size_t id = 0; id < tilesets.size(); id++){
        _tileSet = tilesets.at(id);

        QWidget *sideView = new QWidget(this);
        sideView->setFixedWidth(330);

        int gridCell = 0;
        int gridRow  = 0;

        QGridLayout  *tilesLayout = new QGridLayout;
        QScrollArea  *scrollView  = new QScrollArea;

        if(_tileSet){
            for(int row = 0; row < _tileSet->getNbRow(); row++){
                for(int cell = 0; cell < _tileSet->getNbCell(); cell++){
                    if(gridCell > 3){
                        gridCell = 0;
                        gridRow++;
                    }

                    QImage img = _tileSet->getQImageTile(cell, row).copy();
                    if(!QImageIsTransparent(img)){
                        QTile *tile = new QTile(img, row, cell, id);

                        if(row == 0 && cell == 0)
                            tile->setSelected();

                        connect(tile, SIGNAL(clicked(QTile*)), this, SLOT(tileClicked(QTile*)));
                        connect(this, SIGNAL(resetSelection(bool)), tile, SLOT(setSelected(bool)));

                        tilesLayout->addWidget(tile, gridRow, gridCell);

                        gridCell++;
                    }
                }
            }
        }

        sideView->setLayout(tilesLayout);
        scrollView->setWidget(sideView);

        _tabs->addTab(scrollView, QString::number(id + 1));
    }

    _tileSet = NULL;
}

void EditorTab::setMapMode(editionMode mode){
    _glWidget->getScene()->getMap()->setEditionMode(mode);
    _glWidget->getScene()->getMap()->resetTilesSelection();

    _andDoorOption->hide();
    _switchOption->hide();
    _laserOption->hide();
    _particuleOption->hide();
    _pushButtonOption->hide();
    _platformOption->hide();
    _orDoorOption->hide();
    _noDoorOption->hide();

    if(mode == EDIT_MODE_SELECTION_TILE){
        _tileOption->clearTiles();
        _tileOption->show();
    }
    else
        _tileOption->hide();
}

void EditorTab::setSelectedObjects(vector<MapTile*> tiles){
    _tileOption->setSelectedObjects(tiles);
}

void EditorTab::laserSelected(Laser *laser){
    if(laser){
        _laserOption->setLaser(laser);
        _laserOption->show();
    }
}

void EditorTab::particuleEmitterSelected(ParticleEmitter *emitter){
    _particuleOption->setEmitter(emitter);
    _particuleOption->show();
}

void EditorTab::switchSelected(Switch *s){
    _switchOption->setSwitch(s);
    _switchOption->setMap(_glWidget->getScene()->getMap());
    _switchOption->show();
}

void EditorTab::pushButtonSelected(PushButton *b){
    _pushButtonOption->setPushButton(b);
    _pushButtonOption->setMap(_glWidget->getScene()->getMap());
    _pushButtonOption->show();
}

void EditorTab::andDoorSelected(AndDoor *d){
    _andDoorOption->setAndDoor(d);
    _andDoorOption->setMap(_glWidget->getScene()->getMap());
    _andDoorOption->show();
}

void EditorTab::orDoorSelected(OrDoor *d){
    _orDoorOption->setOrDoor(d);
    _orDoorOption->setMap(_glWidget->getScene()->getMap());
    _orDoorOption->show();
}

void EditorTab::noDoorSelected(NoDoor *d){
    _noDoorOption->setNoDoor(d);
    _noDoorOption->setMap(_glWidget->getScene()->getMap());
    _noDoorOption->show();
}

void EditorTab::platformSelected(Platform *p){
    _platformOption->setPlatform(p);
    _platformOption->setMap(_glWidget->getScene()->getMap());
    _platformOption->show();
}

void EditorTab::objectSelected(Object *obj){
    _tileOption->hide();
    _laserOption->hide();
    _particuleOption->hide();
    _switchOption->hide();
    _andDoorOption->hide();
    _orDoorOption->hide();
    _noDoorOption->hide();
    _platformOption->hide();
    _pushButtonOption->hide();

    switch(obj->getType()){
    case Object::OBJECT_TYPE_LASER:
        laserSelected(static_cast<Laser *>(obj));
        break;
    case Object::OBJECT_TYPE_EMITTER:
        particuleEmitterSelected(static_cast<ParticleEmitter *>(obj));
        break;
    case Object::OBJECT_TYPE_SWITCH:
        switchSelected(static_cast<Switch *>(obj));
        break;
    case Object::OBJECT_TYPE_AND_DOOR:
        andDoorSelected(static_cast<AndDoor *>(obj));
        break;
    case Object::OBJECT_TYPE_OR_DOOR:
        orDoorSelected(static_cast<OrDoor *>(obj));
        break;
    case Object::OBJECT_TYPE_NO_DOOR:
        noDoorSelected(static_cast<NoDoor *>(obj));
        break;
    case Object::OBJECT_TYPE_PLATFORM:
        platformSelected(static_cast<Platform *>(obj));
        break;
    case Object::OBJECT_TYPE_PUSH_BUTTON:
        pushButtonSelected(static_cast<PushButton *>(obj));
        break;
    default:
        break;
    }
}
