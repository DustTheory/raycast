#include <stdexcept>
#include <string>
#include "Map.h"

int PASSED_TESTS, FAILED_TESTS;
std::string CURRENT_TEST;

void START_TEST(std::string testName){
    CURRENT_TEST = testName;
}

#define PASS(str) { PASSED_TESTS ++;printf("TEST %s PASS %s\n", CURRENT_TEST.c_str(), str); return;}
#define FAIL(str) { FAILED_TESTS ++;printf("TEST %s FAIL %s\n", CURRENT_TEST.c_str(), str); return;}

Map defaultMap(){
    std::string mapdata = (std::string) "111111111111111111111111" +
                                        "100000000000000000000001" +
                                        "100000000000000000000001" +
                                        "100000000000000000000001" +
                                        "100000222220000303030001" +
                                        "100000200020000000000001" +
                                        "100000200020000300030001" +
                                        "100000200020000000000001" +
                                        "100000220220000303030001" +
                                        "100000000000000000000001" +
                                        "100000000000000000000001" +
                                        "100000000000000000000001" +
                                        "100000000000000000000001" +
                                        "100000000000000000000001" +
                                        "100000000000000000000001" +
                                        "100000000000000000000001" +
                                        "144444444000000000000001" +
                                        "140400004000000000000001" +
                                        "140000504000000000000001" +
                                        "140400004000000000000001" +
                                        "140444444000000000000001" +
                                        "140000000000000000000001" +
                                        "144444444000000000000001" +
                                        "111111111111111111111111";
    return Map(mapdata, 24, 24);
}

void testConstructor(){
    START_TEST("Constructor test");
    try{
        Map map = defaultMap();
    }catch(const std::bad_alloc &){
        FAIL("Failed to allocate memory");
    }
    PASS(""); 
}


void testOutOfBounds(){
    START_TEST("isOutOfBounds test");
    try{
        Map map = defaultMap();
        if(map.isOutOfBounds(0, 0))
            FAIL("Wrong answer");
        if(map.isOutOfBounds(1, 10))
            FAIL("Wrong answer");
        if(map.isOutOfBounds(23, 23))
            FAIL("Wrong answer");
        if(!map.isOutOfBounds(24, 23))
            FAIL("Wrong answer");
        if(!map.isOutOfBounds(1, 25))
            FAIL("Wrong answer");
        if(!map.isOutOfBounds(-1, 0))
            FAIL("Wrong answer");
        if(!map.isOutOfBounds(0, -100))
            FAIL("Wrong answer");
    }catch(const std::bad_alloc &){
        FAIL("Failed to allocate memory");
    }
    PASS(""); 
}

void testAtCoordsInBounds(){
    START_TEST("atCoords in bounds test");
    try{
        Map map = defaultMap();
        try{
            if(map.atCoords(0, 0) != MapCell::Wall1)
                FAIL("Wrong answer");
            if(map.atCoords(1, 1) != MapCell::EmptyCell)
                FAIL("Wrong answer");
            if(map.atCoords(1, 1) != MapCell::EmptyCell)
                FAIL("Wrong answer");
            if(map.atCoords(22, 1) != MapCell::Wall4)
                FAIL("Wrong answer");
        }catch(const std::out_of_range &){
            FAIL("Out of bounds");
        }
    }catch(const std::bad_alloc &){
        FAIL("Failed to allocate memory");
    }
    PASS(""); 
}

void testAtCoordsOutOfBounds(){
    START_TEST("atCoords out of bounds test");
    try{
        Map map = defaultMap();
        try{
            map.atCoords(-1, 1);
            map.atCoords(-1, -2);
            map.atCoords(25, 1);
        }catch(const std::out_of_range &){
            PASS("");
        }
    }catch(const std::bad_alloc &){
        FAIL("Failed to allocate memory");
    }
    PASS(""); 
}

int main(){
    PASSED_TESTS = FAILED_TESTS = 0;

    testConstructor();
    testOutOfBounds();
    testAtCoordsInBounds();

    printf("\n#############################################################\n");
    printf("PASSED: %d\n", PASSED_TESTS);
    printf("FAILED: %d\n", FAILED_TESTS);
    printf("TOTAL: %d\n", FAILED_TESTS+PASSED_TESTS);
}