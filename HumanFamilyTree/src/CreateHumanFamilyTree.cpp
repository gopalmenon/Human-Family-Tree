/*
 * test.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#include "FamilyTreeGraph.hpp"
#include "FileOperations.hpp"
#include "MitochondrialDnaSample.hpp"
#include "MtDnaDistanceMatrix.hpp"

#include <iostream>
#include <string>
#include <vector>

int main() {

	std::vector<MitochondrialDnaSample> mtDnaSamples = getAllFileContents();
	MtDnaDistanceMatrix mtDnaDistanceMatrix(mtDnaSamples);

	FamilyTreeGraph familyTreeGraph(mtDnaSamples, mtDnaDistanceMatrix);
	familyTreeGraph.printGraph();
}

