#include "particleemitteroptionwidget.h"
#include "ui_particleemitteroptionwidget.h"

ParticleEmitterOptionWidget::ParticleEmitterOptionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParticleEmitterOptionWidget)
{
    ui->setupUi(this);
    setFixedWidth(400);
    _emitter = NULL;

    connect(ui->_particuleLifeEdit, SIGNAL(valueChanged(int)), this, SLOT(particuleLifeUpdated(int)));
    connect(ui->_particuleSizeEdit, SIGNAL(valueChanged(int)), this, SLOT(particuleSizeUpdated(int)));
    connect(ui->_particuleSpeedEdit, SIGNAL(valueChanged(int)), this, SLOT(particuleSpeedUpdated(int)));
    connect(ui->_particuleAngleEdit, SIGNAL(valueChanged(int)), this, SLOT(particuleAngleUpdate(int)));
    connect(ui->_particuleDeltaAngleEdit, SIGNAL(valueChanged(int)), this, SLOT(particuleAngleDeltaUpdated(int)));
    connect(ui->_updateAlphaEdit, SIGNAL(toggled(bool)), this, SLOT(updateParticuleAlphaUpdated(bool)));
    connect(ui->_updateSizeEdit, SIGNAL(toggled(bool)), this, SLOT(updateParticuleSizeUpdated(bool)));
    connect(ui->_particuleGravityXEdit, SIGNAL(textChanged(QString)), this, SLOT(gravityXChanged(QString)));
    connect(ui->_particuleGravityYEdit, SIGNAL(textChanged(QString)), this, SLOT(gravityYChanged(QString)));
    connect(ui->_colorRedEdit, SIGNAL(valueChanged(int)), this, SLOT(particuleColorRedUpdated(int)));
    connect(ui->_colorGreenEdit, SIGNAL(valueChanged(int)), this, SLOT(particuleColorGreenUpdated(int)));
    connect(ui->_colorBlueEdit, SIGNAL(valueChanged(int)), this, SLOT(particuleColorBlueUpdated(int)));
    connect(ui->_endColorRedEdit, SIGNAL(valueChanged(int)), this, SLOT(particuleEndColorRedUpdated(int)));
    connect(ui->_endColorGreenEdit, SIGNAL(valueChanged(int)), this, SLOT(particuleEndColorGreenUpdated(int)));
    connect(ui->_endColorBlueEdit, SIGNAL(valueChanged(int)), this, SLOT(particuleEndColorBlueUpdated(int)));
    connect(ui->_endColorEdit, SIGNAL(toggled(bool)), this, SLOT(setEndColorUpdated(bool)));
    connect(ui->_emitterWidthEdit, SIGNAL(valueChanged(int)), this, SLOT(emitterWidthUpdated(int)));
    connect(ui->_emitterHeightEdit, SIGNAL(valueChanged(int)), this, SLOT(emitterHeightUpdated(int)));
    connect(ui->_emitterQtyEdit, SIGNAL(valueChanged(int)), this, SLOT(emitterNbParticuleUpdated(int)));
    connect(ui->_chooseColorButton, SIGNAL(clicked(bool)), this, SLOT(chooseColorClicked(bool)));
    connect(ui->_chooseEndColorButton, SIGNAL(clicked(bool)), this, SLOT(chooseEndColorClicked(bool)));
    connect(ui->_particleUseTextureCheckbox, SIGNAL(toggled(bool)), this, SLOT(particleUseTextureUpdated(bool)));
}

ParticleEmitterOptionWidget::~ParticleEmitterOptionWidget()
{
    delete ui;
}


void ParticleEmitterOptionWidget::particuleLifeUpdated(int lifeRaw){
    if(_emitter)
        _emitter->setLife(15.0 * ((double)lifeRaw / (double)ui->_particuleLifeEdit->maximum()));
}

void ParticleEmitterOptionWidget::particuleSizeUpdated(int sizeRaw){
    if(_emitter)
        _emitter->setSize(15.0 * ((double)sizeRaw / (double)ui->_particuleSizeEdit->maximum()));
}

void ParticleEmitterOptionWidget::particuleSpeedUpdated(int speedRaw){
    if(_emitter)
        _emitter->setSpeed(15.0 * ((double)speedRaw / (double)ui->_particuleSpeedEdit->maximum()));
}

