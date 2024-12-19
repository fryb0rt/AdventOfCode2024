#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

std::map<std::string,bool> set;

bool possible(std::string rug, std::vector<std::string>& patterns) {
	if (rug.empty()) {
		return true;
	}
	auto it = set.find(rug);
	if (it != set.end()) {
		return it->second;
	}
	for(int i = 0; i < patterns.size(); ++i) {
		if (rug.substr(0, patterns[i].size()) == patterns[i]) {
			std::string partRug = rug.substr(patterns[i].size());
			if (possible(partRug, patterns)) {
				set.insert({ partRug, true });
				return true;
			}
			else {
				set.insert({ partRug, false });
			}
		}
	}
	return false;
}

int main()
{
	std::ifstream stream("..\\input19.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> patterns;
	std::vector<std::string> rugs;
	while (std::getline(stream, line) && !line.empty()) {
		std::istringstream iss(line);
		while (!iss.eof()) {
			std::string s;
			iss >> s;
			if (s[s.size() - 1] == ',') {
				s.erase(s.size() - 1);
			}
			patterns.push_back(s);
		}
	}
	while (std::getline(stream, line) && !line.empty()) {
		rugs.push_back(line);
	}
	
	for (auto r : rugs) {
		sum += possible(r, patterns);
	}
	std::cout << sum;
	return 0;
}
