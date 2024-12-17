#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

int main()
{
	std::ifstream stream("..\\input17.txt");
	int64_t sum = 0;
	int A = 41644071;
	int B = 0;
	int C = 0;
	std::string program = "2412751744035530";

	int pointer = 0;

	const auto operand = [&](int n) {
		if (n <= 3) {
			return n;
		}
		if (n == 4) {
			return A;
		}
		if (n == 5) {
			return B;
		}
		if (n == 6) {
			return C;
		}
		return -1;
	};

	const auto code0 = [&](int c) {
		A = A >> operand(c);
		pointer += 2;
	};

	const auto code1 = [&](int l) {
		B = B ^ l;
		pointer += 2;
	};

	const auto code2 = [&](int c) {
		B = operand(c) % 8;
		pointer += 2;
	};

	const auto code3 = [&](int l) {
		if (A == 0) {
			pointer += 2;
		}
		else {
			pointer = l;
		}
	};

	const auto code4 = [&](int l) {
		B = B ^ C;
		pointer += 2;
	};

	const auto code5 = [&](int c) {
		int o = operand(c) % 8;
		std::ostringstream s;
		s << o;
		auto ss = s.str();
		for (int i = ss.size() - 1; i >= 0; --i) {
			std::cout << ss[i] << ",";
		}
		B = B ^ C;
		pointer += 2;
	};

	const auto code6 = [&](int c) {
		B = A >> operand(c);
		pointer += 2;
	};

	const auto code7 = [&](int c) {
		C = A >> operand(c);
		pointer += 2;
	};

	while (pointer < program.size()) {
		int opcode = program[pointer] - '0';
		int operand = program[pointer + 1] - '0';
		switch (opcode) {
		case 0:code0(operand); break;
		case 1:code1(operand); break;
		case 2:code2(operand); break;
		case 3:code3(operand); break;
		case 4:code4(operand); break;
		case 5:code5(operand); break;
		case 6:code6(operand); break;
		case 7:code7(operand); break;
		}
	}
	return 0;
}
