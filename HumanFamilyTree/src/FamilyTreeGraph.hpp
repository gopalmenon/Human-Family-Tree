/*
 * FamilyTreeGraph.hpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#ifndef FAMILYTREEGRAPH_HPP_
#define FAMILYTREEGRAPH_HPP_

#include "FamilyTreeNode.hpp"
#include "MitochondrialDnaSample.hpp"
#include "MtDnaDistanceMatrix.hpp"

#include <queue>
#include <vector>

class FamilyTreeGraph {

private:

	std::vector<MitochondrialDnaSample> totalPopulation;
	std::vector<FamilyTreeNode> graphNodes;
	MtDnaDistanceMatrix mtDnaDistanceMatrix;

	//Form initial clusters made up of mtDNA samples
	void formInitialClusters();

	//Run Hierarchical Clustering using UPGMA (Unweighted Pair Group Method with Arithmetic Mean)
	void runHierarchicalClustering();

public:

	//Constructor
	FamilyTreeGraph(std::vector<MitochondrialDnaSample> totalPopulation, MtDnaDistanceMatrix mtDnaDistanceMatrix);

};

#endif /* FAMILYTREEGRAPH_HPP_ */
