######################################################################
# Automatically generated by qmake (2.01a) So. Jan 3 20:05:17 2010
######################################################################

TEMPLATE = app
TARGET = build/Quiz
DEPENDPATH += .
TRANSLATIONS = languages/Quiz_de.ts
INCLUDEPATH += .
MOC_DIR=src/moc/

# Input
HEADERS += include/Frage.hpp \
           include/Fragefrei.hpp \
           include/Frageimg.hpp \
           include/Editor.hpp \
           include/ParseXML.hpp \
           include/Steuerung.hpp \
           include/Window.hpp
SOURCES += src/Frage.cpp \
           src/Fragefrei.cpp \
          src/Frageimg.cpp \
          src/Editor.cpp \
           src/main.cpp \
           src/ParseXML.cpp \
           src/Steuerung.cpp \
           src/Window.cpp
QT +=xml
QT +=widgets
