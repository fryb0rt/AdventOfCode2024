#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

struct s {
	int seq[4];
	bool operator<(const s& other) const {
		return seq[0] < other.seq[0] || (seq[0] == other.seq[0] && (seq[1] < other.seq[1] || seq[1] == other.seq[1] && (seq[2] < other.seq[2] || seq[2] == other.seq[2] && (seq[3] < other.seq[3]))));
	}
};
int main()
{
	std::ifstream stream("..\\input22.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::vector<int>> changes;
	std::vector<std::vector<int>> values;
	while (std::getline(stream, line)) {
		std::istringstream iss(line);
		int64_t value;
		iss >> value;
		changes.push_back(std::vector<int>{});
		values.push_back(std::vector<int>{});
		for (int i = 0; i < 2000; ++i) {
			int64_t prev = value;
			value = (value ^ (value * 64)) % 16777216;
			value = (value ^ (value / 32)) % 16777216;
			value = (value ^ (value * 2048)) % 16777216;
			changes.back().push_back(value % 10 - prev % 10);
			values.back().push_back(value % 10);
		}
	}
	std::set<s> sequences;
	for (int k = 0; k < changes.size(); ++k) {
		auto& v = changes[k];
		for (int i = 0; i < v.size() - 3; ++i) {
			s t;
			for (int j = 0; j < 4; ++j) {
				t.seq[j] = v[i + j];
			}
			sequences.insert(t);
		}
	}

	std::cout << sequences.size() << std::endl;
	std::vector<s> seqVector;
	for (auto& s : sequences) {
		seqVector.push_back(s);
	}
	std::vector<int64_t> sums(seqVector.size(), 0);
#pragma omp parallel for num_threads(16)
	for (int j = 0; j < seqVector.size();++j) {
		const auto & seq = seqVector[j].seq;
		int64_t sumCurr = 0;
		for (int k = 0; k < changes.size(); ++k) {
			auto& v = changes[k];
			for (int i = 0; i < v.size() - 3; ++i) {
				bool found = true;
				for (int j = 0; j < 4; ++j) {
					if (v[i + j] != seq[j]) {
						found = false;
						break;
					}
				}
				if (found) {
					sumCurr += values[k][i + 3];
					break;
				}
			}
		}
		sums[j] = sumCurr;
	}
	for (auto& i : sums) {
		sum = std::max(i, sum);
	}
	std::cout << sum << std::endl;
	return 0;
}
