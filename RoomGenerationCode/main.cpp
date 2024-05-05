#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <math.h>

using namespace std;

bool containChecker(vector<int> v = {0}, int t = 0) {
	int cnt = count(v.begin(), v.end(), t);
	if (cnt > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

vector<int> sort(vector<int> v = {}) {
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	return v;
}

bool checkRight(vector<int> v, int i) {
	int cnt = count(v.begin(), v.end(), i + 1);
	if (cnt > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool checkLeft(vector<int> v, int i) {
	int cnt = count(v.begin(), v.end(), i - 1);
	if (cnt > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool checkUp(vector<int> v, int i, int g = 4) {
	int cnt = count(v.begin(), v.end(), i + g);
	if (cnt > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool checkDown(vector<int> v, int i, int g = 4) {
	int cnt = count(v.begin(), v.end(), i - g);
	if (cnt > 0) {
		return true;
	}
	else {
		return false;
	}
}

void list(vector<int> v) {
	for(int i = 0; i < v.size(); i++) {
		cout << v[i] << ", ";
	}
	cout << "\n";
}

int main() {
	srand(time(0));
	int gridSize = 4;
	vector<int> rooms = {};
	int startRoom = rand() % (gridSize * gridSize);
	rooms.push_back(startRoom);
	int shopRoom = rand() % (gridSize * gridSize);
	while(shopRoom == startRoom || abs(startRoom - shopRoom) == gridSize || abs(startRoom - shopRoom) == 1) {
		shopRoom = rand() % (gridSize * gridSize);
	}
	rooms.push_back(shopRoom);
	int startX = startRoom % gridSize;
	int startY = floor(startRoom / gridSize);
	int shopX = shopRoom % gridSize;
	int shopY = floor(shopRoom / gridSize);
	if (startX < shopX) {
		int d = shopX - startX;
		if (startY == shopY) {
			d = (shopX - startX) - 1;
		}
		for(int i = 0; i < d; i++ ) {
			rooms.push_back(startRoom + (i + 1));
		}
	}
	if (startX > shopX) {
		int d = startX - shopX;
		if (startY == shopY) {
			d = (startX - shopX) - 1;
		}
		for(int i = 0; i < d; i++ ) {
			rooms.push_back(startRoom - (i + 1));
		}
	}
	int temp = (startY * gridSize) + shopX;
	if (startY < shopY) {
		int d = (shopY - startY) - 1;
		for(int i = 0; i < d; i++ ) {
			rooms.push_back(temp + (i + 1) * gridSize);
		}
	}
	if (startY > shopY) {
		int d = (startY - shopY) - 1;
		for(int i = 0; i < d; i++ ) {
			rooms.push_back(temp - (i + 1) * gridSize);
		}
	}
	cout << "Start room is " << startRoom << " (" << startX << ", " << startY << ").\n";
	cout << "Shop room is " << shopRoom << " (" << shopX << ", " << shopY << ").\n";
	cout << "The connecting rooms are:\n";
	for(int i = 2; i < rooms.size(); i++) {
		cout << rooms[i] << "\n";
	}
	rooms = sort(rooms);
	vector<int> verticalConnections = {};
	vector<int> horizontalConnections = {};
	vector<int> tempRooms = {};
	for(int i = 0; i < rooms.size(); i++) {
		int room = rooms[i];
		int temp = rand() % 50;
		if (floor(room / gridSize) != gridSize - 1 && temp < 25 && !checkUp(rooms, room, gridSize && !containChecker(horizontalConnections, room))) {
			tempRooms.push_back(room + gridSize);
		}
		if (room % gridSize != gridSize - 1 && temp > 10 && temp < 35 && !checkRight(rooms, room) && !containChecker(verticalConnections, room)) {
			tempRooms.push_back(room + 1);
		}
		if (floor(room / gridSize) != 0 && temp > 20 && temp < 45 && !checkDown(rooms, room) && !containChecker(horizontalConnections, room - 4)) {
			tempRooms.push_back(room - gridSize);
		}
		if (room % gridSize != 0 && temp > 25 && !checkLeft(rooms, room) && !containChecker(verticalConnections, room - 1)) {
			tempRooms.push_back(room - 1);
		}
	}
	rooms.insert(rooms.end(), tempRooms.begin(), tempRooms.end());
	int bRoom = rooms[rand() % rooms.size()];
	int bossRoom = 0;
	while(bRoom == startRoom || bRoom == shopRoom || (checkUp(rooms, bRoom) && checkDown(rooms, bRoom) && checkLeft(rooms, bRoom) && checkRight(rooms, bRoom))) {
		bRoom = rooms[rand() % rooms.size()];
	}
	if(!checkUp(rooms, bRoom) && floor(bRoom / gridSize) != gridSize - 1) {
		bossRoom = bRoom + gridSize;
		rooms.push_back(bossRoom);
	}
	else if(!checkDown(rooms, bRoom) && floor(bRoom / gridSize) != 0) {
		bossRoom = bRoom - gridSize;
		rooms.push_back(bossRoom);
	}
	else if(!checkLeft(rooms, bRoom) && bRoom % gridSize != 0) {
		bossRoom = bRoom - 1;
		rooms.push_back(bossRoom);
	}
	else if(!checkRight(rooms, bRoom) && bRoom % gridSize != gridSize - 1) {
		bossRoom = bRoom + 1;
		rooms.push_back(bossRoom);
	}
	else {
		bossRoom = bRoom;
		rooms.push_back(bossRoom);
	}
	for(int i = 0; i < rooms.size(); i++) {
		int room = rooms[i];
		if(room % gridSize != gridSize - 1 && checkRight(rooms, room) && !containChecker(verticalConnections, room)) {
			verticalConnections.push_back(room);
		}
		if (floor(room / gridSize) != gridSize - 1 && checkUp(rooms, room, gridSize) && !containChecker(horizontalConnections, room)) {
			horizontalConnections.push_back(room);
		}
	}
	
	
	rooms = sort(rooms);
	verticalConnections = sort(verticalConnections);
	horizontalConnections = sort(horizontalConnections);
	cout << "total rooms:\n";
	list(rooms);
	cout << "vertical connecting doors:\n";
	list(verticalConnections);
	cout << "horizontal connecting doors:\n";
	list(horizontalConnections);
	cout << "Boss room:\n" << bossRoom << "\n";
	vector<int> commonRooms = rooms;
	vector<int> removePoint = {};
	for(int i = 0; i < commonRooms.size(); i++) {
		if(commonRooms[i] == startRoom || commonRooms[i] == shopRoom || commonRooms[i] == bossRoom) {
			removePoint.push_back(i);
		}
	}
	sort(removePoint.begin(), removePoint.end(), greater<>());
	for(int i = 0; i < removePoint.size(); i++) {
		int r = removePoint[i];
		commonRooms.erase(commonRooms.begin() + r);
	}
	vector<string> roomNames = {
	"Cage", "Rocks", "Waterfall", "Bats", "Orcs", "Dungeon", "Vines", "Garden", "Monsters", "Squids", 
	"Dogs", "Rats"
	};
	vector<string> cRoomNames = {};
	for(int i = 0; i < commonRooms.size(); i++) {
		int t = rand() % roomNames.size();
		cRoomNames.push_back(roomNames[t]);
	}
	cout << "the common room names are:\n";
	for(int i = 0; i < commonRooms.size(); i++) {
		cout << i + 1 << ".\t" << commonRooms[i] << ":\t" << cRoomNames[i] << "\n";
	}
}


