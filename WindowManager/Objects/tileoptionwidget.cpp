#include "tileoptionwidget.h"

TileOptionWidget::TileOptionWidget(QWidget *parent) : QWidget(parent){
    QFormLayout *layout = new QFormLayout(this);

    _labelNbSelected = new QLabel(this);
    _labelNbSelected->setText("0 Tuile");

    _labelMultipleValue = new QLabel(this);
    _labelMultipleValue->setText("Valeurs multiples");
    _labelMultipleValue->hide();

    _destructible = new QCheckBox(this);
    _destructible->setChecked(true);
    connect(_destructible, SIGNAL(toggled(bool)), this, SLOT(setDestructibleData(bool)));

    _climbable = new QCheckBox(this);
    _climbable->setChecked(false);
    connect(_climbable, SIGNAL(toggled(bool)), this, SLOT(setClimbableData(bool)));

    _slippery = new QCheckBox(this);
    _slippery->setChecked(false);
    connect(_slippery, SIGNAL(toggled(bool)), this, SLOT(setSlipperyData(bool)));

    _deadly = new QCheckBox(this);
    _deadly->setChecked(false);
    connect(_deadly, SIGNAL(toggled(bool)), this, SLOT(setDeadlyData(bool)));

    _horizontalMove = new QCheckBox(this);
    _horizontalMove->setChecked(false);
    connect(_horizontalMove, SIGNAL(toggled(bool)), this, SLOT(setHorizontalMoveData(bool)));

    _horizontalMoveSpeed = new QLineEdit(this);
    _horizontalMoveSpeed->setText("1.0");
    connect(_horizontalMoveSpeed, SIGNAL(editingFinished()), this, SLOT(setHorizontalMoveData()));

    _horizontalMoveMax = new QLineEdit(this);
    _horizontalMoveMax->setText("6.0");
    connect(_horizontalMoveMax, SIGNAL(editingFinished()), this, SLOT(setHorizontalMoveData()));


    setFixedWidth(300);
    layout->addRow(_labelNbSelected);
    layout->addRow(_labelMultipleValue);
    layout->addItem(new QSpacerItem(200, 20));
    layout->addRow("Est cassable", _destructible);
    layout->addRow("Est montable", _climbable);
    layout->addRow("Est glissant", _slippery);
    layout->addRow("Est mortel", _deadly);
    layout->addItem(new QSpacerItem(200, 20));
    layout->addRow("Mouvement horizontal", _horizontalMove);
    layout->addRow("Vitesse", _horizontalMoveSpeed);
    layout->addRow("Max", _horizontalMoveMax);
    setLayout(layout);
}

void TileOptionWidget::setSelectedObjects(vector<MapTile*> tiles){
    _tiles = tiles;
    update();
}

void TileOptionWidget::update(){
    QString label = QString::number(_tiles.size()) + " Tuile";
    if(_tiles.size() > 1)
        label += "s";
    _labelNbSelected->setText(label);

    _labelMultipleValue->hide();

    bool destructible = true;
    bool climbable    = false;
    bool slippery     = false;
    bool deadly       = false;
    bool multi        = false;
    bool horizontal   = false;
    GLfloat horizontalSpeed = 1.0f;
    GLfloat horizontalMax   = 6.0f;

    if(_tiles.size() > 0){
        destructible = _tiles.at(0)->isDestructible();
        climbable    = _tiles.at(0)->isClimbable();
        slippery     = _tiles.at(0)->isSlippery();
        deadly       = _tiles.at(0)->isDeadly();
        horizontal   = _tiles.at(0)->getHorizontalMove();
        horizontalSpeed = fabs(_tiles.at(0)->getHorizontalMoveSpeed());
        horizontalMax   = _tiles.at(0)->getHorizontalMoveMax();

        for(size_t i = 0; i < _tiles.size(); i++){
            if(_tiles.at(i)->isDestructible() != destructible){
                destructible = false;
                multi        = true;
            }

            if(_tiles.at(i)->isClimbable() != climbable){
                climbable = false;
                multi     = true;
            }

            if(_tiles.at(i)->isSlippery() != slippery){
                slippery = false;
                multi    = true;
            }

            if(_tiles.at(i)->isDeadly() != deadly){
                deadly = false;
                multi  = true;
            }

            if(_tiles.at(i)->getHorizontalMove() != horizontal){
                multi      = true;
            }
        }
    }

    if(multi)
        _labelMultipleValue->show();

    _destructible->setChecked(destructible);
    _climbable->setChecked(climbable);
    _slippery->setChecked(slippery);
    _deadly->setChecked(deadly);
    _horizontalMove->setChecked(horizontal);
    _horizontalMoveMax->setText(QString::number(horizontalMax));
    _horizontalMoveSpeed->setText(QString::number(horizontalSpeed));
}

void TileOptionWidget::setDestructibleData(bool d){
    for(size_t i = 0; i < _tiles.size(); i++){
        _tiles.at(i)->setDestructible(d);
    }
}

void TileOptionWidget::setClimbableData(bool c){
    for(size_t i = 0; i < _tiles.size(); i++){
        _tiles.at(i)->setClimbable(c);
    }
}

void TileOptionWidget::setSlipperyData(bool s){
    for(size_t i = 0; i < _tiles.size(); i++){
        _tiles.at(i)->setSlippery(s);
    }
}

void TileOptionWidget::setDeadlyData(bool d){
    for(size_t i = 0; i < _tiles.size(); i++){
        _tiles.at(i)->setDeadly(d);
    }
}


void TileOptionWidget::setHorizontalMoveData(bool){
    if(_horizontalMove->isChecked()){
        GLfloat speed = _horizontalMoveSpeed->text().toFloat();
        GLfloat max   = _horizontalMoveMax->text().toFloat();

        for(size_t i = 0; i < _tiles.size(); i++)
            _tiles.at(i)->setHorizontalMove(true, speed, max);
    }
    else{
        for(size_t i = 0; i < _tiles.size(); i++)
            _tiles.at(i)->setHorizontalMove(false);
    }
}
