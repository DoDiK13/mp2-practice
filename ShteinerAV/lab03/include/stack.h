#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>

const int MAX_SIZE = 100000000;

template <typename T>
class TStack {
private:
	size_t memSize;
	int topInd;
	T* pMem;
public:
	TStack(size_t size = 1) : memSize(size) {
		if (memSize > MAX_SIZE || memSize <= 0) {
			throw std::out_of_range("...");
		}
		topInd = -1;
		pMem = new T[memSize]();
	};
	TStack(const TStack<T>& temp) : memSize(temp.memSize), topInd(temp.topInd) {

		T* newMem = new T[memSize]();
		try {
			std::copy(temp.pMem, temp.pMem + memSize, newMem);
		}
		catch (...) {
			delete[] newMem;
			throw;
		}

		pMem = newMem;
	};
	TStack(TStack<T>&& temp) : memSize(temp.memSize), topInd(temp.topInd), pMem(temp.pMem) {
		temp.memSize = 0;
		temp.topInd = -1;
		temp.pMem = nullptr;
	}
	~TStack() {
		delete[] pMem;
	}

	const TStack<T>& operator = (const TStack<T>& temp) {
		if (this == &temp) { return *this; }
		if (memSize != temp.memSize) {
			memSize = temp.memSize;
		}

		T* newMem = new T[memSize]();
		try {
			std::copy(temp.pMem, temp.pMem + memSize, newMem);
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

	size_t size() { return topInd + 1; }
	bool isEmpty() const { return topInd == -1; }
	bool isFull() const { return topInd == memSize - 1; }
	T Top() { 
		if (isEmpty()) { throw std::out_of_range("..."); }
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
