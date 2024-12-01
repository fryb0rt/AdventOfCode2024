#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream stream("..\\input1.txt");
    std::string line;
    std::vector<int> data1, data2;
    int pos = 0;
    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        int num1, num2;
        iss >> num1 >> num2;
        data1.push_back(num1);
        data2.push_back(num2);
        ++pos;
    }
    std::sort(data1.begin(), data1.end());
    std::sort(data2.begin(), data2.end());
    int sum = 0;
    for (int i = 0; i < data1.size(); ++i) {
        sum += abs(data1[i] - data2[i]);
    }
    std::cout << sum << std::endl;
    return 0;
}