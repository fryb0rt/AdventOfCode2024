#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

struct AV {
	std::vector<int> binary;
	int pointer = 0;

	AV() {
		binary.resize(256, -1);
	}

	bool isZero() const {
		for (int b : binary) {
			if (b == 1) {
				return false;
			}
		}
		return true;
	}

	void shift(int value) {
		pointer += value;
	}

	void getAs(int pos, int count, std::vector<AV>& out) {
		if (count == 0) {
			out.push_back(*this);
			return;
		}
		if (binary[pos + pointer] == -1) {
			AV a0 = *this, a1 = *this;
			a0.binary[pos + pointer] = 0;
			a1.binary[pos + pointer] = 1;
			a0.getAs(pos + 1, count - 1, out);
			a1.getAs(pos + 1, count - 1, out);
		}
		else {
			getAs(pos + 1, count - 1, out);
		}
	}

	int64_t get(int shift) const {
		return get(shift, pointer, 3);
	}

	int64_t getAll() const {
		return get(0, 0, binary.size());
	}

	int64_t get(int shift, int pt, int cnt) const {
		int64_t value = 0, power = 1;
		for (int i = 0; i < cnt; ++i) {
			if (binary[i + shift + pt] == -1) {
				break;
			}
			value += power * binary[i + shift + pt];
			power *= 2;
		}
		return value;
	}
};

struct Elem {
	AV A;
	int64_t B = 0;
	int64_t C = 0;
	int64_t pointer = 0;
	int64_t output = 0;
};

class Program {
public:

	void handle(const std::string& program) {
		std::vector<Elem> stack;
		stack.push_back(Elem{});
		int64_t minValue = -1;
		while (!stack.empty()) {
			Elem elem = stack.back();
			stack.pop_back();
			elem.pointer += 1;
			std::vector<AV> As;
			switch (elem.pointer - 1) {
			case 0:
				elem.A.getAs(0, 3, As);
				for (const AV& a : As) {
					elem.A = a;
					elem.B = a.get(0);
					stack.push_back(elem);
				}
				break;
			case 1:
				elem.B = elem.B ^ 2;
				stack.push_back(elem);
				break;
			case 2:
				elem.A.getAs(elem.B, 3, As);
				for (const AV& a : As) {
					elem.A = a;
					elem.C = a.get(elem.B);
					stack.push_back(elem);
				}
				break;
			case 3:
				elem.B = elem.B ^ 7;
				stack.push_back(elem);
				break;
			case 4:
				elem.B = elem.B ^ elem.C;
				stack.push_back(elem);
				break;
			case 5:
				elem.A.shift(3);
				stack.push_back(elem);
				break;
			case 6:
				if (elem.B % 8 + '0' == program[elem.output]) {
					++elem.output;
					if (elem.output == program.size()) {
						int64_t value = elem.A.getAll();
						if (minValue == -1 || minValue > value) {
							minValue = value;
						}
					}
					else {
						stack.push_back(elem);
					}
				}
				break;
			case 7:
				elem.pointer = 0;
				stack.push_back(elem);
				break;
			}
		}
		std::cout << minValue << std::endl;
	}
};

int main()
{
	std::ifstream stream("..\\input17.txt");
	std::string program = "2412751744035530";
	Program p;
	p.handle(program);
	return 0;
}
