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
 *  Created on: Aug 18, 2015
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#ifndef MIXT_FUNCTION_H
#define MIXT_FUNCTION_H

#include "Rcpp.h"
#include "MixtComp/src/Composer/mixt_MixtureComposer.h"
#include "MixtComp/src/Strategy/mixt_StrategyParam.h"

namespace mixt
{

void IDClass(mixt::MixtureComposer& mc,
             Rcpp::NumericMatrix& idc);

void lnProbaGivenClass(mixt::MixtureComposer& mc,
                       Rcpp::NumericMatrix& pGCR);

void matDelta(mixt::MixtureComposer& mc,
              Rcpp::NumericMatrix& delta);

void paramRToCpp(const Rcpp::List& RParam,
                 StrategyParam& CppParam);

} // namespace mixt

#endif // MIXT_FUNCTION_H
