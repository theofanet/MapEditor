#include "switchoptionwidget.h"
#include "ui_switchoptionwidget.h"

SwitchOptionWidget::SwitchOptionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SwitchOptionWidget)
{
    setFixedWidth(300);
    ui->setupUi(this);

    _switch = NULL;
    _map    = NULL;

    connect(ui->_initialStateCheckBox, SIGNAL(toggled(bool)), this, SLOT(stateUpdated(bool)));
    connect(ui->_addConnexionButton, SIGNAL(clicked(bool)), this, SLOT(selectTargetClicked(bool)));
}

SwitchOptionWidget::~SwitchOptionWidget()
{
    delete ui;
}

void SwitchOptionWidget::setMap(Map *m){
    if(!_map || _map != m){
        _map = m;
        if(_map)
            connect(_map, SIGNAL(switchTargetSelected(Object *)), this, SLOT(targetSelected(Object*)));
    }
}

void SwitchOptionWidget::selectTargetClicked(bool){
    if(_map)
        _map->setEditionMode(EDIT_MODE_SWITCH_SELECT_TARGET);
}

void SwitchOptionWidget::targetSelected(Object *target){
    if(_switch && target != _switch){
        GetObjectCmdDialog *d = new GetObjectCmdDialog(target);
        d->setModal(true);
        connect(d, SIGNAL(cmdSelected(Object*,string)), this, SLOT(connectSwitch(Object*,string)));
        d->exec();
        delete_obj(d);
    }
}

void SwitchOptionWidget::connectSwitch(Object *target, string cmd){
    _switch->connect(target, cmd);
    ui->_connexionTable->insertRow(0);
    QTableWidgetItem *objname = new QTableWidgetItem(QString::fromStdString(target->getName()));
    QTableWidgetItem *cmdLbl  = new QTableWidgetItem(QString::fromStdString(cmd));
    ui->_connexionTable->setItem(0, 0, objname);
    ui->_connexionTable->setItem(0, 1, cmdLbl);
}

void SwitchOptionWidget::stateUpdated(bool checked){
    if(_switch)
        _switch->setState(checked);
}

void SwitchOptionWidget::setSwitch(Switch *s){
    _switch = s;
    if(_switch){
        ui->_objectNameEdit->setText(QString::fromStdString(s->getName()));
        ui->_initialStateCheckBox->setChecked(s->isOn());
        ui->_connexionTable->clear();
        ui->_connexionTable->setRowCount(0);
        vector<pair<Object *, string>> links = _switch->getConnexions();
        for(vector<pair<Object*, string>>::iterator it = links.begin(); it != links.end(); ++it){
            ui->_connexionTable->insertRow(0);
            QTableWidgetItem *objname = new QTableWidgetItem(QString::fromStdString(it->first->getName()));
            QTableWidgetItem *cmdLbl  = new QTableWidgetItem(QString::fromStdString(it->second));
            ui->_connexionTable->setItem(0, 0, objname);
            ui->_connexionTable->setItem(0, 1, cmdLbl);
        }
    }
}
