#pragma once
#include <iostream>
#include <cmath>
#include <iomanip>
#include "Vector.h"
#define BAD_NUMBER -1.11
//#define true false

/* 
1) methods including T& at can't be const, operator [] is not safe;
2) only numeric types can be used as template's types.
*/

template <typename T>
class SquareMatrix {
public:

	SquareMatrix<T>(unsigned size = 0, T value = 0) : size(size) {

		size_t new_size = size * size;
		T* arr = new T[new_size];
		for (unsigned it = 0; it != new_size; ++it)
			arr[it] = value;

		this->array = arr;
	}

	SquareMatrix<T>(const SquareMatrix<T>& other) : size(other.size) {

		size_t new_size = size * size;
		T* new_arr = new T[new_size];
		for (unsigned it = 0; it != new_size; ++it)
			new_arr[it] = other.array[it];

		this->array = new_arr;
	}

	void swap(SquareMatrix<T>& other) {

		unsigned temp = this->size;
		this->size = other.size;
		other.size = temp;

		T* tempPtr = this->array;
		this->array = other.array;
		other.array = tempPtr;
	}

	void fillTheMatrix() {

		for (unsigned it = 0; it != size; ++it)
			for (unsigned j = 0; j != size; ++j)
				std::cin >> this->array[it * size + j];
	}

	void output() {
		
		for (unsigned it = 0; it != size; ++it) {
			for (unsigned j = 0; j != size; ++j)
				std::cout << this->at(it, j) << " ";
			std::cout << "\n";
		}
	}

	unsigned getSize() const {
		return this->size;
	}

	SquareMatrix<T>& operator=(const SquareMatrix<T>& other) {

		if (this != &other)
			SquareMatrix<T>(other).swap(*this);
		return *this;
	}

	T const* operator[](unsigned line) const {

		if (line > size - 1)
			return nullptr;
		return array + line * size;
	}

	T& at(unsigned line, unsigned colomn) {

		if (line > size - 1 || colomn > size - 1)
			return this->array[0];
		return array[line * size + colomn];
	}

	T at(unsigned line, unsigned colomn) const {

		if (line > size - 1 || colomn > size - 1)
			return static_cast<T>(BAD_NUMBER);
		return array[line * size + colomn];
	}

	bool checkSymmetry() {

		for (unsigned it = 0; it != size; ++it)
			for (unsigned j = 0; j < it; ++j)
				if (this->at(it, j) != this->at(j, it))
					return false;
		return true;
	}

	T* mulVector(T* vector) const {

		T* result = new T[this->size];
		for (unsigned it = 0; it != this->size; ++it)
			result[it] = 0;

		for (unsigned it = 0; it != this->size; it++) {
			for (unsigned j = 0; j != this->size; ++j)
				result[it] += array[it * this->size + j] * vector[j];
		}
		return result;
	}

	Vector<T>& mulVector(const Vector<T>& vector) const {

		Vector<T>* New = new Vector<T>(size, static_cast<T>(0));
		for (unsigned it = 0; it != size; ++it)
			for (unsigned j = 0; j != size; ++j)
				(*New)[it] += array[it * size + j] * vector.at(j);

		return *New;
	}

	~SquareMatrix<T>() {
		delete[] this->array;
	}

private:

	T* array;
	unsigned size;
};

template <typename T>
SquareMatrix<T>& makeSymmetryMatrix(unsigned size, T diagonal_value, T other_values) {

	SquareMatrix<T>* example = new SquareMatrix<T>(size);

	for (unsigned it = 0; it != size; ++it)
		for (unsigned j = 0; j < it; ++j) {
			example->at(it, j) = other_values;
			example->at(j, it) = other_values;
		}

	for (unsigned it = 0; it != size; ++it)
		example->at(it, it) = diagonal_value;

	return *example;
}

double _RoundTo(float value, int precision) {
	int mult = (int)pow(10, precision);
	return (floor(value * mult)) / mult;
}

double random(int precision) {
	float m = (rand() % RAND_MAX) / 3276.8;
	return _RoundTo(m, precision);
}

template <typename T>
SquareMatrix<T>& makeRandomSymmetryMatrix(unsigned size) {

	SquareMatrix<T>* example = new SquareMatrix<T>(size);
	for (unsigned it = 0; it != size; ++it)
		for (unsigned j = 0; j < it; ++j) {
			example->at(j, it) = example->at(it, j) = static_cast<T>(random(6));
		}

	for (unsigned it = 0; it != size; ++it)
		example->at(it, it) = static_cast<T>(random(7));

	return *example;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const SquareMatrix<T>& matrix) {
	
	unsigned size = matrix.getSize();
	for (unsigned it = 0; it != size; ++it) {
		for (unsigned j = 0; j != size; ++j)
			out << matrix.at(it, j) << " ";
		out << "\n";
	}
	out << "\n";

	return out;
}