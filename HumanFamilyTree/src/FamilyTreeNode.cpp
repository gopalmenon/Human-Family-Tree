/*
 * FamilyTreeNode.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#include "FamilyTreeNode.hpp"
#include "MtDnaDistanceMatrix.hpp"

#include <map>
#include <utility>

//Constructor
FamilyTreeNode::FamilyTreeNode(std::vector<MitochondrialDnaSample> samplesInNode, MtDnaDistanceMatrix mtDnaDistanceMatrix) : mtDnaDistanceMatrix(mtDnaDistanceMatrix) {
	this->samplesInNode = samplesInNode;
}

//Return distance from another node
float FamilyTreeNode::distanceFrom(FamilyTreeNode other) {

	//Add up the distances between each pair
	float distanceFromOtherNode = 0.0;
	for (MitochondrialDnaSample mitochondrialDnaSampleThis : this->samplesInNode) {
		for (MitochondrialDnaSample mitochondrialDnaSampleOther : other.samplesInNode) {

			distanceFromOtherNode += this->mtDnaDistanceMatrix.getDistanceBetween(mitochondrialDnaSampleThis, mitochondrialDnaSampleOther);

		}
	}

	//Divide by the product of the number of nodes in each cluster
	distanceFromOtherNode /= this->samplesInNode.size() * other.samplesInNode.size();

	return distanceFromOtherNode;
}

//Merge the nodes by adding the mtDNA samples in the other to the current one
void FamilyTreeNode::mergeWith(FamilyTreeNode other) {
	for (MitochondrialDnaSample mitochondrialDnaSample : other.samplesInNode) {
		this->samplesInNode.push_back(mitochondrialDnaSample);
	}
}
