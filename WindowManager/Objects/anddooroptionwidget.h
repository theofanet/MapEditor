#ifndef ANDDOOROPTIONWIDGET_H
#define ANDDOOROPTIONWIDGET_H

#include <QWidget>

#include "Objects/Logical/anddoor.h"
#include "getobjectcmddialog.h"
#include "map.h"

namespace Ui {
class AndDoorOptionWidget;
}

class AndDoorOptionWidget : public QWidget{
    Q_OBJECT

public:
    explicit AndDoorOptionWidget(QWidget *parent = 0);
    ~AndDoorOptionWidget();

    void setAndDoor(AndDoor *d);
    void setMap(Map *m);

private slots:
    void selectTargetClicked(bool clicked);
    void targetSelected(Object *target);
    void connectDoor(Object *target, string cmd);

private:
    Ui::AndDoorOptionWidget *ui;

    AndDoor *_door;
    Map    *_map;
};

#endif // ANDDOOROPTIONWIDGET_H
