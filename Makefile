#
# Makefile - build screenshot and screenshot.dylib for Mac OS X
#
#  Created by Leopold O'Donnell on 3/18/13.
#  MIT-LIcense Copyright (c) 2013 Leo O'Donnell.
#
CC=g++
FRAMEWORKS=-framework IOKit -framework ApplicationServices
CFLAGS=-c -Wall

OFILES= screen_shooter.o screen_shot.o

all: screenshot.dylib screenshot


screenshot: main.o $(OFILES)
	$(CC) $(FRAMEWORKS) $^ -o screenshot

screenshot.dylib: $(OFILES)
	$(CC) -dynamiclib -undefined suppress -flat_namespace $^ -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f screenshot *.o *.dylib
