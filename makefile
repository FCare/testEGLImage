SHELL=/bin/bash

TARGET = TestEGLImage.ex

#lista directory in cui cercare sorgenti 
VPATH =	. \

#lista directory in cui cercare .h
INCLUDE = 

#elenco dei sorgenti
SOURCES =  TestEGLImage.cpp


#elenco lib
LIBS = \
       -lc \
       -lpthread \
       -lstdc++ \
       -ldl \
       -lEGL \
       -lGLESv2 \
       -lX11

#dir base di output
BASEOUTDIR = linuxout/

#dipendenza da altre librerie: per ognuna delle librerie aggiungere un comando al target lib
LIBRARYDEPENDENCY = 

include target-linux.mk

lib:
	@echo
