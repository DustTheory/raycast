#include "World.h"
#include <sqlite3.h>
#include <string>
#include <stdexcept>
#include <sstream>

World::World(Map map): map(map){}

static int placeHolderCallback(void *NotUsed, int argc, char **argv, char **szColName){
    return 0;
}

// Loads World from world file
World::World(std::string filename){
    // Open world file
    sqlite3 *db;
    char *szErrMsg = 0;
    int rc = sqlite3_open_v2(filename.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if(rc)
        throw std::runtime_error("Can't open world file");

    // Read map from worldfile
    rc = sqlite3_exec(db, "SELECT mapdata, mapWidth, mapHeight FROM Maps WHERE id=0;", [](void *world, int argc, char **argv, char **szColName){
        ((World*)world)->map = Map((std::string)argv[0], std::stoi(argv[1]), std::stoi(argv[1]));
        return 0;
    }, this, &szErrMsg);  
    if(rc)
        throw std::runtime_error("Failed reading map from world file");  
    
}

void World::saveToFile(const std::string filename){

    // Open world file
    sqlite3 *db;
    char *szErrMsg = 0;
    int rc = sqlite3_open_v2(filename.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if(rc)
        throw std::runtime_error("Can't open world file");

    
    // Create maps table
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Maps(id INTEGER PRIMARY KEY, mapdata TEXT NOT NULL, mapWidth INTEGER NOT NULL, mapHeight INTEGER NOT NULL);", placeHolderCallback, 0, &szErrMsg);    
    if(rc)
        throw std::runtime_error("Failed to initialize Map table");

    // Upsert our map into maps
    std::stringstream mapUpsertQuery;
    mapUpsertQuery << "INSERT INTO Maps values(0 , '";
    mapUpsertQuery << map.toString() << "', ";
    mapUpsertQuery << map.getMapHeight() << ",";
    mapUpsertQuery << map.getMapWidth() << ")";
    mapUpsertQuery << "ON CONFLICT(id) DO UPDATE SET mapdata=excluded.mapdata;";

    rc = sqlite3_exec(db, mapUpsertQuery.str().c_str(), placeHolderCallback, 0, &szErrMsg);

    if(rc)
        throw std::runtime_error("Error writing to world file");
        
}
