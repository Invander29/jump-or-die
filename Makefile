CC = gcc
CXX = g++

CFLAGS = -std=c11 -I3rdParty/include
CXXFLAGS = -std=c++11 -I3rdParty/include

SOURCES = $(wildcard src/*.cpp) $(wildcard src/Models/*.cpp) $(wildcard src/Images/*.cpp) $(wildcard src/Engine/*.cpp) $(wildcard src/Engine/Graphics/*.cpp) $(wildcard src/Engine/Input/*.cpp) $(wildcard src/Engine/Lighting/*.cpp) $(wildcard src/Engine/Managers/*.cpp) $(wildcard src/Engine/Models/*.cpp) $(wildcard src/Engine/Scenes/*.cpp) $(wildcard src/Engine/Utils/*.cpp)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

GLFW_SOURCES = $(wildcard 3rdParty/src/glfw/unix/*.c)
GLFW_OBJECTS = $(patsubst %.c,%.glfwo,$(GLFW_SOURCES))
GLFW_FLAGS = $(CFLAGS) -I3rdParty/src/glfw -I3rdParty/src/glfw/unix -D_GLFW_USE_CONFIG_H
GLFW_LIBS = -lrt -lm -lX11 -lpthread -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor -lGL

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  GLFW_LIBS += -ldl
endif

GL3W_SOURCES = $(wildcard 3rdParty/src/gl3w/*.c)
GL3W_OBJECTS = $(patsubst %.c,%.gl3wo,$(GL3W_SOURCES))
GL3W_FLAGS = $(CFLAGS) 
GL3W_LIBS = 

LODEPNG_SOURCES = $(wildcard 3rdParty/src/lodepng/*.cpp)
LODEPNG_OBJECTS = $(patsubst %.cpp,%.lodepngo,$(LODEPNG_SOURCES))
LODEPNG_FLAGS = $(CXXFLAGS)
LODEPNG_LIBS = 

TINYOBJ_SOURCES = $(wildcard 3rdParty/src/tiny_obj_loader/*.cc)
TINYOBJ_OBJECTS = $(patsubst %.cc,%.tinyobjo,$(TINYOBJ_SOURCES))
TINYOBJ_FLAGS = $(CXXFLAGS)
TINYOBJ_LIBS =

all: bin

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

%.glfwo: %.c
	$(CC) $(GLFW_FLAGS) -c -o $@ $<

%.gl3wo: %.c
	$(CC) $(GL3W_FLAGS) -c -o $@ $<

%.lodepngo: %.cpp
	$(CXX) $(LODEPNG_FLAGS) -c -o $@ $<

%.tinyobjo: %.cc
	$(CXX) $(TINYOBJ_FLAGS) -c -o $@ $<

glfw.a: $(GLFW_OBJECTS)
	ar -rcs $@ $^

gl3w.a: $(GL3W_OBJECTS)
	ar -rcs $@ $^

lodepng.a: $(LODEPNG_OBJECTS)
	ar -rcs $@ $^

tinyobjloader.a: $(TINYOBJ_OBJECTS)
	ar -rcs $@ $^

bin: glfw.a gl3w.a lodepng.a tinyobjloader.a $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ glfw.a gl3w.a lodepng.a tinyobjloader.a $(GLFW_LIBS) $(GL3W_LIBS) $(LODEPNG_LIBS) $(TINYOBJ_LIBS)

clean:
	rm -f $(OBJECTS)
	rm -f $(GLFW_OBJECTS)
	rm -f $(GL3W_OBJECTS)
	rm -f $(LODEPNG_OBJECTS)
	rm -f $(TINYOBJ_OBJECTS)
	rm -f glfw.a gl3w.a lodepng.a tinyobjloader.a bin
