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
	int sum = 0;
	std::vector<Node> nodes;
	while (std::getline(stream, line)) {
		std::string n1 = line.substr(0, 2);
		std::string n2 = line.substr(3, 2);
		int i1 = -1, i2 = - 1;
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
	for (int i = 0; i < nodes.size(); ++i) {
		for (int k = 0; k < nodes[i].connections.size(); ++k) {
			int nodeK = nodes[i].connections[k];
			for (int j = 0; j < nodes[i].connections.size(); ++j) {
				int nodeJ = nodes[i].connections[j];
				if ((nodes[nodeK].name[0] == 't' || nodes[i].name[0] == 't' || nodes[nodeJ].name[0] == 't') && 
					i < nodeK && nodeK < nodeJ) {
					for (int l = 0; l < nodes[nodeK].connections.size(); ++l) {
						if (nodes[nodeK].connections[l] == nodeJ) {
							++sum;
							std::cout << nodes[i].name << " " << nodes[nodeK].name << " " << nodes[nodeJ].name << std::endl;
							break;
						}
					}
				}
				
			}
		}
	}
	std::cout << sum << std::endl;
	return 0;
}
