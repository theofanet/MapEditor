#ifndef NODOOROPTIONWIDGET_H
#define NODOOROPTIONWIDGET_H

#include <QWidget>
#include "Objects/Logical/nodoor.h"
#include "getobjectcmddialog.h"
#include "map.h"

namespace Ui {
class NoDoorOptionWidget;
}

class NoDoorOptionWidget : public QWidget{
    Q_OBJECT

public:
    explicit NoDoorOptionWidget(QWidget *parent = 0);
    ~NoDoorOptionWidget();

    void setNoDoor(NoDoor *d);
    void setMap(Map *m);

private slots:
    void selectTargetClicked(bool clicked);
    void targetSelected(Object *target);
    void connectDoor(Object *target, string cmd);

private:
    Ui::NoDoorOptionWidget *ui;

    NoDoor *_door;
    Map    *_map;
};

#endif // NODOOROPTIONWIDGET_H
