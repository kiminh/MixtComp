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
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 *              iovleff, serge.iovleff@stkpp.org
 **/

#ifndef MIXT_CATEGORICALSAMPLER_H
#define MIXT_CATEGORICALSAMPLER_H

#include "stkpp/projects/Arrays/include/STK_Array2D.h"

#include "../Data/mixt_AugmentedData.h"
#include "mixt_CategoricalSamplerIterator.h"

namespace mixt
{

class CategoricalSampler
{
  public:
    CategoricalSampler(const AugmentedData<STK::Array2D<int> >* pm_augDataij,
                       const STK::Array2D<STK::Real>* p_param);
    CategoricalSampler(const CategoricalSampler& sampler);
    ~CategoricalSampler();
    CategoricalSamplerIterator begin() const;
    CategoricalSamplerIterator end() const;
    void setZi(const STK::CArrayVector<int>* p_zi);
  private:
    const AugmentedData<STK::Array2D<int> >* pm_augDataij_;
    const STK::Array2D<STK::Real>* p_param_;
    const STK::CArrayVector<int>* p_zi_;
};

} // namespace mixt

#endif /* MIXT_CATEGORICALSAMPLER_H */