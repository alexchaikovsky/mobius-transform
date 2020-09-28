#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <sstream>
#include <queue> 
#include <future>
#include <set>
#include <functional>
#include <bitset>
#include <array>

#define WIDTH 8
#define VAR_NUM 8
#define BASE0 31
#define BASE1 113
#define MATRIX_LENGTH 64
#define PERMUTATION_LENGTH 12

struct Pair {
	int x, y, num;
};



class TScheme
{
public:
	char permutation[PERMUTATION_LENGTH];
	std::bitset <MATRIX_LENGTH> bitMatrix;
	std::bitset <MATRIX_LENGTH> sortedForm;

	void PrintMat();
	void PrintSorted();
	void PrintVector(int L);
	void PrintPairs(std::vector <Pair> pairs, int L);
	void remove(std::vector<int>& v);
	TScheme(int c);
	TScheme(int L, std::bitset <64>& ds);
	void GetSF();
	friend bool operator <(const TScheme& a, const TScheme& b)
	{
		return a.sortedForm.to_ullong() < b.sortedForm.to_ullong();
	}


	friend std::ostream& operator <<(std::ostream& os, const TScheme& pt)
	{
		for (int i = 0; i < PERMUTATION_LENGTH; i++) {
			os << +pt.permutation[i] << ".";
		}
		return os;
	}

	void Copy(TScheme& b) {
		memcpy(permutation, b.permutation, PERMUTATION_LENGTH * sizeof(char));
		bitMatrix = b.bitMatrix;
	}




};

