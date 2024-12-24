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
	int expected;
};

struct Conn {
	std::string n1, n2, o;
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
	int maxZ = 0;
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
		if (c.o[0] == 'z') {
			++maxZ;
		}
	}
	const auto find = [&](const std::string& n1, const std::string& n2, const std::string& op) {
		for (auto& c : conns) {
			if (((c.n1 == n1 && c.n2 == n2) || (c.n1 == n2 && c.n2 == n1)) && c.operation == op) {
				return c;
			}
		}
		return Conn{};
	};
	const auto num = [&](const int i) {
		std::string res;
		if (i < 10) {
			res = "0";
			res += (char(i) + '0');
		}
		else {
			res = (char(i / 10) + '0');
			res += (char(i % 10) + '0');
		}
		return res;
	};
	bool correct = false;
	std::vector<std::string> wrong;
	const auto swap = [&](const std::string& o1, const std::string& o2) {
		for (auto& c : conns) {
			if (c.o == o1) {
				c.o = o2;
			}
			else if (c.o == o2) {
				c.o = o1;
			}
		}
		wrong.push_back(o1);
		wrong.push_back(o2);
		correct = false;
	};
	const auto missingConn = [&](const std::string& n1, const std::string& n2, const std::string& o) {
		for (Conn& c : conns) {
			if (c.o == o) {
				if (c.n1 == n1 || c.n2 == n1) {
					swap(n2, n1 == c.n1 ? c.n2 : c.n1);
				}
				else {
					swap(n1, n2 == c.n1 ? c.n2 : c.n1);
				}
				break;
			}
		}
	};
	while (!correct) {
		correct = true;
		std::string lastCout = "";
		for (int i = 0; i < maxZ - 1; ++i) {
			std::string n = num(i);
			auto x = find("x" + n, "y" + n, "XOR"); // XOR result
			auto a = find("x" + n, "y" + n, "AND"); // AND result
			if (i == 0) {
				if (x.o != "z" + n) {
					swap(x.o, "z" + n);
					break;
				}
				lastCout = a.o;
			}
			else {
				auto x2 = find(x.o, lastCout, "XOR"); // XOR result
				if (x2.n1 == "") {
					missingConn(x.o, lastCout, "z" + n);
					break;
				}
				if (x2.o != "z" + n) {
					swap(x2.o, "z" + n);
					break;
				}
				auto a2 = find(x.o, lastCout, "AND"); // AND result
				if (a2.n1 == "") {
					// Should never happen
					std::cout << "ERROR" << std::endl;
					break;
				}
				auto o = find(a2.o, a.o, "OR"); // OR result
				lastCout = o.o;
				if (o.n1 == "") {
					// Either a2 is wrong or a.o is wrong
					for (Conn& c : conns) {
						if ((c.n1 == a.o || c.n2 == a.o) && c.operation == "OR") {
							// A2 is wrong
							swap(a2.o, c.n1 == a.o ? c.n2 : c.n1);
							break;
						}
						if ((c.n1 == a2.o || c.n2 == a2.o) && c.operation == "OR") {
							// A2 is wrong
							swap(a.o, c.n1 == a2.o ? c.n2 : c.n1);
							break;
						}
					}
					// Should never happen
					std::cout << "ERROR" << std::endl;
					break;
				}
			}
		}
	}
	std::sort(wrong.begin(), wrong.end());
	for (auto& w : wrong) {
		std::cout << w << ",";
	}
	return 0;
}
