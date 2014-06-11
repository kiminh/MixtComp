/*--------------------------------------------------------------------*/
/*     Copyright (C) 2004-2014  Serge Iovleff

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

    Contact : S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
*/

/*
 * Project:  stkpp::Analysis
 * created on: 7 mars 2014
 * Author:   iovleff, S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
 **/

/** @file STK_Const_Sequences.h
 *  @brief In this file we define static arrays with useful integer sequences .
 **/


#ifndef STK_CONST_SEQUENCES_H
#define STK_CONST_SEQUENCES_H

#include "../../STKernel/include/STK_Real.h"

namespace STK
{

namespace Const
{

/** @ingroup Analysis
 *  @brief array for the 51th fisrt factorial elements.
 *
 * The coefficients \f$ n! =n 1 \times 2 \times ... \times n\f$.
 * have been computed using the infinite precision calculator bc.
 * @see http://www.gnu.org/software/bc/
 * @see fact.bc
 **/
const Real factorialArray[51] =
{
                                                                1.0, //  0!
                                                                1.0, //  1!
                                                                2.0, //  2!
                                                                6.0, //  3!
                                                               24.0, //  4!
                                                              120.0, //  5!
                                                              720.0, //  6!
                                                             5040.0, //  7!
                                                            40320.0, //  8!
                                                           362880.0, //  9!
                                                          3628800.0, // 10!
                                                         39916800.0, // 11!
                                                        479001600.0, // 12!
                                                       6227020800.0, // 13!
                                                      87178291200.0, // 14!
                                                    1307674368000.0, // 15!
                                                   20922789888000.0, // 16!
                                                  355687428096000.0, // 17!
                                                 6402373705728000.0, // 18!
                                               121645100408832000.0, // 19!
                                              2432902008176640000.0, // 20!
                                             51090942171709440000.0, // 21!
                                           1124000727777607680000.0, // 22!
                                          25852016738884976640000.0, // 23!
                                         620448401733239439360000.0, // 24!
                                       15511210043330985984000000.0, // 25!
                                      403291461126605635584000000.0, // 26!
                                    10888869450418352160768000000.0, // 27!
                                   304888344611713860501504000000.0, // 28!
                                  8841761993739701954543616000000.0, // 29!
                                265252859812191058636308480000000.0, // 30!
                               8222838654177922817725562880000000.0, // 31!
                             263130836933693530167218012160000000.0, // 32!
                            8683317618811886495518194401280000000.0, // 33!
                          295232799039604140847618609643520000000.0, // 34!
                        10333147966386144929666651337523200000000.0, // 35!
                       371993326789901217467999448150835200000000.0, // 36!
                     13763753091226345046315979581580902400000000.0, // 37!
                    523022617466601111760007224100074291200000000.0, // 38!
                  20397882081197443358640281739902897356800000000.0, // 39!
                 815915283247897734345611269596115894272000000000.0, // 40!
               33452526613163807108170062053440751665152000000000.0, // 41!
             1405006117752879898543142606244511569936384000000000.0, // 42!
            60415263063373835637355132068513997507264512000000000.0, // 43!
          2658271574788448768043625811014615890319638528000000000.0, // 44!
        119622220865480194561963161495657715064383733760000000000.0, // 45!
       5502622159812088949850305428800254892961651752960000000000.0, // 46!
     258623241511168180642964355153611979969197632389120000000000.0, // 47!
   12413915592536072670862289047373375038521486354677760000000000.0, // 48!
  608281864034267560872252163321295376887552831379210240000000000.0, // 49!
30414093201713378043612608166064768844377641568960512000000000000.0  // 50!
};

/** @ingroup Analysis
 *  @brief array for the double factorial of odd numbers.
 *
 * The coefficients \f$ (2n+1)!! = 1\times 3\times 5\times...\times(2n+1)\f$.
 * have been found on http://oeis.org/.
 **/
const Real doubleFactorialOddArray[19] =
{
                       1.0, //  1!!
                       3.0, //  3!!
                      15.0, //  5!!
                     105.0, //  7!!
                     945.0, //  9!!
                   10395.0, // 11!!
                  135135.0, // 13!!
                 2027025.0, // 15!!
                34459425.0, // 17!!
               654729075.0, // 19!!
             13749310575.0, // 21!!
            316234143225.0, // 23!!
           7905853580625.0, // 25!!
         213458046676875.0, // 27!!
        6190283353629375.0, // 29!!
      191898783962510625.0, // 31!!
     6332659870762850625.0, // 33!!
   221643095476699771875.0, // 35!!
  8200794532637891559375.0  // 37!!
};

/** @ingroup Analysis
 *  @brief array for the double factorial of even numbers.
 *
 * The coefficients \f$ (2n)!! = 2\times 4\times 6\times...\times(2n)\f$.
 * have been found on http://oeis.org/.
 **/
const Real doubleFactorialEvenArray[20] =
{
                       1.0, //  0!!
                       2.0, //  2!!
                       8.0, //  4!!
                      48.0, //  6!!
                     384.0, //  8!!
                    3840.0, // 10!!
                   46080.0, // 12!!
                  645120.0, // 14!!
                10321920.0, // 16!!
               185794560.0, // 18!!
              3715891200.0, // 20!!
             81749606400.0, // 22!!
           1961990553600.0, // 24!!
          51011754393600.0, // 26!!
        1428329123020800.0, // 28!!
       42849873690624000.0, // 30!!
     1371195958099968000.0, // 32!!
    46620662575398912000.0, // 34!!
  1678343852714360832000.0, // 36!!
 63777066403145711616000.0  // 38!!
};

/** @ingroup Analysis
 *  @brief array for the double factorial.
 *
 * The coefficients (2n)!! have been found on http://oeis.org/.
 **/
const Real doubleFactorialArray[39] =
{
                       1.0, //  0!!
                       1.0, //  1!!
                       2.0, //  2!!
                       3.0, //  3!!
                       8.0, //  4!!
                      15.0, //  5!!
                      48.0, //  6!!
                     105.0, //  7!!
                     384.0, //  8!!
                     945.0, //  9!!
                    3840.0, // 10!!
                   10395.0, // 11!!
                   46080.0, // 12!!
                  135135.0, // 13!!
                  645120.0, // 14!!
                 2027025.0, // 15!!
                10321920.0, // 16!!
                34459425.0, // 17!!
               185794560.0, // 18!!
               654729075.0, // 19!!
              3715891200.0, // 20!!
             13749310575.0, // 21!!
             81749606400.0, // 22!!
            316234143225.0, // 23!!
           1961990553600.0, // 24!!
           7905853580625.0, // 25!!
          51011754393600.0, // 26!!
         213458046676875.0, // 27!!
        1428329123020800.0, // 28!!
        6190283353629375.0, // 29!!
       42849873690624000.0, // 30!!
      191898783962510625.0, // 31!!
     1371195958099968000.0, // 32!!
     6332659870762850625.0, // 33!!
    46620662575398912000.0, // 34!!
   221643095476699771875.0, // 35!!
  1678343852714360832000.0, // 36!!
  8200794532637891559375.0, // 37!!
 63777066403145711616000.0  // 38!!
};

/** @ingroup Analysis
 *  Array of the 40th first Bernouilli numbers
 *  Bernouilli(n) n=0, 2, 4, ... ,40.
 **/
static const Real bernouilliNumbersArray[21] =
{
                         1.0,             // 0
                         1.0/      6.0,   // 2
                        -1.0/     30.0,   // 4
                         1.0/     42.0,   // 6
                        -1.0/     30.0,   // 8
                         5.0/     66.0,   // 10
                      -691.0/   2730.0,   // 12
                         7.0/      6.0,   // 14
                     -3617.0/    510.0,   // 16
                     43867.0/    798.0,   // 18
                   -174611.0/    330.0,   // 20
                    854513.0/    138.0,   // 22
                -236364091.0/   2730.0,   // 24
                   8553103.0/      6.0,   // 26
              -23749461059.0/    870.0,   // 28
             8615841276005.0/  14322.0,   // 30
            -7709321041217.0/    510.0,   // 32
             2577687858367.0/      6.0,   // 34
     -26315271553053477373.0/1919190.0,   // 36
          2929993913841559.0/      6.0,   // 38
    -261082718496449122051.0/  13530.0    // 40
};

} // namespace Const

} // namespace STK

#endif /* STK_CONST_SEQUENCES_H */
