#include "addtilesetdialog.h"
#include "ui_addtilesetdialog.h"

AddTilesetDialog::AddTilesetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTilesetDialog)
{
    ui->setupUi(this);

    connect(ui->_tilsetLoadButton, SIGNAL(clicked(bool)), this, SLOT(loadTilesetFile()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(createSlot()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

AddTilesetDialog::~AddTilesetDialog()
{
    delete ui;
}


void AddTilesetDialog::createSlot(){
    if(!ui->_tilesetFilePath->text().isEmpty()){
        emit createSignal(this);
        accept();
    }
    else
        QMessageBox::critical(this, "Erreur", "Veuillez choisir un tileset");
}

void AddTilesetDialog::loadTilesetFile(){
    ui->_tilesetFilePath->setText(QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QDir::homePath(), "Images (*.png *.gif *.jpg *.jpeg)"));
}

QString AddTilesetDialog::getTilesetFilePath(){ return ui->_tilesetFilePath->text(); }
int     AddTilesetDialog::getTileWidth(){ return ui->_tileWidth->text().toInt(); }
int     AddTilesetDialog::getTileHeight(){ return ui->_tileHeight->text().toInt(); }
