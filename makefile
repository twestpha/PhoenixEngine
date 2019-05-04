# Engine Makefile
TARGET = engine

CC = g++
CFLAGS = -std=c++11 -I.
LFLAGS = -lgdi32 -lglu32 -lopengl32

# Directories
SRCDIR = src
OBJDIR = obj

# Getting Objects from directories, src/*.cpp -> obj/*.o
HPP = $(wildcard $(SRCDIR)/*.hpp)
CPP = $(wildcard $(SRCDIR)/*.cpp)
_OBJ = $(subst cpp,o,$(CPP))
OBJ = $(subst $(SRCDIR),$(OBJDIR),$(_OBJ))

# Building Rules
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HPP)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CC) -static $(CFLAGS) -o $@ $^ $(LFLAGS)

debug:
	$(CC) -static $(CFLAGS) -g -o $@ $^$(LFLAGS)

clean:
	del $(OBJDIR)\*
