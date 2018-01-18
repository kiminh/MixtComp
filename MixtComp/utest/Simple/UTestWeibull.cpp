/* MixtComp version 2.0  - 13 march 2017
 * Copyright (C) Inria - Lille 1 */

/*
 *  Project:    MixtComp
 *  Created on: 15th of January, 2018
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "../UTest.h"

using namespace mixt;

/**
 * Estimation of k using Newton-Raphson.
 */
TEST(Weibull, EstimateK) {
	Index nObs = 100000;

	Real kExpected = 1.5;

	WeibullStatistic weib;
	Weibull w;

	Vector<Real> x(nObs);
	for (Index i = 0; i < nObs; ++i) {
		x(i) = weib.sample(1.0, kExpected);
	}

	Real kComputed = w.positiveNewtonRaphson(x, 10.0, 10);

	ASSERT_NEAR(kExpected, kComputed, 0.01);
}
