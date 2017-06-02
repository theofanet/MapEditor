#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle(tr("CubeWorld MapEditor"));
    setGeometry(QRect(0, 50, WINDOW_WIDTH, WINDOW_HEIGHT));

    //Actions
    QAction *action_new = new QAction(("&New"), this);
    action_new->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    connect(action_new, SIGNAL(triggered()), this, SLOT(newTabAction()));

    _saveDir = "";

    _toolbar = new QToolBar(this);
    //_toolbar->setFixedHeight(40.0);
    _toolbar->setCursor(QCursor(Qt::PointingHandCursor));

    _editorWidget = new EditorTab();

    QAction *add_world_action = new QAction(QIcon(imagesDirPath()+"New.png"), tr("&Nouvelle map"), this);
    connect(add_world_action, SIGNAL(triggered()), this, SLOT(newTabAction()));
    _toolbar->addAction(add_world_action);

    _saveMapAction = new QAction(QIcon(imagesDirPath()+"Save.png"), tr("&Sauvegarder la map"), this);
    connect(_saveMapAction, SIGNAL(triggered()), this, SLOT(saveMapClicked()));
    _saveMapAction->setEnabled(false);
    _toolbar->addAction(_saveMapAction);

    _loadMapAction = new QAction(QIcon(imagesDirPath()+"Folder.png"), tr("&Charger la map"), this);
    connect(_loadMapAction, SIGNAL(triggered()), this, SLOT(loadMapClicked()));
    _toolbar->addAction(_loadMapAction);

    _toolbar->addSeparator();

    _addSpriteAction = new QAction(QIcon(imagesDirPath()+"AddSprite.png"), tr("&Ajouter un tileset"), this);
    connect(_addSpriteAction, SIGNAL(triggered()), this, SLOT(addSpriteClicked()));
    _addSpriteAction->setEnabled(false);
    _toolbar->addAction(_addSpriteAction);

    QImage colorImg = QImage( 32, 24, QImage::Format_ARGB32  );
    colorImg.fill( QColor(51, 51, 51) );

    _setBackgroundColorAction = new QAction(QIcon(QPixmap::fromImage(colorImg)), tr("&Ajouter un tileset"), this);
    connect(_setBackgroundColorAction, SIGNAL(triggered()), this, SLOT(backgroundColorClicked()));
    _setBackgroundColorAction->setEnabled(false);
    _toolbar->addAction(_setBackgroundColorAction);


    _toolbar->addSeparator();

    _setAddTileModeAction = new QAction(QIcon(imagesDirPath()+"Add.png"), tr("&Ajouter des tuiles"), this);
    connect(_setAddTileModeAction, SIGNAL(triggered()), this, SLOT(setCurrentTabModeAdd()));
    _setAddTileModeAction->setEnabled(false);
    _toolbar->addAction(_setAddTileModeAction);

    _setAddPaintBucketMode = new QAction(QIcon(imagesDirPath()+"PaintBucket.png"), tr("&Ajouter des tuiles en mode pot de peinture"), this);
    connect(_setAddPaintBucketMode, SIGNAL(triggered()), this, SLOT(setCurrentTabModeAddPaintBucket()));
    _setAddPaintBucketMode->setEnabled(false);
    _toolbar->addAction(_setAddPaintBucketMode);

    _setEraseTileModeAction = new QAction(QIcon(imagesDirPath()+"Erase.png"), tr("Effacer des tuiles"), this);
    connect(_setEraseTileModeAction, SIGNAL(triggered()), this, SLOT(setCurrentTabModeErase()));
    _setEraseTileModeAction->setEnabled(false);
    _toolbar->addAction(_setEraseTileModeAction);

    _setEditTileModeAction = new QAction(QIcon(imagesDirPath()+"Edit.png"), tr("&Editer des tuiles"), this);
    connect(_setEditTileModeAction, SIGNAL(triggered()), this, SLOT(setCurrentTabModeEdit()));
    _setEditTileModeAction->setEnabled(false);
    _toolbar->addAction(_setEditTileModeAction);

    _setSelectionTileMode = new QAction(QIcon(imagesDirPath()+"selection.png"), tr("Selectionner les tuiles"), this);
    connect(_setSelectionTileMode, SIGNAL(triggered(bool)), this, SLOT(setCurrentTabSelectionMode()));
    _setSelectionTileMode->setEnabled(false);
    _toolbar->addAction(_setSelectionTileMode);

    _toolbar->addSeparator();

    _setAddObjectModeAction = new QAction(QIcon(imagesDirPath()+"AddObject.png"), tr("Ajouter un objet"), this);
    connect(_setAddObjectModeAction, SIGNAL(triggered(bool)), this, SLOT(chooseObjectModeToAdd()));
    _setAddObjectModeAction->setEnabled(false);
    _toolbar->addAction(_setAddObjectModeAction);

    _setSelectObjectModeAction = new QAction(QIcon(imagesDirPath()+"SelectObject.png"), tr("Selectionner un objet"), this);
    connect(_setSelectObjectModeAction, SIGNAL(triggered(bool)), this, SLOT(chooseObjectModeToSelect()));
    _setSelectObjectModeAction->setEnabled(false);
    _toolbar->addAction(_setSelectObjectModeAction);

    _toolbar->addSeparator();

    _setStartPositionMode = new QAction(QIcon(imagesDirPath()+"Start.png"), tr("Editer la position de depart"), this);
    connect(_setStartPositionMode, SIGNAL(triggered(bool)), this, SLOT(SetCurrentTabStartPositionMode()));
    _setStartPositionMode->setEnabled(false);
    _toolbar->addAction(_setStartPositionMode);

    _setFlagMode = new QAction(QIcon(imagesDirPath()+"Flag.png"), tr("Ajouer des checkpoints"), this);
    connect(_setFlagMode, SIGNAL(triggered(bool)), this, SLOT(SetCurrentTabFlagMode()));
    _setFlagMode->setEnabled(false);
    _toolbar->addAction(_setFlagMode);

    _setEndPositionMode = new QAction(QIcon(imagesDirPath()+"End.png"), tr("Editer la position de fin"), this);
    connect(_setEndPositionMode, SIGNAL(triggered(bool)), this, SLOT(SetCurrentTabEndPositionMode()));
    _setEndPositionMode->setEnabled(false);
    _toolbar->addAction(_setEndPositionMode);

    _toolbar->addSeparator();

    _toggleBottomLayerAction = new QAction(QIcon(imagesDirPath()+"Back_selected.png"), tr("Afficher le layer arriere"), this);
    connect(_toggleBottomLayerAction, SIGNAL(triggered()), this, SLOT(toggleCurrentTabBackLayer()));
    _toggleBottomLayerAction->setEnabled(false);
    _toolbar->addAction(_toggleBottomLayerAction);

    _toggleMiddleLayerAction = new QAction(QIcon(imagesDirPath()+"Middle_selected.png"), tr("Afficher le layer centrale"), this);
    connect(_toggleMiddleLayerAction, SIGNAL(triggered()), this, SLOT(toggleCurrentTabMiddleLayer()));
    _toggleMiddleLayerAction->setEnabled(false);
    _toolbar->addAction(_toggleMiddleLayerAction);

    _toggleTopLayerAction = new QAction(QIcon(imagesDirPath()+"Front_selected.png"), tr("Afficher le layer avant"), this);
    connect(_toggleTopLayerAction, SIGNAL(triggered()), this, SLOT(toggleCurrentTabTopLayer()));
    _toggleTopLayerAction->setEnabled(false);
    _toolbar->addAction(_toggleTopLayerAction);

    _addToLayerCombo = new QComboBox(this);
    _addToLayerCombo->addItem(tr("Ajouter au layer arriere"));
    _addToLayerCombo->addItem(tr("Ajouter au layer centrale"));
    _addToLayerCombo->addItem(tr("Ajouter au layer superieur"));
    _addToLayerCombo->setCurrentIndex(1);
    _addToLayerCombo->setEnabled(false);
    connect(_addToLayerCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(addToLayerChanged(int)));
    _toolbar->addWidget(_addToLayerCombo);

    addToolBar(_toolbar);
    setCentralWidget(_editorWidget);


    _addObjectSelectionMenu = new QMenu(this);
    QAction *addLaser = new QAction(tr("Ajouter un laser"), _addObjectSelectionMenu);
    connect(addLaser, SIGNAL(triggered()), this, SLOT(setAddLaserMode()));
    _addObjectSelectionMenu->addAction(addLaser);
    QAction *addJeton = new QAction(tr("Ajouter un jeton"), _addObjectSelectionMenu);
    connect(addJeton, SIGNAL(triggered()), this, SLOT(setAddJetonMode()));
    _addObjectSelectionMenu->addAction(addJeton);
    QAction *addEmitter = new QAction(tr("Ajouter des particules"), _addObjectSelectionMenu);
    connect(addEmitter, SIGNAL(triggered()), this, SLOT(setAddEmitterMode()));
    _addObjectSelectionMenu->addAction(addEmitter);
    QAction *addPlatform = new QAction(tr("Ajouter une platfrom"), _addObjectSelectionMenu);
    connect(addPlatform, SIGNAL(triggered()), this, SLOT(setAddPlatformMode()));
    _addObjectSelectionMenu->addAction(addPlatform);

    QMenu *addObjectLogicalMenu = new QMenu("Logique", _addObjectSelectionMenu);
    QAction *addSwitch = new QAction(tr("Ajouter un interupteur ON/OFF"), _addObjectSelectionMenu);
    connect(addSwitch, SIGNAL(triggered()), this, SLOT(setAddSwitchMode()));
    addObjectLogicalMenu->addAction(addSwitch);
    QAction *addPushButton = new QAction(tr("Ajouter un bouton poussoir"), _addObjectSelectionMenu);
    connect(addPushButton, SIGNAL(triggered()), this, SLOT(setAddPushButtonMode()));
    addObjectLogicalMenu->addAction(addPushButton);
    QAction *addAndDoor = new QAction(tr("Ajouter une porte logique ET"), _addObjectSelectionMenu);
    connect(addAndDoor, SIGNAL(triggered()), this, SLOT(setAddAndDoorMode()));
    addObjectLogicalMenu->addAction(addAndDoor);
    QAction *addOrDoor = new QAction(tr("Ajouter une porte logique OU"), _addObjectSelectionMenu);
    connect(addOrDoor, SIGNAL(triggered()), this, SLOT(setAddOrDoorMode()));
    addObjectLogicalMenu->addAction(addOrDoor);
    QAction *addNoDoor = new QAction(tr("Ajouter une porte logique NON"), _addObjectSelectionMenu);
    connect(addNoDoor, SIGNAL(triggered()), this, SLOT(setAddNoDoorMode()));
    addObjectLogicalMenu->addAction(addNoDoor);
    _addObjectSelectionMenu->addMenu(addObjectLogicalMenu);


    _selectObjectSelectionMenu = new QMenu(this);
    QAction *selectObj = new QAction(tr("Selectionner un objet"), _selectObjectSelectionMenu);
    connect(selectObj, SIGNAL(triggered()), this, SLOT(setSelectObjectMode()));
    _selectObjectSelectionMenu->addAction(selectObj);

    QAction *deletObj = new QAction(tr("Supprimer un objet"), _selectObjectSelectionMenu);
    connect(deletObj, SIGNAL(triggered()), this, SLOT(setRemoveObjectMode()));
    _selectObjectSelectionMenu->addAction(deletObj);
}

