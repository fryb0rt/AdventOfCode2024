#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int64_t concat(int64_t a, int64_t b) {
	std::ostringstream s;
	s << a;
	s << b;
	std::istringstream i(s.str());
	int64_t res;
	i >> res;
	return res;
}

bool determine(std::vector<int64_t>& nums, int64_t index, int64_t value, int64_t target) {
	if (index == nums.size() - 1) {
		return value == target;
	}
	else {
		return determine(nums, index + 1, nums[index + 1] * value, target) ||
			determine(nums, index + 1, nums[index + 1] + value, target) || determine(nums, index + 1, concat(value, nums[index + 1]), target);
	}
}

int main()
{
	std::ifstream stream("..\\input7.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> lines;

	int i = 0;
	while (std::getline(stream, line) && !line.empty()) {
		std::cout << i << std::endl;
		++i;
		std::istringstream iss(line);
		int64_t num;
		char c;
		std::vector<int64_t> nums;
		iss >> num;
		iss >> c;
		int64_t target = num;
		while (!iss.eof()) {
			iss >> num;
			nums.push_back(num);
		}
		if (determine(nums, 0, nums[0], target)) {
			sum += target;
		}

	}
	std::cout << sum << std::endl;
	return 0;
}
