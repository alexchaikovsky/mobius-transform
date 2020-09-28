#pragma once
#include "TSchemeLib.h"


TSchemeLib::TSchemeLib() {
	counter = 0;
	total = 0;
	//currentDupsCount.resize(28, 0);
	currentDupsCount.resize(28, 0);
	pairsVector = GetPairs(VAR_NUM);
}


std::vector <Pair> TSchemeLib::GetPairs(int trhld)
{
	ints.resize(8);
	std::vector <Pair> v;
	Pair p;
	for (int i = 0; i < trhld; i++) {
		p.x = i;
		for (int j = i + 1; j < trhld; j++) {
		//for (int j = 0; j < trhld; j++) {
			//if (j != i) {
				p.y = j;
				v.push_back(p);
			//}
		}
	}

	return v;
}

void TSchemeLib::PrintPairs() {
	for (int i = 0; i < pairsVector.size(); i++) {
		printf("%d) (%d, %d) \n", i, pairsVector[i].x, pairsVector[i].y);
	}
	return;
}



bool TSchemeLib::isMinimal(char* permutation) {
	bool foundDup = false;
	int currNumber;

	for (int i = 0; i < complexity; i++)
	{
		currNumber = permutation[i];
		currentDupsCount[currNumber]++;
		if (currentDupsCount[currNumber] > 1) {
			memset(&currentDupsCount[0], 0, sizeof(int) * 28);
			return false;
		}
	}
	memset(&currentDupsCount[0], 0, sizeof(int) * 28);
	return true;
}


void TSchemeLib::PrintListSet() {
	for (std::set<TScheme>::iterator it = libSet.begin(); it != libSet.end(); ++it) {
		//std::cout << '\n' << *it;
		TScheme x = *it;
		std::cout << pairsVector.size() << "  " << complexity << std::endl;
		x.PrintPairs(pairsVector, complexity);
		x.PrintMat();
	}
	std::cout << std::endl;
}

void TSchemeLib::GetSchemeMatrix(TScheme& newScheme) {
	int id1, id2;

	for (int i = 0; i < complexity; i++) {
		id1 = pairsVector[newScheme.permutation[i]].x;
		id2 = pairsVector[newScheme.permutation[i]].y;
		for (int j = 0; j < VAR_NUM; j++) {
			newScheme.bitMatrix[id2 * VAR_NUM + j] = newScheme.bitMatrix[id2 * VAR_NUM + j] ^
				newScheme.bitMatrix[id1 * VAR_NUM + j];
		}
	}
	return;
}



int TSchemeLib::SerializeBin(std::string fileName) {
	std::ofstream myfile;
	TScheme newScheme(complexity);
	myfile.open(fileName, std::ios::app | std::ios::binary);
	for (std::set<TScheme>::iterator it = libSet.begin(); it != libSet.end(); ++it) {
		newScheme = *it;
		myfile.write((char*)&newScheme, sizeof(newScheme));
	}
	myfile.close();
	return 1;
}

int TSchemeLib::DeserializeBin(std::string fileName) {
	std::ifstream myfile;
	myfile.open(fileName, std::ios::binary);
	TScheme newScheme(complexity);
	while (myfile.read((char*)&newScheme, sizeof(newScheme))) {
		libSet.insert(std::move(newScheme));
	}
	total = libSet.size();
	myfile.close();
	return 1;
}





int TSchemeLib::GetNewScheme(TScheme& newScheme, int newPiece) {
	newScheme.permutation[complexity - 1] = newPiece;
	if (!isMinimal(newScheme.permutation)) {
		return 0;
	}
	AppToMat(newScheme, newPiece);
	newScheme.GetSF();
	SortMatrixByColumn(newScheme);
	SortMatrixByRow(newScheme);
	return 1;

}


void TSchemeLib::AppToMat(TScheme& newScheme, int newPiece) {

	int id1 = pairsVector[newPiece].x;
	int id2 = pairsVector[newPiece].y;
	for (int j = 0; j < VAR_NUM; j++) {
		newScheme.bitMatrix[id2 * VAR_NUM + j] = newScheme.bitMatrix[id2 * VAR_NUM + j] ^ newScheme.bitMatrix[id1 * VAR_NUM + j];
	}
	return;
}


int TSchemeLib::GetNextLib2(TSchemeLib& oldLib) {
	TScheme newScheme(oldLib.complexity);
	for (std::set<TScheme>::iterator it = oldLib.libSet.begin(); it != oldLib.libSet.end(); ++it) {
		newScheme = *it;
		for (int j = 0; j < 28; j++) {
			TScheme newSchemeFor(complexity);
			newSchemeFor.Copy(newScheme);
			if (GetNewScheme(newSchemeFor, j)) {
				libSet.insert(std::move(newSchemeFor));

			}
		}
	}
	total = libSet.size();
	return 1;
}

int TSchemeLib::CreateBase() {
	PrintPairs();
	TScheme newScheme(1, default_bits);
	newScheme.permutation[0] = 0;
	GetSchemeMatrix(newScheme);
	libSet.insert(std::move(newScheme));
	
	total = libSet.size();
	return 1;
}


int TSchemeLib::SortMatrixByRow(TScheme& scheme) {

	
	//std::vector <std::string> strings;
	//std::vector <long> ints(8);
	//strings.reserve(VAR_NUM);
	std::bitset <12> bs;
	for (int i = 0; i < VAR_NUM; i++) {
		for (int j = 0; j < VAR_NUM; j++) {
			bs[j] = scheme.sortedForm[j + i * VAR_NUM];
		}

		ints[i] = bs.to_ulong();
	}

	std::sort(ints.begin(), ints.end(), std::greater<int>());


	for (int i = 0; i < ints.size(); i++) {
		std::bitset <12> bssorted(ints[i]);
		for (int j = 0; j < VAR_NUM; j++) {
			scheme.sortedForm[j + i * VAR_NUM] = bssorted[j];
		}
	}
	return 1;

}

int TSchemeLib::SortMatrixByColumn(TScheme& scheme) {
	//std::vector <std::string> strings;
	//std::vector <long> ints(8);
	//strings.reserve(VAR_NUM);
	std::bitset <12> bs;
	for (int i = 0; i < VAR_NUM; i++) {
		for (int j = 0; j < VAR_NUM; j++) {
			bs[j] = scheme.sortedForm[i + j * VAR_NUM];
		}
		ints[i] = bs.to_ulong();
	}
	std::sort(ints.begin(), ints.end(), std::greater<int>());

	for (int i = 0; i < ints.size(); i++) {
		std::bitset <12> bssorted(ints[i]);
		for (int j = 0; j < VAR_NUM; j++) {
			scheme.sortedForm[i + j * VAR_NUM] = bssorted[j];
		}
	}
	return 1;

}