MainWindow::~MainWindow(){
    delete_obj(_editorWidget);
    delete_obj(_toolbar);
    delete_obj(_mainLayout);
    delete_obj(_saveMapAction);
    delete_obj(_loadMapAction);
    delete_obj(_addSpriteAction);
    delete_obj(_setAddTileModeAction);
    delete_obj(_setEraseTileModeAction);
    delete_obj(_setFlagMode);
    delete_obj(_setEditTileModeAction);
    delete_obj(_setSelectionTileMode);
    delete_obj(_setStartPositionMode);
    delete_obj(_setEndPositionMode);
    delete_obj(_setAddPaintBucketMode);
    delete_obj(_setAddObjectModeAction);
    delete_obj(_setSelectObjectModeAction);
    delete_obj(_toggleTopLayerAction);
    delete_obj(_toggleMiddleLayerAction);
    delete_obj(_toggleBottomLayerAction);
    delete_obj(_addObjectSelectionMenu);
    delete_obj(_selectObjectSelectionMenu);
    delete_obj(_setBackgroundColorAction);
}

void MainWindow::newTabAction(){
    NewMapDialog *dialog = new NewMapDialog(this);
    connect(dialog, SIGNAL(createSignal(NewMapDialog*)), this, SLOT(createNewTabWithData(NewMapDialog*)));
    dialog->exec();
}

