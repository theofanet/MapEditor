#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QTabWidget>
#include <QAction>
#include <QComboBox>

#include "Utilities/defines.h"
#include "editortab.h"
#include "Dialog/newmapdialog.h"
#include "Dialog/addtilesetdialog.h"
#include "Utilities/mapjsondata.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newTabAction();
    void saveMapClicked();
    void loadMapClicked();
    void addSpriteClicked();
    void createNewTabWithData(NewMapDialog *dialog);
    void addTilesetWithData(AddTilesetDialog *dialog);
    void setEditorNewMap(Map *map);
    void setCurrentTabMode(editionMode newMode);
    void setCurrentTabModeAdd();
    void setCurrentTabModeAddPaintBucket();
    void setCurrentTabModeErase();
    void setCurrentTabModeEdit();
    void setCurrentTabSelectionMode();
    void SetCurrentTabFlagMode();
    void SetCurrentTabStartPositionMode();
    void SetCurrentTabEndPositionMode();
    void toggleCurrentTabTopLayer();
    void toggleCurrentTabBackLayer();
    void toggleCurrentTabMiddleLayer();
    void addToLayerChanged(int index);
    void chooseObjectModeToAdd();
    void setAddLaserMode();
    void setAddJetonMode();
    void setAddEmitterMode();
    void setAddPlatformMode();
    void setAddSwitchMode();
    void setAddPushButtonMode();
    void setAddAndDoorMode();
    void setAddOrDoorMode();
    void setAddNoDoorMode();
    void chooseObjectModeToSelect();
    void setSelectObjectMode();
    void setRemoveObjectMode();
    void backgroundColorClicked();

private:
    QToolBar   *_toolbar;

    EditorTab *_editorWidget;
    QVBoxLayout *_mainLayout;

    QAction *_saveMapAction, *_loadMapAction, *_addSpriteAction, *_setBackgroundColorAction;
    QAction *_setAddTileModeAction, *_setEraseTileModeAction, *_setFlagMode;
    QAction *_setEditTileModeAction, *_setSelectionTileMode;
    QAction *_setStartPositionMode, *_setEndPositionMode;
    QAction *_setAddPaintBucketMode;
    QAction *_setAddObjectModeAction, *_setSelectObjectModeAction;
    QAction *_toggleTopLayerAction, *_toggleMiddleLayerAction, *_toggleBottomLayerAction;

    QMenu *_addObjectSelectionMenu, *_selectObjectSelectionMenu;

    QString _saveDir;

    QComboBox *_addToLayerCombo;
};

#endif // MAINWINDOW_H
