# Makefile para compilar FractalDimension3D

CXX = g++
CXXFLAGS = -std=c++11 -Wall

OBJS = Atom.o Sphere.o FractalDimension3D.o main.o
TARGET = FractalDimension3D

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

Atom.o: Atom.cpp Atom.h
	$(CXX) $(CXXFLAGS) -c Atom.cpp

Sphere.o: Sphere.cpp Sphere.h Atom.h
	$(CXX) $(CXXFLAGS) -c Sphere.cpp

FractalDimension3D.o: FractalDimension3D.cpp FractalDimension3D.h Atom.h Sphere.h
	$(CXX) $(CXXFLAGS) -c FractalDimension3D.cpp

main.o: main.cpp FractalDimension3D.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(OBJS) $(TARGET)

