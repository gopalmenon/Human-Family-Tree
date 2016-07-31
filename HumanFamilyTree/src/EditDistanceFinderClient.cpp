/*
 * EditDistanceFinderClient.cpp
 *
 *  Created on: Jul 23, 2016
 *      Author: gopalmenon
 */

#include "MinimumEditDistanceFinder.hpp"

#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <ratio>
#include <string>

std::string VALID_BASES[] = {"A", "C", "G", "T"};
int MAXIMUM_NUCLEOTIDE_STRING_LENGTH = 16569;

std::string getRandomNucleotideString() {

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(0, 3);

	std::string mitochondrialDnaString;

	for (int nucleotideCounter = 0; nucleotideCounter < MAXIMUM_NUCLEOTIDE_STRING_LENGTH; ++nucleotideCounter) {

		mitochondrialDnaString.append(VALID_BASES[distribution(generator)]);

	}

	return mitochondrialDnaString;
}

int findEditDistance() {

	std::string stringA(getRandomNucleotideString());
	std::string stringB(getRandomNucleotideString());

	std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
	MinimumEditDistanceFinder finder(stringA, stringB);
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::steady_clock::now() - startTime);
	std::cout << "Alignment score is " << finder.getAlignmentScore() << ". Took " << time_span.count() << " seconds to complete." << std::endl;
}


