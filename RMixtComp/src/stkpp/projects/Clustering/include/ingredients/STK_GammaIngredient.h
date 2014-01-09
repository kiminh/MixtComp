/*--------------------------------------------------------------------*/
/*     Copyright (C) 2004-2013 Vincent KUBICKI

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this program; if not, write to the
    Free Software Foundation, Inc.,
    59 Temple Place,
    Suite 330,
    Boston, MA 02111-1307
    USA

    Contact : S..._DOT_I..._AT_stkpp.org (see copyright for ...)
*/

/*
 * Project:  stkpp::Clustering
 * created on: 15 nov. 2013
 * Author:   iovleff, serge.iovleff@stkpp.org
 **/



#ifndef STK_GAMMAINGREDIENT_H
#define STK_GAMMAINGREDIENT_H

#include "STK_MixtureBridge.h"

#include "../GammaMixtureModels/STK_Gamma_ajk_bjk.h"
#include "../GammaMixtureModels/STK_Gamma_ajk_bj.h"

namespace STK
{

namespace Clust
{
/** @ingroup Clust
 *  Given the Id of a mixture model, the struct IngredientTraits allow to get
 *  type of the input and output.
 **/
template<>
struct IngredientTraits<Clust::Gamma_ajk_bjk_>
{
   /** Type of the data set to used as input */
   typedef STK::Array2D<STK::Real> Data;
   /** Type of the parameter set to used as output */
   typedef STK::Array2D<STK::Real> Param;
   /** Type of the Data */
   typedef typename Data::Type Type;
   /** Type of the mixture model */
   typedef STK::Gamma_ajk_bjk<Data> Ingredient;
};


/** @ingroup Clust
 *  Given the Id of a mixture model, the struct IngredientTraits allow to get
 *  type of the input and output.
 **/
template<>
struct IngredientTraits<Clust::Gamma_ajk_bj_>
{
   /** Type of the data set to used as input */
   typedef STK::Array2D<STK::Real> Data;
   /** Type of the parameter set to used as output */
   typedef STK::Array2D<STK::Real> Param;
   /** Type of the Data */
   typedef typename Data::Type Type;
   /** Type of the mixture model */
   typedef STK::Gamma_ajk_bj<Data> Ingredient;
};

} // namespace Clust

typedef MixtureBridge<Clust::Gamma_ajk_bjk_> IngredientGamma_ajk_bjk;
typedef MixtureBridge<Clust::Gamma_ajk_bj_> IngredientGamma_ajk_bj;

} /* namespace STK */

#endif /* STK_GAMMAINGREDIENT_H */
