/* MixtComp version 4  - july 2019
 * Copyright (C) Inria - Université de Lille - CNRS*/

/*
 *  Project:    MixtComp
 *  Created on: January the 23rd, 2018
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "gtest/gtest.h"
#include "MixtComp.h"

using namespace mixt;

/**
 * Numerically check that pdf is the derivative of cdf, as per the definition. And that lpdf is correctly computed.
 * */
TEST(WeibullStatistic, DistributionFunctions) {
	Real k = 2.3;
	Real lambda = 0.9;
	Real obs = 3.0;

	WeibullStatistic weibull;

	Real cdf1 = weibull.cdf(obs + epsilon, k, lambda);
	Real cdf0 = weibull.cdf(obs, k, lambda);

	Real derivPDF = (cdf1 - cdf0) / epsilon;
	Real directPDF = weibull.pdf(obs, k, lambda);
	Real directLPDF = weibull.lpdf(obs, k, lambda);

	ASSERT_NEAR(derivPDF, directPDF, epsilon);
	ASSERT_NEAR(std::log(directPDF), directLPDF, epsilon);
}
