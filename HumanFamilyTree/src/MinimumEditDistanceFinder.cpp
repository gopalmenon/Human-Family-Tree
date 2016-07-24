/*
 * MinimumEditDistanceFinder.cpp
 *
 *  Created on: Jul 23, 2016
 *      Author: gopalmenon
 */

#include "MinimumEditDistanceFinder.hpp"

#include <algorithm>
#include <string>

//Constructor
MinimumEditDistanceFinder::MinimumEditDistanceFinder(std::string stringA, std::string stringB) {

	this->stringA = stringA;
	this->stringALength = stringA.size();
	this->stringB = stringB;
	this->stringBLength = stringB.size();
	this->alignmentScore = 0;
	alignStrings();
}

//Align the strings and compute score
void MinimumEditDistanceFinder::alignStrings() {

	//Create a strip of memory two columns wide that will be slid along from beginning to end of string A
	int  twoColumnScoreMatrix[this->stringBLength + 1][2];

	for (int columnCounter = 0; columnCounter <= this->stringALength; ++columnCounter) {

		//When column counter is zero, fill in the alignment with an empty string A
		if (columnCounter == 0) {
			for (int emptyStringAlignmentCounter = 0; emptyStringAlignmentCounter <= this->stringBLength; ++emptyStringAlignmentCounter) {
				twoColumnScoreMatrix[emptyStringAlignmentCounter][0] = emptyStringAlignmentCounter;
			}
			continue;
		}

		//Fill in the alignment scores one column at a time
		for (int rowCounter = 0; rowCounter <= this->stringBLength; ++rowCounter) {

			if (rowCounter == 0) {
				twoColumnScoreMatrix[rowCounter][columnCounter % 2] = columnCounter;
			} else {
				twoColumnScoreMatrix[rowCounter][columnCounter % 2] = getMinimumScore(twoColumnScoreMatrix[rowCounter - 1][columnCounter % 2] + 1,
																					  twoColumnScoreMatrix[rowCounter][(columnCounter - 1) % 2] + 1,
																					  twoColumnScoreMatrix[rowCounter - 1][(columnCounter - 1) % 2] +
																				   	 (this->stringA.at(columnCounter - 1) == this->stringB.at(rowCounter - 1) ? 0 : 1));
			}

		}
	}

	//The alignment score is the value at the top right corner of the array
	this->alignmentScore =  twoColumnScoreMatrix[this->stringBLength][this->stringALength % 2];

}

//Return the minimum of three integers
int MinimumEditDistanceFinder::getMinimumScore(int integer1, int integer2, int integer3) {
	return std::min(std::min(integer1, integer2), integer3);
}

//Return the alignment score or edit distance
int MinimumEditDistanceFinder::getAlignmentScore() {
	return this->alignmentScore;
}
