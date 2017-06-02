#include "plateformoptionwidget.h"
#include "ui_plateformoptionwidget.h"

PlateformOptionWidget::PlateformOptionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlateformOptionWidget){
    setFixedWidth(300);
    ui->setupUi(this);
    _platform = NULL;
    _map      = NULL;

    _addingPoints = false;

    connect(ui->_addPointButton, SIGNAL(clicked(bool)), this, SLOT(addPointClicked(bool)));
    connect(ui->_isMovingCheckbox, SIGNAL(toggled(bool)), this, SLOT(setMovingChecked(bool)));
    connect(ui->_normalizeDirectionCheckbox, SIGNAL(toggled(bool)), this, SLOT(setNormalizeDirectionChecked(bool)));
    connect(ui->_speedSlider, SIGNAL(valueChanged(int)), this, SLOT(speedUpdated(int)));
    connect(ui->_circleMovementCheckbox, SIGNAL(toggled(bool)), this, SLOT(cicleMovementChecked(bool)));
    connect(ui->_widthEdit, SIGNAL(textChanged(QString)), this, SLOT(widthUpdated(QString)));
    connect(ui->_heightEdit, SIGNAL(textChanged(QString)), this, SLOT(heightUpdated(QString)));
    connect(ui->_showTextureCheckbox, SIGNAL(toggled(bool)), this, SLOT(showingTextureChecked(bool)));
    connect(ui->_loadTextureButton, SIGNAL(clicked(bool)), this, SLOT(loadTextureClicked(bool)));
}

PlateformOptionWidget::~PlateformOptionWidget(){
    delete ui;
}

void PlateformOptionWidget::setPlatform(Platform *p){
    _platform = p;
    if(_platform){
        ui->_objectNameEdit->setText(QString::fromStdString(_platform->getName()));
        ui->_pointsTable->clear();
        ui->_pointsTable->setRowCount(0);
        vector<b2Vec2> pts = _platform->getPoints();
        for(vector<b2Vec2>::iterator it = pts.begin(); it != pts.end(); ++it){
            b2Vec2 p = *it;
            ui->_pointsTable->insertRow(0);
            QTableWidgetItem *pos = new QTableWidgetItem(QString::number(p.x) + "x" + QString::number(p.y));
            ui->_pointsTable->setItem(0, 0, pos);
        }
        ui->_widthEdit->setText(QString::number(_platform->getSize().x));
        ui->_heightEdit->setText(QString::number(_platform->getSize().y));
        ui->_isMovingCheckbox->setChecked(_platform->isMoving());
        ui->_normalizeDirectionCheckbox->setChecked(!_platform->getNormalizeDirection());
        ui->_speedSlider->setValue((ui->_speedSlider->maximum() * _platform->getSpeed()) / 10.0f);
        ui->_showTextureCheckbox->setChecked(_platform->isShowingTexture());
        ui->_loadTextureButton->setEnabled(_platform->isShowingTexture());
    }
}

void PlateformOptionWidget::setMap(Map *m){
    if(!_map || _map != m){
        _map = m;
        if(_map)
            connect(_map, SIGNAL(platformPointAdded(b2Vec2)), this, SLOT(pointAdded(b2Vec2)));
    }
}

void PlateformOptionWidget::addPointClicked(bool){
    if(_platform && _map){
        _addingPoints = !_addingPoints;
        if(_addingPoints){
            ui->_addPointButton->setText("Stop");
            _map->setEditionMode(EDIT_MODE_PLATFORM_ADD_POINT);
        }
        else{
            ui->_addPointButton->setText("Ajouter un point");
            _map->setEditionMode(EDIT_MODE_SELECT_OBJECT);
        }
    }
}

void PlateformOptionWidget::setMovingChecked(bool checked){
    if(_platform)
        _platform->setIsMoving(checked);

    ui->_speedLbl->setEnabled(checked);
    ui->_speedSlider->setEnabled(checked);
    ui->_normalizeDirectionCheckbox->setEnabled(checked);
}

void PlateformOptionWidget::setNormalizeDirectionChecked(bool checked){
    if(_platform)
        _platform->setNormalizeDirection(!checked);
}

void PlateformOptionWidget::speedUpdated(int speedRaw){
    if(_platform)
        _platform->setSpeed(((double)speedRaw / (double)ui->_speedSlider->maximum()) * 10.0f);
}

void PlateformOptionWidget::cicleMovementChecked(bool checked){
    if(_platform)
        _platform->setMovingCircle(checked);
}

void PlateformOptionWidget::widthUpdated(QString value){
    if(_platform)
        _platform->setWidth(value.toDouble());
}

void PlateformOptionWidget::heightUpdated(QString value){
    if(_platform)
        _platform->setHeight(value.toDouble());
}

void PlateformOptionWidget::showingTextureChecked(bool checked){
    if(_platform)
        _platform->showTexture(checked);
    ui->_loadTextureButton->setEnabled(checked);
}

void PlateformOptionWidget::loadTextureClicked(bool){
    QString filename = QFileDialog::getOpenFileName(this, tr("Charger une texture"),
                                                         QDir::homePath(),
                                                         "Images (*.png *.jpg *.jpeg)");

    if(_platform && !filename.isNull())
        _platform->setTexture(filename.toStdString());
}

void PlateformOptionWidget::pointAdded(b2Vec2 pts){
    if(_platform){
        _platform->addPoint(pts);
        ui->_pointsTable->insertRow(0);
        QTableWidgetItem *pos = new QTableWidgetItem(QString::number(pts.x) + "x" + QString::number(pts.y));
        ui->_pointsTable->setItem(0, 0, pos);
    }
}
