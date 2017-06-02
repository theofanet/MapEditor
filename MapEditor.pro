#-------------------------------------------------
#
# Project created by QtCreator 2016-05-08T20:06:03
#
#-------------------------------------------------

QT       += core gui opengl
win32: LIBS+= -lglut32 -lopengl32 -lglu32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapEditor
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        scene.cpp \
    map.cpp \
    maptile.cpp \
    Objects/jeton.cpp \
    Objects/laser.cpp \
    Objects/object.cpp \
    Objects/Particle.cpp \
    Objects/ParticleEmitter.cpp \
    Render/animation.cpp \
    Render/animationabstract.cpp \
    Render/image.cpp \
    Render/sprite.cpp \
    WindowManager/editortab.cpp \
    WindowManager/mainwindow.cpp \
    WindowManager/openglwidget.cpp \
    WindowManager/Dialog/addtilesetdialog.cpp \
    WindowManager/Dialog/newmapdialog.cpp \
    WindowManager/qtile.cpp \
    Utilities/jsoncpp.cpp \
    Utilities/mapjsondata.cpp \
    Objects/checkpoint.cpp \
    WindowManager/Objects/laseroptionwidget.cpp \
    WindowManager/Objects/particleemitteroptionwidget.cpp \
    WindowManager/Objects/tileoptionwidget.cpp \
    WindowManager/Objects/switchoptionwidget.cpp \
    Objects/Logical/anddoor.cpp \
    WindowManager/Objects/getobjectcmddialog.cpp \
    WindowManager/Objects/anddooroptionwidget.cpp \
    Objects/Logical/switch.cpp \
    Objects/Logical/ordoor.cpp \
    WindowManager/Objects/ordooroptionwidget.cpp \
    Objects/Logical/nodoor.cpp \
    WindowManager/Objects/nodooroptionwidget.cpp \
    Objects/platform.cpp \
    WindowManager/Objects/plateformoptionwidget.cpp \
    Objects/Logical/pushbutton.cpp \
    WindowManager/Objects/pushbuttonoptionwidget.cpp

HEADERS  += scene.h \
    map.h \
    maptile.h \
    Objects/jeton.h \
    Objects/laser.h \
    Objects/object.h \
    Objects/Particle.h \
    Objects/ParticleEmitter.h \
    Render/animation.h \
    Render/animationabstract.h \
    Render/image.h \
    Render/sprite.h \
    WindowManager/editortab.h \
    WindowManager/mainwindow.h \
    WindowManager/openglwidget.h \
    WindowManager/qtile.h \
    WindowManager/Dialog/addtilesetdialog.h \
    WindowManager/Dialog/newmapdialog.h \
    Utilities/defines.h \
    Utilities/json-forwards.h \
    Utilities/json.h \
    Utilities/Listener.h \
    Utilities/mapjsondata.h \
    Utilities/json/autolink.h \
    Utilities/json/config.h \
    Utilities/json/features.h \
    Utilities/json/forwards.h \
    Utilities/json/json.h \
    Utilities/json/reader.h \
    Utilities/json/value.h \
    Utilities/json/writer.h \
    Objects/checkpoint.h \
    WindowManager/Objects/laseroptionwidget.h \
    WindowManager/Objects/particleemitteroptionwidget.h \
    WindowManager/Objects/tileoptionwidget.h \
    WindowManager/Objects/switchoptionwidget.h \
    Objects/Logical/anddoor.h \
    WindowManager/Objects/getobjectcmddialog.h \
    WindowManager/Objects/anddooroptionwidget.h \
    Objects/Logical/switch.h \
    Objects/Logical/ordoor.h \
    WindowManager/Objects/ordooroptionwidget.h \
    Objects/Logical/nodoor.h \
    WindowManager/Objects/nodooroptionwidget.h \
    Objects/platform.h \
    WindowManager/Objects/plateformoptionwidget.h \
    Objects/Logical/pushbutton.h \
    WindowManager/Objects/pushbuttonoptionwidget.h


DISTFILES += \
    images/New.png \
    images/Save.png \
    images/Add.png \
    images/Erase.png \
    images/Folder.png \
    images/Edit.png \
    images/Add_selected.png \
    images/Edit_selected.png \
    images/Erase_selected.png \
    images/Back_selected.png \
    images/Back.png \
    images/Middle_selected.png \
    images/Middle.png \
    images/Top_selected.png \
    images/Front_selected.png \
    images/Front.png \
    images/selection_selected.png \
    images/selection.png \
    images/Flag_selected.png \
    images/Flag.png \
    images/FlagItem.png \
    images/Start_Item.png \
    images/Start_selected.png \
    images/Start.png \
    images/End_selected.png \
    images/End.png \
    images/EndItem.png \
    icon.icns \
    images/laser.png \
    images/laserBase.png \
    images/laser_end_back.png \
    images/laser_end_front.png \
    images/laser_mid_back.png \
    images/laser_mid_front.png \
    images/laser_start_back.png \
    images/laser_start_front.png \
    images/AddObject_selected.png \
    images/AddObject.png \
    images/SelectObject_selected.png \
    images/SelectObject.png \
    images/tileJetons.png \
    images/particleTexture.png \
    images/Switch.png \
    images/PushButton.png

OTHER_FILES += \
    images/New.png \
    images/Save.png \
    images/Add.png \
    images/Erase.png \
    images/Folder.png \
    images/Edit.png \
    images/Add_selected.png \
    images/Edit_selected.png \
    images/Erase_selected.png \
    images/Back_selected.png \
    images/Back.png \
    images/Middle_selected.png \
    images/Middle.png \
    images/Top_selected.png \
    images/Front_selected.png \
    images/Front.png \
    images/selection_selected.png \
    images/selection.png \
    images/Flag_selected.png \
    images/Flag.png \
    images/FlagItem.png \
    images/Start_Item.png \
    images/Start_selected.png \
    images/Start.png \
    images/End_selected.png \
    images/End.png \
    images/EndItem.png \
    icon.icns\
    images/laser.png \
    images/laserBase.png \
    images/laser_end_back.png \
    images/laser_end_front.png \
    images/laser_mid_back.png \
    images/laser_mid_front.png \
    images/laser_start_back.png \
    images/laser_start_front.png \
    images/AddObject_selected.png \
    images/AddObject.png \
    images/SelectObject_selected.png \
    images/SelectObject.png \
    images/tileJetons.png \
    images/particleTexture.png \
    images/Switch.png

IMAGES_DATA.files = images
IMAGES_DATA.path = Contents/Resources

QMAKE_BUNDLE_DATA += IMAGES_DATA

FORMS += WindowManager/Dialog/addtilesetdialog.ui \
    WindowManager/Dialog/newmapdialog.ui \
    WindowManager/Objects/laseroptionwidget.ui \
    WindowManager/Objects/particleemitteroptionwidget.ui \
    WindowManager/Objects/switchoptionwidget.ui \
    WindowManager/Objects/getobjectcmddialog.ui \
    WindowManager/Objects/anddooroptionwidget.ui \
    WindowManager/Objects/ordooroptionwidget.ui \
    WindowManager/Objects/nodooroptionwidget.ui \
    WindowManager/Objects/plateformoptionwidget.ui \
    WindowManager/Objects/pushbuttonoptionwidget.ui

unix: LIBS += -L$$PWD/Utilities/json/ -ljson

INCLUDEPATH += $$PWD/Utilities/json
DEPENDPATH += $$PWD/Utilities/json

unix: PRE_TARGETDEPS += $$PWD/Utilities/json/libjson.a

macx:ICON = icon.icns
win32:RC_ICONS = icon.ico
