#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

struct Node {
	std::string name;
	int value;
};

struct Conn {
	std::string n1,n2,o;
	std::string operation;
	int in1, in2, io;
	bool done = false;
};
int main()
{
	std::ifstream stream("..\\input24.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::vector<int>> map;
	int maxX = 71, maxY = 71;
	std::vector<Node> nodes;
	std::vector<int> zs;
	while (std::getline(stream, line) && !line.empty()) {
		std::istringstream iss(line);
		Node n;
		iss >> n.name;
		n.name = n.name.substr(0, n.name.size() - 1);
		iss >> n.value;
		nodes.push_back(n);
	}
	int undetereminted = 0;
	const auto addNode = [&](const std::string name) {
		for (int i = 0; i < nodes.size(); ++i) {
			if (nodes[i].name == name) {
				return i;
			}
		}
		++undetereminted;
		nodes.push_back(Node{ name, -1 });
		return int(nodes.size() - 1);
	};
	
	std::vector<Conn> conns;
	while (std::getline(stream, line) && !line.empty()) {
		std::istringstream iss(line);
		Conn c;
		iss >> c.n1;
		iss >> c.operation;
		iss >> c.n2;
		std::string tmp;
		iss >> tmp;
		iss >> c.o;
		c.in1 = addNode(c.n1);
		c.in2 = addNode(c.n2);
		c.io = addNode(c.o);
		conns.push_back(c);
	}
	int maxZ = 0;
	for (int i = 0; i < nodes.size(); ++i) {
		if (nodes[i].name[0] == 'z') {
			std::istringstream iss(nodes[i].name.substr(1));
			int num;
			iss >> num;
			maxZ = std::max(num, maxZ);
		}
	}
	zs.resize(maxZ + 1);
	for (int i = 0; i < nodes.size(); ++i) {
		if (nodes[i].name[0] == 'z') {
			std::istringstream iss(nodes[i].name.substr(1));
			int num;
			iss >> num;
			zs[num] = i;
		}
	}
	while (undetereminted > 0) {
		for (auto& c : conns) {
			if (nodes[c.in1].value != -1 && nodes[c.in2].value != -1 && nodes[c.io].value == -1) {
				if (c.operation == "AND") {
					nodes[c.io].value = nodes[c.in1].value & nodes[c.in2].value;
				}
				else if (c.operation == "OR") {
					nodes[c.io].value = nodes[c.in1].value | nodes[c.in2].value;
				}
				else if (c.operation == "XOR") {
					nodes[c.io].value = nodes[c.in1].value ^ nodes[c.in2].value;
				}
				--undetereminted;
			}
		}
	}
	for (Node& n : nodes) {
		std::cout << n.name << " = " << n.value << std::endl;
	}
	int64_t value = 0;
	for (int i = zs.size() - 1; i >= 0; --i) {
		value = value * 2 + nodes[zs[i]].value;
	}
	std::cout << value << std::endl;
	return 0;
}
