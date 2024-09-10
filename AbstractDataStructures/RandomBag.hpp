#ifndef RANDOM_BAG_HPP
#define RANDOM_BAG_HPP

#include <random>
#include "Bag.hpp"

class RandomBag : public Bag<int>
{
public:
    RandomBag(int maxSize) : Bag<int>(maxSize), rng(std::random_device{}()), dist(0, 5) {
        // Any additional initialization for RandomBag can go here
   
    }

    void setRNG(int min = 0, int max = 5) {
        dist = std::uniform_int_distribution<int>(min, max);
    }


    

    int getRandomElement() {
        if (currentSize == 0) {
            throw std::runtime_error("Bag is empty");
        }
        int randomIndex = dist(rng) % currentSize;
        return dataPtr[randomIndex];
    }

    void fillBag() {
        clear(); // Ensure the bag is empty before filling
        while (currentSize < max) {
            int randomValue = dist(rng);
            add(randomValue);
        }
    }


    

private:
    std::mt19937 rng; // Mersenne Twister random number generator
    std::uniform_int_distribution<int> dist; // Uniform distribution for integers

};


#endif // !RANDOM_BAG_HPP
