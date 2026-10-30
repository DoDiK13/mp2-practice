#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>

const int MAX_SIZE = 100000000;

template <typename T>
class Stack {
private:
	size_t maxSize;
	int topInd;
	T* pMem;
public:
	Stack(size_t size = 1) : maxSize(size) {
		if (maxSize > MAX_SIZE) {
			throw std::out_of_range("...");
		}
		topInd = -1;
		pMem = new T[maxSize]();
	};
	Stack(const Stack<T>& temp) : maxSize(temp.maxSize), topInd(temp.topInd) {

		T* newMem = new T[maxSize]();
		try {
			std::copy(temp.pMem, temp.pMem + maxSize, newMem);
		}
		catch (...) {
			delete[] newMem;
			throw;
		}

		pMem = newMem;
	};
	Stack(Stack<T>&& temp) : maxSize(temp.maxSize), topInd(temp.topInd), pMem(temp.pMem) {
		temp.maxSize = 0;
		temp.topInd = -1;
		temp.pMem = nullptr;
	}
	~Stack() {
		delete[] pMem;
	}

	const Stack<T>& operator = (const Stack<T>& temp) {
		if (this == &temp) { return *this; }
		if (maxSize != temp.maxSize) {
			maxSize = temp.maxSize;
		}

		T* newMem = new T[maxSize]();
		try {
			std::copy(temp.pMem, temp.pMem + maxSize, newMem);
		}
		catch (...) {
			delete[] newMem;
			throw;
		}

		topInd = temp.topInd;
		delete[] pMem;
		pMem = newMem;

		return *this;
	}

	bool isEmpty() const { return topInd == -1; }
	bool isFull() const { return topInd == maxSize - 1; }
	T Top() { 
		if (isEmpty()) { throw("Стек пуст"); }
		return pMem[topInd];
	}
	void push(const T& elem) {
		if (isFull()) {
			throw std::out_of_range("...");
		}
		pMem[++topInd] = elem;
	}
	void pop() {
		if (isEmpty()) {
			throw std::out_of_range("...");
		}
		topInd--;
	}
};
