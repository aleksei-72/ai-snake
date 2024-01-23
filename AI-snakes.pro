TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        classes/game.cpp \
        classes/map.cpp \
        classes/render_manager.cpp \
        classes/snake/snake.cpp \
        classes/snake/strategies/ai_strategy.cpp \
        classes/snake/strategies/manual_strategy.cpp \
        main.cpp

HEADERS += \
    classes/game.h \
    classes/map.h \
    classes/render_manager.h \
    classes/snake/snake.h \
    classes/snake/snake_directions.h \
    classes/snake/strategies/abstract_strategy.h \
    classes/snake/strategies/ai_strategy.h \
    classes/snake/strategies/manual_strategy.h

DEFINES += enable-sjlj-exceptions fexceptions DSFML_DYNAMIC


INCLUDEPATH += \
    libs/SFML-2.5.0/include \

win32: LIBS += -lopengl32 -lglu32
win32: LIBS += -L$$PWD/libs/SFML-2.5.0/lib/ -lsfml-system -lsfml-graphics -lsfml-window
