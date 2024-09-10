#ifndef BAG_H
#define BAG_H

#include "IBag.h"
#include <vector>

template <typename T>
class Bag : public IBag<T> {
protected:


    T* dataPtr;
    int max;
    int currentSize;


public:

    Bag(int maxSize) : max(maxSize), currentSize(0) {
        dataPtr = new T[max];
    }

    ~Bag() {
        delete[] dataPtr;  // Release the memory - Mr. Burns probably
        dataPtr = nullptr; // prevent dangling pointer
    };

    int getCurrentSize() const override {
        return this->currentSize;
    }

    bool isEmpty() const override {
        return this->currentSize == 0;
    }
    bool add(const T& newEntry) override {
        if (this->currentSize < max) {
            dataPtr[currentSize++] = newEntry;
            return true;
        }
        return false;
    }

    bool remove(const T& targetEntry) override {
        for (int i = 0; i < currentSize; ++i) {
            if (dataPtr[i] == targetEntry) {
                for (int j = i; j < currentSize - 1; ++j) {
                    dataPtr[j] = dataPtr[j + 1];
                }
                --currentSize;
                return true;
            }
        }
        return false;
    }
    void clear() override {
        currentSize = 0;
    }

    int getFrequencyOf(const T& entry) const override {
        int frequency = 0;
        for (int i = 0; i < currentSize; ++i) {
            if (dataPtr[i] == entry) {
                ++frequency;
            }
        }
        return frequency;
    }
    bool contains(const T& targetEntry) const override {
        for (int i = 0; i < currentSize; ++i) {
            if (dataPtr[i] == targetEntry) {
                return true;
            }
        }
        return false;
    }



    friend std::ostream& operator<<(std::ostream& os, const Bag<T>& bag) {
        os << "Bag contents: ";
        for (int i = 0; i < bag.currentSize; ++i) {
            os << bag.dataPtr[i] << " ";
        }
        return os;
    }

    // Return a new Bag with no duplicates
    Bag<T> getBagWithoutDuplicates() const {
        Bag<T> uniqueBag(max);
        for (int i = 0; i < currentSize; ++i) {
            if (!uniqueBag.contains(dataPtr[i])) {
                uniqueBag.add(dataPtr[i]);
            }
        }
        return uniqueBag;
    }

    // Return a vector containing the bag contents
    std::vector<T> toVector() const {
        std::vector<T> vec;
        for (int i = 0; i < currentSize; ++i) {
            vec.push_back(dataPtr[i]);
        }
        return vec;
    }

};

#endif // !BAG_HPP