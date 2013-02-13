/*--------------------------------------------------------------------*/
/*     Copyright (C) 2004-2012  Serge Iovleff

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

    Contact : Serge.Iovleff@stkpp.org
*/

/*
 * Project:  stkpp::Arrays
 * created on: 17 févr. 2012
 * Author:   iovleff, serge.iovleff@stkpp.org
 **/

/** @file STK_Arrays_Util.h
 *  @brief In this file we define utilities for the Array classes.
 *
 *  @namespace Arrays the namespace Arrays contain all the internal stuff needed
 *  by The Arrays* classes.
 *
 **/
#include "../include/STK_Arrays_Util.h"

namespace STK
{

namespace Arrays
{

/* Return n+m, where n is the first number such that m < 2^n.
  *  @param m the size of the container
 **/
int evalCapacity(int const& m)
{
  int n = 0;
  for (int k=1, n=0 ; k <= m; n++, k <<= 1);
  return m+n;
}


/** Return n+m, where n is the first number such that m < 2^n.
  *  @param I the range of the container
 **/
Range evalCapacity(STK::Range const& I)
{
  int n = 0;
  for (int k=1, n=0 ; k <= I.size(); n++, k <<= 1);
  return Range(I.firstIdx(),I.size() + n);
}

} // namespace Arrays

} // namespace STK
