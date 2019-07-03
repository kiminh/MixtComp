/* MixtComp version 4  - july 2019
 * Copyright (C) Inria - Université de Lille - CNRS*/

/*
 *  Project:    MixtComp
 *  Created on: July 19, 2018
 *  Authors:    Quentin GRIMONPREZ <quentin.grimonprez@inria.fr>
 **/

#include <Mixture/IMixture.h>
#include "NegativeBinomialSampler.h"

namespace mixt
{
NegativeBinomialSampler::NegativeBinomialSampler(AugmentedData<Vector<int> >& augData,
                               const Vector<Real>& param,
                               int nbClass) :
    augData_(augData),
    param_(param) {}

void NegativeBinomialSampler::samplingStepNoCheck(int i, int z_i) {
  if (augData_.misData_(i).first != present_) {
    int x = 0;
    Real n = param_(2 * z_i);
    Real p = param_(2 * z_i + 1);

    switch(augData_.misData_(i).first) {
      case missing_: {
        x = negativeBinomial_.sample(n, p);
      }
      break;

	  case missingRUIntervals_: {
	    x = negativeBinomial_.sampleIB(n, p, augData_.misData_(i).second[0]);
	  }
	  break;

	  case missingIntervals_: {
	    x = negativeBinomial_.sampleI(n, p, augData_.misData_(i).second[0], augData_.misData_(i).second[1]);
	  }
	  break;

	  default: {
    	  throw("NegativeBinomialSampler::samplingStepNoCheck, error in missing data handling, please report to the maintainer.");
      }
      break;
    }

    augData_.data_(i) = x;
  }
}

} // namespace mixt
