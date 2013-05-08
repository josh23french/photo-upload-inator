HEADERS += \
    src/mythread.h \
    src/tetherthumb.h \
    src/tetherwindow.h \
    src/abortablenetworkreply.h \
    forms/signindialog.h \
    src/fastresizer.h \
    src/familycompletion.h \
    src/searchbox.h \
    src/previewgraphicsview.h \
    forms/settingsdialog.h \
    src/photouploadinator.h \
    src/cookiejar.h \
    src/autosaver.h \
    src/flowlayout.h
SOURCES += \
    src/main.cpp \
    src/mythread.cpp \
    src/tetherthumb.cpp \
    src/tetherwindow.cpp \
    src/abortablenetworkreply.cpp \
    forms/signindialog.cpp \
    src/fastresizer.cpp \
    src/familycompletion.cpp \
    src/searchbox.cpp \
    src/previewgraphicsview.cpp \
    forms/settingsdialog.cpp \
    src/photouploadinator.cpp \
    src/cookiejar.cpp \
    src/autosaver.cpp \
    src/flowlayout.cpp
FORMS += \
    forms/settingsdialog.ui \
    forms/tetherwindow.ui \
    forms/signindialog.ui

LIBS += -lgphoto2 \
    -lm \
    -lcurl \
    -lgphoto2_port \
    -ldl \
    -lqjson \
    -lexif

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
