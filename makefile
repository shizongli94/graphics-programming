main: Screen2DSquare.o Drawer2DRectangle.o DisplayFileInterpreter2DRectangle.o Transformer2D.o main.o 
	g++ $(shell Magick++-config --ldflags --cxxflags) $(wildcard *.o)  -o main

main.o: main.cc
	g++ -c main.cc

FrameBuffer2DRectangle.o: include/FrameBuffer2DRectangle.h src/FrameBuffer2DRectangle.cc FrameBuffer2D.o
	g++ -c include/FrameBuffer2DRectangle.h src/FrameBuffer2DRectangle.cc

FrameBuffer2DSquare.o: include/FrameBuffer2DSquare.h src/FrameBuffer2DSquare.cc FrameBuffer2DRectangle.o
	g++ -c include/FrameBuffer2DSquare.h src/FrameBuffer2DSquare.cc

Screen2DSquare.o: include/Screen2DSquare.h src/Screen2DSquare.cc FrameBuffer2DSquare.o
	g++ -c $(shell Magick++-config --cxxflags --cppflags) include/Screen2DSquare.h src/Screen2DSquare.cc

Drawer2DRectangle.o: include/Drawer2DRectangle.h src/Drawer2DRectangle.cc FrameBuffer2DRectangle.o
	g++ -c include/Drawer2DRectangle.h src/Drawer2DRectangle.cc

Command.o: include/Command.h src/Command.cc
	g++ -c include/Command.h src/Command.cc

DisplayFileInterpreter2DRectangle.o: include/DisplayFileInterpreter2DRectangle.h src/DisplayFileInterpreter2DRectangle.cc Command.o Drawer2DRectangle.o PolySide.o Transformer2D.o
	g++ -c include/DisplayFileInterpreter2DRectangle.h src/DisplayFileInterpreter2DRectangle.cc

PolySide.o: include/PolySide.h src/PolySide.cc
	g++ -c include/PolySide.h src/PolySide.cc

Transformer2D.o: include/Transformer2D.h src/Transformer2D.cc
	g++ -c include/Transformer2D.h src/Transformer2D.cc