void MainWindow::addSpriteClicked(){
    AddTilesetDialog *dialog = new AddTilesetDialog(this);
    connect(dialog, SIGNAL(createSignal(AddTilesetDialog*)), this, SLOT(addTilesetWithData(AddTilesetDialog*)));
    dialog->exec();
}

void MainWindow::addTilesetWithData(AddTilesetDialog *dialog){
    _editorWidget->getScene()->getMap()->addTileset(dialog->getTilesetFilePath(), dialog->getTileWidth(), dialog->getTileHeight());
    _editorWidget->loadTilesets();
}

void MainWindow::createNewTabWithData(NewMapDialog *dialog){
    Map *map = new Map(dialog->getMapName(), dialog->getMapWidth(), dialog->getMapHeight());
    map->addTileset(dialog->getTilesetFilePath(), dialog->getTileWidth(), dialog->getTileHeight());

    setEditorNewMap(map);
}


void MainWindow::loadMapClicked(){
    QString filename = QFileDialog::getExistingDirectory(this, tr("Ouvrir une map"),
                                                         QDir::homePath(),
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);

    if(!filename.isNull()){
        QString dirpath = filename;
        dirpath.replace(".map", "");
        _saveDir = dirpath;

        MapJsonData data;
        data.loadFromFile(filename.toStdString());

        Map *map = data.getMap();

        setEditorNewMap(map);
    }
}

