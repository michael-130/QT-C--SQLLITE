QT       += core gui sql
QT += axcontainer
QT += multimedia
RC_ICONS += icon.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calculate.cpp \
    input.cpp \
    main.cpp \
    login.cpp \
    output.cpp

HEADERS += \
    calculate.h \
    input.h \
    login.h \
    output.h

FORMS += \
    calculate.ui \
    input.ui \
    login.ui \
    output.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
