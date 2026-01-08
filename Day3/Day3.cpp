#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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

unsigned joltage_2(std::vector<unsigned>& bank) {
	auto maxIt = std::max_element(std::begin(bank), std::end(bank));
	unsigned joltage1 = *maxIt;
	unsigned idx_of_joltage1 = std::distance(std::begin(bank), maxIt);

	unsigned joltage2 = 0, idx_of_joltage2 = 0;
	if (idx_of_joltage1 == bank.size() - 1) {
		maxIt = std::max_element(std::begin(bank), maxIt);
	}
	else {
		maxIt = std::max_element(maxIt + 1, std::end(bank));
	}

	joltage2 = *maxIt;
	idx_of_joltage2 = std::distance(std::begin(bank), maxIt);

	std::string joltage = "";
	if (idx_of_joltage1 > idx_of_joltage2) {
		joltage = std::to_string(joltage2) + std::to_string(joltage1);
	}
	else {
		joltage = std::to_string(joltage1) + std::to_string(joltage2);
	}

	return std::stoi(joltage);
}

unsigned joltage_12(std::vector<unsigned>& bank) {
	const size_t SIZE_OF_BANK = bank.size();
	std::vector<unsigned> result(SIZE_OF_BANK, 0);

	auto maxIt = std::max_element(std::begin(bank), std::end(bank));

	unsigned joltage = *maxIt;
	unsigned idx_of_joltage = std::distance(std::begin(bank), maxIt);

	result[idx_of_joltage] = joltage;

	const unsigned NUM_OF_BATTERIES = 12;
	static auto end = std::end(bank);
	for (auto i = 1; i < NUM_OF_BATTERIES; ++i) {
		std::cout << "Jolt: " << joltage << ", index: " << idx_of_joltage << std::endl;
		if (idx_of_joltage == bank.size() - 1) {
			end = maxIt;
		}

		maxIt = std::max_element(std::begin(bank), end);
		unsigned joltage = *maxIt;
		unsigned idx_of_joltage = std::distance(std::begin(bank), maxIt);

	}
	std::cout << std::endl;

	return 0;
}

int main()
{
	unsigned max_joltage = 0;
	unsigned max_joltage12 = 0;
	auto bankLines = readFile("test_input.txt");

	for (auto& line : bankLines) {
		auto bank = convertToBatteryBank(line);

		max_joltage += joltage_2(bank);
		max_joltage12 += joltage_12(bank);
	}
	std::cout << max_joltage << std::endl;
	std::cout << max_joltage12 << std::endl;
}

