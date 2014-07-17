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
 *  Created on: July 1, 2014
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#ifndef MIXT_CATEGORICALDATASTAT_H
#define MIXT_CATEGORICALDATASTAT_H

#include "Arrays/include/STK_Array2D.h"
#include "mixt_AugmentedData.h"

namespace mixt
{

typedef std::pair<int, int> pos;
typedef typename std::vector<          pos                        >::const_iterator iv_missing;
typedef typename std::vector<std::pair<pos, std::vector<int>    > >::const_iterator iv_missingFiniteValues;

class CategoricalDataStat
{
  public:
    CategoricalDataStat(const AugmentedData<STK::Array2D<int> >* pm_augDataij);
    ~CategoricalDataStat();
    void initPos();
    void initialize();
    void setModalities();
    void sampleVals();
    void exportVals(STK::Array2D<int>& posMissing, STK::Array2D<STK::Real>& statMissing) const;
  private:
    // number of iterations used to compute the statistics
    int nbIter_;
    // total number of missing values
    int nbMissing_;
    // number of modalities
    int nbModalities_;
    // pointer to data array
    const AugmentedData<STK::Array2D<int> >* pm_augDataij_;
    // array to store the positions of all missing data, regardless of the type (missing, interval, etc...)
    STK::Array2D<int> posMissing_;
    // array to store the statistics on the data
    STK::Array2D<STK::Real> statMissing_;
};

} // namespace mixt

#endif // MIXT_CATEGORICALDATASTAT_H
