/* MixtComp version 2.0  - 13 march 2017
 * Copyright (C) Inria - Lille 1 */

/*
 *  Project:    MixtComp
 *  Created on: December 16, 2014
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#ifndef MIXT_UNIFORMSTATISTIC_H
#define MIXT_UNIFORMSTATISTIC_H

#include "../LinAlg/mixt_LinAlg.h"
#include <boost/random/mersenne_twister.hpp>

namespace mixt
{

class UniformStatistic
{
  public:
    UniformStatistic();

    /** cdf evaluated at individual x */
    Real cdf(Real x,
             Real min,
             Real max) const;

    /** pdf evaluated at individual x */
    Real pdf(Real x,
             Real min,
             Real max) const;

    /**
     * Sample a Real from a uniform distribution
     * @param min lower bound of the support
     * @param max higher bound of the support
     * @return Real uniformly sampled from [low:high]
     */
    Real sample(Real min,
                Real max);
  private:
    /** Random number generator */
    boost::random::mt19937 rng_;
};

} // namespace mixt

#endif // MIXT_UNIFORMSTATISTIC_H
