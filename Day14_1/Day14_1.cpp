#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

int64_t solve(int64_t aX, int64_t aY, int64_t bX, int64_t bY, int64_t priceX, int64_t priceY) {
	const int64_t det = aX * bY - bX * aY;
	if (det != 0) {
		const int64_t a = priceX * bY - priceY * bX;
		const int64_t b = priceY * aX - priceX * aY;
		if (a % det == 0 && b % det == 0) {
			return (a * 3 + b * 1) / det;
		}
	}
	return 0;
}

struct Robot {
	int x, y;
	int vx, vy;
};

int simulate(Robot r, int maxx, int maxy, int steps) {
	r.x = r.x + r.vx * steps;
	r.y = r.y + r.vy * steps;
	if (r.x >= 0) {
		r.x %= maxx;
	} else {
		r.x += ((-r.x + maxx - 1) / maxx) * maxx;
		/*while (r.x < 0) {
			r.x += maxx;
		}*/
	}
	if (r.y >= 0) {
		r.y %= maxy;
	}
	else {
		r.y += ((-r.y + maxy - 1) / maxy) * maxy;
		/*while (r.y < 0) {
			r.y += maxy;
		}*/
	}
	int middleX = maxx / 2;
	int middleY = maxy / 2;
	if (r.x == middleX || r.y == middleY) {
		return 4;
	}
	int qX = r.x < middleX ? 0 : 1;
	int qY = r.y < middleY ? 0 : 1;
	return qX * 2 + qY;
}

int main()
{
	std::ifstream stream("..\\input14.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> lines;
	while (std::getline(stream, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}
	std::vector<Robot> robots;
	int quadrant[5] = { 0,0,0,0,0 };
	for (int i = 0; i < lines.size(); i += 1) {
		std::istringstream is(lines[i]);
		Robot r;
		char c;
		is >> c;
		is >> c;
		is >> r.x;
		is >> c;
		is >> r.y;
		is >> c;
		is >> c;
		is >> r.vx;
		is >> c;
		is >> r.vy;
		++quadrant[simulate(r, 101, 103, 100)];
	}

	sum = 1;
	for (int i = 0; i < 4; ++i) {
		sum *= quadrant[i];
	}

	std::cout << sum << std::endl;
	return 0;
}
