/* MixtComp version 4  - july 2019
 * Copyright (C) Inria - Université de Lille - CNRS*/

/*
 *  Project:    MixtComp
 *  Created on: June 29, 2017
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#ifndef RNG_H
#define RNG_H

#include <iostream>
#include <time.h>

#include <Various/Constants.h>

namespace mixt {

bool deterministicMode();

int deterministicInitialSeed();

template<class T>
std::size_t seed(const T* const p_caller) {
	static Index nCall = deterministicInitialSeed();

	if (deterministicMode() == false) {
		return size_t(p_caller) + time(0);
	} else {
		++nCall;
		//	std::cout << "seed, nCall: " << nCall << std::endl;
		return nCall;
	}
}

} // namespace mixt

#endif
