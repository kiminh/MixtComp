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
 *  Created on: Mar 27, 2014
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include "mixt_CategoricalSampler.h"

namespace mixt
{
CategoricalSampler::CategoricalSampler(AugmentedData<STK::Array2D<int> >* p_augData,
                                       const STK::Array2D<STK::Real>* p_param) :
    p_augData_(p_augData),
    p_param_(p_param),
    p_zi_(0)
{}

CategoricalSampler::~CategoricalSampler()
{}

void CategoricalSampler::setZi(const STK::CArrayVector<int>* p_zi)
{
  p_zi_ = p_zi;
}

void CategoricalSampler::sampleIndividual(int i)
{
  // loop on missing variables
  for (AugmentedData<STK::Array2D<int> >::ConstIt_MisVar itVar = p_augData_->misData_.find(i)->second.begin(); // p_augData_->misData_.find(i)->(mapped element).(get iterator on variables)()
      itVar != p_augData_->misData_.find(i)->second.end();
      ++itVar)
  {
    int j = itVar->first;
    int sampleVal;
    int minModality = p_augData_->dataRanges_[j].min_;
    int nbModalities = p_augData_->dataRanges_[j].range_;
    int z_i = p_zi_->elt(i);

    switch(itVar->second.first) // (iterator on map)->(mapped element).(MisType)
    {
      case missing_:
      {
        STK::Array2DVector<STK::Real> modalities = (*p_param_)(STK::Range(z_i * nbModalities,
                                                                          nbModalities),
                                                               j);
        sampleVal = STK::Law::Categorical::rand(modalities) - z_i * nbModalities + minModality;
      }
      break;

      case missingFiniteValues_:
      {
        STK::Array2DVector<STK::Real> modalities(STK::Range(minModality,
                                                            nbModalities),
                                                 0.);
        STK::Array2DVector<STK::Real> equiModalities(STK::Range(minModality,
                                                                nbModalities),
                                                     0.);
        for(std::vector<int>::const_iterator currMod = itVar->second.second.begin(); // (iterator on map)->(mapped element).(vector of parameters)
            currMod != itVar->second.second.end();
            ++currMod)
        {
          modalities.elt(*currMod) = (*p_param_)(z_i * nbModalities + *currMod,
                                                 j);
          equiModalities.elt(*currMod) = 1.;
        }
        STK::Real modSum = modalities.sum();
        if (modSum < minStat)
        {
          equiModalities = equiModalities / equiModalities.sum();
          sampleVal = STK::Law::Categorical::rand(equiModalities);
        }
        else
        {
          modalities = modalities / modalities.sum();
          sampleVal = STK::Law::Categorical::rand(modalities);
        }
      }
      break;
    }
    p_augData_->data_(i, j) = sampleVal;
  }
}

} // namespace mixt
