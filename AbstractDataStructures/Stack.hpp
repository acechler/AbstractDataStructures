#ifndef STACK_HPP
#define STACK_HPP

#include "IStack.h"
#include <stdexcept>

template <typename T>
class Stack : public IStack<T> {
private:
	T* dataPtr;
	int currentSize;
	int capacity;

	void resize() {
		// If the capacity is 0 then increment it by one, otherwise double the capacity.
		// This allows us to add new data on top of the stack without going out of bounds in memory
		//
		// Let's say we have 2 ints in our stack
		// [0],[1]
		//  4 + 4 = 8 Bytes
		// If we need to add a new int to the stack we double the capacity to 16 bytes
		// [0],[1],[2]
		//  4 + 4 + 4 = 12 bytes
		//  We now have a 4 byte buffer between the last item of the stack and going out of bounds.
		capacity = (capacity == 0) ? 1 : capacity * 2;

		// Allocate the new buffer.
		T* newDataPtr = new T[capacity];

		try {
			// Attempt to copy existing elements to the new buffer.
			for (int i = 0; i < currentSize; ++i) {
				newDataPtr[i] = dataPtr[i];
			}
		}
		catch (...) {
			// If an exception occurs, clean up the new buffer and rethrow the exception.
			delete[] newDataPtr;
			throw;
		}

		// Deallocate the old buffer and reassign.
		delete[] dataPtr;
		dataPtr = newDataPtr;
	}

public:
	Stack() : dataPtr(nullptr), currentSize(0), capacity(0) {}

	~Stack() {
		delete[] dataPtr;
		dataPtr = nullptr;
	}

	bool push(const T& item) override {
		if (currentSize == capacity) {
			resize();
		}
		dataPtr[currentSize++] = item;
		return true;
	}

	T* pop() override {
		if (currentSize == 0) {
			throw std::out_of_range("Stack is empty");
		}
		return &dataPtr[--currentSize];
	}

	void empty() override {
		currentSize = 0;
	}

	T* peek() override {
		if (currentSize == 0) {
			throw std::out_of_range("Stack is empty");
		}
		return &dataPtr[currentSize - 1];
	}
};

#endif // !STACK_HPP