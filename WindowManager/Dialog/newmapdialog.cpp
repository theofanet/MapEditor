#include "newmapdialog.h"
#include "ui_newmapdialog.h"

NewMapDialog::NewMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMapDialog){

    ui->setupUi(this);

    connect(ui->_tilsetLoadButton, SIGNAL(clicked(bool)), this, SLOT(loadTilesetFile()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(createSlot()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

NewMapDialog::~NewMapDialog(){
    delete ui;
}

void NewMapDialog::createSlot(){
    if(!ui->_tilesetFilePath->text().isEmpty()){
        emit createSignal(this);
        accept();
    }
    else
        QMessageBox::critical(this, "Erreur", "Veuillez choisir un tileset");
}

void NewMapDialog::loadTilesetFile(){
    ui->_tilesetFilePath->setText(QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QDir::homePath(), "Images (*.png *.gif *.jpg *.jpeg)"));
}

QString NewMapDialog::getMapName(){ return ui->_mapName->text(); }
int     NewMapDialog::getMapWidth(){ return std::min(std::max(20, ui->_mapWidth->text().toInt()), 200); }
int     NewMapDialog::getMapHeight(){ return std::min(std::max(20, ui->_mapHeight->text().toInt()), 200); }
QString NewMapDialog::getTilesetFilePath(){ return ui->_tilesetFilePath->text(); }
int     NewMapDialog::getTileWidth(){ return ui->_tileWidth->text().toInt(); }
int     NewMapDialog::getTileHeight(){ return ui->_tileHeight->text().toInt(); }
