#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

struct Point {
	int x, y, c;
	
};
struct An {
	std::vector<Point> points;
};

int trailhead(int y, int x, std::vector<std::string> lines) {
	if (lines[y][x] != '0') {
		return 0;
	}
	std::vector<Point> stack;
	int sum = 0;
	stack.push_back(Point{ x,y,0 });
	while (!stack.empty()) {
		Point p = stack.back();
		stack.pop_back();
		int c = p.c + 1;
		const auto test = [&](Point pn) {
			if (pn.c == 9) {
				++sum;
			}
			else {
				stack.push_back(pn);
			}
		};
		if (p.x > 0 && lines[p.y][p.x - 1] == c + '0') {
			test(Point{ p.x - 1,p.y,c });
		}
		if (p.y > 0 && lines[p.y-1][p.x] == c + '0') {
			test(Point{ p.x,p.y-1,c });
		}
		if (p.x + 1 < lines[0].size() && lines[p.y][p.x + 1] == c + '0') {
			test(Point{ p.x + 1,p.y,c });
		}
		if (p.y + 1 < lines.size() && lines[p.y + 1][p.x] == c + '0') {
			test(Point{ p.x,p.y + 1,c });
		}
	}
	return sum;
}
int main()
{
	std::ifstream stream("..\\input10.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> lines;
	while (std::getline(stream, line) && !line.empty()) {
		lines.push_back(line);
	}
	for (int i = 0; i < lines.size(); ++i) {
		for (int j = 0; j < lines[0].size(); ++j) {
			sum += trailhead(i, j, lines);
		}
	}
	std::cout << sum << std::endl;
	return 0;
}
