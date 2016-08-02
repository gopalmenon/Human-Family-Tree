/*
 * MtDnaDistanceMatrix.hpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#ifndef MTDNADISTANCEMATRIX_HPP_
#define MTDNADISTANCEMATRIX_HPP_

#include "MitochondrialDnaSample.hpp"

#include <map>
#include <utility>
#include <vector>

class MtDnaDistanceMatrix {

private:

	//mtDNA samples
	std::vector<MitochondrialDnaSample> samples;

	//Matrix to hold distances between pairs of mtDNA samples
	std::map<std::pair<int, int>, int> distanceMatrix;

	//Use the mtDNA samples and find the distance between each pair
	void fillDistanceMatrix();

public:

	//Constructor
	MtDnaDistanceMatrix(std::vector<MitochondrialDnaSample> samples);

	//Copy constructor
	MtDnaDistanceMatrix (const MtDnaDistanceMatrix &other);

	//Get the distance between two samples using the distance matrix
	int getDistanceBetween(MitochondrialDnaSample sample1, MitochondrialDnaSample sample2);

};

#endif /* MTDNADISTANCEMATRIX_HPP_ */
