
TEMPLATE = app
TARGET = Stock.Mobile
QT += qml
CONFIG += c++14 qzxing_qml

OTHER_FILES = qml/main.qml

SOURCES = main.cpp

HEADERS =

RESOURCES = resources.qrc

DISTFILES += qml/main.qml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += android/AndroidManifest.xml

include( ../../3rdparty/qzxing/qzxing/QZXing.pri )