void MainWindow::setEditorNewMap(Map *map){
    if(_editorWidget->getScene()->getMap())
        setCurrentTabMode(EDIT_MODE_ADD_TILE);

    _editorWidget->getScene()->setMap(map);
    _editorWidget->loadTilesets();

    _setAddTileModeAction->setEnabled(true);
    _setAddPaintBucketMode->setEnabled(true);
    _setEraseTileModeAction->setEnabled(true);
    _setEditTileModeAction->setEnabled(true);
    _setSelectionTileMode->setEnabled(true);
    _setFlagMode->setEnabled(true);
    _setStartPositionMode->setEnabled(true);
    _setEndPositionMode->setEnabled(true);
    _saveMapAction->setEnabled(true);
    _addSpriteAction->setEnabled(true);
    _toggleBottomLayerAction->setEnabled(true);
    _toggleMiddleLayerAction->setEnabled(true);
    _toggleTopLayerAction->setEnabled(true);
    _addToLayerCombo->setEnabled(true);
    _addToLayerCombo->setCurrentIndex(1);
    _setAddObjectModeAction->setEnabled(true);
    _setSelectObjectModeAction->setEnabled(true);
    _setBackgroundColorAction->setEnabled(true);

    setCurrentTabMode(EDIT_MODE_ADD_TILE);
}

