/* MixtComp version 4  - july 2019
 * Copyright (C) Inria - Université de Lille - CNRS*/

/*
 *  Project:    MixtComp
 *  Created on: 18th of January, 2018
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "WeibullStatistic.h"
#include <boost/math/distributions/weibull.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/weibull_distribution.hpp>
#include <Statistic/RNG.h>

namespace mixt {

WeibullStatistic::WeibullStatistic() :
		rng_(seed(this)) {
}

Real WeibullStatistic::quantile(Real k, Real lambda, Real p) const {
	boost::math::weibull weib(k, lambda);
	Real x = boost::math::quantile(weib, p);
	return x;
}

Real WeibullStatistic::quantileIB(Real k, Real lambda, Real infBound, Real p) const {
	Real u = (1.0 - p) * cdf(infBound, k, lambda) + p;
	return quantile(k, lambda, u);
}


Real WeibullStatistic::quantileI(Real k, Real lambda, Real infBound, Real supBound, Real p) const {
	Real u = p * cdf(supBound, k, lambda) + (1.0 - p) * cdf(infBound, k, lambda);
	return quantile(k, lambda, u);
}

Real WeibullStatistic::sample(Real k, Real lambda) {
	boost::random::weibull_distribution<> w(k, lambda);
	boost::variate_generator<boost::mt19937&,
			boost::random::weibull_distribution<> > generator(rng_, w);
	return generator();
}

Real WeibullStatistic::sampleIB(Real k, Real lambda, Real infBound) {
	Real u = uniform_.sample(0., 1.);
	return quantileIB(k, lambda, infBound, u);
}

Real WeibullStatistic::sampleI(Real k, Real lambda, Real infBound, Real supBound) {
	Real u = uniform_.sample(0., 1.);
	return quantileI(k, lambda, infBound, supBound, u);
}

Real WeibullStatistic::pdf(Real x, Real k, Real lambda) const {
	boost::math::weibull weib(k, lambda);
	Real proba = boost::math::pdf(weib, x);
	return proba;
}

Real WeibullStatistic::lpdf(Real x, Real k, Real lambda) const {
	Real logLambda = std::log(lambda);
	return std::log(k) - logLambda + (k - 1.0) * (std::log(x) - logLambda)
			- std::pow(x / lambda, k);
}

Real WeibullStatistic::cdf(Real x, Real k, Real lambda) const {
	return 1.0 - std::exp(-std::pow(x / lambda, k));
}

Real WeibullStatistic::cdfIB(Real x, Real k, Real lambda, Real infBound) const {
	Real cdfIB = cdf(infBound, k, lambda);
	return (cdf(x, k, lambda) - cdfIB) / (1.0 - cdfIB);
}

Real WeibullStatistic::lcdf(Real x, Real k, Real lambda) const {
	return std::log(cdf(x, k, lambda));
}

}
