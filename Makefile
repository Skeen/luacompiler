CXX = g++
CPPFLAGS = -Wall -g
INCLUDES = -I..

LFLAGS = 
LIBS = -lboost_unit_test_framework

SOURCEDIR = .
BUILDDIR = build
EXECUTABLE = test

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

.PHONY: clean dir test

all: $(BUILDDIR)/$(EXECUTABLE)

test: 
	make -f test/Makefile

clean:
	rm -rf $(BUILDDIR)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(INCLUDES) -o $@ $^ $(LFLAGS) $(LIBS)

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CXX) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
