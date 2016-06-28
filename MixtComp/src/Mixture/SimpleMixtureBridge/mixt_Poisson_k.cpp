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
 *  Created on: December 12, 2014
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "mixt_Poisson_k.h"
#include "../../IO/mixt_IO.h"
#include "../../Various/mixt_Constants.h"
#include "../../Various/mixt_Enum.h"

namespace mixt {

Poisson_k::Poisson_k(const std::string& idName,
                     int nbClass,
                     Vector<Real>& param,
                     const Vector<std::set<Index> >& classInd) :
    idName_(idName),
    nbClass_(nbClass),
    param_(param),
    p_data_(0),
    classInd_(classInd) {
  param_.resize(nbClass);
}

Vector<bool> Poisson_k::acceptedType() const {
  Vector<bool> at(nb_enum_MisType_);
  at(0) = true; // present_,
  at(1) = true;// missing_,
  at(2) = false;// missingFiniteValues_,
  at(3) = false;// missingIntervals_,
  at(4) = false;// missingLUIntervals_,
  at(5) = false;// missingRUIntervals_,
  return at;
}

int Poisson_k::computeNbFreeParameters() const {
  return nbClass_;
}

bool Poisson_k::hasModalities() const {
  return false;
}

void Poisson_k::mStep(EstimatorType bias) {
  for (int k = 0; k < nbClass_; ++k) {
    Real sumClass = 0.;
    for (std::set<Index>::const_iterator it = classInd_(k).begin(), itE = classInd_(k).end();
         it != itE;
         ++it) {
      sumClass += (*p_data_)(*it);
    }

    param_(k) = sumClass / Real(classInd_(k).size());
  }

  if (bias == biased_) {
    for (int k = 0; k < nbClass_; ++k) {
      param_(k) = std::max(epsilon, param_(k));
    }
  }
}

std::vector<std::string> Poisson_k::paramNames() const {
  std::vector<std::string> names(nbClass_);
  for (int k = 0; k < nbClass_; ++k) {
    std::stringstream sstm;
    sstm << "k: "
         << k + minModality
         << ", lambda";
    names[k] = sstm.str();
  }
  return names;
}

std::string Poisson_k::setData(const std::string& paramStr,
                               AugmentedData<Vector<int> >& augData) {
  std::string warnLog;

  p_data_ = &(augData.data_);

  if (augData.dataRange_.min_ < 0) {
    std::stringstream sstm;
    sstm << "Variable: " << idName_ << " requires a minimum value of : " << minModality << " in either provided values or bounds. "
         << "The minimum value currently provided is : " << augData.dataRange_.min_ + minModality << std::endl;
    warnLog += sstm.str();
  }

  return warnLog;
}

void Poisson_k::writeParameters() const {
  std::stringstream sstm;
  for (int k = 0; k < nbClass_; ++k) {
    sstm << "Class: " << k << std::endl;
    sstm << "\tlambda: " << param_[k] << std::endl;
  }

  std::cout << sstm.str() << std::endl;
}

int Poisson_k::checkSampleCondition(std::string* warnLog) const {
  for (int k = 0; k < nbClass_; ++k) {
    for (std::set<Index>::const_iterator it = classInd_(k).begin(), itE = classInd_(k).end();
         it != itE;
         ++it) {
      if ((*p_data_)(*it) > 0) {
        goto endItK;
      }
    }

    if (warnLog != NULL) {
      std::stringstream sstm;
      sstm << "Poisson variables must have at least one non-zero individual per class. At least one class "
           << "only contains the 0 modality. If your data has too many individuals "
           << "with a value of 0, a Poisson model can not describe it." << std::endl;
      *warnLog += sstm.str();
    }

    return 0;

    endItK:;
  }

  return 1;
}

} // namespace mixt
