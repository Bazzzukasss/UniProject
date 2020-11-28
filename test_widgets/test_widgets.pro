QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/item_delegate.cpp \
    src/item_widget.cpp \
    src/list_view.cpp \
    src/list_widget.cpp \
    src/main.cpp \
    src/main_window.cpp

HEADERS += \
    include/item_data.h \
    include/item_delegate.h \
    include/item_widget.h \
    include/list_view.h \
    include/list_widget.h \
    include/main_window.h

FORMS += \
    forms/item_widget.ui \
    forms/main_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../assets/user_icons/user_icons.qrc