void MainWindow::setCurrentTabMode(editionMode newMode){
    editionMode oldMode = _editorWidget->getScene()->getMap()->getEditionMode();
    _editorWidget->setMapMode(newMode);

    if(oldMode == EDIT_MODE_EDIT_TILE)
        _setEditTileModeAction->setIcon(QIcon(imagesDirPath()+"Edit.png"));
    else if(oldMode == EDIT_MODE_ERASE_TILE)
        _setEraseTileModeAction->setIcon(QIcon(imagesDirPath()+"Erase.png"));
    else if(oldMode == EDIT_MODE_SELECTION_TILE)
        _setSelectionTileMode->setIcon(QIcon(imagesDirPath()+"selection.png"));
    else if(oldMode == EDIT_MODE_FLAG)
        _setFlagMode->setIcon(QIcon(imagesDirPath()+"Flag.png"));
    else if(oldMode == EDIT_MODE_START_POSITION)
        _setStartPositionMode->setIcon(QIcon(imagesDirPath()+"Start.png"));
    else if(oldMode == EDIT_MODE_END_POSITION)
        _setEndPositionMode->setIcon(QIcon(imagesDirPath()+"End.png"));
    else if(oldMode == EDIT_MODE_ADD_PAINT_BUCKET_TILE)
        _setAddPaintBucketMode->setIcon(QIcon(imagesDirPath()+"PaintBucket.png"));
    else if(oldMode == EDIT_MODE_ADD_TILE)
        _setAddTileModeAction->setIcon(QIcon(imagesDirPath()+"Add.png"));
    else if(oldMode == EDIT_MODE_ADD_LASER || oldMode == EDIT_MODE_ADD_JETON || oldMode == EDIT_MODE_ADD_EMITTER || oldMode == EDIT_MODE_ADD_SWITCH
             || oldMode == EDIT_MODE_ADD_AND_DOOR || oldMode == EDIT_MODE_ADD_OR_DOOR || oldMode == EDIT_MODE_ADD_NO_DOOR || oldMode == EDIT_MODE_ADD_PLATFORM
            || oldMode == EDIT_MODE_ADD_PUSH_BUTTON)
        _setAddObjectModeAction->setIcon(QIcon(imagesDirPath()+"AddObject.png"));
    else if(oldMode == EDIT_MODE_SELECT_OBJECT || oldMode == EDIT_MODE_REMOVE_OBJECT)
        _setSelectObjectModeAction->setIcon(QIcon(imagesDirPath()+"SelectObject.png"));


    if(newMode == EDIT_MODE_EDIT_TILE)
        _setEditTileModeAction->setIcon(QIcon(imagesDirPath()+"Edit_selected.png"));
    else if(newMode == EDIT_MODE_ERASE_TILE)
        _setEraseTileModeAction->setIcon(QIcon(imagesDirPath()+"Erase_selected.png"));
    else if(newMode == EDIT_MODE_SELECTION_TILE)
        _setSelectionTileMode->setIcon(QIcon(imagesDirPath()+"selection_selected.png"));
    else if(newMode == EDIT_MODE_FLAG)
        _setFlagMode->setIcon(QIcon(imagesDirPath()+"Flag_selected.png"));
    else if(newMode == EDIT_MODE_START_POSITION)
        _setStartPositionMode->setIcon(QIcon(imagesDirPath()+"Start_selected.png"));
    else if(newMode == EDIT_MODE_END_POSITION)
        _setEndPositionMode->setIcon(QIcon(imagesDirPath()+"End_selected.png"));
    else if(newMode == EDIT_MODE_ADD_PAINT_BUCKET_TILE)
        _setAddPaintBucketMode->setIcon(QIcon(imagesDirPath()+"PaintBucket_selected.png"));
    else if(newMode == EDIT_MODE_ADD_TILE)
        _setAddTileModeAction->setIcon(QIcon(imagesDirPath()+"Add_selected.png"));
    else if(newMode == EDIT_MODE_ADD_LASER || newMode == EDIT_MODE_ADD_JETON || newMode == EDIT_MODE_ADD_EMITTER || newMode == EDIT_MODE_ADD_SWITCH
            || newMode == EDIT_MODE_ADD_AND_DOOR || newMode == EDIT_MODE_ADD_OR_DOOR || newMode == EDIT_MODE_ADD_NO_DOOR || newMode == EDIT_MODE_ADD_PLATFORM
            || newMode == EDIT_MODE_ADD_PUSH_BUTTON)
        _setAddObjectModeAction->setIcon(QIcon(imagesDirPath()+"AddObject_selected.png"));
    else if(newMode == EDIT_MODE_SELECT_OBJECT || newMode == EDIT_MODE_REMOVE_OBJECT)
        _setSelectObjectModeAction->setIcon(QIcon(imagesDirPath()+"SelectObject_selected.png"));
}

