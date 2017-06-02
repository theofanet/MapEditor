#include "getobjectcmddialog.h"
#include "ui_getobjectcmddialog.h"

GetObjectCmdDialog::GetObjectCmdDialog(Object* obj, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetObjectCmdDialog)
{
    ui->setupUi(this);

    _object = obj;
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(cmdChoosed()));

    ui->_objectCmdComboBox->addItem("Choisir ...");
    vector<string> cmdList = _object->getCmdList();
    for(vector<string>::iterator it = cmdList.begin(); it != cmdList.end(); ++it)
        ui->_objectCmdComboBox->addItem(QString::fromStdString(*it));
}

GetObjectCmdDialog::~GetObjectCmdDialog()
{
    delete ui;
}

void GetObjectCmdDialog::cmdChoosed(){
    int indexCmd = ui->_objectCmdComboBox->currentIndex();
    if(indexCmd){
        emit cmdSelected(_object, ui->_objectCmdComboBox->currentText().toStdString());
        accept();
    }
}