void ParticleEmitterOptionWidget::particuleAngleUpdate(int angleRaw){
    if(_emitter)
        _emitter->setAngle((double)angleRaw / 1000.0);
}

void ParticleEmitterOptionWidget::particuleAngleDeltaUpdated(int angleDelatRaw){
    if(_emitter)
        _emitter->setAndleDist((double)angleDelatRaw / 1000.0);
}

void ParticleEmitterOptionWidget::updateParticuleSizeUpdated(bool checked){
    if(_emitter)
        _emitter->setUpdateRadius(checked);
}

void ParticleEmitterOptionWidget::updateParticuleAlphaUpdated(bool checked){
    if(_emitter)
        _emitter->setUpdateAlpha(checked);
}

void ParticleEmitterOptionWidget::gravityXChanged(QString value){
    if(_emitter)
        _emitter->setGravity(b2Vec2(value.toDouble(), ui->_particuleGravityYEdit->text().toDouble()));
}

void ParticleEmitterOptionWidget::gravityYChanged(QString value){
    if(_emitter)
        _emitter->setGravity(b2Vec2(ui->_particuleGravityXEdit->text().toDouble(), value.toDouble()));
}

void ParticleEmitterOptionWidget::particuleColorRedUpdated(int redRaw){
    if(_emitter)
        _emitter->setColor(0, (double)redRaw/(double)ui->_colorRedEdit->maximum());
}

void ParticleEmitterOptionWidget::particuleColorGreenUpdated(int greenRaw){
    if(_emitter)
        _emitter->setColor(1, (double)greenRaw/(double)ui->_colorGreenEdit->maximum());
}

void ParticleEmitterOptionWidget::particuleColorBlueUpdated(int blueRaw){
    if(_emitter)
        _emitter->setColor(2, (double)blueRaw/(double)ui->_colorBlueEdit->maximum());
}

void ParticleEmitterOptionWidget::setEndColorUpdated(bool checked){
    if(_emitter)
        _emitter->setEndColorActive(checked);

    ui->_endColorRedEdit->setEnabled(checked);
    ui->_endColorGreenEdit->setEnabled(checked);
    ui->_endColorBlueEdit->setEnabled(checked);
    ui->_endColorRedLbl->setEnabled(checked);
    ui->_endColorGreenLbl->setEnabled(checked);
    ui->_endColorBlueLbl->setEnabled(checked);
    ui->_chooseEndColorButton->setEnabled(checked);
}

void ParticleEmitterOptionWidget::particuleEndColorRedUpdated(int redRaw){
    if(_emitter && ui->_endColorEdit->isChecked())
        _emitter->setEndColor(0, (double)redRaw/(double)ui->_endColorRedEdit->maximum());
}

void ParticleEmitterOptionWidget::particuleEndColorGreenUpdated(int greenRaw){
    if(_emitter && ui->_endColorEdit->isChecked())
        _emitter->setEndColor(1, (double)greenRaw/(double)ui->_endColorGreenEdit->maximum());
}

void ParticleEmitterOptionWidget::particuleEndColorBlueUpdated(int blueRaw){
    if(_emitter && ui->_endColorEdit->isChecked())
        _emitter->setEndColor(2, (double)blueRaw/(double)ui->_endColorBlueEdit->maximum());
}

void ParticleEmitterOptionWidget::emitterWidthUpdated(int valueRaw){
 if(_emitter){
     _emitter->setEmitteSize(b2Vec2(
                                 20*((double)valueRaw/(double)ui->_emitterWidthEdit->maximum()),
                                 20*((double)ui->_emitterHeightEdit->value() /(double)ui->_emitterHeightEdit->maximum())
                                 ));
 }
}

void ParticleEmitterOptionWidget::emitterHeightUpdated(int valueRaw){
    if(_emitter){
        _emitter->setEmitteSize(b2Vec2(
                                    20*((double)ui->_emitterWidthEdit->value() /(double)ui->_emitterWidthEdit->maximum()),
                                    20*((double)valueRaw/(double)ui->_emitterHeightEdit->maximum())
                                    ));
    }
}

void ParticleEmitterOptionWidget::emitterNbParticuleUpdated(int nbValue){
    if(_emitter)
        _emitter->setNbParticules(nbValue);
}

