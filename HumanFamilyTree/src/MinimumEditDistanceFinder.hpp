/*
 * MinimumEditDistanceFinder.hpp
 *
 *  Created on: Jul 23, 2016
 *      Author: gopalmenon
 */

#ifndef MINIMUMEDITDISTANCEFINDER_HPP_
#define MINIMUMEDITDISTANCEFINDER_HPP_

#include <string>

class MinimumEditDistanceFinder {

private:

	std::string stringA;
	std::string stringB;
	int stringALength;
	int stringBLength;
	int alignmentScore;

	//Return the minimum of three integers
	int getMinimumScore(int integer1, int integer2, int integer3);

	//Align the strings and compute score
	void alignStrings();

public:
	//Constructor for minimum edit distance finder
	MinimumEditDistanceFinder(std::string stringA, std::string stringB);

	//Returns the alignment score for the two strings A and B
	int getAlignmentScore();
};

#endif /* MINIMUMEDITDISTANCEFINDER_HPP_ */
