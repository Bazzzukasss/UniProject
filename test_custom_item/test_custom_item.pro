#-------------------------------------------------
#
# Project created by QtCreator 2017-09-29T11:11:57
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = custom_item_test
TEMPLATE = app

INCLUDEPATH += ../modules/custom_item/include \
                include

SOURCES += src/main.cpp\
        src/main_window.cpp \
    ../modules/custom_item/src/CustomItem.cpp \
    ../modules/custom_item/src/CustomItemData.cpp \
    ../modules/custom_item/src/CustomItemDelegate.cpp \
    ../modules/custom_item/src/CustomItemModel.cpp \
    ../modules/custom_item/src/CustomItemSortFilterProxyModel.cpp \
    ../modules/custom_item/src/CustomItemTableModel.cpp \
    ../modules/custom_item/src/CustomItemTableMonitor.cpp \
    ../modules/custom_item/src/CustomItemTableView.cpp \
    ../modules/custom_item/src/CustomItemTreeModel.cpp \
    ../modules/custom_item/src/CustomItemTreeMonitor.cpp \
    ../modules/custom_item/src/CustomItemTreeView.cpp \
    ../modules/custom_item/src/CustomItemTypes.cpp \
    ../modules/custom_item/src/CustomItemWidget.cpp \
    ../modules/custom_item/src/CustomItemWidgets.cpp \
    ../modules/custom_item/src/qcustomplot.cpp

HEADERS  += include/main_window.h \
    ../modules/custom_item/include/CustomItem.h \
    ../modules/custom_item/include/CustomItemClasses.h \
    ../modules/custom_item/include/CustomItemData.h \
    ../modules/custom_item/include/CustomItemDelegate.h \
    ../modules/custom_item/include/CustomItemModel.h \
    ../modules/custom_item/include/CustomItemSortFilterProxyModel.h \
    ../modules/custom_item/include/CustomItemTableModel.h \
    ../modules/custom_item/include/CustomItemTableMonitor.h \
    ../modules/custom_item/include/CustomItemTableView.h \
    ../modules/custom_item/include/CustomItemTreeModel.h \
    ../modules/custom_item/include/CustomItemTreeMonitor.h \
    ../modules/custom_item/include/CustomItemTreeView.h \
    ../modules/custom_item/include/CustomItemTypes.h \
    ../modules/custom_item/include/CustomItemWidget.h \
    ../modules/custom_item/include/CustomItemWidgets.h \
    ../modules/custom_item/include/qcustomplot.h

FORMS    += forms/main_window.ui
