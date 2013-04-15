HEADERS += src/infodialog.h \
    src/imagedisplaydialog.h \
    src/mythread.h \
    src/familycompleter.h \
    src/tetherthumb.h \
    src/tetherwindow.h \
    abortablenetworkreply.h \
    forms/signindialog.h
SOURCES += src/infodialog.cpp \
    src/main.cpp \
    src/imagedisplaydialog.cpp \
    src/mythread.cpp \
    src/familycompleter.cpp \
    src/tetherthumb.cpp \
    src/tetherwindow.cpp \
    abortablenetworkreply.cpp \
    forms/signindialog.cpp
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
