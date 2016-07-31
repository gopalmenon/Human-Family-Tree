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

#include <memory>
#include <vector>

class FamilyTreeNode {

private:

	std::vector<MitochondrialDnaSample> samplesInNode;
	MtDnaDistanceMatrix mtDnaDistanceMatrix;
	std::shared_ptr<FamilyTreeNode> leftChild;
	std::shared_ptr<FamilyTreeNode> rightChild;

	//Set child nodes
	void setChildNodes(FamilyTreeNode leftChild, FamilyTreeNode rightChild);

public:

	//Constructor
	FamilyTreeNode(std::vector<MitochondrialDnaSample> samplesInNode, MtDnaDistanceMatrix mtDnaDistanceMatrix);

	//Copy constructor
	FamilyTreeNode (const FamilyTreeNode& other);

	//Return distance from another node
	float distanceFrom(FamilyTreeNode other);

	//Merge the nodes by adding the mtDNA samples in the other to the current one
	FamilyTreeNode mergeWith(FamilyTreeNode other);

	//Return left child
	std::shared_ptr<FamilyTreeNode> getLeftChild() {
		return this->leftChild;
	}

	//Return right child
	std::shared_ptr<FamilyTreeNode> getRightChild() {
		return this->rightChild;
	}

};

#endif /* FAMILYTREENODE_HPP_ */
