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
 *  Created on: December 9, 2014
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "mixt_PoissonLikelihood.h"
#include "../Various/mixt_Def.h"
#include "../LinAlg/mixt_LinAlg.h"

namespace mixt
{

PoissonLikelihood::PoissonLikelihood(const Vector<Real>* p_param,
                                     const AugmentedData<Matrix<int> >* augData,
                                     const Matrix<RowVector<int> >* p_dataStatStorage,
                                     int nbClass) :
    p_param_(p_param),
    p_augData_(augData),
    p_dataStatStorage_(p_dataStatStorage)
{}

PoissonLikelihood::~PoissonLikelihood()
{}

void PoissonLikelihood::lnCompletedLikelihood(Vector<Real>* lnComp, int k)
{
#ifdef MC_DEBUG
   std::cout << "PoissonLikelihood::lnCompletedLikelihood" << std::endl;
   std::cout << "\t(*p_param_): " << (*p_param_) << std::endl;
#endif
  // likelihood for present data

  Real lambda = (*p_param_)(k, 0);
  Real proba;

  for (int i = 0; i < p_augData_->data_.rows(); ++i)
  {
    if (p_augData_->misData_(i, 0).first == present_)   // likelihood for present value
    {
      proba = poisson_.pdf(p_augData_->data_(i, 0),
                           lambda);
    }
    else // likelihood for missing values, imputation by the expectation (temporary placeholder ...)
    {
      proba = poisson_.pdf((*p_dataStatStorage_)(i, 0)[0],
                           lambda);
    }
    (*lnComp)(i) += std::log(proba);
  }
}

void PoissonLikelihood::lnObservedLikelihood(Vector<Real>* lnComp, int k)
{
#ifdef MC_DEBUG
      std::cout << "PoissonLikelihood::lnObservedLikelihood" << std::endl;
      std::cout << "\t(*p_param_): " << (*p_param_) << std::endl;
#endif
  // likelihood for present data
  for (int i = 0; i < p_augData_->data_.rows(); ++i)
  {
    Real lambda = (*p_param_)(k, 0);
    Real proba;

    switch(p_augData_->misData_(i, 0).first)   // likelihood for present value
    {
      case present_:
      {
        proba = poisson_.pdf(p_augData_->data_(i, 0),
                             lambda);
      }
      break;

      case missing_: // no contribution to the observed likelihood
      {
#ifdef MC_DEBUG
        std::cout << "\tmissing" << std::endl;
#endif
        proba = 1.;
      }
      break;

      default:
      {}
      break;
    }
    (*lnComp)(i) += std::log(proba);

#ifdef MC_DEBUG
    std::cout << "\tproba: " << proba << std::endl;
#endif
  }
}

} /* namespace mixt */
