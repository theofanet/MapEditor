#ifndef SWITCHOPTIONWIDGET_H
#define SWITCHOPTIONWIDGET_H

#include <QWidget>

#include "map.h"
#include "Objects/Logical/switch.h"
#include "getobjectcmddialog.h"

namespace Ui {
class SwitchOptionWidget;
}

class SwitchOptionWidget : public QWidget{
    Q_OBJECT

public:
    explicit SwitchOptionWidget(QWidget *parent = 0);
    ~SwitchOptionWidget();
    
    void setSwitch(Switch *s);
    void setMap(Map *m);

private slots:
    void stateUpdated(bool checked);
    void selectTargetClicked(bool clicked);
    void targetSelected(Object *target);
    void connectSwitch(Object *target, string cmd);

private:
    Ui::SwitchOptionWidget *ui;

    Switch *_switch;
    Map    *_map;
};

#endif // SWITCHOPTIONWIDGET_H
