/*
 * MitochondrialDnaSample.hpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#ifndef MITOCHONDRIALDNASAMPLE_HPP_
#define MITOCHONDRIALDNASAMPLE_HPP_

#include <string>

class MitochondrialDnaSample {

private:

	std::string dnaSequence;
	std::string sampleLabel;
	int sampleNumber;

public:

	MitochondrialDnaSample(std::string dnaSequence, std::string sampleLabel, int sampleNumber);
	int getDistanceFrom(MitochondrialDnaSample other);
	std::string getDnaSequence();
	std::string getSampleLabel();
	int getSampleNumber();
};



#endif /* MITOCHONDRIALDNASAMPLE_HPP_ */
