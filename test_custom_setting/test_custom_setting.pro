QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += \
    include \
    ../modules/custom_setting/include

SOURCES += \
    ../modules/custom_setting/src/custom_setting.cpp \
    ../modules/custom_setting/src/custom_setting_data.cpp \
    ../modules/custom_setting/src/custom_setting_serializer.cpp \
    ../modules/custom_setting/src/custom_widgets.cpp \
    ../modules/custom_setting/src/custom_setting_item.cpp \
    ../modules/custom_setting/src/custom_setting_widget.cpp \
    ../modules/custom_setting/src/custom_setting_manager.cpp \
    ../modules/custom_setting/src/custom_setting_tree_widget.cpp \
    ../modules/custom_setting/src/custom_setting_item_tree_model.cpp \
    ../modules/custom_setting/src/custom_setting_item_delegate.cpp \
    src/main.cpp \
    src/main_window.cpp \
    src/app_settings.cpp \
    src/app_setting_manager.cpp

HEADERS += \
    ../modules/custom_setting/include/custom_setting.h \
    ../modules/custom_setting/include/custom_setting_data.h \
    ../modules/custom_setting/include/custom_setting_serializer.h \
    ../modules/custom_setting/include/custom_widgets.h \
    ../modules/custom_setting/include/custom_setting_item.h \
    ../modules/custom_setting/include/custom_setting_widget.h \
    ../modules/custom_setting/include/custom_setting_manager.h \
    ../modules/custom_setting/include/custom_setting_tree_widget.h \
    ../modules/custom_setting/include/custom_setting_item_tree_model.h \
    ../modules/custom_setting/include/custom_setting_item_delegate.h \
    include/main_window.h \
    include/app_settings.h \
    include/app_setting_manager.h

FORMS += \
    forms/main_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
