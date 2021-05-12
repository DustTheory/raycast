#include <stdexcept>

#include "Camera.h"

int PASSED_TESTS, FAILED_TESTS;
std::string CURRENT_TEST;

#define PASS(str) { PASSED_TESTS ++;printf("TEST %s PASS %s\n", CURRENT_TEST.c_str(), str); return;}
#define FAIL(str) { FAILED_TESTS ++;printf("TEST %s FAIL %s\n", CURRENT_TEST.c_str(), str); return;}

void START_TEST(std::string testName){
    CURRENT_TEST = testName;
}

void testConstructor(){
    START_TEST("Test constructor");
    try{
        World world = World("worlds/testWorld.world");
        Camera camera = Camera(&world, 90, 100);
    }catch(...){
        FAIL("");
    }
    PASS("");
}

void testFireRay(){
    START_TEST("Test fireRay");
    World world = World("worlds/testWorld.world");
    Camera camera = Camera(&world, 90, 100);

    int mapX, mapY, side;
    std::tie(mapX, mapY, side) = camera.fireRay({1, 1}, {1, 0});
    if(mapX != 1 || mapY != 23 || side != 1)
        FAIL("");

    std::tie(mapX, mapY, side) = camera.fireRay({1, 1}, {0, 1});
    if(mapX != 16 || mapY != 1 || side != 0)
        FAIL("");
    
    std::tie(mapX, mapY, side) = camera.fireRay({1, 1}, {0, 1});
    if(mapX != 16 || mapY != 1 || side != 0)
        FAIL("");

    std::tie(mapX, mapY, side) = camera.fireRay({1, 1}, {1, 1});
    if(mapX != 5 || mapY != 6 || side != 1)
        FAIL("");

    PASS("");
}


int main(){
    PASSED_TESTS = FAILED_TESTS = 0;

    testConstructor();
    testFireRay();

   
    printf("\n#############################################################\n");
    printf("PASSED: %d\n", PASSED_TESTS);
    printf("FAILED: %d\n", FAILED_TESTS);
    printf("TOTAL: %d\n", FAILED_TESTS+PASSED_TESTS);
}