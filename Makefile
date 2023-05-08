# Makefile

SRC = $(wildcard src/*.cpp)
INC = $(wildcard src/*.h)
MAIN = $(wildcard main/*.cpp)

ROOTLIB = $(shell root-config --libs)

CXX = g++ $(shell root-config --cflags) -I ~/eigen-3.4.0

########################################

SRC_OBJ = $(patsubst %.cpp, bin/%.o, $(notdir $(SRC)))
MAIN_OBJ = $(patsubst %.cpp, bin/%.o, $(notdir $(MAIN)))

bin/%.exe: bin/%.o $(SRC_OBJ)
	@echo "compiling and linking file [ &< ]"
	$(CXX)  -I src $< -o $@ $(SRC_OBJ) $(ROOTLIB)


bin/%.o: src/%.cpp
	@echo "compiling file [ $< ] to [ $@ ]"
	$(CXX) -c $< -o $@

bin/%.o: main/%.cpp
	@echo "compiling file [ $< ] to [ $@ ]"
	$(CXX) -c $< -o $@


#########################################

FTILDE = $(wildcard src/*~) $(wildcard main/*~)

clean:
	@echo "cleaning..."
	@rm $(FTILDE) $(FBIN)
dump:
	@echo "dump list of src files..."
	@echo $(SRC)
	@echo $(INC)
	@echo $(MAIN)
	@echo $(FTILDE)
	@echo $(FBIN)
	@echo $(BIN)
	