#include "laseroptionwidget.h"
#include "ui_laseroptionwidget.h"

LaserOptionWidget::LaserOptionWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LaserOptionWidget){
    ui->setupUi(this);

    connect(ui->_powerEdit, SIGNAL(valueChanged(int)), this, SLOT(powerUpdate(int)));
    connect(ui->_angleEdit, SIGNAL(valueChanged(int)), this, SLOT(angleUpdate(int)));
    connect(ui->_chooseColorButton, SIGNAL(clicked(bool)), this, SLOT(chooseColorClicked(bool)));
    connect(ui->_colorRedEdit, SIGNAL(valueChanged(int)), this, SLOT(colorRedUpdate(int)));
    connect(ui->_colorGreenEdit, SIGNAL(valueChanged(int)), this, SLOT(colorGreenUpdate(int)));
    connect(ui->_colorBlueEdit, SIGNAL(valueChanged(int)), this, SLOT(colorBlueUpdate(int)));
    connect(ui->_automaticRotationCheckbox, SIGNAL(toggled(bool)), this, SLOT(autoRotatioChanged(bool)));
    connect(ui->_autoAngleStartEdit, SIGNAL(textChanged(QString)), this, SLOT(autoStartAngleChanged(QString)));
    connect(ui->_autoAngleEndEdit, SIGNAL(textChanged(QString)), this, SLOT(autoEndAngleChanged(QString)));
    connect(ui->_autoAngleStepEdit, SIGNAL(textChanged(QString)), this, SLOT(autoStepChanged(QString)));

    _laser = NULL;
    setFixedWidth(300);
}

LaserOptionWidget::~LaserOptionWidget(){
    delete ui;
}

GLfloat LaserOptionWidget::getPower(){
    return (double)(ui->_powerEdit->value()/100.0f);
}

GLfloat LaserOptionWidget::getAngle(){
    return (double)(ui->_angleEdit->value()/100.0f);
}

void LaserOptionWidget::powerUpdate(int powerRaw){
    if(_laser)
        _laser->setPower((double)(powerRaw)/100.0f);
}

void LaserOptionWidget::angleUpdate(int angleRaw){
    if(_laser)
        _laser->setAngle((double)(angleRaw)/100.0f);
}

void LaserOptionWidget::colorRedUpdate(int redRaw){
    if(_laser)
        _laser->setColor(0, (double)redRaw / (double)ui->_colorRedEdit->maximum());
}

void LaserOptionWidget::colorGreenUpdate(int greenRaw){
    if(_laser)
        _laser->setColor(1, (double)greenRaw / (double)ui->_colorGreenEdit->maximum());
}

void LaserOptionWidget::colorBlueUpdate(int blueRaw){
    if(_laser)
        _laser->setColor(2, (double)blueRaw / (double)ui->_colorBlueEdit->maximum());
}

void LaserOptionWidget::chooseColorClicked(bool){
    QColor init  = QColor((ui->_colorRedEdit->value()*255) / ui->_colorRedEdit->maximum(),
                          (ui->_colorGreenEdit->value()*255) / ui->_colorGreenEdit->maximum(),
                          (ui->_colorBlueEdit->value()*255) / ui->_colorBlueEdit->maximum());

    QColor color = QColorDialog::getColor(init, this);

    ui->_colorRedEdit->setValue((color.red() * ui->_colorRedEdit->maximum()) / 255);
    ui->_colorGreenEdit->setValue((color.green() * ui->_colorGreenEdit->maximum()) / 255);
    ui->_colorBlueEdit->setValue((color.blue() * ui->_colorBlueEdit->maximum()) / 255);

    if(_laser)
        _laser->setColor((double)color.red()/255.0f, (double)color.green()/255.0f, (double)color.blue()/255.0f);
}

void LaserOptionWidget::autoRotatioChanged(bool checked){
    ui->_angleEdit->setEnabled(!checked);
    ui->_angleLabel->setEnabled(!checked);

    ui->_autoAngleStepEdit->setEnabled(checked);
    ui->_autoAngleStartEdit->setEnabled(checked);
    ui->_autoAngleEndEdit->setEnabled(checked);
    ui->_autoAngleStepLbl->setEnabled(checked);
    ui->_autoAngleStartLbl->setEnabled(checked);
    ui->_autoAngleEndLbl->setEnabled(checked);

    if(_laser){
        _laser->setAutoRoatation(checked);
        if(!checked)
            _laser->setAngle((double)(ui->_angleEdit->value())/100.0f);
    }
}

void LaserOptionWidget::autoStepChanged(QString stepValue){
    if(_laser)
        _laser->setAutoRotationStep(stepValue.toDouble());
}

void LaserOptionWidget::autoStartAngleChanged(QString angleValue){
    if(_laser)
        _laser->setAutoRotationStartAngle(angleValue.toDouble());
}

void LaserOptionWidget::autoEndAngleChanged(QString angleValue){
    if(_laser)
        _laser->setAutoRotationEndAngle(angleValue.toDouble());
}

void LaserOptionWidget::setLaser(Laser *laser){
    _laser = laser;
    if(_laser){
        ui->_objectName->setText(QString(_laser->getName().c_str()));

        ui->_powerEdit->setValue(_laser->getPower()*100);
        ui->_angleEdit->setValue(_laser->getAngle()*100);

        ui->_colorRedEdit->setValue(_laser->getColor(0)*ui->_colorRedEdit->maximum());
        ui->_colorGreenEdit->setValue(_laser->getColor(1)*ui->_colorGreenEdit->maximum());
        ui->_colorBlueEdit->setValue(_laser->getColor(2)*ui->_colorBlueEdit->maximum());

        ui->_automaticRotationCheckbox->setChecked(_laser->getAutoRotation());
        ui->_autoAngleStepEdit->setText(QString::number(_laser->getAutoRotationStep()));
        ui->_autoAngleStartEdit->setText(QString::number(_laser->getAutoRotationStartAngle()));
        ui->_autoAngleEndEdit->setText(QString::number(_laser->getAutoRotationEndAngle()));
    }
}
