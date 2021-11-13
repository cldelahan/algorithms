CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCS := src test

BUILDDIR := build
TARGET := bin/runner
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCS) -type f -name *.$(SRCEXT))
_OBJECTS := $(SOURCES:.$(SRCEXT)=.o)
OBJECTS := $(patsubst %,$(BUILDDIR)/%,$(_OBJECTS))
# OBJECTS := $(patsubst $(SRCDIR)/%,$(SRC_BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
# TEST_OBJECTS := $(patsubst $(TESTDIR)/%,$(TEST_BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS := -g -Wall
LIB := 
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: %.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@find $(BUILDDIR)/ -name *.o -delete

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean