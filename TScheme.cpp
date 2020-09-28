#include "TScheme.h"
void TScheme::PrintVector(int L) {
	for (int i = 0; i < L; i++) {
		//std::cout << permutation[i] << ".";
		printf("%c.", permutation[i]);
	}
	std::cout << " ";
}

void TScheme::PrintPairs(std::vector <Pair> pairs, int L)
{
	for (int i = 0; i < L; i++) {
		printf("(%d, %d) ", pairs[permutation[i]].x, pairs[permutation[i]].y);
	}
	std::cout << std::endl;
}

void TScheme::PrintMat() {
	std::cout << "\n------------\n";
	for (int i = 0; i < MATRIX_LENGTH; i++) {
		std::cout << bitMatrix[i];
		if ((i + 1) % VAR_NUM == 0) {
			std::cout << std::endl;
		}
	}
	std::cout << "------------\n";
}

void TScheme::GetSF() {
	for (int i = 0; i < MATRIX_LENGTH; i++) {
		if (bitMatrix[i] == 1 && i % 9 == 0) {
			sortedForm[i] = 0;
		}
		else {
			sortedForm[i] = bitMatrix[i];
		}
	}
}

void TScheme::PrintSorted() {
	std::cout << "\n------------\n";
	for (int i = 0; i < MATRIX_LENGTH; i++) {
		std::cout << sortedForm[i];
		if ((i + 1) % VAR_NUM == 0) {
			std::cout << std::endl;
		}
	}
	std::cout << "------------\n";
}



TScheme::TScheme(int c) {
	
}


TScheme::TScheme(int L, std::bitset <64>& ds) {
	bitMatrix = ds;
	
	for (int i = 0; i < PERMUTATION_LENGTH; i++) {
		permutation[i] = 0;
	}
}




void TScheme::remove(std::vector<int>& v)
{
	auto end = v.end();
	for (auto it = v.begin(); it != end; ++it) {
		end = std::remove(it + 1, end, *it);
	}

	v.erase(end, v.end());
}