QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcontact.cpp \
    chat.cpp \
    client.cpp \
    getuserdata.cpp \
    main.cpp \
    authentication.cpp \
    message.cpp \
    user.cpp \
    userspace.cpp

HEADERS += \
    addcontact.h \
    authentication.h \
    chat.h \
    client.h \
    getuserdata.h \
    message.h \
    user.h \
    userspace.h

FORMS += \
    addcontact.ui \
    authentication.ui \
    getuserdata.ui \
    userspace.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
