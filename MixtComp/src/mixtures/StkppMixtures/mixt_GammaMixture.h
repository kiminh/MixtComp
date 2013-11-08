/*--------------------------------------------------------------------*/
/*     Copyright (C) 2004-2013  Serge Iovleff

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this program; if not, write to the
    Free Software Foundation, Inc.,
    59 Temple Place,
    Suite 330,
    Boston, MA 02111-1307
    USA

    Contact : S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
*/

/*
 * Author:   iovleff, S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
 **/

#ifndef MIXT_GAMMAMIXTURE_H
#define MIXT_GAMMAMIXTURE_H

#include "mixt_MixtureBridge.h"

namespace mixt
{

// get the Type of the data
typedef STK::Array2D<STK::Real> dataType;

class Gamma_pk_ajk_bjk : MixtureBridge<STK::Gamma_pk_ajk_bjk<dataType>>
{
  virtual Gamma_pk_ajk_bjk* clone()
  {
    return new Gamma_pk_ajk_bjk(*this);
  }

  virtual void setData()
  {
    data_.move(p_compositeModel_->getData<dataType>());
  }
};

} /* namespace mixt */

#endif /* MIXT_GAMMAMIXTURE_H_ */
