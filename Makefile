#############################################################################
# Makefile for building: LBCPhotoTether
# Generated by qmake (2.01a) (Qt 4.8.3) on: Wed Apr 10 01:51:47 2013
# Project:  QTGPhotoInfo.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile QTGPhotoInfo.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4 -Itmp -Itmp
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lgphoto2 -lm -lcurl -lgphoto2_port -ldl -lqjson -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = tmp/

####### Files

SOURCES       = src/infodialog.cpp \
		src/main.cpp \
		src/imagedisplaydialog.cpp \
		src/mythread.cpp \
		src/familycompleter.cpp \
		src/tetherthumb.cpp \
		src/tetherwindow.cpp \
		abortablenetworkreply.cpp \
		forms/signindialog.cpp tmp/moc_infodialog.cpp \
		tmp/moc_imagedisplaydialog.cpp \
		tmp/moc_mythread.cpp \
		tmp/moc_familycompleter.cpp \
		tmp/moc_tetherthumb.cpp \
		tmp/moc_tetherwindow.cpp \
		tmp/moc_abortablenetworkreply.cpp \
		tmp/moc_signindialog.cpp
OBJECTS       = tmp/infodialog.o \
		tmp/main.o \
		tmp/imagedisplaydialog.o \
		tmp/mythread.o \
		tmp/familycompleter.o \
		tmp/tetherthumb.o \
		tmp/tetherwindow.o \
		tmp/abortablenetworkreply.o \
		tmp/signindialog.o \
		tmp/moc_infodialog.o \
		tmp/moc_imagedisplaydialog.o \
		tmp/moc_mythread.o \
		tmp/moc_familycompleter.o \
		tmp/moc_tetherthumb.o \
		tmp/moc_tetherwindow.o \
		tmp/moc_abortablenetworkreply.o \
		tmp/moc_signindialog.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		config/local.pro \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		QTGPhotoInfo.pro
QMAKE_TARGET  = LBCPhotoTether
DESTDIR       = 
TARGET        = LBCPhotoTether

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): tmp/ui_infodialog.h tmp/ui_imagedisplaydialog.h tmp/ui_settingsdialog.h tmp/ui_tetherwindow.h tmp/ui_signindialog.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: QTGPhotoInfo.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		config/local.pro \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtNetwork.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile QTGPhotoInfo.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
config/local.pro:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtNetwork.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile QTGPhotoInfo.pro

dist: 
	@$(CHK_DIR_EXISTS) tmp/LBCPhotoTether1.0.0 || $(MKDIR) tmp/LBCPhotoTether1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) tmp/LBCPhotoTether1.0.0/ && $(COPY_FILE) --parents src/infodialog.h src/imagedisplaydialog.h src/mythread.h src/familycompleter.h src/tetherthumb.h src/tetherwindow.h abortablenetworkreply.h forms/signindialog.h tmp/LBCPhotoTether1.0.0/ && $(COPY_FILE) --parents src/infodialog.cpp src/main.cpp src/imagedisplaydialog.cpp src/mythread.cpp src/familycompleter.cpp src/tetherthumb.cpp src/tetherwindow.cpp abortablenetworkreply.cpp forms/signindialog.cpp tmp/LBCPhotoTether1.0.0/ && $(COPY_FILE) --parents forms/infodialog.ui forms/imagedisplaydialog.ui forms/settingsdialog.ui forms/tetherwindow.ui forms/signindialog.ui tmp/LBCPhotoTether1.0.0/ && (cd `dirname tmp/LBCPhotoTether1.0.0` && $(TAR) LBCPhotoTether1.0.0.tar LBCPhotoTether1.0.0 && $(COMPRESS) LBCPhotoTether1.0.0.tar) && $(MOVE) `dirname tmp/LBCPhotoTether1.0.0`/LBCPhotoTether1.0.0.tar.gz . && $(DEL_FILE) -r tmp/LBCPhotoTether1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: tmp/moc_infodialog.cpp tmp/moc_imagedisplaydialog.cpp tmp/moc_mythread.cpp tmp/moc_familycompleter.cpp tmp/moc_tetherthumb.cpp tmp/moc_tetherwindow.cpp tmp/moc_abortablenetworkreply.cpp tmp/moc_signindialog.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) tmp/moc_infodialog.cpp tmp/moc_imagedisplaydialog.cpp tmp/moc_mythread.cpp tmp/moc_familycompleter.cpp tmp/moc_tetherthumb.cpp tmp/moc_tetherwindow.cpp tmp/moc_abortablenetworkreply.cpp tmp/moc_signindialog.cpp
tmp/moc_infodialog.cpp: src/familycompleter.h \
		src/settingsdialog.h \
		src/imagedisplaydialog.h \
		src/infodialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/infodialog.h -o tmp/moc_infodialog.cpp

tmp/moc_imagedisplaydialog.cpp: src/imagedisplaydialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/imagedisplaydialog.h -o tmp/moc_imagedisplaydialog.cpp

tmp/moc_mythread.cpp: src/mythread.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/mythread.h -o tmp/moc_mythread.cpp