void MainWindow::setCurrentTabModeAdd(){
    setCurrentTabMode(EDIT_MODE_ADD_TILE);
}

void MainWindow::setCurrentTabModeAddPaintBucket(){
    setCurrentTabMode(EDIT_MODE_ADD_PAINT_BUCKET_TILE);
}

void MainWindow::setCurrentTabModeErase(){
    setCurrentTabMode(EDIT_MODE_ERASE_TILE);
}

void MainWindow::setCurrentTabSelectionMode(){
    setCurrentTabMode(EDIT_MODE_SELECTION_TILE);
}

//DB2121
void MainWindow::setCurrentTabModeEdit(){
    setCurrentTabMode(EDIT_MODE_EDIT_TILE);
}

void MainWindow::SetCurrentTabFlagMode(){
    setCurrentTabMode(EDIT_MODE_FLAG);
}


void MainWindow::SetCurrentTabStartPositionMode(){
    setCurrentTabMode(EDIT_MODE_START_POSITION);
}

void MainWindow::SetCurrentTabEndPositionMode(){
    setCurrentTabMode(EDIT_MODE_END_POSITION);
}

void MainWindow::setAddLaserMode(){
    setCurrentTabMode(EDIT_MODE_ADD_LASER);
}

void MainWindow::setAddJetonMode(){
    setCurrentTabMode(EDIT_MODE_ADD_JETON);
}

void MainWindow::setAddEmitterMode(){
    setCurrentTabMode(EDIT_MODE_ADD_EMITTER);
}

void MainWindow::setAddPlatformMode(){
    setCurrentTabMode(EDIT_MODE_ADD_PLATFORM);
}

void MainWindow::setAddSwitchMode(){
    setCurrentTabMode(EDIT_MODE_ADD_SWITCH);
}

void MainWindow::setAddPushButtonMode(){
    setCurrentTabMode(EDIT_MODE_ADD_PUSH_BUTTON);
}

void MainWindow::setAddAndDoorMode(){
    setCurrentTabMode(EDIT_MODE_ADD_AND_DOOR);
}

void MainWindow::setAddOrDoorMode(){
    setCurrentTabMode(EDIT_MODE_ADD_OR_DOOR);
}

void MainWindow::setAddNoDoorMode(){
    setCurrentTabMode(EDIT_MODE_ADD_NO_DOOR);
}

void MainWindow::setSelectObjectMode(){
    setCurrentTabMode(EDIT_MODE_SELECT_OBJECT);
}

void MainWindow::setRemoveObjectMode(){
    setCurrentTabMode(EDIT_MODE_REMOVE_OBJECT);
}

