/*
 * FamilyTreeNode.hpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#ifndef FAMILYTREENODE_HPP_
#define FAMILYTREENODE_HPP_

#include "MitochondrialDnaSample.hpp"
#include "MtDnaDistanceMatrix.hpp"

#include <vector>

class FamilyTreeNode {

private:

	std::vector<MitochondrialDnaSample> samplesInNode;
	MtDnaDistanceMatrix mtDnaDistanceMatrix;

public:

	//Constructor
	FamilyTreeNode(std::vector<MitochondrialDnaSample> samplesInNode, MtDnaDistanceMatrix mtDnaDistanceMatrix);

	//Return distance from another node
	float distanceFrom(FamilyTreeNode other);

	//Merge the nodes by adding the mtDNA samples in the other to the current one
	void mergeWith(FamilyTreeNode other);

};

#endif /* FAMILYTREENODE_HPP_ */
