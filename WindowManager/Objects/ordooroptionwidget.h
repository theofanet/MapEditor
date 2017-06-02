#ifndef ORDOOROPTIONWIDGET_H
#define ORDOOROPTIONWIDGET_H

#include <QWidget>
#include "Objects/Logical/ordoor.h"
#include "getobjectcmddialog.h"
#include "map.h"

namespace Ui {
class OrDoorOptionWidget;
}

class OrDoorOptionWidget : public QWidget{
    Q_OBJECT

public:
    explicit OrDoorOptionWidget(QWidget *parent = 0);
    ~OrDoorOptionWidget();

    void setOrDoor(OrDoor *d);
    void setMap(Map *m);

private slots:
    void selectTargetClicked(bool clicked);
    void targetSelected(Object *target);
    void connectDoor(Object *target, string cmd);

private:
    Ui::OrDoorOptionWidget *ui;

    OrDoor *_door;
    Map    *_map;
};

#endif // ORDOOROPTIONWIDGET_H
