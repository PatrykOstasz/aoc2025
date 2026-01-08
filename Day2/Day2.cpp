#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <numeric>
#include <utility>
#include <unordered_map>
#include <set>
/***
* Możnaby przepisać na pracę na liczbach
* byłoby to szybsze niż kilka konwersji + praca na stringach
***/
std::vector<std::string> readFile(const std::string& filename) {
	auto inputVec = std::vector<std::string>();
	auto line = std::string();
	auto in = std::ifstream(filename.c_str());
	while (in.good() && !in.eof()) {
		std::getline(in, line, ',');
		inputVec.push_back(line);
	}
	return inputVec;
}

unsigned long long findWrongIDs1(const std::vector<std::string>& ranges) {
	unsigned long long count = 0;
	for (auto& range : ranges) {
		auto delimPos = range.find('-');
		unsigned long long lowerBound = std::stoull(range.substr(0, delimPos));
		unsigned long long upperBound = std::stoull(range.substr(delimPos + 1, range.size() - delimPos + 1));

		for (auto i = lowerBound; i <= upperBound; ++i) {
			auto num = std::to_string(i);
			if (num.size() % 2 == 1) continue;

			auto str1 = num.substr(0, num.size() / 2);
			auto str2 = num.substr(num.size() / 2, str1.size());

			if (str1 == str2) {
				count += std::stoull(str1 + str2);
			}
		}
	}
	return count;
}

unsigned long long findWrongIDs2(const std::vector<std::string>& ranges) {
	auto bounds = std::vector<std::pair<unsigned long long, unsigned long long>>();
	for (auto& range : ranges) {
		auto delimPos = range.find('-');
		auto lowerBound = std::stoull(range.substr(0, delimPos));
		auto upperBound = std::stoull(range.substr(delimPos + 1, range.size() - delimPos + 1));

		bounds.emplace_back(std::make_pair(lowerBound, upperBound));
	}

	std::unordered_map<unsigned, std::set<unsigned>> denominators;
	for (auto& b : bounds) {
		for (auto i = b.first; i <= b.second; ++i) {
			auto num = std::to_string(i);

			// find all common denominators
			for (int i = 1; i <= num.size(); ++i) {
				if (num.size() % i == 0 and i != 1) {
					auto& dens = denominators[num.size()];
					dens.insert(i);
				}
			}
		}
	}

	std::vector<unsigned long long> fakeIds;
	for (auto& b : bounds) {
		for (auto i = b.first; i <= b.second; ++i) {
			auto num = std::to_string(i);
			auto& dens = denominators[num.size()];
			for (auto& den : dens) {
				unsigned numberCount = num.size() / den;
				unsigned comparisonCounter = 1;

				for (auto i = 0; i < num.size() - 1; i += numberCount) {
					auto str1 = num.substr(i, numberCount);
					auto str2 = num.substr(i + numberCount, numberCount);

					if (str1 != str2) break;
					if (str1 == str2) comparisonCounter++;
				}

				if (comparisonCounter == den) {
					fakeIds.push_back(std::stoull(num));
				}
			}
		}
	}

	std::sort(std::begin(fakeIds), std::end(fakeIds));
	auto ptr = std::unique(std::begin(fakeIds), std::end(fakeIds));
	fakeIds.erase(ptr, fakeIds.end());
	return std::accumulate(std::begin(fakeIds), std::end(fakeIds), 0ULL);

}

int main()
{
	auto ranges = readFile("input.txt");
	auto solution1 = findWrongIDs1(ranges);
	auto solution2 = findWrongIDs2(ranges);


	std::cout << "SOLUTION1 = " << solution1 << std::endl;
	std::cout << "SOLUTION2 = " << solution2 << std::endl;
}

