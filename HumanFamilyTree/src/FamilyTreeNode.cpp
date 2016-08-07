/*
 * FamilyTreeNode.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#include "FamilyTreeNode.hpp"
#include "MtDnaDistanceMatrix.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

//Constructor
FamilyTreeNode::FamilyTreeNode(std::vector<MitochondrialDnaSample> samplesInNode, MtDnaDistanceMatrix mtDnaDistanceMatrix) : mtDnaDistanceMatrix(mtDnaDistanceMatrix) {
	this->samplesInNode = samplesInNode;
	this->nodeHeight = 0.0;
	this->leftEdgeLength = 0.0;
	this->rightEdgeLength = 0.0;
}

//Constructor
FamilyTreeNode::FamilyTreeNode(std::vector<MitochondrialDnaSample> samplesInNode, MtDnaDistanceMatrix mtDnaDistanceMatrix, FamilyTreeNode& leftChild, FamilyTreeNode& rightChild) : mtDnaDistanceMatrix(mtDnaDistanceMatrix) {
	this->samplesInNode = samplesInNode;
	this->nodeHeight = 0.0;
	this->leftEdgeLength = 0.0;
	this->rightEdgeLength = 0.0;
}

//Copy constructor
FamilyTreeNode::FamilyTreeNode (const FamilyTreeNode& other) : mtDnaDistanceMatrix(other.mtDnaDistanceMatrix) {
	this->samplesInNode = other.samplesInNode;
	this->nodeHeight = other.nodeHeight;
	this->leftEdgeLength = other.leftEdgeLength;
	this->rightEdgeLength = other.rightEdgeLength;
	this->newickFormatNodeScript = other.newickFormatNodeScript;
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
	distanceFromOtherNode /= (this->samplesInNode.size() * other.samplesInNode.size());

	return distanceFromOtherNode;
}

//Merge the nodes and return the merged node
FamilyTreeNode FamilyTreeNode::mergeWith(FamilyTreeNode& other) {

	//Create a merged list of mtDNA samples
	std::vector<MitochondrialDnaSample> mtDnaSamplesInMergedNode;

	for (MitochondrialDnaSample mitochondrialDnaSample : this->samplesInNode) {
		mtDnaSamplesInMergedNode.push_back(mitochondrialDnaSample);
	}


	for (MitochondrialDnaSample mitochondrialDnaSample : other.samplesInNode) {
		mtDnaSamplesInMergedNode.push_back(mitochondrialDnaSample);
	}

	//Create a merged node
	FamilyTreeNode mergedNode(mtDnaSamplesInMergedNode, this->mtDnaDistanceMatrix, *this, other);

	float distanceFromOther = distanceFrom(other);
	mergedNode.nodeHeight = distanceFromOther / 2.0;
	mergedNode.leftEdgeLength = mergedNode.nodeHeight - this->nodeHeight;
	mergedNode.rightEdgeLength = mergedNode.nodeHeight - other.nodeHeight;
	mergedNode.setNewickFormatNodeScript("(" + this->getNewickFormatNodeScript() + ":" + std::to_string(mergedNode.leftEdgeLength) + "," + other.getNewickFormatNodeScript() + ":" + std::to_string(mergedNode.rightEdgeLength) + ")");

	return mergedNode;
}


float FamilyTreeNode::getNodeHeight() {
	return this->nodeHeight;
}

float FamilyTreeNode::getLeftEdgeLength() {
	return this->leftEdgeLength;
}

float FamilyTreeNode::getRightEdgeLength() {
	return this->rightEdgeLength;
}

const bool FamilyTreeNode::isLeafNode() const {

	return this->samplesInNode.size() == 1;

}

std::string FamilyTreeNode::getLeafSampleLabel() {

	if (isLeafNode()) {
		return this->samplesInNode.at(0).getSampleLabel();
	} else {
		return std::string("");
	}

}

std::string FamilyTreeNode::getNodeSampleLabels() {

	std::string nodeSampleLabels;
	bool firstTime = true;
	for (MitochondrialDnaSample mitochondrialDnaSample : this->samplesInNode) {
		if (firstTime) {
			firstTime = false;
		} else {
			nodeSampleLabels += ",";
		}
		nodeSampleLabels += mitochondrialDnaSample.getSampleLabel();
	}
	return nodeSampleLabels;

}

const int FamilyTreeNode::getLeafSampleNumber() const {

	return this->samplesInNode.at(0).getSampleNumber();

}

const bool FamilyTreeNode::isTwoSamplesSame(std::vector<MitochondrialDnaSample> sample1, std::vector<MitochondrialDnaSample> sample2) const {

	if (sample1.size() == sample2.size()) {
		for (auto sample1Iterator = sample1.begin(), sample2Iterator = sample2.begin(); sample1Iterator != sample1.end(); ++sample1Iterator, ++sample2Iterator) {
			if (sample1Iterator->getSampleNumber() != sample2Iterator->getSampleNumber()) {
				return false;
			}
		}

		return true;
	} else {
		return false;
	}

}

//Override the equal operator
bool const FamilyTreeNode::operator==(const FamilyTreeNode& other) {

	return isTwoSamplesSame(this->samplesInNode, other.samplesInNode);

}
