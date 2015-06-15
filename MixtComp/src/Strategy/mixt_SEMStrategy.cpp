/*--------------------------------------------------------------------*/
/*  Copyright (C) Inria 2013-2014

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 *  Project:    MixtComp
 *  Created on: Sept 3, 2013
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>,
 *              iovleff, serge.iovleff@stkpp.org
 **/

/** @file mixt_MixtureStrategy.cpp
 *  @brief In this file we implement the strategies for estimating mixture model.
 **/

#include "mixt_SEMStrategy.h"
#include "../Various/mixt_Timer.h"
#include "../IO/mixt_IO.h"
#include "../Various/mixt_Various.h"

namespace mixt
{

/** default constructor */
SemStrategy::SemStrategy(mixt::MixtureComposer* p_composer,
                         int nbTrialInInit_,
                         int nbBurnInIter,
                         int nbIter,
                         int nbGibbsBurnInIter,
                         int nbGibbsIter,
                         int nbSamplingAttempts) :
    p_composer_(p_composer),
    nbTrialInInit_(nbTrialInInit_),
    nbGibbsBurnInIter_(nbGibbsBurnInIter),
    nbGibbsIter_(nbGibbsIter),
    nbSamplingAttempts_(nbSamplingAttempts)
{
  p_burnInAlgo_ = new SEMAlgo(p_composer,
                              nbBurnInIter,
                              nbSamplingAttempts);
  p_longAlgo_   = new SEMAlgo(p_composer,
                              nbIter,
                              nbSamplingAttempts);
}

/** copy constructor */
SemStrategy::SemStrategy(SemStrategy const& strategy) :
    p_composer_(strategy.p_composer_),
    nbTrialInInit_(strategy.nbTrialInInit_),
    p_burnInAlgo_(strategy.p_burnInAlgo_),
    p_longAlgo_(strategy.p_longAlgo_)
{}

/** destructor */
SemStrategy::~SemStrategy()
{
  if (p_burnInAlgo_) delete p_burnInAlgo_;
  if (p_longAlgo_) delete p_longAlgo_;
}

std::string SemStrategy::run()
{
  std::string allWarn; // collect warning strings from all the trials

  for (int iterSample = 0; iterSample < nbSamplingAttempts_; ++iterSample) // sample until there are enough individuals per class, using default tik from IMixtureComposerBase::intializeMixtureParameters()
  {
#ifdef MC_DEBUG
    std::cout << "\titerSample: " << iterSample << std::endl;
#endif
    int nbIndPerClass = p_composer_->sStep();
    if (nbIndPerClass > minIndPerClass)
    {
      break; // enough individuals in each class to carry on
    }
    else
    {
      if (iterSample == nbSamplingAttempts_ - 1) // on last attempt, exit with error message
      {
        std::stringstream sstm;
        sstm << "Sampling step problem in SEM. The class with the lowest number "
             << "of individuals has " << nbIndPerClass << " individuals. Each class must have at least "
             << minIndPerClass << " individuals. There has been " << nbSamplingAttempts
             << " partition samplings before failure. The number of classes might be too important"
             << " relative to the number of individuals." << std::endl;
        return sstm.str();
      }
    }
  }
  p_composer_->removeMissing(); // complete missing values without using models (uniform samplings in most cases), as no mStep has been performed yet

  for (int iTry = 0; iTry < nbTrialInInit_; ++iTry)
  {
    std::string tryWarn; // warning for each run
#ifdef MC_DEBUG
  std::cout << "SemStrategy::run(), after randomClassInit()" << std::endl;
  std::cout << "*p_composer_->p_zi()" << std::endl;
  std::cout << *p_composer_->p_zi() << std::endl;
#endif
    tryWarn = p_composer_->mStep();
    if (tryWarn.size() > 0)
    {
      allWarn +=   std::string("SemStrategy, initialization mStep, iTry: ")
                 + type2str(iTry) + "\n"
                 + tryWarn; // append warning to global warning
      continue; // make another try
    }

#ifdef MC_DEBUG
    std::cout << "SemStrategy::run, burn-in" << std::endl;
#endif
    tryWarn = p_burnInAlgo_->run(burnIn_,
                                 0, // group
                                 3); // groupMax
    if (tryWarn.size() > 0) // an empty string means a successful run
    {
      allWarn +=   std::string("SemStrategy, burn-in, iTry: ")
                 + type2str(iTry) + "\n"
                 + tryWarn; // append warning to global warning
      continue; // make another try
    }

#ifdef MC_DEBUG
    std::cout << "SemStrategy::run, run" << std::endl;
#endif
    tryWarn = p_longAlgo_->run(run_,
                               1, // group
                               3); // groupMax
    if (tryWarn.size() > 0) // an empty string means a successful run
    {
      allWarn +=   std::string("SemStrategy, run, iTry: ")
                 + type2str(iTry) + "\n"
                 + tryWarn; // append warning to global warning
      continue; // make another try
    }
  
    Timer myTimer;
    myTimer.setName("Gibbs burn-in");
    for (int iterBurnInGibbs = 0; iterBurnInGibbs < nbGibbsBurnInIter_; ++iterBurnInGibbs)
    {
      myTimer.iteration(iterBurnInGibbs, nbGibbsBurnInIter_ - 1);
      writeProgress(2,
                    3,
                    iterBurnInGibbs,
                    nbGibbsBurnInIter_ - 1);
  #ifdef MC_DEBUG
      std::cout << "SemStrategy::run(), iterBurnInGibbs: " << iterBurnInGibbs << std::endl;
  #endif
      p_composer_->sStep();
      p_composer_->samplingStep();
      p_composer_->eStep();
    }

    p_composer_->gibbsSampling(nbGibbsIter_,
                               3, // group
                               3); // groupMax

    return allWarn; // if the last attempt is a success, consider the run a success. AllWarn is an empty string.
  }

  allWarn += "Number of initialization attempts exhausted. Try again with more initializations or other parameters.\n";
  return allWarn;
}

} // namespace mixt
