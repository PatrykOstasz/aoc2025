#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

constexpr unsigned MAX_TP_AROUND = 4;

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

// for debugging etc
void printVector(const std::vector<std::string>& input) {
	for (auto& x : input) std::cout << x << std::endl;
}

bool checkDirection(const std::vector<std::string>& input, int row, int col) {
	unsigned rowIndex = input.size()-1;
	unsigned colIndex = input[row].size()-1;
	if (row < 0 or row > rowIndex) return false;
	if (col < 0 or col > colIndex) return false;

	if (input[row][col] == '@') return true;

	return false;
}

int main()
{
	auto tps = readFile("input.txt");

	unsigned removedRolls = 0;
	while (true) {
		unsigned tpsCount = 0;
		std::vector<std::pair<unsigned, unsigned>> locations;

		for (int row = 0; row < tps.size(); ++row) {
			for (int col = 0; col < tps[row].size(); ++col) {
				unsigned surroundingCount = 0;
				if (tps[row][col] == '.') continue;

				if (checkDirection(tps, row - 1, col)) surroundingCount++;
				if (checkDirection(tps, row - 1, col + 1)) surroundingCount++;
				if (checkDirection(tps, row, col + 1)) surroundingCount++;
				if (checkDirection(tps, row + 1, col + 1)) surroundingCount++;
				if (checkDirection(tps, row + 1, col)) surroundingCount++;
				if (checkDirection(tps, row + 1, col - 1)) surroundingCount++;
				if (checkDirection(tps, row, col - 1)) surroundingCount++;
				if (checkDirection(tps, row - 1, col - 1)) surroundingCount++;

				if (surroundingCount < MAX_TP_AROUND) {
					tpsCount++;
					locations.push_back(std::make_pair(row, col));
				}
			}
		}

		// only first iteration is correct answer
		std::cout << "SOLUTUION1: " << tpsCount << std::endl;


		removedRolls += tpsCount;
		for (auto& loc : locations) {
			tps[loc.first][loc.second] = '.';
		}
		if (tpsCount == 0) break;
	}

	std::cout << "SOLUTUION2: " << removedRolls << std::endl;

}

