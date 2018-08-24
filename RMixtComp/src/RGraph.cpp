/* MixtComp version 2.0  - 13 march 2017
 * Copyright (C) Inria - Lille 1 */

/*
 *  Project:    MixtComp
 *  Created on: August 21, 2018
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "RGraph.h"

namespace mixt {

RGraph::RGraph(const Rcpp::List& l) :
		l_(l) {
}

void RGraph::set(const Rcpp::List& j) {
	l_ = j;
}

void RGraph::getSubGraph(const std::vector<std::string>& path, RGraph& j) const {
	Rcpp::List l;
	go_to(path, l);

	j.set(l);
}

bool RGraph::exist_payload(const std::vector<std::string>& path, const std::string& name) const {
	Rcpp::List l;
	go_to(path, l);

	if (Rf_isNull(l[name])) {
		return false;
	}

	return true;
}

void RGraph::go_to(const std::vector<std::string>& path, Rcpp::List& l) const {
	go_to(path, 0, l_, l);
}

void RGraph::go_to(const std::vector<std::string>& path, Index currDepth, const Rcpp::List& currLevel, Rcpp::List& l) const {
	if (currDepth == path.size()) {
		l = currLevel;
	} else {
		const Rcpp::List& nextLevel = currLevel[path[currDepth]];
		if (Rf_isNull(nextLevel)) { // if next level does not exist, create it
			std::string askedPath;
			for (Index i = 0; i < currDepth + 1; ++i) {
				askedPath + "/" + path[i];
			}
			throw(askedPath + " path does not exist.");
		}

		go_to(path, currDepth + 1, nextLevel, l);
	}
}

void RGraph::name_payload(const std::vector<std::string>& path, std::list<std::string>& l) const {
	Rcpp::List j;
	go_to(path, j);

	std::vector<std::string> v = j.names();
	std::copy(v.begin(), v.end(), std::back_inserter(l));
}

}
