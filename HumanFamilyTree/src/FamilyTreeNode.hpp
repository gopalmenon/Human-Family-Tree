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
	float nodeHeight, leftEdgeLength, rightEdgeLength;
	std::string newickFormatNodeScript;

	const int getLeafSampleNumber() const;

	const bool isTwoSamplesSame(std::vector<MitochondrialDnaSample> sample1, std::vector<MitochondrialDnaSample> sample2) const;

public:

	//Constructor
	FamilyTreeNode(std::vector<MitochondrialDnaSample> samplesInNode, MtDnaDistanceMatrix mtDnaDistanceMatrix);

	//Constructor
	FamilyTreeNode(std::vector<MitochondrialDnaSample> samplesInNode, MtDnaDistanceMatrix mtDnaDistanceMatrix, FamilyTreeNode& leftChild, FamilyTreeNode& rightChild);

	//Copy constructor
	FamilyTreeNode (const FamilyTreeNode& other);

	//Return distance from another node
	float distanceFrom(FamilyTreeNode other);

	//Merge the nodes by adding the mtDNA samples in the other to the current one
	FamilyTreeNode mergeWith(FamilyTreeNode& other);

	const bool isLeafNode() const;

	std::string getLeafSampleLabel();

	std::string getNodeSampleLabels();

	float getNodeHeight();

	float getLeftEdgeLength();

	float getRightEdgeLength();

	void setNewickFormatNodeScript(std::string script) {
		this->newickFormatNodeScript = script;
	}

	std::string getNewickFormatNodeScript() {
		return this->newickFormatNodeScript;
	}

	//Override the equal operator
	bool const operator==(const FamilyTreeNode& other);

};

#endif /* FAMILYTREENODE_HPP_ */
