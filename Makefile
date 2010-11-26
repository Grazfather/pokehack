TARGER = pokehack.exe
CXXFILES = pkg3.c
OBJECTS = pkg3.o

INCDIRS = -I../include
SRCDIR = ./src/

CXXFLAGS = -g $(INCDIRS) -Wall
$(TARGET): $(OBJECTS) Makefile
	gcc $(CXXFLAGS) $(OBJECTS) -o $(EXEFILE)
	
pkg3.o:
	gcc $(CXXFLAGS) -c $(SRCDIR)pkg3.c

clean:
	rm -f $(OBJECTS) $(TARGET)