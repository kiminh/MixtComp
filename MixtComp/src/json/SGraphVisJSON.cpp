/* MixtComp version 2.0  - 13 march 2017
 * Copyright (C) Inria - Lille 1 */

/*
 *  Project:    MixtComp
 *  Created on: Aug 6, 2018
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "SGraphVisJSON.h"

namespace mixt {

SGraphVisJSON::SGraphVisJSON(nlohmann::json& j, const std::string& payloadName) :
		j_(j), payloadName_(payloadName) {
}
;

void SGraphVisJSON::operator()(Index i) const {
	j_[payloadName_] = i;
}

void SGraphVisJSON::operator()(const Real r) const {
	j_[payloadName_] = r;
}

void SGraphVisJSON::operator()(const std::string& str) const {
	j_[payloadName_] = str;
}

void SGraphVisJSON::operator()(const NamedVector<Real>& vec) const {
	nlohmann::json res; // Since a vector is an union of fields, it is contained in its own json object

	Index ncol = vec.vec_.size();
	const double* rawData = vec.vec_.data();
	std::vector<Real> data(rawData, rawData + vec.vec_.size());

	res["colNames"] = vec.colNames_;
	res["data"] = data;
	res["dtype"] = std::string("Vector<Real>(") + std::to_string(ncol) + std::string(")");

	j_[payloadName_] = res;
}

void SGraphVisJSON::operator()(const NamedMatrix<Real>& mat) const {
	nlohmann::json res; // Since a matrix is an union of fields, it is contained in its own json object

	Index nrow = mat.mat_.rows();
	Index ncol = mat.mat_.cols();
	std::vector<std::vector<Real>> data(nrow, std::vector<Real>(ncol));

	for (Index i = 0; i < nrow; ++i) {
		for (Index j = 0; j < ncol; ++j) {
			data[i][j] = mat.mat_(i, j);
		}
	}

	res["colNames"] = mat.colNames_;
	res["rowNames"] = mat.rowNames_;
	res["data"] = data;
	res["dtype"] = std::string("Matrix<Real>(") + std::to_string(nrow) + std::string(",") + std::to_string(ncol) + std::string(")");

	j_[payloadName_] = res;
}

}