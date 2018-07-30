/* MixtComp version 2.0  - 13 march 2017
 * Copyright (C) Inria - Lille 1 */

/*
 *  Project:    MixtComp
 *  Created on: July 19, 2018
 *  Authors:    Quentin GRIMONPREZ <quentin.grimonprez@inria.fr>
 **/

#include "../UTest.h"

using namespace mixt;

/**
 * Numerically check that lpdf is the log of pdf
 * */
TEST(NegativeBinomialStatistic, DistributionFunctions) {
	Real n = 10.5;
	Real p = 0.6;
	size_t obs = 3;

	NegativeBinomialStatistic nBinom;

	Real lpdf0 = std::log(nBinom.pdf(obs, n, p));
	Real lpdf1 = nBinom.lpdf(obs, n, p);

	EXPECT_NEAR(lpdf0, lpdf1, epsilon);


	// case p == 1
	Real pdf0 = nBinom.pdf(0, n, 1.);
	lpdf0 = nBinom.lpdf(0, n, 1.);

	EXPECT_EQ(pdf0, 1.);
	EXPECT_EQ(lpdf0, 0.);

	Real pdf1 = nBinom.pdf(obs, n, 1.);
	lpdf1 = nBinom.lpdf(obs, n, 1.);

	EXPECT_EQ(pdf1, 0.);
	EXPECT_EQ(lpdf1, minInf);

	// case p == 0
	pdf0 = nBinom.pdf(0, n, 0.);
	lpdf0 = nBinom.lpdf(0, n, 0.);

	EXPECT_EQ(pdf0, 0.);
	EXPECT_EQ(lpdf0, minInf);

	pdf1 = nBinom.pdf(obs, n, 0.);
	lpdf1 = nBinom.lpdf(obs, n, 0.);

	EXPECT_EQ(pdf1, 0.);
	EXPECT_EQ(lpdf1, minInf);

}
