TARGET = pokehack.exe
SRCS = pkg3.c
OBJECTS = $(SRCS:.c=.o)

SRCDIR = src/

INCDIRS = -I./include/

CXXFLAGS = -g $(INCDIRS) -Wall
CXX = gcc

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

$(OBJECTS): $(SRCDIR)$(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJECTS) $(TARGET)