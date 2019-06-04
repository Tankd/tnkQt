INCLUDEPATH += $$PWD/src
DEPENDPATH  += $$PWD/src

QT += network sql



HEADERS += \
    $$PWD/src/tnkcommon/jsonobject.h \
    $$PWD/src/tnkcommon/singleton.h \
    $$PWD/src/tnkcommon/timer.h \
    $$PWD/src/tnkcommon/utils.h \
    $$PWD/src/tnkparser/baseparser.h \
    $$PWD/src/tnkparser/csvparser.h \
    $$PWD/src/tnkparser/xlsparser.h \
    $$PWD/src/tnksql/proxymodel.h \
    $$PWD/src/tnksql/querytablemodel.h \
    $$PWD/src/tnksql/sqldatabase.h \
    $$PWD/src/tnksql/sqltablemodel.h \
    $$PWD/src/tnkunicorn/engine.h \
    $$PWD/src/tnkunicorn/entity.h \
    $$PWD/src/tnkunicorn/model.h \
    $$PWD/src/tnkws/restws.h

SOURCES += \
    $$PWD/src/tnkcommon/jsonobject.cpp \
    $$PWD/src/tnkcommon/timer.cpp \
    $$PWD/src/tnkcommon/utils.cpp \
    $$PWD/src/tnkparser/baseparser.cpp \
    $$PWD/src/tnkparser/csvparser.cpp \
    $$PWD/src/tnkparser/xlsparser.cpp \
    $$PWD/src/tnksql/proxymodel.cpp \
    $$PWD/src/tnksql/querytablemodel.cpp \
    $$PWD/src/tnksql/sqldatabase.cpp \
    $$PWD/src/tnksql/sqltablemodel.cpp \
    $$PWD/src/tnkunicorn/engine.cpp \
    $$PWD/src/tnkunicorn/entity.cpp \
    $$PWD/src/tnkunicorn/model.cpp \
    $$PWD/src/tnkws/restws.cpp



HEADERS += \
    $$PWD/src/tnkcommon.h \
    $$PWD/src/tnkparser.h \
    $$PWD/src/tnksql.h \
    $$PWD/src/tnkunicorn.h \
    $$PWD/src/tnkws.h \
    $$PWD/src/tnkwidgets.h

