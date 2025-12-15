#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::string> readFile(const std::string& filename) {
	auto inputVec = std::vector<std::string>();
	auto line = std::string();
	auto in = std::ifstream(filename.c_str());
	while (in.good() && !in.eof()) {
		std::getline(in, line);
		inputVec.push_back(line);
	}
	return inputVec;
}

std::vector<unsigned> convertToBatteryBank(const std::string& line) {
	std::vector<unsigned> bank;
	for (auto& ch : line) {
		bank.push_back(ch - '0');
	}

	return bank;
}

int main()
{
	auto bankLines = readFile("input.txt");
	unsigned max_joltage = 0;
	for (auto& line : bankLines) {
		auto bank = convertToBatteryBank(line);

		auto it1 = std::max_element(std::begin(bank), std::end(bank));
		unsigned firstMax = *it1;
		unsigned index1 = std::distance(std::begin(bank), it1);

		unsigned secondMax = 0, index2 = 0;
		if (index1 == bank.size() - 1) {
			it1 = std::max_element(std::begin(bank), it1);
			secondMax = *it1;
			index2 = std::distance(std::begin(bank), it1);
		}
		else {
			it1 = std::max_element(it1 + 1, std::end(bank));
			secondMax = *it1;
			index2 = std::distance(std::begin(bank), it1);
		}

		std::string joltage = "";
		if (index1 > index2) {
			joltage = std::to_string(secondMax) + std::to_string(firstMax);
		}
		else {
			joltage = std::to_string(firstMax) + std::to_string(secondMax);
		}

		std::cout << joltage << std::endl;
		max_joltage += std::stoi(joltage);
	}
	std::cout << max_joltage << std::endl;
}

