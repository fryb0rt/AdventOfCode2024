#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

bool test(std::vector<int>& v, int skipIndex) {
	int state = 0;
	int prev = -1;
	bool ok = true;
	int index = -1;
	for (int num : v) {
		++index;
		if (index == skipIndex) {
			continue;
		}
		if (prev > -1) {
			if (abs(prev - num) > 3) {
				ok = false;
			}
			if (prev == num) {
				ok = false;
			}
			if (state == 0) {
				if (prev < num) {
					state = 1;
				}
				else if (prev > num) {
					state = -1;
				}
			}
			else {
				if (state == -1 && prev < num) {
					ok = false;
				}
				if (state == 1 && prev > num) {
					ok = false;
				}
			}
		}
		prev = num;
	}
	return ok;
}

int main()
{
	std::ifstream stream("..\\input2.txt");
	std::string line;
	int sum = 0;
	while (std::getline(stream, line)) {
		std::istringstream iss(line);
		std::vector<int> v;
		while (!iss.eof()) {
			int num;
			iss >> num;
			v.push_back(num);
		}
		bool ok = false;
		for (int i = 0; i < v.size(); ++i) {
			ok |= test(v, i);
		}
		sum += int(ok);
	}
	std::cout << sum << std::endl;
	return 0;
}