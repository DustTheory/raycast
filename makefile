CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsqlite3

T_SRC_DIR   := tests
T_BUILD_DIR := build_tests
SRC_DIR     := src
LIB_DIR	    := lib
BUILD_DIR   := build

SRC         := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
TEST_SRC    := $(foreach tdir,$(T_SRC_DIR),$(wildcard $(tdir)/*.cpp))
OBJ         := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
TEST_OBJ    := $(patsubst $(T_SRC_DIR)/%.cpp,$(T_BUILD_DIR)/%.o,$(TEST_SRC))
TEST_EXEC   := $(patsubst $(T_SRC_DIR)/%.cpp,$(T_BUILD_DIR)/%,$(TEST_SRC))
INCLUDES    := $(addprefix -I ,$(LIB_DIR))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) ${INCLUDES} -c $(SRC_DIR)/$*.cpp -o $(BUILD_DIR)/$*.o

$(T_BUILD_DIR)/%.o: $(T_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) ${INCLUDES} -c $(T_SRC_DIR)/$*.cpp -o $(T_BUILD_DIR)/$*.o

$(T_BUILD_DIR)/%.test: $(T_BUILD_DIR)/%.test.o ${OBJ}
	${CXX} ${CXXFLAGS} -o $@ $+ ${LIBS} 

$(BUILD_DIR)/game: ${OBJ} main.cpp
	${CXX} ${CXXFLAGS} ${INCLUDES} -o $@ $+ ${LIBS} 

main.cpp:
	$(CXX) $(CXXFLAGS) ${INCLUDES} -c main.cpp -o $(BUILD_DIR)/$*.o

clean:
	rm $(BUILD_DIR)/* $(T_BUILD_DIR)/*

tests: $(TEST_EXEC) ;


