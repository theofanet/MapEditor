#ifndef PARTICLEEMITTEROPTIONWIDGET_H
#define PARTICLEEMITTEROPTIONWIDGET_H

#include <QWidget>

#include "Objects/ParticleEmitter.h"

namespace Ui {
class ParticleEmitterOptionWidget;
}

class ParticleEmitterOptionWidget : public QWidget{
    Q_OBJECT
public:
    explicit ParticleEmitterOptionWidget(QWidget *parent = 0);
    ~ParticleEmitterOptionWidget();

    void setEmitter(ParticleEmitter *e);

private slots:
    void particuleLifeUpdated(int lifeRaw);
    void particuleSizeUpdated(int sizeRaw);
    void particuleSpeedUpdated(int speedRaw);
    void particuleAngleUpdate(int angleRaw);
    void particuleAngleDeltaUpdated(int angleDelatRaw);
    void updateParticuleSizeUpdated(bool checked);
    void updateParticuleAlphaUpdated(bool checked);
    void gravityXChanged(QString value);
    void gravityYChanged(QString value);
    void particuleColorRedUpdated(int redRaw);
    void particuleColorGreenUpdated(int redRaw);
    void particuleColorBlueUpdated(int redRaw);
    void setEndColorUpdated(bool checked);
    void particuleEndColorRedUpdated(int redRaw);
    void particuleEndColorGreenUpdated(int redRaw);
    void particuleEndColorBlueUpdated(int redRaw);
    void emitterWidthUpdated(int valueRaw);
    void emitterHeightUpdated(int valueRaw);
    void emitterNbParticuleUpdated(int nbValue);
    void chooseColorClicked(bool clicked);
    void chooseEndColorClicked(bool clicked);
    void particleUseTextureUpdated(bool checked);

private:
    Ui::ParticleEmitterOptionWidget *ui;
    ParticleEmitter *_emitter;
};

#endif // PARTICLEEMITTEROPTIONWIDGET_H
