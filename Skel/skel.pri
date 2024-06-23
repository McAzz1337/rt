include (Cfg/cfg.pri)
include (Doc/doc.pri)
include (Gui/gui.pri)
include (Main/main.pri)
include (Out/out.pri)
include (Thrd/thrd.pri)
include (Util/util.pri)

CONFIG += c++17
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
QT += core gui widgets
