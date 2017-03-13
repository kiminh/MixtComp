/* MixtComp version 2.0  - 13 march 2017
 * Copyright (C) Inria - Lille 1 */

/*
 *  Project:    MixtComp
 *  Created on: August 7, 2014
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>,
 **/

#ifndef MIXT_CONSTANTS_H_
#define MIXT_CONSTANTS_H_

#include "../LinAlg/mixt_LinAlg.h" // for the definition of Real type

namespace mixt {

extern const int nbSamplingAttempts; // number of sampling attempts, when not enough individuals are sampled

extern const Real epsilon; // very small value of real to check for near zero values
extern const Real logEpsilon; // log of very small value

extern const int minModality; // minimal modality for categorical models (for example, 0-based or 1-based numbering)
extern const int minIndex;
extern const Real pi; // pi
extern const Real l2pi; // constant used in pdf computation for normal law
extern const std::string progressFile; // progress file name
extern const Real minInf; // value of log(0)

extern const int sizeTupleBOS; // default size of tuple for Gibbs sampling in BOS model
extern const int nbGibbsIniBOS; // number of Gibbs sampling rounds in initialization to increase variability on z
extern const Real piInitBOS; // value of pi used in Gibbs used in initialization
extern const Real piInitISR; // value of pi used in ISR initialization
extern const Real piThreshold; //threashold on pi to detect degeneracy

extern const int nbGibbsIterRank; // number of iterations in the Gibbs used in the estimation of mu

extern const int nbSampleObserved; // number of sample per class to estimate the observed probability, for example in Ordinal or Rank data

extern const std::string rankPosSep; // separator used in Rank positions

} // namespace mixt

#endif /* MIXT_CONSTANTS_H_ */
