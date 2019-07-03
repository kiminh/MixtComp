/* MixtComp version 4  - july 2019
 * Copyright (C) Inria - Université de Lille - CNRS*/

/*
 *  Project:    MixtComp
 *  Created on: December 9, 2014
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#ifndef POISSONLIKELIHOOD_H
#define POISSONLIKELIHOOD_H

#include "../../../LinAlg/LinAlg.h"
#include "../../../Data/AugmentedData.h"
#include "PoissonStatistic.h"

namespace mixt
{

class PoissonLikelihood
{
  public:
    /** Constructor */
    PoissonLikelihood(const Vector<Real>& param,
                      const AugmentedData<Vector<int> >& augData,
                      int nbClass);

    /** Compute the completed log-likelihood */
    Real lnCompletedProbability(int i, int k) const;

    /** Compute the observed log-likelihood */
    Real lnObservedProbability(int i, int k) const;

  private:
    /** Pointer to parameters table */
    const Vector<Real>& param_;

    /** Pointer to AugmentedData, to get the lists of missing and partially observed values */
    const AugmentedData<Vector<int> >& augData_;

    /** Statistic object to describe Poisson law */
    PoissonStatistic poisson_;
};

} /* namespace mixt */

#endif // POISSONLIKELIHOOD_H
