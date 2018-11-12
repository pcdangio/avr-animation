TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $(ProgramFiles)\Arduino\hardware\arduino\avr\cores\arduino
INCLUDEPATH += $$PWD\src

HEADERS += \
    src/utility/step.h \
    src/utility/script.h \
    src/utility/animator.h \
    src/animation.h

SOURCES += \
    src/utility/step.cpp \
    src/utility/script.cpp \
    src/utility/animator.cpp

DISTFILES += \
    library.properties \
    keywords.txt
