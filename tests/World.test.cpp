#include <stdexcept>
#include <string>

#include "World.h"
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

void constructorTest(){
    START_TEST("Map onstructor test");
    try{
        World world = World(defaultMap());
    }catch(...){
        FAIL("")
    }
    PASS("");
}

void saveToFileTest(){
 START_TEST("Map onstructor test");
    try{
        World world = World(defaultMap());
        world.saveToFile("worlds/testWorld.world");
    }catch(...){
        FAIL("")
    }
    PASS("");
}

void fileConstructorTest(){
    START_TEST("File onstructor test");
    try{
        World world = World("worlds/testWorld.world");
    }catch(const std::exception &e){
        FAIL(e.what());
    }
    PASS("");
}

int main(){
    PASSED_TESTS = FAILED_TESTS = 0;

    fileConstructorTest();
    saveToFileTest();
   
    printf("\n#############################################################\n");
    printf("PASSED: %d\n", PASSED_TESTS);
    printf("FAILED: %d\n", FAILED_TESTS);
    printf("TOTAL: %d\n", FAILED_TESTS+PASSED_TESTS);
}