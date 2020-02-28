O_FILES= Building.o \
		 Planet.o \
		 Resources.o \
		 Simulation.o \
		 SolarPlant.o \
		 CrystalMine.o \
		 DeuteriumMine.o \
		 MetalMine.o \
		 Mine.o \
		 structure.o
VPATH=	Mines/

CXXFLAGS=--std=c++11 -Wall -g
OUT=main.o

all: main.cpp $(O_FILES)
	$(CXX) main.cpp $(O_FILES) -o $(OUT) $(CXXFLAGS)

clean:
	-rm *.o
	-rm Mines/*.o
