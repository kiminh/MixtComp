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
 *  Created on: July 2, 2014
 *  Authors:    Serge IOVLEFF <serge.iovleff@inria.fr>
 *              Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "mixt_MixtureComposer.h"
#include "../Mixture/mixt_IMixture.h"
#include "Arrays/include/STK_Display.h"
#include "Clustering/include/STK_Clust_Util.h"

namespace mixt
{

MixtureComposer::MixtureComposer( int nbSample, int nbVariable, int nbCluster)
                                : STK::IMixtureComposerBase( nbSample, nbVariable, nbCluster)
{}

MixtureComposer::MixtureComposer( MixtureComposer const& composer)
                                : STK::IMixtureComposerBase(composer)
                                , v_mixtures_(composer.v_mixtures_)
{
  // clone mixtures
  for (size_t l = 0; l < v_mixtures_.size(); ++l)
  {
    v_mixtures_[l] = composer.v_mixtures_[l]->clone();
    v_mixtures_[l]->setMixtureComposer(this);
    v_mixtures_[l]->initializeStep();
  }
}

MixtureComposer::~MixtureComposer()
{
  for (MixtIterator it = v_mixtures_.begin() ; it != v_mixtures_.end(); ++it)
  { delete (*it);}
}

/* clone pattern */
MixtureComposer* MixtureComposer::clone() const
{ return new MixtureComposer(*this);}

MixtureComposer* MixtureComposer::create() const
{
  // set dimensions
  MixtureComposer* p_composer = new MixtureComposer(nbSample(), nbVariable(), nbCluster());
  p_composer->createComposer( v_mixtures_);
  return p_composer;
}

STK::Real MixtureComposer::lnComponentProbability(int i, int k)
{
  STK::Real sum=0.0;
  for (ConstMixtIterator it = v_mixtures_.begin() ; it != v_mixtures_.end(); ++it)
  { sum += (*it)->lnComponentProbability(i,k);}
  return sum;
}

STK::Real MixtureComposer::lnObservedLikelihood()
{
  STK::Real lnLikelihood = 0.;
  STK::Array2D<STK::Real> lnComp(nbSample(), nbCluster_, 0.);
  for (int k = 0; k < nbCluster_; ++k)
  {
    for (ConstMixtIterator it = v_mixtures_.begin(); it != v_mixtures_.end(); ++it)
    {
      STK::Array2DVector<STK::Real> tempVec(lnComp.col(k), true);
      (*it)->lnObservedLikelihood(&tempVec, k);
      // (*it)->lnObservedLikelihood(&lnComp.col(k), k);
    }
  }

  // Compute the observed likelihood for the complete mixture model
  for (int i = 0; i < nbSample(); ++i)
  {
    STK::Real max = lnComp.row(i).maxElt();
    STK::Real sum = (lnComp.row(i) -= max).exp().dot(prop_);
    lnLikelihood += max + std::log(sum);
  }

  return lnLikelihood;
}

void MixtureComposer::mStep()
{
  for (MixtIterator it = v_mixtures_.begin() ; it != v_mixtures_.end(); ++it)
  { (*it)->paramUpdateStep();}
}

void MixtureComposer::writeParameters(std::ostream& os) const
{
  stk_cout << _T("Composer lnLikelihood = ") << lnLikelihood() << std::endl;
  stk_cout << _T("Composer nbFreeParameter = ") << this->nbFreeParameter() << std::endl;
  stk_cout << _T("Composer proportions = ") << *(this->p_pk()) << std::endl;

  for (ConstMixtIterator it = v_mixtures_.begin(); it != v_mixtures_.end(); ++it)
  {
    stk_cout << _T("Parameters of the mixtures:") << (*it)->idName() << _T("\n");
    (*it)->writeParameters(os);
  }
}

void MixtureComposer::initializeStep()
{
  if (v_mixtures_.size() == 0)
    std::cout << "MixtureComposer::initializeStep, no mixture have been registered" << std::endl;
  // compute number of free parameters
  setNbFreeParameter(computeNbFreeParameters());
  // compute proportions
  pStep();
#ifdef MC_DEBUG
  std::cout << "MixtureComposer::initializeStep() called on " << v_mixtures_.size() << " mixtures" << std::endl;
#endif
  for (MixtIterator it = v_mixtures_.begin(); it != v_mixtures_.end(); ++it)
  {
#ifdef MC_DEBUG
    std::cout << "(*it)->idName(): " << (*it)->idName() << std::endl;
    try
    {
#endif
      (*it)->initializeStep();
#ifdef MC_DEBUG
    }
    catch (STK::Clust::exceptions exception)
    {
      if (exception == STK::Clust::initializeStepFail_)
        std::cout << "STK mixture initialization failed" << std::endl;
    }
#endif
  }
  setState(STK::Clust::modelInitialized_);
}

void MixtureComposer::randomInit()
{
  for (MixtIterator it = v_mixtures_.begin(); it != v_mixtures_.end(); ++it)
  { (*it)->randomInit();}
}


// implement computeNbFreeParameters
int MixtureComposer::computeNbFreeParameters() const
{
  int sum = nbCluster_-1; // proportions
  for (ConstMixtIterator it = v_mixtures_.begin(); it != v_mixtures_.end(); ++it)
  { sum+= (*it)->nbFreeParameter();}
  return sum;
}

void MixtureComposer::imputationStep()
{
  for (MixtIterator it = v_mixtures_.begin(); it != v_mixtures_.end(); ++it)
  { (*it)->imputationStep();}
}

/* @brief Simulation of all the latent variables and/or missing data
 *  excluding class labels.
 */
void MixtureComposer::samplingStep()
{
  for (MixtIterator it = v_mixtures_.begin(); it != v_mixtures_.end(); ++it)
  { (*it)->samplingStep();}
}

void MixtureComposer::storeIntermediateResults(int iteration)
{
  for (MixtIterator it = v_mixtures_.begin(); it != v_mixtures_.end(); ++it)
  {
    (*it)->storeIntermediateResults(iteration);
  }
}

void MixtureComposer::storeData()
{
  for (MixtIterator it = v_mixtures_.begin(); it != v_mixtures_.end(); ++it)
  {
    (*it)->storeData();
  }
}

void MixtureComposer::exportDataParam() const
{
  for (ConstMixtIterator it = v_mixtures_.begin(); it != v_mixtures_.end(); ++it)
  {
    (*it)->exportDataParam();
  }
}

void MixtureComposer::finalizeStep()
{
  for (size_t l = 0; l < v_mixtures_.size(); ++l)
  { v_mixtures_[l]->finalizeStep();}
}

/* register the mixture in the composer*/
void MixtureComposer::registerMixture(IMixture* p_mixture)
{
  p_mixture->setMixtureComposer(this);
  v_mixtures_.push_back(p_mixture);
}

/* @brief Create the composer using existing data handler and ingredients.
 * This method is essentially used by the create() method and can be
 * reused in derived classes. */
void MixtureComposer::createComposer( std::vector<IMixture*> const& v_mixtures)
{
  intializeMixtureParameters();
  v_mixtures_.resize( v_mixtures.size());
  for (size_t l = 0; l < v_mixtures_.size(); ++l)
  {
    v_mixtures_[l] = v_mixtures[l]->create();
    v_mixtures_[l]->setMixtureComposer(this);
    v_mixtures_[l]->initializeStep();
  }
}

} /* namespace mixt */