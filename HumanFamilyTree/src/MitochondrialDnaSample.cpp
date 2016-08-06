/*
 * MitochondrialDnaSample.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#include "MinimumEditDistanceFinder.hpp"
#include "MitochondrialDnaSample.hpp"

//Constructor
MitochondrialDnaSample::MitochondrialDnaSample(std::string dnaSequence, std::string sampleLabel, int sampleNumber) {
	this->dnaSequence = dnaSequence;
	this->sampleLabel = sampleLabel;
	this->sampleNumber = sampleNumber;
}

//Return the DNA sequence
std::string MitochondrialDnaSample::getDnaSequence() {
	return this->dnaSequence;
}

//Return sample label which will be the geographic region of the human mtDNA sample
std::string MitochondrialDnaSample::getSampleLabel() {
	return this->sampleLabel;
}

//Return the sample number
int MitochondrialDnaSample::getSampleNumber() const {
	return this->sampleNumber;
}

//Get edit distance from another mtDNA sample
int MitochondrialDnaSample::getDistanceFrom(MitochondrialDnaSample other) {

	MinimumEditDistanceFinder editDistanceFinder(this->dnaSequence, other.getDnaSequence());
	return editDistanceFinder.getAlignmentScore();

}

