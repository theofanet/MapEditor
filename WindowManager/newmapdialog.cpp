#include "newmapdialog.h"

NewMapDialog::NewMapDialog(QWidget *parent) : QDialog(parent) {
    _mapName = new QLineEdit("new_map", this);
    _mapWidth = new QLineEdit("20", this);
    _mapHeight = new QLineEdit("20", this);
    _loadTilesetButton = new QPushButton("Charger le tilset", this);
    _tilesetFile = "";

    QFormLayout *form = new QFormLayout;
    form->addRow("Nom", _mapName);
    form->addRow("Largeur", _mapWidth);
    form->addRow("Hauteur", _mapHeight);
    form->addRow(_loadTilesetButton);

    _createButton = new QPushButton("Creer", this);
    _createButton->hide();

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(form);
    layoutPrincipal->addWidget(_createButton);

    setLayout(layoutPrincipal);
    setWindowTitle("Creer une map");

    connect(_createButton, SIGNAL(clicked()), this, SLOT(createSlot()));
    connect(_loadTilesetButton, SIGNAL(clicked(bool)), this, SLOT(loadTilesetFile()));
}

void NewMapDialog::createSlot(){
    emit createSignal(this);
    accept();
}

void NewMapDialog::loadTilesetFile(){
    _tilesetFile = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    _createButton->show();
}
