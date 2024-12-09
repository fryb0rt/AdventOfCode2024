#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

struct Point {
	int x, y;
	bool operator!=(const Point& p) {
		return p.x != x || p.y != y;
	}
};
struct An {
	std::vector<Point> points;
};

struct Space {
	int64_t ID;
	bool free;
	int length;
};

int main()
{
	std::ifstream stream("..\\input9.txt");
	std::string line;
	int64_t sum = 0;
	std::getline(stream, line);
	std::vector<Space> disk;
	bool free = false;
	int64_t ID = 0;
	for (int i = 0; i < line.size(); ++i) {
		int length = line[i] - '0';
		disk.push_back(Space{ ID, free, length });
		if (!free) {
			++ID;
		}
		free = !free;
	}
	int64_t lastID = disk.size() + 1;
	for (int i = disk.size() - 1; i >= 0; --i) {
		if (disk[i].free) {
			continue;
		}
		if (disk[i].ID >= lastID) {
			continue;
		}
		lastID = disk[i].ID;
		/*for (int k = 0; k < disk.size(); ++k) {
			for (int l = 0; l < disk[k].length; ++l) {
				if (disk[k].free) {
					std::cout << ".";
				}
				else {
					std::cout << disk[k].ID;
				}
			}
		}
		std::cout << std::endl;*/

		for (int j = 0; j < i - 1; ++j) {
			if (disk[j].free && disk[j].length >= disk[i].length) {
				int freeRemainder = disk[j].length - disk[i].length;
				disk[j] = disk[i];
				disk[i].free = true;

				// Fix first region
				if (freeRemainder > 0) {
					if (disk[j + 1].free) {
						disk[j + 1].length += freeRemainder;
					}
					else {
						disk.insert(disk.begin() + j + 1, Space{ -1, true, freeRemainder });
						++i;
					}
				}
				// Fix second region
				/*if (i > 0 && disk[i - 1].free) {
					disk[i - 1].length += disk[i].length;
					disk.erase(disk.begin() + i);
					--i;
				}
				if (i + 1 < disk.size() && disk[i + 1].free) {
					disk[i].length += disk[i + 1].length;
					disk.erase(disk.begin() + i + 1);
				}*/
				break;
			}
		}
	}
	int64_t index = 0;
	for (int i = 0; i < disk.size(); ++i) {
		for (int j = 0; j < disk[i].length; ++j) {
			if (!disk[i].free) {
				sum += index * disk[i].ID;
			}
			++index;
		}
	}

	std::cout << sum << std::endl;
	return 0;
}
