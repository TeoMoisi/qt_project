#-------------------------------------------------
#
# Project created by QtCreator 2018-05-13T14:59:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_lab
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    domain.cpp \
    controller.cpp \
    util.cpp \
    repository.cpp \
    repository_exceptions.cpp \
    coat_validator.cpp \
    filebasket.cpp \
    csv_file.cpp \
    admin.cpp \
    user.cpp \
    html_file.cpp \
    undo.cpp \
    table_veiw.cpp \
    setuptable.cpp \
    picture_view.cpp

HEADERS += \
        mainwindow.h \
    domain.h \
    controller.h \
    util.h \
    repository.h \
    repository_exceptions.h \
    coat_validator.h \
    filebasket.h \
    csv_file.h \
    admin.h \
    user.h \
    html_file.h \
    undo.h \
    table_veiw.h \
    setuptable.h \
    picture_view.h

FORMS += \
        mainwindow.ui \
    admin.ui \
    user.ui \
    setuptable.ui

DISTFILES += \
    coats.txt \
    coats.csv \
    coats.html
