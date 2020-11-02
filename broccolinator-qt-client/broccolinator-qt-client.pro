TEMPLATE = app

TARGET = broccolinator-qt-client

HEADERS = broccolinator-qt-client.h mainwindow.h camerathread.h socketthread.h

SOURCES = broccolinator-qt-client.cpp mainwindow.cpp camerathread.cpp socketthread.cpp

DESTDIR = $$(QMAKE_DESTIDIR)

FORMS = mainwindow.ui

QT+= core gui widgets network
