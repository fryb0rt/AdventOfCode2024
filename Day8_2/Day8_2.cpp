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

int main()
{
	std::ifstream stream("..\\input8.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> lines;
	std::vector<An> an(256);
	int i = 0;
	while (std::getline(stream, line) && !line.empty()) {
		lines.push_back(line);
		for (int i = 0; i < line.size(); ++i) {
			if (line[i] != '.' && line[i] != '#') {
				an[line[i]].points.push_back(Point{ i, int(lines.size() - 1) });
			}
		}
	}
	for (int i = 0; i < an.size(); ++i) {
		for (int j = 0; j < an[i].points.size(); ++j) {
			for (int k = j + 1; k < an[i].points.size(); ++k) {
				Point distance, p1 = an[i].points[j], p2 = an[i].points[k];
				distance.x = p1.x - p2.x;
				distance.y = p1.y - p2.y;
				const auto test = [&](Point p) {
					if (p.x >= 0 && p.y >= 0 && p.x < lines[0].size() && p.y < lines.size()) {
						lines[p.y][p.x] = '#';
						return true;
					}
					return false;
				};
				int i = 0;
				while (test(Point{ p1.x + i * distance.x, p1.y + i * distance.y })) {
					++i;
				}
				i = 0;
				while (test(Point{ p1.x - i * distance.x, p1.y - i * distance.y })) {
					++i;
				}
				i = 0;
				while (test(Point{ p2.x + i * distance.x, p2.y + i * distance.y })) {
					++i;
				}
				i = 0;
				while (test(Point{ p2.x - i * distance.x, p2.y - i * distance.y })) {
					++i;
				}
			}
		}
	}

	for (int i = 0; i < lines.size(); ++i) {
		std::cout << lines[i] << std::endl;
		for (int j = 0; j < lines[0].size(); ++j) {
			sum += lines[i][j] == '#';
		}
	}
	std::cout << sum << std::endl;
	return 0;
}
