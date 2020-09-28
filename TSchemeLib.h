#pragma once
#include "TScheme.h"

class TSchemeLib
{
public:
	int complexity;
	int counter;
	int total;
	std::vector <TScheme> list;
	std::vector <Pair> pairsVector;
	std::vector <int> currentDupsCount;
	std::set <TScheme> libSet;

	std::mutex g_display_mutex;
	std::mutex libMutex;
	std::mutex qMutex;
	std::queue <TScheme> schemeQueue;
	bool isUnique;


	TSchemeLib();
	std::vector <Pair> GetPairs(int trhld);

	bool isMinimal(char* permutation);
	void GetSchemeMatrix(TScheme& newScheme);
	int SerializeBin(std::string fileName);
	int DeserializeBin(std::string fileName);
	int CountOnes(std::vector<long>& bits);
	int SortMatrixByRow(TScheme& scheme);
	int SortMatrixByColumn(TScheme& scheme);
	void PrintPairs();
	void PrintListSet();
	int GetNextLib2(TSchemeLib& oldLib);
	int CreateBase();

	std::bitset <MATRIX_LENGTH> default_bits;


private:
	bool isEqual;
	int same;
	int notSame;

	std::vector <std::string> strings;
	std::vector <long> ints;

	int GetNewScheme(TScheme& newScheme, int newPiece);
	void AppToMat(TScheme& newScheme, int newPiece);
};

