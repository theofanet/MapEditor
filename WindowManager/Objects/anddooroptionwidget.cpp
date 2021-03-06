#include "anddooroptionwidget.h"
#include "ui_anddooroptionwidget.h"

AndDoorOptionWidget::AndDoorOptionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AndDoorOptionWidget)
{
    setFixedWidth(300);
    ui->setupUi(this);

    _door = NULL;
    _map  = NULL;

    connect(ui->_addConnexionButton, SIGNAL(clicked(bool)), this, SLOT(selectTargetClicked(bool)));
}

AndDoorOptionWidget::~AndDoorOptionWidget()
{
    delete ui;
}

void AndDoorOptionWidget::setMap(Map *m){
    if(!_map || _map != m){
        _map = m;
        if(_map)
            connect(_map, SIGNAL(andDoorTargetSelected(Object *)), this, SLOT(targetSelected(Object*)));
    }
}

void AndDoorOptionWidget::selectTargetClicked(bool){
    if(_map)
        _map->setEditionMode(EDIT_MODE_AND_DOOR_SELECT_TARGET);
}

void AndDoorOptionWidget::targetSelected(Object *target){
    if(_door && target != _door){
        GetObjectCmdDialog *d = new GetObjectCmdDialog(target);
        d->setModal(true);
        connect(d, SIGNAL(cmdSelected(Object*,string)), this, SLOT(connectDoor(Object*,string)));
        d->exec();
        delete_obj(d);
    }
}

void AndDoorOptionWidget::connectDoor(Object *target, string cmd){
    _door->connect(target, cmd);
    ui->_connexionTable->insertRow(0);
    QTableWidgetItem *objname = new QTableWidgetItem(QString::fromStdString(target->getName()));
    QTableWidgetItem *cmdLbl  = new QTableWidgetItem(QString::fromStdString(cmd));
    ui->_connexionTable->setItem(0, 0, objname);
    ui->_connexionTable->setItem(0, 1, cmdLbl);
}

void AndDoorOptionWidget::setAndDoor(AndDoor *d){
    _door = d;
    if(_door){
        ui->_objectNameEdit->setText(QString::fromStdString(_door->getName()));
        ui->_connexionTable->clear();
        ui->_connexionTable->setRowCount(0);
        vector<pair<Object *, string>> links = _door->getConnexions();
        for(vector<pair<Object*, string>>::iterator it = links.begin(); it != links.end(); ++it){
            ui->_connexionTable->insertRow(0);
            QTableWidgetItem *objname = new QTableWidgetItem(QString::fromStdString(it->first->getName()));
            QTableWidgetItem *cmdLbl  = new QTableWidgetItem(QString::fromStdString(it->second));
            ui->_connexionTable->setItem(0, 0, objname);
            ui->_connexionTable->setItem(0, 1, cmdLbl);
        }
    }
}
