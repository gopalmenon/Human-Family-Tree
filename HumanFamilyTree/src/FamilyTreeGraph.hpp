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

struct InterClusterDistance {

	FamilyTreeNode cluster1;
	FamilyTreeNode cluster2;
	float distance;

	InterClusterDistance(FamilyTreeNode cluster1, FamilyTreeNode cluster2, float distance) : cluster1(cluster1), cluster2(cluster2), distance(distance) {};

};

struct CompareDistance {
    bool operator()(InterClusterDistance const & interClusterDistance1, InterClusterDistance const & interClusterDistance2) {
        return interClusterDistance1.distance > interClusterDistance2.distance;
    }
};

class FamilyTreeGraph {

private:

	const std::string PHYLOGENETIC_TREE_SCRIPT_TEXT_FILE = "../treeScript.txt";

	std::vector<MitochondrialDnaSample> totalPopulation;
	std::vector<FamilyTreeNode> graphNodes;
	std::vector<FamilyTreeNode> nodesNotMergedYet;
	std::priority_queue<InterClusterDistance, std::vector<InterClusterDistance>, CompareDistance> orderedInterClusterDistances;
	std::vector<FamilyTreeNode> removedNodes;
	MtDnaDistanceMatrix mtDnaDistanceMatrix;

	//Form initial clusters made up of mtDNA samples
	void formInitialClusters();

	//Take out parentheses from string
	std::string stripParantheses(std::string text);

	//Run Hierarchical Clustering using UPGMA (Unweighted Pair Group Method with Arithmetic Mean)
	void runHierarchicalClustering();

	//Remove merged clusters from total population
	void removeMergedClusters(FamilyTreeNode& nodeToBeMerged1, FamilyTreeNode& nodeToBeMerged2);

	//Store merged node distances
	void storeNewNodeDistances(FamilyTreeNode& mergedNode);

	//Order the inter-cluster distances in increasing order
	void orderInterClusterDistances();

	void createTreeScriptFile(std::string script);

public:

	//Constructor
	FamilyTreeGraph(std::vector<MitochondrialDnaSample> totalPopulation, MtDnaDistanceMatrix mtDnaDistanceMatrix);

	//Print the graph contents
	void printGraph();

};

#endif /* FAMILYTREEGRAPH_HPP_ */
