# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-filters

CONFIG += sailfishapp

SOURCES += src/harbour-filters.cpp \
    src/models/galleryitemmodel.cpp \
    src/3rdparty/nemo-qml-plugin-thumbnailer/src/nemoimagemetadata.cpp \
    src/3rdparty/nemo-qml-plugin-thumbnailer/src/nemothumbnailprovider.cpp \
    src/models/filteredimage.cpp \
    src/filters/sepiafilter.cpp \
    src/filters/greyscalefilter.cpp \
    src/filters/abstractimagefilter.cpp \
    src/filters/brightnessfilter.cpp \
    #src/filters/blurfilter.cpp \
    #src/filters/sharpenfilter.cpp \
    src/models/filterlistmodel.cpp \
    src/filters/imagefilterparameter.cpp \
    src/models/filterparameterlistmodel.cpp \
    src/filters/rgbfilter.cpp \
    src/models/filteredcoverimage.cpp \
    src/filters/negativefilter.cpp \
    src/filters/rgbswapfilter.cpp \
    src/3rdparty/nemo-qml-plugin-thumbnailer/src/nemothumbnailitem.cpp

OTHER_FILES += qml/harbour-filters.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    qml/images/icon.png \
    rpm/harbour-filters.changes.in \
    rpm/harbour-filters.spec \
    rpm/harbour-filters.yaml \
    translations/*.ts \
    harbour-filters.desktop \
    qml/pages/AboutPage.qml \
    qml/components/ComboBoxExt.qml

# to disable building translations every time, comment out the
# following CONFIG line
#CONFIG += sailfishapp_i18n
#TRANSLATIONS += translations/harbour-filters-de.ts

HEADERS += \
    src/models/galleryitemmodel.h \
    src/3rdparty/nemo-qml-plugin-thumbnailer/src/nemoimagemetadata.h \
    src/3rdparty/nemo-qml-plugin-thumbnailer/src/nemothumbnailprovider.h \
    src/models/filteredimage.h \
    src/filters/sepiafilter.h \
    src/filters/greyscalefilter.h \
    src/filters/abstractimagefilter.h \
    src/filters/brightnessfilter.h \
    #src/filters/blurfilter.h \
    #src/filters/sharpenfilter.h \
    src/models/filterlistmodel.h \
    src/filters/imagefilterparameter.h \
    src/models/filterparameterlistmodel.h \
    src/filters/rgbfilter.h \
    src/models/filteredcoverimage.h \
    src/filters/negativefilter.h \
    src/filters/rgbswapfilter.h \
    src/3rdparty/nemo-qml-plugin-thumbnailer/src/nemothumbnailitem.h \
    src/3rdparty/nemo-qml-plugin-thumbnailer/src/linkedlist.h

