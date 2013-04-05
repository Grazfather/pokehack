TARGET = pokehack.exe
OBJECTS = pkg3.o parsesav.o pokemon_species.o items.o

SRCDIR = src/

INCDIRS = -I./include/

CXXFLAGS = -g $(INCDIRS) -Wall
CXX = gcc

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: $(SRCDIR)%.c
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)
