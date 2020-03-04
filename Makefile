O_FILES= ogame/Building.o \
		 ogame/Planet.o \
		 ogame/Resources.o \
		 ogame/Simulation.o \
		 ogame/SolarPlant.o \
		 ogame/Mines/CrystalMine.o \
		 ogame/Mines/DeuteriumMine.o \
		 ogame/Mines/MetalMine.o \
		 ogame/Mines/Mine.o \
		 ogame/structure.o \
		 genetic_algorithm/basic_crossover_operator.o \
		 genetic_algorithm/chromosome.o \
		 genetic_algorithm/crossover.o

TEST_FILES = tests/ogame_test.o \
			 tests/genetic_test.o

VPATH=	ogame/Mines/ \
		ogame/

INCLUDES=-Iogame \
		 -Igenetic_algorithm \
		 -Iogame/Mines
CXXFLAGS=--std=c++11 -Wall -g $(INCLUDES)

		
OUT=main.o
OUT_TESTS=test.o

all: main.cpp $(O_FILES)
	$(CXX) main.cpp $(O_FILES) -o $(OUT) $(CXXFLAGS) $(INCLUDES)


test: tests/main.cpp $(O_FILES) $(TEST_FILES)
	$(CXX) tests/main.cpp $(O_FILES) $(TEST_FILES) -o $(OUT_TESTS) $(CXXFLAGS) $(INCLUDES)

clean:
	-rm ogame/*.o
	-rm ogame/Mines/*.o
	-rm genetic_algorithm/*.o
	-rm tests/*.o

