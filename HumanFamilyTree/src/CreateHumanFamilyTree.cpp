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
	for (MitochondrialDnaSample mitochondrialDnaSample1 : mtDnaSamples) {
		for (MitochondrialDnaSample mitochondrialDnaSample2 : mtDnaSamples) {
			std::cout << "Distance between " << mitochondrialDnaSample1.getSampleLabel() << " and " << mitochondrialDnaSample2.getSampleLabel() << " is " << mtDnaDistanceMatrix.getDistanceBetween(mitochondrialDnaSample1, mitochondrialDnaSample2) << std::endl;

		}
	}

	FamilyTreeGraph familyTreeGraph(mtDnaSamples, mtDnaDistanceMatrix);
	familyTreeGraph.printGraph();
}

