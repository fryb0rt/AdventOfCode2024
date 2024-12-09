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
		for (int j = 0; j < length; ++j) {
			disk.push_back(Space{ ID, free });
		}
		if (!free) {
			++ID;
		}
		free = !free;
	}
	int left = 0;
	int right = disk.size() - 1;
	while (left < right) {
		while (!disk[left].free) {
			++left;
		}
		while (right >= 0 && disk[right].free) {
			--right;
		}
		if (left < right) {
			disk[left] = disk[right];
			disk[right].free = true;
			++left;
			--right;
		}
	}
	for (int i = 0; i < disk.size(); ++i) {
		if (disk[i].free) {
			break;
		}
		sum += i * disk[i].ID;
	}

	std::cout << sum << std::endl;
	return 0;
}
