/* MixtComp version 2.0  - 13 march 2017
 * Copyright (C) Inria - Lille 1 */

/*
 *  Project:    MixtComp
 *  Created on: August 3, 2018
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "gtest/gtest.h"
#include "mixt_MixtComp.h"

using namespace mixt;

/** Visitor to get value. */
TEST(SGraph, BasicIOVisitor) {
	SGraph test;

	std::string nameStr = "Quote";
	std::string testStr = "They shall not pass.";

	test.add_payload(nameStr, testStr);

	AlgType res = test.get_payload(nameStr);
	std::string resStr = boost::apply_visitor(SGraphVisPrint(), res);

	ASSERT_EQ(testStr, resStr);
}

/** Get to get value. */
TEST(SGraph, BasicIOGet) {
	SGraph test;

	std::string name = "Quote";
	Real val = 12.0;

	test.add_payload(name, val);

	AlgType resAlg = test.get_payload(name);
	Real res = boost::get<Real>(resAlg);

	ASSERT_NEAR(val, res, epsilon);
}