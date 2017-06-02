#ifndef PUSHBUTTONOPTIONWIDGET_H
#define PUSHBUTTONOPTIONWIDGET_H

#include <QWidget>
#include "Objects/Logical/pushbutton.h"
#include "map.h"
#include "getobjectcmddialog.h"

namespace Ui {
class PushButtonOptionWidget;
}

class PushButtonOptionWidget : public QWidget{
    Q_OBJECT

public:
    explicit PushButtonOptionWidget(QWidget *parent = 0);
    ~PushButtonOptionWidget();

    void setPushButton(PushButton *b);
    void setMap(Map *m);

private slots:
    void pushSlot(bool checked);
    void selectTargetClicked(bool clicked);
    void targetSelected(Object *target);
    void connectButton(Object *target, string cmd);

private:
    Ui::PushButtonOptionWidget *ui;

    PushButton *_button;
    Map        *_map;
};

#endif // PUSHBUTTONOPTIONWIDGET_H
