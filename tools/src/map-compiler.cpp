#include <iostream>
#include <iomanip>
#include <fstream>

#include "../../src/json.hpp"

using namespace std;

using json = nlohmann::json;

int main(int argc, char **argv){
	string path = argv[1];
	string opath = argv[2];
	ifstream i(path);
	int h, w;
	i >> h >> w;
	
	json j;

	j["height"] = h;
	j["width"] = w;
	
	vector<int> map;

	int t;
	for(int k = 0; k < h*w; k++){
		i >> t;
		map.push_back(t);
	}

	j["map"] = map;

	int sx, sy; // spawnpoint

	i >> sx >> sy;

	j["spawnpoint_x"] = sx;
	j["spawnpoint_y"] = sy;

	ofstream o(opath);
	o << setw(4) << j << endl;
}
