/*
 * FamilyTreeGraph.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: gopalmenon
 */

#include "FamilyTreeGraph.hpp"

#include <algorithm>
#include <queue>

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
		this->nodesNotMergedYet.push_back(familyTreeNode);
	}
}

//Remove merged clusters from list of nodes not yet merged
void FamilyTreeGraph::removeMergedClusters(const FamilyTreeNode& nodeToBeMerged1, const FamilyTreeNode& nodeToBeMerged2) {

	auto nodeIterator = std::find(this->nodesNotMergedYet.begin(), this->nodesNotMergedYet.end(), nodeToBeMerged1);
	if (nodeIterator != this->nodesNotMergedYet.end()) {
		this->nodesNotMergedYet.erase(nodeIterator);
	} else {
		nodeIterator = std::find(this->nodesNotMergedYet.begin(), this->nodesNotMergedYet.end(), nodeToBeMerged2);
		if (nodeIterator != this->nodesNotMergedYet.end()) {
			this->nodesNotMergedYet.erase(nodeIterator);
		}
	}

}

void FamilyTreeGraph::storeNewNodeDistances(FamilyTreeNode& mergedNode, std::priority_queue<InterClusterDistance, std::vector<InterClusterDistance>, CompareDistance>& orderedInterClusterDistances) {

	for (auto nodeIterator = this->nodesNotMergedYet.begin(); nodeIterator != this->nodesNotMergedYet.end(); ++nodeIterator) {

		InterClusterDistance interClusterDistance(mergedNode, *nodeIterator, mergedNode.distanceFrom(*nodeIterator));
		orderedInterClusterDistances.push(interClusterDistance);

	}


}

//Run Hierarchical Clustering using UPGMA (Unweighted Pair Group Method with Arithmetic Mean)
void FamilyTreeGraph::runHierarchicalClustering() {

	std::priority_queue<InterClusterDistance, std::vector<InterClusterDistance>, CompareDistance> orderedInterClusterDistances;

	//Form initial clusters with each mtDNA sample being a node
	formInitialClusters();

	//Save the inter-node distances in a priority queue ordered by inter-node distance
	orderInterClusterDistances(orderedInterClusterDistances, this->graphNodes);

	//Run clustering by merging the closest nodes. Repeat while there are still more clusters to merge
	while(!orderedInterClusterDistances.empty()) {

		//Get the two closest clusters
		InterClusterDistance interClusterDistance = orderedInterClusterDistances.top();
		orderedInterClusterDistances.pop();
		FamilyTreeNode nodeToBeMerged1 = interClusterDistance.cluster1;
		FamilyTreeNode nodeToBeMerged2 = interClusterDistance.cluster2;

		//Merge the nodes if they exist in the list of nodes not yet merged
		if (std::find(this->nodesNotMergedYet.begin(), this->nodesNotMergedYet.end(), nodeToBeMerged1) != this->nodesNotMergedYet.end() &&
			std::find(this->nodesNotMergedYet.begin(), this->nodesNotMergedYet.end(), nodeToBeMerged2) != this->nodesNotMergedYet.end()) {

			//Merge the two closest clusters
			FamilyTreeNode mergedNode = nodeToBeMerged1.mergeWith(nodeToBeMerged2);

			//Remove merged clusters from total population
			removeMergedClusters(nodeToBeMerged1, nodeToBeMerged2);

			//Store distances to nodes not yet merged
			storeNewNodeDistances(mergedNode, orderedInterClusterDistances);

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

void FamilyTreeGraph::printChildrenAndThenSelf(std::shared_ptr<FamilyTreeNode> node) {


	if (node->getLeftChild() == std::shared_ptr<FamilyTreeNode>(nullptr)) {
		node->printNode();
		return;
	} else {
		printChildrenAndThenSelf(node->getLeftChild());
		printChildrenAndThenSelf(node->getRightChild());
	}

}

//Print the graph contents
void FamilyTreeGraph::printGraph() {

	FamilyTreeNode rootNode = this->graphNodes.back();
	printChildrenAndThenSelf(std::make_shared<FamilyTreeNode>(rootNode));

}

