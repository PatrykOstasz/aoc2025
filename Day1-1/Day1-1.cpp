#include <fstream>
#include <string>
#include <vector>
#include <iostream>


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

unsigned countZero(const std::vector<std::string>& combination, unsigned startCode = 50) {
	unsigned zeroCount = 0;
	int currentCode = startCode;
	for (auto& turn : combination) {
		unsigned turnDistance = std::stoi(turn.substr(1, turn.size() - 1));

		char direction = turn[0];
		int temp = currentCode;

		switch (direction) {
		case 'L':
			temp -= turnDistance;
			if (temp <= 0) {
				currentCode = 100 - std::abs(temp) % 100;
			}
			else {
				currentCode = temp;
			}
			break;
		case 'R':
			temp += turnDistance;
			if (temp >= 100) {
				currentCode = temp % 100;
			}
			else {
				currentCode = temp;
			}
			break;
		}

		if (currentCode == 0 or currentCode == 100) {
			currentCode = 0;
			zeroCount++;
		}
	}

	return zeroCount;
}

unsigned countClicks(const std::vector<std::string>& combination, unsigned startCode = 50) {
	unsigned clickCount = 0;
	int currentCode = startCode;
	std::cout << "START: " << currentCode << std::endl;
	for (auto& turn : combination) {
		unsigned turnDistance = std::stoi(turn.substr(1, turn.size() - 1));

		char direction = turn[0];
		int temp = currentCode;

		switch (direction) {
		case 'L':
			temp -= turnDistance;
			if (temp <= 0) {
				if (temp < -99 and currentCode == 0) clickCount += std::abs(temp) / 100;
				if (temp <= 0 and currentCode > 0) clickCount += std::abs(temp) / 100 + 1;
				currentCode = 100 - std::abs(temp) % 100;
			}
			else {
				currentCode = temp;
			}
			break;
		case 'R':
			temp += turnDistance;
			if (temp >= 100) {
				clickCount += std::abs(temp) / 100;
				currentCode = temp % 100;
			}
			else {
				currentCode = temp;
			}
			break;
		}
		
		if (currentCode == 100) currentCode = 0;
	}
	return clickCount;
}

int main() {
	int currentCode = 50;

	auto combination = readFile("input.txt");
	unsigned zeroCounter = countZero(combination);
	unsigned clickCounter = countClicks(combination);

	std::cout << "SOLUTION1 = " << zeroCounter << std::endl;
	std::cout << "SOLUTION2 = " << clickCounter << std::endl;
}

