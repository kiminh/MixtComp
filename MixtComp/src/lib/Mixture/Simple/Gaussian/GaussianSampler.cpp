/* MixtComp version 4  - july 2019
 * Copyright (C) Inria - Université de Lille - CNRS*/

/*
 *  Project:    MixtComp
 *  Created on: Feb 18, 2014
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include <Mixture/IMixture.h>
#include "GaussianSampler.h"

namespace mixt
{
GaussianSampler::GaussianSampler(AugmentedData<Vector<Real> >& augData,
                                 const Vector<Real>& param,
                                 int nbClass) :
    augData_(augData),
    param_(param)
{}

void GaussianSampler::samplingStepNoCheck(int i,
                                          int z_i) {
  if (augData_.misData_(i).first != present_) {
    Real z = 0.;
    Real mean  = param_(2 * z_i    );
    Real sd    = param_(2 * z_i + 1);

    switch(augData_.misData_(i).first) {
      case missing_: {
        z = normal_.sample(mean,
                           sd);
      }
      break;

      case missingIntervals_: {
        Real infBound = augData_.misData_(i).second[0];
        Real supBound = augData_.misData_(i).second[1];

        z = normal_.sampleI(mean,
                            sd,
                            infBound,
                            supBound);
      }
      break;

      case missingLUIntervals_: { // missingLUIntervals
        Real supBound = augData_.misData_(i).second[0];
        z = normal_.sampleSB(mean,
                             sd,
                             supBound);
      }
      break;

      case missingRUIntervals_: { // missingRUIntervals
        Real infBound = augData_.misData_(i).second[0];
        z = normal_.sampleIB(mean,
                             sd,
                             infBound);
      }
      break;

      default: {
    	  throw("GaussianSampler::samplingStepNoCheck, error in missing data handling, please report to the maintainer.");
      }
      break;
    }

    augData_.data_(i) = z;
  }
}

} // namespace mixt
