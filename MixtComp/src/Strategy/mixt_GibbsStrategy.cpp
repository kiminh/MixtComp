/*--------------------------------------------------------------------*/
/*  Copyright (C) Inria 2014

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
 *  Created on: Nov 11, 2014
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>,
 **/

#include "mixt_GibbsStrategy.h"
#include "../Various/mixt_Timer.h"
#include "../Various/mixt_Various.h"

namespace mixt
{

/** default constructor */
GibbsStrategy::GibbsStrategy(MixtureComposer* p_composer,
                             int nbBurnInIterGibbs,
                             int nbIterGibbs) :
    p_composer_(p_composer),
    nbBurnInIterGibbs_(nbBurnInIterGibbs),
    nbIterGibbs_(nbIterGibbs)
{}

std::string GibbsStrategy::run()
{
  std::string warnLog;
#ifdef MC_DEBUG
  std::cout << "SemStrategy::run(), after randomClassInit()" << std::endl;
  std::cout << "*p_composer_->p_zi()" << std::endl;
  std::cout << *p_composer_->p_zi() << std::endl;
#endif

  p_composer_->sStepNoCheck(); // class of each individual is sampled using the apriori proportions, no condition has to be verified on the sample
  p_composer_->removeMissing(Gibbs_);

  Timer myTimer;
  myTimer.setName("Gibbs: burn-in");
  for (int iterBurnInGibbs = 0; iterBurnInGibbs < nbBurnInIterGibbs_; ++iterBurnInGibbs)
  {
    myTimer.iteration(iterBurnInGibbs, nbBurnInIterGibbs_ - 1);
    writeProgress(0, // group
                  1, // groupMax
                  iterBurnInGibbs,
                  nbBurnInIterGibbs_); // progress write in progress file
#ifdef MC_DEBUG
    std::cout << "GibbsStrategy::run(), iterBurnInGibbs: " << iterBurnInGibbs << std::endl;
#endif
    p_composer_->eStep();
    p_composer_->sStepNoCheck();
    p_composer_->samplingStepNoCheck();
  }

  p_composer_->gibbsSampling(nbIterGibbs_,
                             1, // group
                             1); // groupMax

#ifdef MC_DEBUG
  p_composer_->lnObservedLikelihoodDebug();
#endif

  return warnLog;
}

} // namespace mixt
