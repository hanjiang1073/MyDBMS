QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dfile.cpp \
    loginframe.cpp \
    main.cpp \
    mainwindow.cpp \
    queryframe.cpp \
    tfile.cpp\
    recordinsert.cpp \
    registframe.cpp \
    tabledesign.cpp

HEADERS += \
    dfile.h \
    loginframe.h \
    mainwindow.h \
    queryframe.h \
    tfile.h\
    recordinsert.h \
    registframe.h \
    tabledesign.h

FORMS += \
    loginframe.ui \
    mainwindow.ui \
    queryframe.ui \
    recordinsert.ui \
    registframe.ui \
    tabledesign.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RESOURCES += \
    Resources.qrc
