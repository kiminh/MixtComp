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
 *  Created on: December 17, 2014
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "boost/regex.hpp"

#include "IO/mixt_IO.h"
#include "IO/mixt_SpecialStr.h"
#include "Various/mixt_Constants.h"
#include "LinAlg/mixt_LinAlg.h"
#include "Various/mixt_Enum.h"

#include "mixt_Categorical_pjk.h"

namespace mixt {

Categorical_pjk::Categorical_pjk(const std::string& idName,
                                 int nbClass,
                                 Vector<Real>& param,
                                 const Vector<std::set<Index> >& classInd) :
    idName_(idName),
    nbClass_(nbClass),
    nModality_(0),
    p_data_(0),
    param_(param),
    classInd_(classInd) {} // modalities are not known at the creation of the object, hence a call to setModality is needed later

Vector<bool> Categorical_pjk::acceptedType() const {
  Vector<bool> at(nb_enum_MisType_);
  at(0) = true ; // present_,
  at(1) = true ; // missing_,
  at(2) = true ; // missingFiniteValues_,
  at(3) = false; // missingIntervals_,
  at(4) = false; // missingLUIntervals_,
  at(5) = false; // missingRUIntervals_,
  return at;
}

int Categorical_pjk::computeNbFreeParameters() const {
  return nbClass_ * (nModality_ - 1);
}

void Categorical_pjk::mStep(EstimatorType bias) {
  for (Index k = 0; k < nbClass_; ++k) {
    Vector<Real> modalities(nModality_, 0.);

    for (std::set<Index>::const_iterator it = classInd_(k).begin(), itE = classInd_(k).end();
         it != itE;
         ++it) {
      modalities((*p_data_)(*it)) += 1.;
    }

    modalities = modalities / Real(classInd_(k).size());

    for (Index p = 0; p < nModality_; ++p) {
      param_(k * nModality_ + p) = modalities(p);
    }
  }

  if (bias == biased_) {
    for (Index k = 0; k < nbClass_; ++k) {
      for (Index p = 0; p < nModality_; ++p) {
        param_(k * nModality_ + p) = std::max(param_(k * nModality_ + p), epsilon                     );
        param_(k * nModality_ + p) = std::min(1. - epsilon              , param_(k * nModality_ + p)  );
      }
    }
  }
}

std::vector<std::string> Categorical_pjk::paramNames() const {
  std::vector<std::string> names(nbClass_ * nModality_);
  for (Index k = 0; k < nbClass_; ++k) {
    for (Index p = 0; p < nModality_; ++p) {
      std::stringstream sstm;
      sstm << "k: "
           << k + minModality
           << ", modality: "
           << p + minModality;
      names[k * nModality_ + p] = sstm.str();
    }
  }
  return names;
}

std::string Categorical_pjk::setData(std::string& paramStr,
                                     AugmentedData<Vector<int> >& augData) {
  std::string warnLog;

  p_data_ = &(augData.data_);

  if (paramStr.size() == 0) { // During learning without parameter space descriptor. Parameter space is deduced.
    nModality_ = augData.dataRange_.max_ + 1;
    param_.resize(nbClass_ * nModality_);

    std::stringstream sstm;
    sstm << "nModality: " << nModality_;
    paramStr = sstm.str(); // paramStr must be generated from the data, for future use and export for prediction
  }
  else { // During learning with parameter space descriptor, or in prediction
    std::string nModStr = std::string("nModality: *") + strPositiveInteger;
    boost::regex nModRe(nModStr);
    boost::smatch matchesVal;

    if (boost::regex_match(paramStr, matchesVal, nModRe)) { // value is present
      nModality_ = str2type<Index>(matchesVal[1].str());
    }
    else {
      std::stringstream sstm;
      sstm << "Variable: " << idName_ << " parameter string is not in the correct format, which should be \"nModality: x\" "
           << "with x the number of modalities in the variable." << std::endl;
      warnLog += sstm.str();
    }

    if (nModality_ <= augData.dataRange_.max_) { // check if the range of data is within the parameter space. As > 0 is checked systematically, here only the higher bound is checked
      std::stringstream sstm;
      sstm << "Variable: " << idName_ << " requires a maximum value of : " << nModality_ - 1 + minModality << " in either provided values or bounds. "
           << "The maximum currently provided value is : " << augData.dataRange_.max_ + minModality << std::endl;
      warnLog += sstm.str();
    }
  }

  if (augData.dataRange_.min_ < 0) { // Neither in learning nor in prediction are sub zero values valid
    std::stringstream sstm;
    sstm << "Variable: " << idName_ << " requires a minimum value of : " << minModality << " in either provided values or bounds. "
         << "The minimum value currently provided is : " << augData.dataRange_.min_ + minModality << std::endl;
    warnLog += sstm.str();
  }

  // Once everything has been set, adjust the range of data to align with the parameter space
  augData.dataRange_.min_ = 0;
  augData.dataRange_.max_ = nModality_ - 1;
  augData.dataRange_.range_ = nModality_;

  return warnLog;
}

void Categorical_pjk::writeParameters() const {
  std::stringstream sstm;
  for (Index k = 0; k < nbClass_; ++k) {
    sstm << "Class: " << k << std::endl;
    for (Index p = 0; p < nModality_; ++p) {
      sstm << "\talpha_ "  << p << ": " << param_(k * nModality_ + p) << std::endl;
    }
  }

  std::cout << sstm.str() << std::endl;
}

int Categorical_pjk::checkSampleCondition(std::string* warnLog) const {
  for (Index k = 0; k < nbClass_; ++k) {
    Vector<bool> modalityPresent(nModality_, false);
    for (std::set<Index>::const_iterator it  = classInd_(k).begin(),
                                         itE = classInd_(k).end();
         it != itE;
         ++it) {
      modalityPresent((*p_data_)(*it)) = true;
      if (modalityPresent == true) { // stop all checks on current class
        goto endItK;
      }
    }

    if (warnLog != NULL) {
      for (Index p = 0; p < nModality_; ++p) {
        if (modalityPresent(p) == false) {
          std::stringstream sstm;
          sstm << "Categorical variables must have one individual with each modality present in each class. "
               << "Modality: " << p << " is absent from class: " << k << " "
               << "You can check whether you have enough individuals regarding the number of classes "
               << "and whether all of your modalities are encoded using contiguous integers starting at 0." << std::endl;
          *warnLog += sstm.str();
        }
      }
    }

    return 0;

    endItK:;
  }

  return 1;
}


bool Categorical_pjk::hasModalities() const {
  return true;
}

} // namespace mixt
