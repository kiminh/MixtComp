/* MixtComp version 2.0  - 13 march 2017
 * Copyright (C) Inria - Lille 1 */

/*
 *  Project:    MixtComp
 *  Created on: December 12, 2014
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "PoissonSampler.h"
#include "../../mixt_IMixture.h"

namespace mixt
{
PoissonSampler::PoissonSampler(AugmentedData<Vector<int> >& augData,
                               const Vector<Real>& param,
                               int nbClass) :
    augData_(augData),
    param_(param) {}

void PoissonSampler::samplingStepNoCheck(int i, int z_i) {
  if (augData_.misData_(i).first != present_) {
    int x = 0;
    Real lambda = param_(z_i);

    switch(augData_.misData_(i).first) {
      case missing_: {
        x = poisson_.sample(lambda);
      }
      break;

      default: {
    	  throw("PoissonSampler::samplingStepNoCheck, error in missing data handling, please report to the maintainer.");
      }
      break;
    }

    augData_.data_(i) = x;
  }
}

} // namespace mixt