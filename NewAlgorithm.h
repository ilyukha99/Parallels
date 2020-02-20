#pragma once
#include "Matrixes.h"
#include "Vector.h"

template <typename T>
Vector<T>& givenSolution(unsigned size, T epsilon, T diagonal, T other, T x_i) {

	//initial values
	SquareMatrix<T> A = makeSymmetryMatrix<T>(size, diagonal, other);
	/*Vector<T> b(size, static_cast<T>(size + 1));*/
	Vector<T> b(size); b[0] = 1;  b[1] = 2; b[2] = 3;
	Vector<T>& x = *(new Vector<T>(size, x_i));
	Vector<T> r = b - A.mulVector(x);
	Vector<T> z(r);
	Vector<T> prevR;
	Vector<T> Az;

	unsigned count = 0;
	while (module<T>(r) / module<T>(b) >= epsilon)  {
		Az = A.mulVector(z);
		T alpha = scalarMul<T>(r, r) / scalarMul<T>(Az, z);
		x = x + (z * alpha);
		prevR = r;
		r = r - (Az * alpha);
		T beta = scalarMul<T>(r, r) / scalarMul<T>(prevR, prevR);
		z = r + (z * beta);

		++count;
	}
	std::cout << "\n" << "count = " << count << "\n";
	return x;
}

template <typename T>
Vector<T>& randomSolution(unsigned size, T epsilon, T diagonal, T other, T x_i) {

	//initial values
	SquareMatrix<T> A = makeSymmetryMatrix<T>(size, diagonal, other); //SquareMatrix<T> A = makeRandomSymmetryMatrix<T>(size);
	Vector<T> u(size);
	u.fillTheVectorRand(); std::cout << "u = " << u;
	Vector<T> b = A.mulVector(u);
	Vector<T>& x = *(new Vector<T>(size, x_i));
	Vector<T> r = b - A.mulVector(x);
	Vector<T> z(r);
	Vector<T> prevR;
	Vector<T> Az;

	unsigned count = 0;
	while (module<T>(r) / module<T>(b) >= epsilon) {

		Az = A.mulVector(z);
		T alpha = scalarMul<T>(r, r) / scalarMul<T>(Az, z);
		x = x + (z * alpha);
		prevR = r;
		r = r - (Az * alpha);
		T beta = scalarMul<T>(r, r) / scalarMul<T>(prevR, prevR);
		z = r + (z * beta);

		++count;
	}

	std::cout << "\n" << "count = " << count << "\n";
	return x;
}