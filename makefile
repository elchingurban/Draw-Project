########################
# OS detection
#########################

OS = $(shell uname)

########################
# Compiler options
#########################

CC=gcc

CFLAGS = -I. -I /usr/include \
               -I /usr/local/include \
               -I /opt/local/include/GL \
               -I /opt/X11/include \
               -Wno-deprecated

ifeq (${OS},Darwin)
  CFLAGS += -I /System/Library/Frameworks/OpenGL.framework/Headers -I /System/Library/Frameworks/GLUT.framework/Versions/A//Headers
else
  CFLAGS += -I /usr/include/GL -I /usr/include
endif

CCOPTIONS = -g -O0 -Wall

#########################
# Librairies
#########################

ifeq ($(OS),Darwin)
	LIBS = -lm -framework OpenGL -framework GLUT
else
	LIBS = -lm -lGLU -lGL -lglut
endif

#########################
# Sources and objects
#########################

SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
EXECUTABLE=linedraw

#########################
# Rules
#########################

all : $(EXECUTABLE)


$(EXECUTABLE) : $(OBJECTS)
	${CC} -o $@ $^ ${LIBS}

.c.o:
	$(CC) -c $(CFLAGS) $^ -o $@ $(CCOPTIONS)

clean :
	rm $(OBJECTS) *~

putaway :
	rm $(OBJECTS) *~ $(EXECUTABLE)
