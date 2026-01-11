#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using IdPair = std::pair<unsigned long long, unsigned long long>;
using VectorOfIdPairs = std::vector<IdPair>;

struct IdDataBaseV {
    VectorOfIdPairs idRanges;
    std::vector<unsigned long long> ingredients;
};

IdDataBaseV readFileV(const std::string& filename) {
    IdDataBaseV db;

    auto inputVec = std::vector<std::string>();
    auto line = std::string();
    auto in = std::ifstream(filename.c_str());
    while (in.good() && !in.eof()) {
        std::getline(in, line);
        inputVec.push_back(line);
    }

    auto it = std::find(std::begin(inputVec), std::end(inputVec), "");
    if (it != std::end(inputVec)) {
        const size_t ingredientCount = std::distance(it + 1, std::end(inputVec));
        const size_t idCount = std::distance(std::begin(inputVec), it);

        db.ingredients = std::vector<unsigned long long>(ingredientCount, 0);
        db.idRanges = VectorOfIdPairs(idCount, IdPair());

        std::transform(it + 1, std::end(inputVec), std::begin(db.ingredients), 
            [](auto& elem) { return std::stoull(elem); });

        auto toIdRange = [](auto& elem) {
            auto pos = elem.find('-');
            auto lb = std::stoull(elem.substr(0, pos));
            auto ub = std::stoull(elem.substr(pos + 1, elem.size() - pos + 1));

            return IdPair( lb, ub );
        };

        std::transform(std::begin(inputVec), it, std::begin(db.idRanges), toIdRange);
    }

    return db;
}

unsigned long long solution1(const IdDataBaseV& db) {
    auto freshCount = 0ULL;
    for (auto& ingredient : db.ingredients) {
        for (auto& range : db.idRanges) {
            if (ingredient >= range.first and ingredient <= range.second) {
                freshCount++;
                break;
            }
        }
    }
    return freshCount;
}

unsigned long long solution2(const VectorOfIdPairs& pairs) {
    auto capacityVec = std::vector<unsigned long long>();
    //capacityVec.resize(pairs.size());
    for (auto& x : pairs) {
        capacityVec.push_back(x.first);
        std::cout << x.first << std::endl;
    }


    //for (auto& p : pairs) {
    //    std::cout << p.first << " - " << p.second << std::endl;
    //}
    const auto max_capacity = std::min_element(std::begin(capacityVec), end(capacityVec));
    std::cout << *max_capacity << std::endl;

    std::vector<unsigned> f(56081312757, 0);
    return 0;
}

int main()
{
    auto id_db = readFileV("input.txt");
    std::cout << "SOLUTION1: " << solution1(id_db) << std::endl;
    std::cout << solution2(id_db.idRanges) << std::endl;
}
