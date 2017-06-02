#ifndef PLATEFORMOPTIONWIDGET_H
#define PLATEFORMOPTIONWIDGET_H

#include <QWidget>
#include "Objects/platform.h"
#include "map.h"

namespace Ui {
class PlateformOptionWidget;
}

class PlateformOptionWidget : public QWidget{
    Q_OBJECT

public:
    explicit PlateformOptionWidget(QWidget *parent = 0);
    ~PlateformOptionWidget();

    void setPlatform(Platform *p);
    void setMap(Map *map);

private slots:
    void addPointClicked(bool clicked);
    void pointAdded(b2Vec2 pts);
    void setMovingChecked(bool checked);
    void setNormalizeDirectionChecked(bool checked);
    void speedUpdated(int speedRaw);
    void cicleMovementChecked(bool checked);
    void widthUpdated(QString value);
    void heightUpdated(QString value);
    void showingTextureChecked(bool checked);
    void loadTextureClicked(bool clicked);

private:
    Ui::PlateformOptionWidget *ui;

    bool _addingPoints;

    Platform *_platform;
    Map      *_map;
};

#endif // PLATEFORMOPTIONWIDGET_H