tmp/moc_familycompleter.cpp: src/familycompleter.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/familycompleter.h -o tmp/moc_familycompleter.cpp

tmp/moc_tetherthumb.cpp: src/tetherthumb.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/tetherthumb.h -o tmp/moc_tetherthumb.cpp

tmp/moc_tetherwindow.cpp: src/familycompleter.h \
		src/tetherwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/tetherwindow.h -o tmp/moc_tetherwindow.cpp

tmp/moc_abortablenetworkreply.cpp: abortablenetworkreply.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) abortablenetworkreply.h -o tmp/moc_abortablenetworkreply.cpp

tmp/moc_signindialog.cpp: forms/signindialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) forms/signindialog.h -o tmp/moc_signindialog.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: tmp/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) tmp/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: tmp/ui_infodialog.h tmp/ui_imagedisplaydialog.h tmp/ui_settingsdialog.h tmp/ui_tetherwindow.h tmp/ui_signindialog.h
compiler_uic_clean:
	-$(DEL_FILE) tmp/ui_infodialog.h tmp/ui_imagedisplaydialog.h tmp/ui_settingsdialog.h tmp/ui_tetherwindow.h tmp/ui_signindialog.h
tmp/ui_infodialog.h: forms/infodialog.ui
	/usr/bin/uic-qt4 forms/infodialog.ui -o tmp/ui_infodialog.h

tmp/ui_imagedisplaydialog.h: forms/imagedisplaydialog.ui
	/usr/bin/uic-qt4 forms/imagedisplaydialog.ui -o tmp/ui_imagedisplaydialog.h

tmp/ui_settingsdialog.h: forms/settingsdialog.ui
	/usr/bin/uic-qt4 forms/settingsdialog.ui -o tmp/ui_settingsdialog.h

tmp/ui_tetherwindow.h: forms/tetherwindow.ui
	/usr/bin/uic-qt4 forms/tetherwindow.ui -o tmp/ui_tetherwindow.h

tmp/ui_signindialog.h: forms/signindialog.ui
	/usr/bin/uic-qt4 forms/signindialog.ui -o tmp/ui_signindialog.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

tmp/infodialog.o: src/infodialog.cpp src/mythread.h \
		src/infodialog.h \
		src/familycompleter.h \
		src/settingsdialog.h \
		src/imagedisplaydialog.h \
		tmp/ui_infodialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/infodialog.o src/infodialog.cpp

tmp/main.o: src/main.cpp src/infodialog.h \
		src/familycompleter.h \
		src/settingsdialog.h \
		src/imagedisplaydialog.h \
		src/tetherwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/main.o src/main.cpp

tmp/imagedisplaydialog.o: src/imagedisplaydialog.cpp src/imagedisplaydialog.h \
		tmp/ui_imagedisplaydialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/imagedisplaydialog.o src/imagedisplaydialog.cpp

tmp/mythread.o: src/mythread.cpp src/mythread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/mythread.o src/mythread.cpp

tmp/familycompleter.o: src/familycompleter.cpp src/familycompleter.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/familycompleter.o src/familycompleter.cpp

tmp/tetherthumb.o: src/tetherthumb.cpp src/tetherthumb.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/tetherthumb.o src/tetherthumb.cpp

tmp/tetherwindow.o: src/tetherwindow.cpp src/tetherwindow.h \
		src/familycompleter.h \
		tmp/ui_tetherwindow.h \
		src/tetherthumb.h \
		src/imagedisplaydialog.h \
		forms/signindialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/tetherwindow.o src/tetherwindow.cpp

tmp/abortablenetworkreply.o: abortablenetworkreply.cpp abortablenetworkreply.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/abortablenetworkreply.o abortablenetworkreply.cpp

tmp/signindialog.o: forms/signindialog.cpp forms/signindialog.h \
		tmp/ui_signindialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/signindialog.o forms/signindialog.cpp

tmp/moc_infodialog.o: tmp/moc_infodialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_infodialog.o tmp/moc_infodialog.cpp

tmp/moc_imagedisplaydialog.o: tmp/moc_imagedisplaydialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_imagedisplaydialog.o tmp/moc_imagedisplaydialog.cpp

tmp/moc_mythread.o: tmp/moc_mythread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_mythread.o tmp/moc_mythread.cpp

tmp/moc_familycompleter.o: tmp/moc_familycompleter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_familycompleter.o tmp/moc_familycompleter.cpp

tmp/moc_tetherthumb.o: tmp/moc_tetherthumb.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_tetherthumb.o tmp/moc_tetherthumb.cpp

tmp/moc_tetherwindow.o: tmp/moc_tetherwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_tetherwindow.o tmp/moc_tetherwindow.cpp

tmp/moc_abortablenetworkreply.o: tmp/moc_abortablenetworkreply.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_abortablenetworkreply.o tmp/moc_abortablenetworkreply.cpp

tmp/moc_signindialog.o: tmp/moc_signindialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tmp/moc_signindialog.o tmp/moc_signindialog.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