void ParticleEmitterOptionWidget::chooseColorClicked(bool){
    QColor init  = QColor((ui->_colorRedEdit->value()*255) / ui->_colorRedEdit->maximum(),
                          (ui->_colorGreenEdit->value()*255) / ui->_colorGreenEdit->maximum(),
                          (ui->_colorBlueEdit->value()*255) / ui->_colorBlueEdit->maximum());

    QColor color = QColorDialog::getColor(init, this);

    ui->_colorRedEdit->setValue((color.red() * ui->_colorRedEdit->maximum()) / 255);
    ui->_colorGreenEdit->setValue((color.green() * ui->_colorGreenEdit->maximum()) / 255);
    ui->_colorBlueEdit->setValue((color.blue() * ui->_colorBlueEdit->maximum()) / 255);

    if(_emitter)
        _emitter->setColor((double)color.red()/255.0f, (double)color.green()/255.0f, (double)color.blue()/255.0f);
}

void ParticleEmitterOptionWidget::chooseEndColorClicked(bool){
    QColor init  = QColor((ui->_endColorRedEdit->value()*255) / ui->_endColorRedEdit->maximum(),
                          (ui->_endColorGreenEdit->value()*255) / ui->_endColorGreenEdit->maximum(),
                          (ui->_endColorBlueEdit->value()*255) / ui->_endColorBlueEdit->maximum());

    QColor color = QColorDialog::getColor(init, this);

    ui->_endColorRedEdit->setValue((color.red() * ui->_endColorRedEdit->maximum()) / 255);
    ui->_endColorGreenEdit->setValue((color.green() * ui->_endColorGreenEdit->maximum()) / 255);
    ui->_endColorBlueEdit->setValue((color.blue() * ui->_endColorBlueEdit->maximum()) / 255);

    if(_emitter)
        _emitter->setEndColor((double)color.red()/255.0f, (double)color.green()/255.0f, (double)color.blue()/255.0f);
}

void ParticleEmitterOptionWidget::particleUseTextureUpdated(bool checked){
    if(_emitter)
        _emitter->setShowingTexture(checked);
}

void ParticleEmitterOptionWidget::setEmitter(ParticleEmitter *e){
    _emitter = e;
    if(_emitter){
        ui->_objectName->setText(QString(_emitter->getName().c_str()));
        ui->_particuleLifeEdit->setValue(e->getLife()*ui->_particuleLifeEdit->maximum()/15.0f);
        ui->_particuleSizeEdit->setValue(e->getSize()*ui->_particuleSizeEdit->maximum()/15.0f);
        ui->_particuleSpeedEdit->setValue(e->getSpeed()*ui->_particuleSpeedEdit->maximum()/15.0f);
        ui->_particuleAngleEdit->setValue(e->getAngle()*1000.0);
        ui->_particuleDeltaAngleEdit->setValue(e->getAngleDelta()*1000.0);
        ui->_updateAlphaEdit->setChecked(e->getUpdateAlpha());
        ui->_updateSizeEdit->setChecked(e->getUpdateRadius());
        ui->_particuleGravityXEdit->setText(QString::number(e->getGravity().x));
        ui->_particuleGravityYEdit->setText(QString::number(e->getGravity().y));
        ui->_colorRedEdit->setValue(e->getColor(0)*ui->_colorRedEdit->maximum());
        ui->_colorGreenEdit->setValue(e->getColor(1)*ui->_colorGreenEdit->maximum());
        ui->_colorBlueEdit->setValue(e->getColor(2)*ui->_colorBlueEdit->maximum());
        ui->_endColorRedEdit->setValue(e->getEndColor(0)*ui->_endColorRedEdit->maximum());
        ui->_endColorGreenEdit->setValue(e->getEndColor(1)*ui->_endColorGreenEdit->maximum());
        ui->_endColorBlueEdit->setValue(e->getEndColor(2)*ui->_endColorBlueEdit->maximum());
        ui->_endColorEdit->setChecked(e->isEndColorActive());
        ui->_emitterWidthEdit->setValue(ui->_emitterWidthEdit->maximum()*e->getEmitteSize().x/20);
        ui->_emitterHeightEdit->setValue(ui->_emitterHeightEdit->maximum()*e->getEmitteSize().y/20);
        ui->_emitterQtyEdit->setValue(e->getNbParticules());
        ui->_particleUseTextureCheckbox->setChecked(e->isShowingTexture());
    }
}
