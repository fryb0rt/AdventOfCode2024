#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
	std::ifstream stream("..\\input4.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> data;
	while (std::getline(stream, line)) {
		data.push_back(line);
	}
	std::string word = "XMAS";
	std::vector<int> posX = { 1,-1,0,0,1,1,-1,-1 };
	std::vector<int> posY = { 0,0,1,-1,1,-1,-1,1 };
	for (int y = 0; y < data.size(); ++y) {
		for (int x = 0; x < data[y].size(); ++x) {
			for (int d = 0; d < 8; ++d) {
				bool ok = true;
				for (int i = 0; i < word.size(); ++i) {
					int xx = posX[d] * i + x;
					int yy = posY[d] * i + y;
					if (yy >= 0 && yy < data.size() && xx >= 0 && xx < data[yy].size() && data[yy][xx]==word[i]) {
						
					}
					else {
						ok = false;
					}
				}
				sum += int(ok);
			}
		}
	}
	std::cout << sum << std::endl;
	return 0;
}