O_FILES= ogame/Building.o \
		 ogame/GameObject.o \
		 ogame/structure.o \
		 ogame/Planet.o \
		 ogame/Resources.o \
		 ogame/Simulation.o \
		 ogame/BuildQueue.o \
		 ogame/Buildings/SolarPlant.o \
		 ogame/Buildings/FusionPlant.o \
		 ogame/Buildings/Laboratory.o \
		 ogame/Buildings/RobotFactory.o \
		 ogame/Buildings/Shipyard.o \
		 ogame/Technology.o \
		 ogame/Technologies/Astrophysics.o \
		 ogame/Technologies/EnergyTechnology.o \
		 ogame/Technologies/EspionageTechnology.o \
		 ogame/Technologies/ImpulseDrive.o \
		 ogame/Ship.o \
		 ogame/Ships/SolarSatellite.o \
		 ogame/Ships/ColonizationShip.o \
		 ogame/Mines/CrystalMine.o \
		 ogame/Mines/DeuteriumMine.o \
		 ogame/Mines/MetalMine.o \
		 ogame/Mines/Mine.o \
		 ogame/Storage/MetalStorage.o \
		 ogame/Storage/CrystalStorage.o \
		 ogame/Storage/DeuteriumStorage.o \
		 genetic_algorithm/basic_crossover_operator.o \
		 genetic_algorithm/uniform_crossover_operator.o \
		 genetic_algorithm/PMX_crossover_operator.o \
		 genetic_algorithm/chromosome.o \
		 genetic_algorithm/crossover.o \
		 genetic_algorithm/utility.o \
		 genetic_algorithm/random_generators.o \

TEST_FILES = tests/ogame_test.o \
			 tests/genetic_test.o

VPATH=	ogame/Mines/ \
		ogame/Buildings/ \
		ogame/Ships/ \
		ogame/Technologies/ \
		ogame/Storage/ \
		ogame/

INCLUDES=-Iogame \
		 -Igenetic_algorithm \
		 -Iogame/Mines \
		 -Iogame/Buildings \
		 -Iogame/Ships \
		 -Iogame/Technologies \
		 -Iogame/Storage

CXXFLAGS=--std=c++14 -Wall -g $(INCLUDES)

		
OUT=main.o
OUT_TESTS=test.o

all: main.cpp $(O_FILES)
	$(CXX) main.cpp $(O_FILES) -o $(OUT) $(CXXFLAGS) $(INCLUDES)


test: tests/main.cpp $(O_FILES) $(TEST_FILES)
	$(CXX) tests/main.cpp $(O_FILES) $(TEST_FILES) -o $(OUT_TESTS) $(CXXFLAGS) $(INCLUDES)

clean:
	-rm ogame/*.o
	-rm ogame/Mines/*.o
	-rm ogame/Buildings/*.o
	-rm ogame/Technologies/*.o
	-rm ogame/Ships/*.o
	-rm ogame/Storage/*.o
	-rm genetic_algorithm/*.o
	-rm tests/*.o

