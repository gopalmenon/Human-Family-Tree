/*
 * MtDnaDistanceMatrix.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#include "MtDnaDistanceMatrix.hpp"

//Fill in the distance between all pair combinations
void MtDnaDistanceMatrix::fillDistanceMatrix() {

	int numberOfSamples = this->samples.size();
	//Find distance between unique pairs of samples. It will be on one side of the diagonal to a square array.
	for (int sampleCounter = 0; sampleCounter < numberOfSamples - 1; ++sampleCounter) {
		for (int otherSampleCounter = sampleCounter + 1; otherSampleCounter < numberOfSamples; ++otherSampleCounter) {

			this->distanceMatrix.insert(std::make_pair(std::make_pair(sampleCounter, otherSampleCounter), samples.at(sampleCounter).getDistanceFrom(samples.at(otherSampleCounter))));

		}
	}

}

//Constructor
MtDnaDistanceMatrix::MtDnaDistanceMatrix(std::vector<MitochondrialDnaSample> samples) {
	this->samples = samples;
	fillDistanceMatrix();
}

//Get the distance between two samples using the distance matrix
int MtDnaDistanceMatrix::getDistanceBetween(MitochondrialDnaSample sample1, MitochondrialDnaSample sample2) {

	int sample1Number = sample1.getSampleNumber(), sample2Number = sample2.getSampleNumber();
	//Check if the sample pair entry exists and return the value
	std::map<std::pair<int, int>, int>::iterator distanceMatrixIterator = this->distanceMatrix.find(std::make_pair(sample1Number, sample2Number));
	if (distanceMatrixIterator != this->distanceMatrix.end()) {
		return distanceMatrixIterator->second;
	} else {
		distanceMatrixIterator = this->distanceMatrix.find(std::make_pair(sample2Number, sample1Number));
		if (distanceMatrixIterator != this->distanceMatrix.end()) {
			return distanceMatrixIterator->second;
		}
	}
	return 0;
}
