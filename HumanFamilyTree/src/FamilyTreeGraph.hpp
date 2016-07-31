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

#include <vector>

class FamilyTreeGraph {

private:

	std::vector<MitochondrialDnaSample> totalPopulation;

	//Run Hierarchical Clustering using UPGMA (Unweighted Pair Group Method with Arithmetic Mean)
	void runHierarchicalClustering();

public:

	//Constructor
	FamilyTreeGraph(std::vector<MitochondrialDnaSample> totalPopulation);

};


#endif /* FAMILYTREEGRAPH_HPP_ */
