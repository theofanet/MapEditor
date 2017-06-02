#ifndef LASEROPTIONWIDGET_H
#define LASEROPTIONWIDGET_H

#include <QWidget>
#include "Utilities/defines.h"
#include "Objects/laser.h"

namespace Ui {
class LaserOptionWidget;
}

class LaserOptionWidget : public QWidget{
    Q_OBJECT

public:
    explicit LaserOptionWidget(QWidget *parent = 0);
    ~LaserOptionWidget();

    GLfloat getPower();
    GLfloat getAngle();

    void setLaser(Laser *laser);

private slots:
    void powerUpdate(int powerRaw);
    void angleUpdate(int angleRaw);
    void colorRedUpdate(int redRaw);
    void colorGreenUpdate(int greenRaw);
    void colorBlueUpdate(int blueRaw);
    void chooseColorClicked(bool clicked);
    void autoRotatioChanged(bool checked);
    void autoStartAngleChanged(QString startAngleValue);
    void autoEndAngleChanged(QString endAngleValue);
    void autoStepChanged(QString stepValue);

private:
    Ui::LaserOptionWidget *ui;
    Laser *_laser;
};

#endif // LASEROPTIONWIDGET_H
