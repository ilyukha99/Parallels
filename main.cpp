#include "Algorithm.h"
#include "NewAlgorithm.h"

unsigned************************ main(int argc, char** argv) {

	srand(static_cast<unsigned int>(time(0)));
	unsigned size = 3;

	Vector<double> x = givenSolution<double>(size, 0.0000001, 2.0, 1.0, 0.0);
	std::cout << x;

	Vector<double> y = randomSolution<double>(size, 0.00001, 2.0, 1.0, 0.0);
	std::cout << "\n" << y;

	//d* f = givenSolutionAlgorithm<d>(size, 0.00001, 2.0, 1.0, 0.0);
	//ITSIZE std::cout << std::fixed << std::setprecision(1) << f[it] << " ";
	//std::cout << "\n";

	system("pause");
	return nullptr;
}

void testing() {

	SquareMatrix<int> F(5, 0);
	F = makeSymmetryMatrix(5, 1, 0);
	SquareMatrix<int> L(F);
	SquareMatrix<int> K;
	K = L = F;
	L.output(); K.output(); F.output();

	d* v1 = new d[3]{ 1.0, 2.0, 3.0 };
	d* v2 = new d[3]{ 3.0, 2.0, 1.0 };
	std::cout << scalarMul<d>(3, v1, v2) << "\n";

	int* f = new int[5];
	f[0] = 1; f[1] = 2; f[2] = 1; f[3] = 2; f[4] = 1;
	f = F.mulVector(f);
	for (int i = 0; i != 5; ++i)
		std::cout << f[i] << " ";

	char* first = new char[15]{ "firstfirst" };
	char* second = new char[15]{ "secondsecond" };
	char* third = new char[15]{ "thirdthird" };
	free<char>(first, second, third, nullptr);

	Vector<float> ve1(5, 12.0);
	Vector<float> ve2(5, 5.0);
	ve1.output();
	SquareMatrix<float> F1(5, 3);
	std::cout << F;
	std::cout << (F1.mulVector(ve1 - ve2) * 3.0f) - ve2;

	unsigned size = 100;
	d* x = givenSolutionAlgorithm<d>(size, 0.00001, 2.0, 1.0, 0.0);
	ITSIZE std::cout << std::fixed << std::setprecision(1) << x[it] << "\n";
	std::cout << "\n";

	std::cout << "\n" << "\n";
	d* y = randomSolutionAlgorithm<d>(size, 0.00001, 2.0, 1.0, 0.0);
	ITSIZE std::cout << std::fixed << std::setprecision(3) << y[it] << "\n";

	Vector<double> xx(size);
	std::cin >> xx;
}
