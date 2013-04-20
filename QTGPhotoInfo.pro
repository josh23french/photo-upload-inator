HEADERS += \
    src/imagedisplaydialog.h \
    src/mythread.h \
    src/tetherthumb.h \
    src/tetherwindow.h \
    abortablenetworkreply.h \
    forms/signindialog.h \
    fastresizer.h \
    src/familycompletion.h \
    src/searchbox.h \
    src/previewgraphicsview.h \
    forms/settingsdialog.h
SOURCES += \
    src/main.cpp \
    src/imagedisplaydialog.cpp \
    src/mythread.cpp \
    src/tetherthumb.cpp \
    src/tetherwindow.cpp \
    abortablenetworkreply.cpp \
    forms/signindialog.cpp \
    fastresizer.cpp \
    src/familycompletion.cpp \
    src/searchbox.cpp \
    src/previewgraphicsview.cpp \
    forms/settingsdialog.cpp
FORMS += forms/infodialog.ui \
    forms/imagedisplaydialog.ui \
    forms/settingsdialog.ui \
    forms/tetherwindow.ui \
    forms/signindialog.ui

LIBS += -lgphoto2 \
    -lm \
    -lcurl \
    -lgphoto2_port \
    -ldl \
    -lqjson

TARGET = LBCPhotoTether

QT += network

# All objects should go into tmp
MOC_DIR = tmp/
UI_DIR = tmp/
UI_HEADER_DIR = tmp/
UI_SOURCE_DIR = tmp/
OBJECTS_DIR = tmp/
RCC_DIR = tmp/

include("config/local.pro")
