#include "pushbuttonoptionwidget.h"
#include "ui_pushbuttonoptionwidget.h"

PushButtonOptionWidget::PushButtonOptionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PushButtonOptionWidget)
{
    setFixedWidth(300);
    ui->setupUi(this);

    _button = NULL;
    _map    = NULL;

    connect(ui->_pushButton, SIGNAL(clicked(bool)), this, SLOT(pushSlot(bool)));
    connect(ui->_addConnexionButton, SIGNAL(clicked(bool)), this, SLOT(selectTargetClicked(bool)));
}

PushButtonOptionWidget::~PushButtonOptionWidget()
{
    delete ui;
}

void PushButtonOptionWidget::setMap(Map *m){
    if(!_map || _map != m){
        _map = m;
        if(_map)
            connect(_map, SIGNAL(pushButtonTargetSelected(Object *)), this, SLOT(targetSelected(Object*)));
    }
}

void PushButtonOptionWidget::selectTargetClicked(bool){
    if(_map)
        _map->setEditionMode(EDIT_MODE_PUSH_BUTTON_SELECT_TARGET);
}

void PushButtonOptionWidget::targetSelected(Object *target){
    if(_button && target != _button){
        GetObjectCmdDialog *d = new GetObjectCmdDialog(target);
        d->setModal(true);
        connect(d, SIGNAL(cmdSelected(Object*,string)), this, SLOT(connectButton(Object*,string)));
        d->exec();
        delete_obj(d);
    }
}

void PushButtonOptionWidget::connectButton(Object *target, string cmd){
    if(_button){
        _button->connect(target, cmd);
        ui->_connexionTable->insertRow(0);
        QTableWidgetItem *objname = new QTableWidgetItem(QString::fromStdString(target->getName()));
        QTableWidgetItem *cmdLbl  = new QTableWidgetItem(QString::fromStdString(cmd));
        ui->_connexionTable->setItem(0, 0, objname);
        ui->_connexionTable->setItem(0, 1, cmdLbl);
    }
}

void PushButtonOptionWidget::pushSlot(bool){
    if(_button)
        _button->push();
}

void PushButtonOptionWidget::setPushButton(PushButton *b){
    _button = b;
    if(_button){
        ui->_objectNameEdit->setText(QString::fromStdString(_button->getName()));
        ui->_connexionTable->clear();
        ui->_connexionTable->setRowCount(0);
        vector<pair<Object *, string>> links = _button->getConnexions();
        for(vector<pair<Object*, string>>::iterator it = links.begin(); it != links.end(); ++it){
            ui->_connexionTable->insertRow(0);
            QTableWidgetItem *objname = new QTableWidgetItem(QString::fromStdString(it->first->getName()));
            QTableWidgetItem *cmdLbl  = new QTableWidgetItem(QString::fromStdString(it->second));
            ui->_connexionTable->setItem(0, 0, objname);
            ui->_connexionTable->setItem(0, 1, cmdLbl);
        }
    }
}
