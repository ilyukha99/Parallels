#pragma once
#include "Matrixes.h"
#define BAD_NUMBER -1.11

template <typename T>
class Vector {
public:

	Vector<T>(unsigned size = 0, T element = 0) : size(size) {

		T* new_arr = new T[size];
		for (unsigned it = 0; it != size; ++it)
			new_arr[it] = element;

		this->array = new_arr;
	}

	Vector<T>(const Vector<T>& other) : size(other.size) {
		
		T* new_arr = new T[size];
		for (unsigned it = 0; it != size; ++it)
			new_arr[it] = other.array[it];

		this->array = new_arr;
	}

	void swap(Vector<T>& other) {

		unsigned temp = this->size;
		this->size = other.size;
		other.size = temp;

		T* tempPtr = this->array;
		this->array = other.array;
		other.array = tempPtr;
	}

	void output() const  {

		for (unsigned it = 0; it != size; ++it)
			std::cout << this->at(it) << " ";
		std::cout << "\n";
	}

	void fill() {

		for (unsigned it = 0; it != size; ++it)
			std::cin >> array[it];
	}

	Vector<T>& operator=(const Vector<T>& other) {

		if (this != &other)
			Vector<T>(other).swap(*this);

		return *this;
	}

	T& operator[](unsigned index) {
		return array[index];
	}

	T const & operator[](unsigned index) const {
		return array[index];
	}

	T at(unsigned index) const {

		if (index > size)
			return static_cast<T>(BAD_NUMBER);
		return array[index];
	}

	T& at(unsigned index) {

		if (index > size - 1)
			return array[0];
		return array[index];
	}

	unsigned getSize() const {
		return this->size;
	}

	void fillTheVectorRand() {

		T* vector = new T[size];
		double pi = 3.1415926536;
		for (unsigned it = 0; it != size; ++it)
			vector[it] = static_cast<T>(sin(2 * pi * it / size));
		this->array = vector;
	}

	void fillTheVectorRandom() {

		T* vector = new T[size];
		for (unsigned it = 0; it != size; ++it)
			vector[it] = static_cast<T>(Vector<T>::random(6));
		this->array = vector;
	}

	~Vector<T>() {
		delete[] this->array;
	}

private:
	unsigned size;
	T* array;
};

template <typename T>
T module(Vector<T>& vector) {

	T sum = 0;
	unsigned size = vector.getSize();
	for (unsigned it = 0; it != size; ++it)
		sum += vector[it] * vector[it];

	return static_cast<T>(sqrt(sum));
}

template <typename T>
T scalarMul(const Vector<T>& vector1, const Vector<T>& vector2) {

	T sum = 0;
	if (vector1.getSize() == vector2.getSize())
		for (unsigned it = 0; it != vector1.getSize(); ++it)
			sum += vector1.at(it) * vector2.at(it);
	else return static_cast<T>(0);

	return static_cast<T>(sum);
}

template <typename T>
Vector<T>& operator+(const Vector<T>& v1, const Vector<T>& v2) {
	
	Vector<T>* New = new Vector<T>(v1.getSize());
	if (v1.getSize() == v2.getSize()) {
		unsigned size = New->getSize();
		for (unsigned it = 0; it != size; ++it)
			(*New)[it] = v1.at(it) + v2.at(it);
	}

	return *New;
}

template <typename T>
Vector<T>& operator-(const Vector<T>& v1, const Vector<T>& v2) {

	Vector<T>* New = new Vector<T>(v1.getSize());
	if (v1.getSize() == v2.getSize()) {
		unsigned size = New->getSize();
		for (unsigned it = 0; it != size; ++it)
			(*New)[it] = v1.at(it) - v2.at(it);
	}

	return *New;
}

template <typename T>
Vector<T>& operator*(const Vector<T>& v1, const T& value) {

	Vector<T>* New = new Vector<T>(v1);
	unsigned size = New->getSize();
	for (unsigned it = 0; it != size; ++it)
		(*New)[it] *= value;

	return *New;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& vector) {

	unsigned size = vector.getSize();
	for (unsigned it = 0; it != size; ++it)
		out << vector.at(it) << " ";
	out << "\n";

	return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Vector<T>& vector) {

	unsigned size = vector.getSize();
	for (unsigned it = 0; it != size; ++it)
		in >> vector.at(it);

	return in;
}