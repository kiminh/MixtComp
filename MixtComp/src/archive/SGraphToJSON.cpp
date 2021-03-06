/* MixtComp version 2.0  - 13 march 2017
 * Copyright (C) Inria - Lille 1 */

/*
 *  Project:    MixtComp
 *  Created on: Aug 3, 2018
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include <AlgTypeVisJSON.h>
#include <iostream>
#include <map>

#include "json.hpp"

#include "JSONToSGraph.h"

namespace mixt {

nlohmann::json SGraphToJSON(const SGraph& graph) {
	nlohmann::json res;

	const std::map<std::string, AlgType>& payload = graph.get_payload();
	for (std::map<std::string, AlgType>::const_iterator it = payload.begin(),
			itEnd = payload.end(); it != itEnd; ++it) {
		const std::pair<std::string, AlgType>& val = *it;

		boost::apply_visitor(AlgTypeVisJSON(res, val.first), val.second);
	}

	const std::map<std::string, SGraph>& children = graph.get_children();
	for (std::map<std::string, SGraph>::const_iterator it = children.begin(),
			itEnd = children.end(); it != itEnd; ++it) {
		const std::pair<std::string, SGraph>& val = *it;
		res[val.first] = SGraphToJSON(val.second);
	}

	return res;
}

}
