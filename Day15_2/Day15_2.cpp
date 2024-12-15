#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>


struct P {
	int x, y;
	bool moved;
	int nx, ny;
};

void moveBoxes(int x, int y, int vx, int vy, const std::vector<std::string>& map, std::vector<P>& boxes) {
	for (auto& b : boxes) {
		if ((b.x == x || b.x + 1 == x) && b.y == y && !b.moved) {
			b.nx = b.x + vx;
			b.ny = b.y + vy;
			b.moved = true;
			moveBoxes(b.nx, b.ny, vx, vy, map, boxes);
			moveBoxes(b.nx + 1, b.ny, vx, vy, map, boxes);
		}
	}
}

bool checkBoxes(const std::vector<std::string>& map, const std::vector<P>& boxes) {
	for (auto& b : boxes) {
		if (b.moved && (map[b.ny][b.nx] == '#' || map[b.ny][b.nx + 1] == '#')) {
			return false;
		}
	}
	return true;
}

void performMove(bool ok, std::vector<P>& boxes) {
	for (auto& b : boxes) {
		if (b.moved) {
			b.moved = false;
			if (ok) {
				b.x = b.nx;
				b.y = b.ny;
			}
		}
	}
}

void move(char m, int& rx, int& ry, std::vector<std::string>& map, std::vector<P>& boxes) {
	int vx = 0, vy = 0;
	switch (m) {
	case '<': vx = -1; break;
	case '>': vx = 1; break;
	case '^': vy = -1; break;
	case 'v': vy = 1; break;
	default:return;
	}
	int sx = rx + vx, sy = ry + vy;
	if (map[sy][sx] == '#') {
		return;
	}
	moveBoxes(sx, sy, vx, vy, map, boxes);
	if (checkBoxes(map, boxes)) {
		rx = sx;
		ry = sy;
		performMove(true, boxes);
	}
	else {
		performMove(false, boxes);
	}
}

int main()
{
	std::ifstream stream("..\\input15.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> map;
	while (std::getline(stream, line) && !line.empty()) {
		map.push_back(line);
	}
	std::string moves;
	while (std::getline(stream, line) && !line.empty()) {
		moves += line;
	}

	std::vector<std::string> mapNew(map.size());
	std::vector<P> boxes;
	int rx = 0;
	int ry = 0;
	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			if (map[y][x] == '@') {
				mapNew[y] += "..";
				rx = x * 2;
				ry = y;
			}
			if (map[y][x] == 'O') {
				mapNew[y] += "..";
				boxes.push_back(P{ x * 2,y, false, x * 2,y });
			}
			if (map[y][x] == '.') {
				mapNew[y] += "..";
			}
			if (map[y][x] == '#') {
				mapNew[y] += "##";
			}
		}
	}
	for (char c : moves) {
		move(c, rx, ry, mapNew, boxes);
	}

	for (int y = 0; y < mapNew.size(); ++y) {
		for (int x = 0; x < mapNew[0].size(); ++x) {
			bool box = false;
			for (auto& b : boxes) {
				if (x == b.x && y == b.y) {
					std::cout << '[';
					box = true;
				}
				if (x == b.x + 1 && y == b.y) {
					std::cout << ']';
					box = true;
				}
			}
			if (!box) {
				if (rx == x && ry == y) {
					std::cout << '@';
				}
				else {
					std::cout << mapNew[y][x];

				}
			}
		}
		std::cout << std::endl;
	}
	for (auto& b : boxes) {
		sum += b.y * 100 + b.x;
	}


	std::cout << sum << std::endl;
	return 0;
}
