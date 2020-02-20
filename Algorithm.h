#pragma once
#include "Matrixes.h"
#include "Vector.h"
#define ITSIZE for (unsigned it = 0; it != size; ++it)
typedef double d;

template <typename T>
T module(unsigned size, T* vector) {

	T result = 0;
	ITSIZE result += vector[it] * vector[it];
	return static_cast<T>(sqrt(result));
}

template <typename T>
T scalarMul(unsigned size, T* vector1, T* vector2) {

	T result = 0;
	ITSIZE result += *(vector1 + it) * *(vector2 + it);
	return result;
}

template <typename T>
T* subtractVectors(unsigned size, T* vector1, T* vector2) {

	T* resultV = new T[size * sizeof(T)];
	ITSIZE resultV[it] = vector1[it] - vector2[it];
	return resultV;
}

template <typename T>
T* addVectors(unsigned size, T* vector1, T* vector2) {

	T* resultV = new T[size * sizeof(T)];
	ITSIZE resultV[it] = vector1[it] + vector2[it];
	return resultV;
}

template <typename T>
T* fillTheVector(unsigned size, T value) {

	T* vector = new T[size * sizeof(T)];
	ITSIZE vector[it] = value;

	return vector;
}

template <typename T>
T* copyVector(unsigned size, T* vector) {

	T* resultV = new T[size * sizeof(T)];
	ITSIZE resultV[it] = vector[it];

	return resultV;
}

template <typename T>
T* mulNum(unsigned size, T* vector, T num) {

	T* resultV = new T[size * sizeof(T)];
	ITSIZE resultV[it] = num * vector[it];

	return resultV;
}

template <typename T>
void free(unsigned amount, T* first, ...) {

	T** pointer = &first;
	unsigned count = 0;
	while (count != amount) {
		T* cur = *pointer;
		delete[] cur;
		++pointer;
		++count;
	}
}

template <typename T>
void free(T* first, ...) {

	T** pointer = &first;
	while (*pointer != nullptr) {
		T* cur = *pointer;
		delete[] cur;
		++pointer;
	}
}

template <typename T>
T* fillTheVectorRandomly(unsigned size) {

	T* vector = new T[size * sizeof(T)];
	double pi = 3.1415926536;
	ITSIZE vector[it] = sin(2 * pi * it / size);

	return vector;
}

template <typename T>
T* givenSolutionAlgorithm(unsigned size, T epsilon, T diagonal, T other, T x_i) {

	//initial values
	SquareMatrix<T> A = makeSymmetryMatrix<T>(size, diagonal, other);
	//A.fillTheMatrix();
	T* b = fillTheVector<T>(size, 0); b[0] = 1; b[1] = 2; b[2] = 3;
	T* x = fillTheVector<T>(size, x_i);

	T* Ax = A.mulVector(x);
	T* r = subtractVectors<T>(size, b, Ax);
	T* z = copyVector(size, r);

	unsigned count = 0;
	while (module(size, r) / module(size, b) > epsilon) {

		T* Az = A.mulVector(z);
		T alpha = scalarMul<T>(size, r, r) / scalarMul<T>(size, Az, z);

		T* prevX = x;
		T* alphaz = mulNum<T>(size, z, alpha);
		x = addVectors(size, prevX, alphaz);

		T* prevR = copyVector(size, r);
		T* alphaAz = mulNum<T>(size, Az, alpha);
		r = subtractVectors<T>(size, prevR, alphaAz);

		T beta = scalarMul<T>(size, r, r) / scalarMul<T>(size, prevR, prevR);

		T* betaz = mulNum<T>(size, z, beta);
		z = addVectors<T>(size, r, betaz);

		free<T>(Az, prevX, prevR, alphaz, alphaAz, betaz, nullptr);
		++count;
	}
	std::cout << "\n" << "count = " << count << "\n";
	free<T>(4, b, r, z, Ax);
	return x;
}

template <typename T>
T* randomSolutionAlgorithm(unsigned size, T epsilon, T diagonal, T other, T x_i) {

	//initial values
	SquareMatrix<T> A = makeRandomSymmetryMatrix<T>(size);
	T* u = fillTheVectorRandomly<T>(size);
	T* b = A.mulVector(u);
	T* x = fillTheVector<T>(size, x_i);
	T* Ax = A.mulVector(x);
	T* r = subtractVectors<T>(size, b, Ax);
	T* z = copyVector(size, r);

	ITSIZE std::cout << u[it] << " ";
	unsigned count = 0;

	while (module(size, r) / module(size, b) > epsilon) {

		T* Az = A.mulVector(z);
		T alpha = scalarMul<T>(size, r, r) / scalarMul<T>(size, Az, z);

		T* prevX = x;
		T* alphaz = mulNum<T>(size, z, alpha);
		x = addVectors(size, prevX, alphaz);

		T* prevR = copyVector(size, r);
		T* alphaAz = mulNum<T>(size, Az, alpha);
		r = subtractVectors<T>(size, prevR, alphaAz);

		T beta = scalarMul<T>(size, r, r) / scalarMul<T>(size, prevR, prevR);

		T* betaz = mulNum<T>(size, z, beta);
		z = addVectors<T>(size, r, betaz);

		free<T>(Az, prevX, prevR, alphaz, alphaAz, betaz, nullptr);
		++count;
	}

	std::cout << "\n" << "count = " << count << "\n";
	free<T>(4, b, r, z, Ax);
	return x;
}