void MainWindow::saveMapClicked(){
    QString path = QDir::homePath() + "/" + _editorWidget->getScene()->getMap()->getName();
    if(!_saveDir.isEmpty())
        path = _saveDir;

    QString filename = QFileDialog::getSaveFileName(this, "Enregistrer la map", path, "Map (*.map)", 0, QFileDialog::ShowDirsOnly);

    if(!filename.isNull()){
        QDir dir = QDir::root();
        dir.mkdir(filename);
        dir.mkdir(filename + "/Objects");

        QString data_filename = filename + "/data.mjs";

        MapJsonData data(_editorWidget->getScene()->getMap());
        data.saveToFile(data_filename.toStdString());

        vector<Sprite *> tilsets = _editorWidget->getScene()->getMap()->getTilsets();
        for(size_t i = 0; i < tilsets.size(); i++){
            QFileInfo tilesetinfo(tilsets.at(i)->getImage()->getFilePath());
            QString img_filename  = filename + "/" + tilesetinfo.fileName();
            QFile::copy(tilsets.at(i)->getImage()->getFilePath(), img_filename);
        }

        vector<pair<string, string>> filesToCopy = _editorWidget->getScene()->getMap()->getFilesToCopy();
        for(vector<pair<string, string>>::iterator it = filesToCopy.begin(); it != filesToCopy.end(); ++it){
            QString filenameTo = filename + "/" + QString::fromStdString(it->second);
            if(!QFile::exists(filenameTo))
                QFile::copy(QString::fromStdString(it->first), filenameTo);
        }
    }
}

void MainWindow::toggleCurrentTabBackLayer(){
    _editorWidget->toggleBackLayer();
    if(_editorWidget->showingBackLayer())
        _toggleBottomLayerAction->setIcon(QIcon(imagesDirPath()+"Back_selected.png"));
    else
        _toggleBottomLayerAction->setIcon(QIcon(imagesDirPath()+"Back.png"));
}

void MainWindow::toggleCurrentTabMiddleLayer(){
    _editorWidget->toggleMiddleLayer();
    if(_editorWidget->showingMiddleLayer())
        _toggleMiddleLayerAction->setIcon(QIcon(imagesDirPath()+"Middle_selected.png"));
    else
        _toggleMiddleLayerAction->setIcon(QIcon(imagesDirPath()+"Middle.png"));
}

void MainWindow::toggleCurrentTabTopLayer(){
    _editorWidget->toggleFrontLayer();
    if(_editorWidget->showingFrontLayer())
        _toggleTopLayerAction->setIcon(QIcon(imagesDirPath()+"Front_selected.png"));
    else
        _toggleTopLayerAction->setIcon(QIcon(imagesDirPath()+"Front.png"));
}

void MainWindow::addToLayerChanged(int index){
    _editorWidget->setLayerIndex(index);
}

void MainWindow::chooseObjectModeToAdd(){
    _addObjectSelectionMenu->exec(this->mapToParent(QPoint(460, 40)));
}

void MainWindow::chooseObjectModeToSelect(){
    _selectObjectSelectionMenu->exec(this->mapToParent(QPoint(500, 40)));
}

void MainWindow::backgroundColorClicked(){
    if(_editorWidget->getScene()->getMap()){
        QColor init  = QColor(_editorWidget->getScene()->getMap()->getBackgroundColor(0) * 255.0,
                              _editorWidget->getScene()->getMap()->getBackgroundColor(1) * 255.0,
                              _editorWidget->getScene()->getMap()->getBackgroundColor(2) * 255.0);

        QColor color = QColorDialog::getColor(init, this);

        QImage colorImg = QImage( 32, 24, QImage::Format_ARGB32  );
        colorImg.fill( color );
        _setBackgroundColorAction->setIcon(QIcon(QPixmap::fromImage(colorImg)));

        _editorWidget->getScene()->getMap()->setBackgroundColor(0, (double)color.red() / 255.0);
        _editorWidget->getScene()->getMap()->setBackgroundColor(1, (double)color.green() / 255.0);
        _editorWidget->getScene()->getMap()->setBackgroundColor(2, (double)color.blue() / 255.0);
    }
}
