/* MixtComp version 2.0  - 13 march 2017
 * Copyright (C) Inria - Lille 1 */

/*
 *  Project:    MixtComp
 *  Created on: August 21, 2018
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#ifndef JSON_CPPTOJSONTRANSLATE_H
#define JSON_CPPTOJSONTRANSLATE_H

#include <IO/NamedAlgebra.h>
#include "json.hpp"

#include <iostream>
#include <LinAlg/mixt_LinAlg.h>
#include <LinAlg/names.h>

namespace mixt {

template<typename InType>
void CPPToJSONTranslate(const InType& in, nlohmann::json& out) {
	out = in;
}

template<typename T>
void CPPToJSONTranslate(const NamedVector<T>& in, nlohmann::json& out) {
	Index nrow = in.vec_.size();
	const T* rawData = in.vec_.data();
	std::vector<T> data(rawData, rawData + in.vec_.size());

	out["ctype"] = "Vector";
	out["data"] = data;
	out["dtype"] = names<T>::name;
	out["rowNames"] = in.rowNames_;
	out["nrow"] = nrow;
}

template<typename T>
void CPPToJSONTranslate(const NamedMatrix<T>& in, nlohmann::json& out) {
	Index nrow = in.mat_.rows();
	Index ncol = in.mat_.cols();
	std::vector<std::vector<T>> data(nrow, std::vector<Real>(ncol));

	for (Index i = 0; i < nrow; ++i) {
		for (Index j = 0; j < ncol; ++j) {
			data[i][j] = in.mat_(i, j);
		}
	}

	out["colNames"] = in.colNames_;
	out["ctype"] = "Matrix";
	out["data"] = data;
	out["dtype"] = names<T>::name;
	out["rowNames"] = in.rowNames_;
	out["ncol"] = ncol;
	out["nrow"] = nrow;
}

//template<typename T>
//void JSONTranslate(const std::vector<std::vector<T>>& in, nlohmann::json& out) {
//	std::cout << "JSONTranslate(const std::vector<std::vector<T>>& in, nlohmann::json& out)" << std::endl;
//	out.
//}

/**
 * Specialization necessary to remove ambiguity on the = operator used for vector.
 */
//template<>
//void JSONTranslate(const nlohmann::json& in, std::vector<std::string>& out);
//
//}
}

#endif
