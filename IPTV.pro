QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    channel.cpp \
    database.cpp \
    group.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.cpp \
    playlist.cpp \
    soundtrack.cpp

HEADERS += \
    channel.h \
    database.h \
    datatypes.h \
    group.h \
    logger.h \
    mainwindow.h \
    parser.h \
    playlist.h \
    soundtrack.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    iptv.qrc

win32 {
        RC_FILE += icon.rc
        OTHER_FILES += icon.rc
}

DISTFILES += \
    icon.rc
