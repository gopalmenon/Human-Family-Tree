/*
 * FamilyTreeNode.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#include "FamilyTreeNode.hpp"
#include "MtDnaDistanceMatrix.hpp"

#include <map>
#include <memory>
#include <utility>
#include <vector>

//Constructor
FamilyTreeNode::FamilyTreeNode(std::vector<MitochondrialDnaSample> samplesInNode, MtDnaDistanceMatrix mtDnaDistanceMatrix) : mtDnaDistanceMatrix(mtDnaDistanceMatrix) {
	this->samplesInNode = samplesInNode;
	this->leftChild = std::shared_ptr<FamilyTreeNode>(nullptr);
	this->rightChild = std::shared_ptr<FamilyTreeNode>(nullptr);
}

//Copy constructor
FamilyTreeNode::FamilyTreeNode (const FamilyTreeNode& other) : mtDnaDistanceMatrix(other.mtDnaDistanceMatrix) {
	this->samplesInNode = other.samplesInNode;
	this->leftChild = std::shared_ptr<FamilyTreeNode>(nullptr);
	this->rightChild = std::shared_ptr<FamilyTreeNode>(nullptr);
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

//Set child nodes
void FamilyTreeNode::setChildNodes(FamilyTreeNode leftChild, FamilyTreeNode rightChild) {
	this->leftChild = std::make_shared<FamilyTreeNode>(leftChild);
	this->rightChild = std::make_shared<FamilyTreeNode>(rightChild);
}

//Merge the nodes and return the merged node
FamilyTreeNode FamilyTreeNode::mergeWith(FamilyTreeNode other) {

	//Create a merged list of mtDNA samples
	std::vector<MitochondrialDnaSample> mtDnaSamplesInMergedNode;

	for (MitochondrialDnaSample mitochondrialDnaSample : this->samplesInNode) {
		mtDnaSamplesInMergedNode.push_back(mitochondrialDnaSample);
	}


	for (MitochondrialDnaSample mitochondrialDnaSample : other.samplesInNode) {
		mtDnaSamplesInMergedNode.push_back(mitochondrialDnaSample);
	}

	//Create a merged node
	FamilyTreeNode mergedNode(mtDnaSamplesInMergedNode, this->mtDnaDistanceMatrix);

	//Specify the child nodes for the merged node
	mergedNode.setChildNodes(*this, other);

	return mergedNode;
}
