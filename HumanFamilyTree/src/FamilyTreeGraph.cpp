/*
 * FamilyTreeGraph.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#include "FamilyTreeGraph.hpp"

#include <algorithm>
#include <iostream>
#include <queue>

//Order the inter-cluster distances in increasing order
void FamilyTreeGraph::orderInterClusterDistances() {

	int numberOfInitialClusters = this->graphNodes.size();
	for (int clusterCounter1 = 0; clusterCounter1 < numberOfInitialClusters - 1; ++clusterCounter1) {
		for (int clusterCounter2 = clusterCounter1 + 1; clusterCounter2 < numberOfInitialClusters; ++clusterCounter2) {
			InterClusterDistance interClusterDistance(this->graphNodes.at(clusterCounter1), this->graphNodes.at(clusterCounter2), this->graphNodes.at(clusterCounter1).distanceFrom(this->graphNodes.at(clusterCounter2)));
			this->orderedInterClusterDistances.push(interClusterDistance);
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
		this->nodesNotMergedYet.push_back(familyTreeNode);
	}
}

//Remove merged clusters from list of nodes not yet merged
void FamilyTreeGraph::removeMergedClusters(FamilyTreeNode& nodeToBeMerged1, FamilyTreeNode& nodeToBeMerged2) {

	auto nodeIterator = std::find(this->nodesNotMergedYet.begin(), this->nodesNotMergedYet.end(), nodeToBeMerged1);
	if (nodeIterator != this->nodesNotMergedYet.end()) {
		this->nodesNotMergedYet.erase(nodeIterator);
	}
	nodeIterator = std::find(this->nodesNotMergedYet.begin(), this->nodesNotMergedYet.end(), nodeToBeMerged2);
	if (nodeIterator != this->nodesNotMergedYet.end()) {
		this->nodesNotMergedYet.erase(nodeIterator);
	}

}

void FamilyTreeGraph::storeNewNodeDistances(FamilyTreeNode& mergedNode) {

	for (auto nodeIterator = this->nodesNotMergedYet.begin(); nodeIterator != this->nodesNotMergedYet.end(); ++nodeIterator) {

		InterClusterDistance interClusterDistance(mergedNode, *nodeIterator, mergedNode.distanceFrom(*nodeIterator));
		this->orderedInterClusterDistances.push(interClusterDistance);

	}

}

//Run Hierarchical Clustering using UPGMA (Unweighted Pair Group Method with Arithmetic Mean)
void FamilyTreeGraph::runHierarchicalClustering() {

	//Form initial clusters with each mtDNA sample being a node
	formInitialClusters();

	//Save the inter-node distances in a priority queue ordered by inter-node distance
	orderInterClusterDistances();

	//Run clustering by merging the closest nodes. Repeat while there are still more clusters to merge
	while(!this->orderedInterClusterDistances.empty()) {

		//Get the two closest clusters
		InterClusterDistance interClusterDistance = this->orderedInterClusterDistances.top();
		this->orderedInterClusterDistances.pop();
		this->removedNodes.push_back(interClusterDistance.cluster1);
		this->removedNodes.push_back(interClusterDistance.cluster2);
		long lastRemovedElementIndex = this->removedNodes.size() - 1;
		FamilyTreeNode& nodeToBeMerged1 = this->removedNodes.at(lastRemovedElementIndex);
		FamilyTreeNode& nodeToBeMerged2 = this->removedNodes.at(lastRemovedElementIndex - 1);

		//Merge the nodes if they exist in the list of nodes not yet merged
		if (std::find(this->nodesNotMergedYet.begin(), this->nodesNotMergedYet.end(), nodeToBeMerged1) != this->nodesNotMergedYet.end() &&
			std::find(this->nodesNotMergedYet.begin(), this->nodesNotMergedYet.end(), nodeToBeMerged2) != this->nodesNotMergedYet.end()) {

			//Merge the two closest clusters
			FamilyTreeNode mergedNode = nodeToBeMerged1.mergeWith(nodeToBeMerged2);

			//Remove merged clusters from total population
			removeMergedClusters(nodeToBeMerged1, nodeToBeMerged2);

			//Store distances to nodes not yet merged
			storeNewNodeDistances(mergedNode);

			//Store new node into list of nodes to be merged
			this->nodesNotMergedYet.push_back(mergedNode);

			//Store the merged node
			this->graphNodes.push_back(mergedNode);

		}

	}

}

//Constructor
FamilyTreeGraph::FamilyTreeGraph(std::vector<MitochondrialDnaSample> totalPopulation, MtDnaDistanceMatrix mtDnaDistanceMatrix) : mtDnaDistanceMatrix(mtDnaDistanceMatrix) {
	this->totalPopulation = totalPopulation;
	runHierarchicalClustering();
}

//Print the graph contents
void FamilyTreeGraph::printGraph() {

	long numberOfClusters = this->graphNodes.size();
	for (int clusterIndex = numberOfClusters - 1; clusterIndex >= 0; --clusterIndex) {
		if (this->graphNodes.at(clusterIndex).isLeafNode()) {
			std::cout << "Node is " << this->graphNodes.at(clusterIndex).getLeafSampleLabel() << std::endl;
		} else {
			std::cout << "Node height " << std::to_string(this->graphNodes.at(clusterIndex).getNodeHeight()) << ", left edge length " << std::to_string(this->graphNodes.at(clusterIndex).getLeftEdgeLength()) << ", right edge length " << std::to_string(this->graphNodes.at(clusterIndex).getRightEdgeLength()) << std::endl;
			std::cout << "Node contains " << this->graphNodes.at(clusterIndex).getNodeSampleLabels() << std::endl;

		}

	}

}

