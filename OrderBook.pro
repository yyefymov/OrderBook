TEMPLATE = app
CONFIG += console c++11 c++14
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
        ../googletest/googletest

INCLUDEPATH += \
        ../googletest/googletest/include

SOURCES += \
        src/Order.cpp \
        src/OrderBook.cpp \
        test/OrderBookTests.cpp \
        test/OrderTests.cpp \
        main.cpp \
        test/testsOverData/TestsOverData.cpp

SOURCES += \
        ../googletest/googletest/src/gtest-all.cc

HEADERS += \
    include/CustomTypes.h \
    include/Order.h \
    include/OrderBook.h \
    test/OrderBookTests.h \
    test/OrderTests.h \
    test/testsOverData/TestsOverData.h

QT += testlib
