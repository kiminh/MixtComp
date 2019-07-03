/* MixtComp version 4  - july 2019
 * Copyright (C) Inria - Université de Lille - CNRS*/

/*
 *  Project:    MixtComp
 *  Created on: 17th of January, 2018
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#ifndef WEIBULL_H
#define WEIBULL_H

#include <Data/AugmentedData.h>
#include <LinAlg/LinAlg.h>
#include <set>
#include <utility>

#include "Data/ConfIntDataStat.h"
#include "WeibullLikelihood.h"
#include "WeibullSampler.h"

namespace mixt {

/**
 * https://en.wikipedia.org/wiki/Weibull_distribution
 * Inspired by the code: https://github.com/vkubicki/ScalaTest/tree/master/src/main/scala/p02Statistics
 */
class Weibull {

public:
	static const std::string name;

	typedef Vector<Real> Data;
	typedef ConfIntDataStat<Real> DataStat;
	typedef WeibullSampler Sampler;
	typedef WeibullLikelihood Likelihood;

	Weibull(const std::string& idName, Index nbClass, Vector<Real>& param);

	/**
	 * Evaluate both the value and derivative of the residue of the equation verified by k.
	 */
	std::pair<Real, Real> evalFuncDeriv(const Vector<Real>& x, Real k) const;


	/**
	 * Data is passed as an argument to emphasize a functional approach and easier testing.
	 */
	Real estimateK(const Vector<Real>& x, Real k0) const;

	Real estimateLambda(const Vector<Real>& x, Real k) const;

	Vector<bool> acceptedType() const;

	Index computeNbFreeParameters() const;

	bool hasModalities() const;

	std::string setData(const std::string& paramStr,
			AugmentedData<Vector<Real> >& augData, RunMode mode);

	std::string mStep(const Vector<std::set<Index>>& classInd);

	std::vector<std::string> paramNames() const;

	void writeParameters() const;

	std::string checkSampleCondition(
			const Vector<std::set<Index>>& classInd) const;

	/**
	 * The idea is to initialize the distribution in each class with the parameters lambda = 1, and a suitable value of k
	 * so that the median of the distribution equals the representative observation for this class.
	 * Formulae to be found here: https://en.wikipedia.org/wiki/Weibull_distribution
	 * Median is easier to invert for Weibull than mean.
	 */
	void initParam();

private:
	std::string idName_;

	Index nClass_;

	Vector<Real>& param_; // storage is linear, k0, lambda0, k1, lambda1, k2, lambda2, ...

	Vector<Real>* p_data_;
};

}

#endif
