HEADERS += \
	$$PWD/coreapp.h \
	$$PWD/control.h \
	$$PWD/ipresenter.h \
	$$PWD/messageresult.h \
	$$PWD/coremessage.h \
    $$PWD/qtmvvmbinding.h

SOURCES += \
	$$PWD/coreapp.cpp \
	$$PWD/control.cpp \
	$$PWD/messageresult.cpp \
	$$PWD/coremessage.cpp \
    $$PWD/qtmvvmbinding.cpp
	
TRANSLATIONS += $$PWD/qtmvvm_core_de.ts \
	$$PWD/qtmvvm_core_template.ts

INCLUDEPATH += $$PWD

