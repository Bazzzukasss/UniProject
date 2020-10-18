#-------------------------------------------------
#
# Project created by QtCreator 2017-09-29T11:11:57
#
#-------------------------------------------------

QT       += core gui opengl printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gl_scene_test
TEMPLATE = app

INCLUDEPATH += ../modules/gl_scene/include \
                include

SOURCES += src/main.cpp\
        src/data.cpp \
        src/main_window.cpp \
        ../modules/gl_scene/src/gl_scene.cpp \
        ../modules/gl_scene/src/gl_scene_camera.cpp \
        ../modules/gl_scene/src/gl_scene_defaults.cpp \
        ../modules/gl_scene/src/gl_scene_generator.cpp \
        ../modules/gl_scene/src/gl_scene_loader.cpp \
        ../modules/gl_scene/src/gl_scene_mesh.cpp \
        ../modules/gl_scene/src/gl_scene_pipe.cpp \
        ../modules/gl_scene/src/gl_scene_projection.cpp \
        ../modules/gl_scene/src/gl_scene_glass.cpp \
        ../modules/gl_scene/src/gl_scene_utility.cpp \
        ../modules/gl_scene/src/gl_scene_view.cpp \
        ../modules/gl_scene/src/gl_scene_item.cpp \
        ../modules/gl_scene/src/gl_scene_object.cpp \
        ../modules/gl_scene/src/gl_scene_manipulator.cpp

HEADERS  += include/main_window.h \
        include/data.h\
        ../modules/gl_scene/include/gl_scene.h \
        ../modules/gl_scene/include/gl_scene_camera.h \
        ../modules/gl_scene/include/gl_scene_defaults.h \
        ../modules/gl_scene/include/gl_scene_generator.h \
        ../modules/gl_scene/include/gl_scene_loader.h \
        ../modules/gl_scene/include/gl_scene_mesh.h \
        ../modules/gl_scene/include/gl_scene_pipe.h \
        ../modules/gl_scene/include/gl_scene_projection.h \
        ../modules/gl_scene/include/gl_scene_glass.h \
        ../modules/gl_scene/include/gl_scene_types.h \
        ../modules/gl_scene/include/gl_scene_utility.h \
        ../modules/gl_scene/include/gl_scene_view.h \
        ../modules/gl_scene/include/gl_scene_item.h \
        ../modules/gl_scene/include/gl_scene_object.h \
        ../modules/gl_scene/include/gl_scene_manipulator.h

FORMS    += forms/main_window.ui

unix:LIBS += -lGL
win32:LIBS += -lopengl32 -lglu32
