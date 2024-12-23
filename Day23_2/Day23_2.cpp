#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

struct Node
{
	std::string name;
	std::vector<int> connections;
};

int main()
{
	std::ifstream stream("..\\input23.txt");
	std::string line;
	std::vector<Node> nodes;
	while (std::getline(stream, line)) {
		std::string n1 = line.substr(0, 2);
		std::string n2 = line.substr(3, 2);
		int i1 = -1, i2 = -1;
		for (int i = 0; i < nodes.size(); ++i) {
			if (nodes[i].name == n1) {
				i1 = i;
			}
			if (nodes[i].name == n2) {
				i2 = i;
			}
		}
		if (i1 == -1) {
			nodes.push_back(Node{ n1 });
			i1 = nodes.size() - 1;
		}
		if (i2 == -1) {
			nodes.push_back(Node{ n2 });
			i2 = nodes.size() - 1;
		}
		nodes[i1].connections.push_back(i2);
		nodes[i2].connections.push_back(i1);
	}
	std::set<std::set<int>> nodesSet, newNodesSet;
	// Initial
	for (int i = 0; i < nodes.size(); ++i) {
		for (int j = 0; j < nodes[i].connections.size(); ++j) {
			int nodeJ = nodes[i].connections[j];
			if (nodeJ > i) {
				newNodesSet.insert({ nodeJ, i });
			}
		}
	}
	int i = 0;
	while (!newNodesSet.empty()) {
		nodesSet.clear();
		for (auto& n : newNodesSet) {
			for (int j = 0; j < nodes[*n.begin()].connections.size(); ++j) {
				int nodeJ = nodes[*n.begin()].connections[j];
				int contains = 0;
				for (auto& n2 : n) {
					if (nodeJ == n2) {
						break;
					}
					for (auto nodeK : nodes[n2].connections) {
						if (nodeK == nodeJ) {
							++contains;
							break;
						}
					}
				}
				if (contains == n.size()) {
					auto nn = n;
					nn.insert(nodeJ);
					nodesSet.insert(nn);
				}

			}
		}
		++i;
		std::cout << i << " " << nodesSet.size() << std::endl;
		std::swap(nodesSet, newNodesSet);
	}
	std::vector<std::string> names;
	for (auto& i : *nodesSet.begin())
	{
		names.push_back(nodes[i].name);
	}
	std::sort(names.begin(), names.end());
	for (int i = 0; i < names.size(); ++i) {
		std::cout << names[i] << ",";
	}
	std::cout << std::endl;
	return 0;
}
