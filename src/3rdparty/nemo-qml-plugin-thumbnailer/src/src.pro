TARGET = nemothumbnailer
PLUGIN_IMPORT_PATH = org/nemomobile/thumbnailer

TEMPLATE = lib
CONFIG += qt plugin hide_symbols
equals(QT_MAJOR_VERSION, 4): QT += declarative
equals(QT_MAJOR_VERSION, 5): QT += qml quick

equals(QT_MAJOR_VERSION, 4): target.path = $$[QT_INSTALL_IMPORTS]/$$PLUGIN_IMPORT_PATH
equals(QT_MAJOR_VERSION, 5): target.path = $$[QT_INSTALL_QML]/$$PLUGIN_IMPORT_PATH
INSTALLS += target

qmldir.files += $$_PRO_FILE_PWD_/qmldir
qmldir.path +=  $$target.path
INSTALLS += qmldir

SOURCES += plugin.cpp \
           nemothumbnailprovider.cpp \
           nemoimagemetadata.cpp \
           nemothumbnailitem.cpp    \
           nemovideothumbnailer.cpp
HEADERS += nemothumbnailprovider.h \
           nemoimagemetadata.h \
           nemothumbnailitem.h \
           nemovideothumbnailer.h

DEFINES += NEMO_THUMBNAILER_DIR=\\\"$$target.path/thumbnailers\\\"
