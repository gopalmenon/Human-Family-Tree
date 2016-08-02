/*
 * FamilyTreeGraph.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#include "FamilyTreeGraph.hpp"

#include <queue>

struct InterClusterDistance {

	FamilyTreeNode cluster1;
	FamilyTreeNode cluster2;
	float distance;

	InterClusterDistance(FamilyTreeNode cluster1, FamilyTreeNode cluster2, float distance) : cluster1(cluster1), cluster2(cluster2), distance(distance) {};
};

struct CompareDistance {
    bool operator()(InterClusterDistance const & interClusterDistance1, InterClusterDistance const & interClusterDistance2) {
        return interClusterDistance1.distance < interClusterDistance2.distance;
    }
};
//Order the inter-cluster distances in increasing order
void orderInterClusterDistances(std::priority_queue<InterClusterDistance, std::vector<InterClusterDistance>, CompareDistance>& orderedInterClusterDistances, std::vector<FamilyTreeNode> graphNodes) {

	int numberOfInitialClusters = graphNodes.size();
	for (int clusterCounter1 = 0; clusterCounter1 < numberOfInitialClusters - 1; ++clusterCounter1) {
		for (int clusterCounter2 = clusterCounter1 + 1; clusterCounter2 < numberOfInitialClusters; ++clusterCounter2) {
			InterClusterDistance interClusterDistance(graphNodes.at(clusterCounter1), graphNodes.at(clusterCounter1), graphNodes.at(clusterCounter1).distanceFrom(graphNodes.at(clusterCounter2)));
			orderedInterClusterDistances.push(interClusterDistance);
		}
	}

}

//Form initial clusters made up of mtDNA samples
void FamilyTreeGraph::formInitialClusters() {
	for (MitochondrialDnaSample mitochondrialDnaSample : this->totalPopulation) {
		std::vector<MitochondrialDnaSample> samplesInCluster;
		samplesInCluster.push_back(mitochondrialDnaSample);
		FamilyTreeNode familyTreeNode(samplesInCluster, this->mtDnaDistanceMatrix);
		this->graphNodes.push_back(familyTreeNode);
	}
}

//Run Hierarchical Clustering using UPGMA (Unweighted Pair Group Method with Arithmetic Mean)
void FamilyTreeGraph::runHierarchicalClustering() {

	std::priority_queue<InterClusterDistance, std::vector<InterClusterDistance>, CompareDistance> orderedInterClusterDistances;
	formInitialClusters();
	orderInterClusterDistances(orderedInterClusterDistances, this->graphNodes);

}

//Constructor
FamilyTreeGraph::FamilyTreeGraph(std::vector<MitochondrialDnaSample> totalPopulation, MtDnaDistanceMatrix mtDnaDistanceMatrix) : mtDnaDistanceMatrix(mtDnaDistanceMatrix) {
	this->totalPopulation = totalPopulation;
	runHierarchicalClustering();
}
