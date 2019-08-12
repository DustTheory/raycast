CXX := g++
LD  := g++

EXEC := GAME
FLAGS := -Wall
CXXFLAGS := $(FLAGS)
LDFLAGS := $(FLAGS)
INC := -I inc
SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:src/%.cpp=tmp/%.o)

EXEC_TEST := test
FLAGS_TEST := $(FLAGS)
CXXFLAGS_TEST := $(CXXFLAGS)
LDFLAGS_TEST := $(LDFLAGS)
INC_TEST := $(INC) -I lib/catch/inc
SRC_TEST := $(wildcard tst/*.cpp)
OBJ_TEST := $(filter-out tmp/game.o, $(OBJ)) $(SRC_TEST:tst/%.cpp=tmp/%.o)

SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system 

.SUFIXES:

# ------------------------------------------------------------------------

.PHONY: all

all: out/$(EXEC)

out/$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $(OBJ) $(SFML_LIBS)

# -----------------------------------------------------------------------

.PHONY: test
test: out/$(EXEC_TEST)

out/$(EXEC_TEST): $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) $(INC_TEST) -o $@ $(OBJ_TEST) $(SFML_LIBS)	

# -----------------------------------------------------------------------

tmp/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< $(INC) -o $@ && echo "[OK] $@"

tmp/%.o: tst/%.cpp
	$(CXX) $(CXXFLAGS) -c $< $(INC_TEST) -o $@ && echo "[OK] $@"

# -----------------------------------------------------------------------

.PHONY: clean clear
clean clear: 
	@rm -f out/* && echo "[CL] out/"
	@rm -f tmp/* && echo "[CL] tmp/"

