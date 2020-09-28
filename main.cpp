#pragma once
#include "TSchemeLib.h"
#include "TScheme.h"
#pragma once




int main()
{

	std::vector<std::vector<int>> searchMat = {
			{ 1, 0, 0, 0, 0, 0, 0, 0},
			{ 1, 1, 0, 0, 0, 0, 0, 0},
			{ 1, 0, 1, 0, 0, 0, 0, 0},
			{ 1, 1, 1, 1, 0, 0, 0, 0},
			{ 1, 0, 0, 0, 1, 0, 0, 0},
			{ 1, 1, 0, 0, 1, 1, 0, 0},
			{ 1, 0, 1, 0, 1, 0, 1, 0},
			{ 1, 1, 1, 1, 1, 1, 1, 1} };
	int c;

	std::bitset <64> default_bits;
	std::bitset <64> checkBits;
	std::vector <std::vector <int>> equalV;

	for (int i = 0; i < 64; i++) {
		if (i % 9 == 0) {
			default_bits[i] = 1;
		}
	}

	for (int i = 0; i < VAR_NUM; i++) {
		for (int j = 0; j < VAR_NUM; j++) {
			checkBits[i * VAR_NUM + j] = searchMat[i][j];
		}
	}

	std::cout << checkBits << std::endl;

	std::vector <TSchemeLib> lib(12);
	for (int i = 0; i < 12; i++) {
		lib[i].complexity = i + 1;
		lib[i].pairsVector = lib[i].GetPairs(VAR_NUM);
		lib[i].default_bits = default_bits;
	}


	lib[0].CreateBase();
	std::cout << "L1 total: " << lib[0].total << std::endl;


	//int intPermutation[11];

	for (int i = 1; i < 12; i++) {
		auto start_time = std::chrono::high_resolution_clock::now();
		lib[i].GetNextLib2(lib[i - 1]);
		auto end_time = std::chrono::high_resolution_clock::now();
		auto time = end_time - start_time;
		//lib[i].PrintListSet();
		printf("L%d total: %d\n", i + 1, lib[i].total);
		std::cout << time / std::chrono::milliseconds(1) << "ms to run.\n";

		//for (std::set<TScheme>::iterator it = lib[i].libSet.begin(); it != lib[i].libSet.end(); ++it) {
		//	TScheme newScheme(1);
		//	newScheme= *it;
		//	newScheme.PrintPairs(lib[i].pairsVector, i + 1);
		//}


		//lib[i - 1].libSet.clear();

		std::string libFileName = "libbinary";
		libFileName.append(std::to_string(i + 1));
		libFileName.append(".txt");
		//lib[i].SerializeBin(libFileName);
		//c = getchar();
	}


	int eqcounts = 0;

	for (std::set<TScheme>::iterator it = lib[9].libSet.begin(); it != lib[9].libSet.end(); ++it) {
		TScheme newScheme(10);
		newScheme = *it;
		if (checkBits == newScheme.bitMatrix) {
			eqcounts++;
			newScheme.PrintPairs(lib[9].pairsVector, 10);
		}

	}
	std::cout << "EQ 10 = " << eqcounts << std::endl;


	eqcounts = 0;
	for (std::set<TScheme>::iterator it = lib[10].libSet.begin(); it != lib[10].libSet.end(); ++it) {
		TScheme newScheme(11);
		newScheme= *it;
		if (checkBits == newScheme.bitMatrix) {
			eqcounts++;
			newScheme.PrintPairs(lib[10].pairsVector, 11);
		}
			
		}
	std::cout << "EQ 11 = " << eqcounts << std::endl;
	for (std::set<TScheme>::iterator it = lib[11].libSet.begin(); it != lib[11].libSet.end(); ++it) {
		TScheme newScheme(12);
		newScheme = *it;

		if (checkBits == newScheme.bitMatrix) {
			eqcounts++;
			newScheme.PrintPairs(lib[11].pairsVector, 12);
		}

	}
	std::cout << "EQ12 = " << eqcounts << std::endl;
	std::cout << "END!\n";
	c = getchar();
	return 0;
}