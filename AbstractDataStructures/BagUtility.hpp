

#ifndef BAG_UTILITY_HPP
#define BAG_UTILITY_HPP

#include <random>
#include "Bag.hpp"

class BagUtility {
public:
    static Bag<int> generateRandomBag(int bagSize, int minValue = 0, int maxValue = 5) {
        Bag<int> randomBag(bagSize);
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(minValue, maxValue);

        while (randomBag.getCurrentSize() < bagSize) {
            int randomValue = dist(rng);
            randomBag.add(randomValue);
        }

        return randomBag;
    }
};

#endif // BAG_UTILITY_HPP