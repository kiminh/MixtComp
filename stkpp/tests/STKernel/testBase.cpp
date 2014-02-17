/*--------------------------------------------------------------------*/
/*     Copyright (C) 2004-2007  Serge Iovleff

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
 * Project:  stkpp::STKernel::Base
 * Purpose:  test program for testing Base classes.
 * Author:   Serge Iovleff, S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
 */

/** @file testBase.cpp
 *  @brief In this file we test the classes of the STKernel::Base subproject.
 **/

#include "../../include/STKernel.h"

using namespace STK;


/* main.                                                              */
int main(int argc, char *argv[])
{
  try
  {
    stk_cout << _T("\n\n");
    stk_cout << _T("+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    stk_cout << _T("+ Test STK::Base                                      +\n");
    stk_cout << _T("+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    stk_cout << _T("\n\n");

    // first test
    stk_cout << _T("Test: istringstream in(stringNa); Real x; in >> Proxy<Real>(x);\n");
    istringstream in(stringNa);
    Real x;
    in >> Proxy<Real>(x);
    stk_cout << _T("x =")              << Proxy<Real>(x) << _T("\n");
    stk_cout << _T("isNA(x) =")       << STK::Arithmetic<Real>::isNA(x) << _T("\n");
    stk_cout << _T("isInfinite(x) =") << STK::Arithmetic<Real>::isInfinite(x) << _T("\n\n");

    stk_cout << _T(" Test: x = Arithmetic<Real>::infinity();\n");
    x = Arithmetic<Real>::infinity();
    stk_cout << _T("x =")             << Proxy<Real>(x) << _T("\n");
    stk_cout << _T("isNA(x) =")       << STK::Arithmetic<Real>::isNA(x) << _T("\n");
    stk_cout << _T("isInfinite(x) =") << STK::Arithmetic<Real>::isInfinite(x) << _T("\n\n");

    // second test
    stk_cout << _T("\n\n");
    stk_cout << _T("+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    stk_cout << _T("+ Testing all types:\n");
    stk_cout << _T("Char c;\n");
    stk_cout << _T("+++++++\n");
    Char c;
    stk_cout << _T("stringToType(c, stringNa) = ") << stringToType(c, stringNa) << _T("\n");
    stk_cout << _T("c =")             << Proxy<Char>(c) << _T("\n");
    stk_cout << _T("isNA(c) =")       << STK::Arithmetic<Char>::isNA(c) << _T("\n");
    stk_cout << _T("isInfinite(c) =") << STK::Arithmetic<Char>::isInfinite(c) << _T("\n\n");

    stk_cout << _T("String l;\n");
    stk_cout << _T("+**++++++\n");
    String l;
    stk_cout << _T("stringToType(l, stringNa) = ") << stringToType(l, stringNa) << _T("\n");
    stk_cout << _T("l =") << Proxy<String>(l) << _T("\n");
    stk_cout << _T("isNA(l) =") << STK::Arithmetic<String>::isNA(l) << _T("\n");
    stk_cout << _T("isInfinite(l) =") << STK::Arithmetic<String>::isInfinite(l) << _T("\n\n");

    stk_cout << _T("Real r;\n");
    Real r;
    stk_cout << _T("stringToType(r, stringNa) = ")
             << stringToType(r, stringNa)
             << _T("\n");
    stk_cout << _T("r =") << Proxy<Real>(r) << _T("\n");
    stk_cout << _T("isNA(r) =")
             << STK::Arithmetic<Real>::isNA(r)
             << _T("\n");
    stk_cout << _T("isInfinite(r) =")
             << STK::Arithmetic<Real>::isInfinite(r)
             << _T("\n");

    stk_cout << _T("\n");
    stk_cout << _T("int d;\n");
    int d;
    stk_cout << _T("stringToType(d, stringNa) = ") << stringToType(d, stringNa)<< _T("\n");
    stk_cout << _T("d =") << Proxy<int> (d) << _T("\n");
    stk_cout << _T("isNA(d) =")
             << STK::Arithmetic<int> ::isNA(d)
             << _T("\n");
    stk_cout << _T("isInfinite(d) =")
             << STK::Arithmetic<int> ::isInfinite(d)
             << _T("\n");

    stk_cout << _T("\n\n");
    stk_cout << _T("+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    stk_cout << _T("Testing Binary base type.\n");
    Binary b;
    String zero(_T("0")), one(_T("1")), two(_T("2")), three(_T("3"));
    stk_cout << _T("stringToType(b,") << stringNa  <<_T(") = ") << stringToType(b, stringNa)<< _T("\n");
    stk_cout << _T("b =") << Proxy<Binary>(b) << _T("\n");
    stk_cout << _T("isNA(b) =") << STK::Arithmetic<Binary>::isNA(b) << _T("\n");
    stk_cout << _T("isInfinite(b) =")<< STK::Arithmetic<Binary>::isInfinite(b) << _T("\n");
    stk_cout << _T("stringToType(b,") << zero  <<_T(") = ") << stringToType(b, zero)<< _T("\n");
    stk_cout << _T("b =") << Proxy<Binary>(b) << _T("\n");
    stk_cout << _T("isNA(b) =") << STK::Arithmetic<Binary>::isNA(b) << _T("\n");
    stk_cout << _T("isInfinite(b) =")<< STK::Arithmetic<Binary>::isInfinite(b) << _T("\n");
    stk_cout << _T("stringToType(b,") << one  <<_T(") = ") << stringToType(b, one)<< _T("\n");
    stk_cout << _T("b =") << Proxy<Binary>(b) << _T("\n");
    stk_cout << _T("isNA(b) =") << STK::Arithmetic<Binary>::isNA(b) << _T("\n");
    stk_cout << _T("isInfinite(b) =")<< STK::Arithmetic<Binary>::isInfinite(b) << _T("\n");
    stk_cout << _T("stringToType(b,") << two  <<_T(") = ") << stringToType(b, two)<< _T("\n");
    stk_cout << _T("b =") << Proxy<Binary>(b) << _T("\n");
    stk_cout << _T("isNA(b) =") << STK::Arithmetic<Binary>::isNA(b) << _T("\n");
    stk_cout << _T("isInfinite(b) =")<< STK::Arithmetic<Binary>::isInfinite(b) << _T("\n");
    stk_cout << _T("stringToType(b,") << three  <<_T(") = ") << stringToType(b, three)<< _T("\n");
    stk_cout << _T("b =") << Proxy<Binary>(b) << _T("\n");
    stk_cout << _T("isNA(b) =") << STK::Arithmetic<Binary>::isNA(b) << _T("\n");
    stk_cout << _T("isInfinite(b) =")<< STK::Arithmetic<Binary>::isInfinite(b) << _T("\n");

    stk_cout << _T("\n\n");
    stk_cout << _T("+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    stk_cout << _T("Testing Sign base type.\n");
    Sign s;
    stk_cout << _T("stringToType(s, stringNa) = ")
    << stringToType(s, stringNa)<< _T("\n");
    stk_cout << _T("s =") << Proxy<Sign>(s) << _T("\n");
    stk_cout << _T("isNA(s) =")
              << STK::Arithmetic<Sign>::isNA(s) << _T("\n");
    stk_cout << _T("isInfinite(s) =")
             << STK::Arithmetic<Sign>::isInfinite(s) << _T("\n");

    // third test
    stk_cout << _T("\n\n");
    stk_cout << _T("Testing all types:\n");
    stk_cout << _T("String pi = 3.14159;\n");
    String pi = _T("3.14159");
    stk_cout << _T("Char c;\n");
    stk_cout << _T("stringToType(c, l) = ")
    << stringToType(c, pi)<< _T("\n");
    stk_cout << _T("c =") << Proxy<Char>(c) << _T("\n");
    stk_cout << _T("isNA(c) =")
             << STK::Arithmetic<Char>::isNA(c) << _T("\n");
    stk_cout << _T("isInfinite(c) =")
             << STK::Arithmetic<Char>::isInfinite(c)
             << _T("\n");

    stk_cout << _T("\n");
    stk_cout << _T("String l;\n");
    stk_cout << _T("stringToType(l, pi) = ")
    << stringToType(l, pi)<< _T("\n");
    stk_cout << _T("l =") << Proxy<String>(l) << _T("\n");
    stk_cout << _T("isNA(l) =")
             << STK::Arithmetic<String>::isNA(l)
             << _T("\n");
    stk_cout << _T("isInfinite(l) =")
             << STK::Arithmetic<String>::isInfinite(l) << _T("\n");

    stk_cout << _T("\n");
    stk_cout << _T("Real r;\n");
    stk_cout << _T("stringToType(r, pi) = ")
    << stringToType(r, pi)<< _T("\n");
    stk_cout << _T("r =") << Proxy<Real>(r) << _T("\n");
    stk_cout << _T("isNA(r) =")
             << STK::Arithmetic<Real>::isNA(r) << _T("\n");
    stk_cout << _T("isInfinite(r) =")
             << STK::Arithmetic<Real>::isInfinite(r)
             << _T("\n");

    stk_cout << _T("\n");
    stk_cout << _T("int d;\n");
    stk_cout << _T("stringToType(d, pi) = ")
    << stringToType(d, pi)<< _T("\n");
    stk_cout << _T("d =") << Proxy<int> (d) << _T("\n");
    stk_cout << _T("isNA(d) =")
             << STK::Arithmetic<int> ::isNA(d)
             << _T("\n");
    stk_cout << _T("isInfinite(d) =")
             << STK::Arithmetic<int> ::isInfinite(d)
             << _T("\n");

    stk_cout << _T("\n");
    stk_cout << _T("Binary b;\n");
    stk_cout << _T("stringToType(b, pi) = ")
    << stringToType(b, pi)<< _T("\n");
    stk_cout << _T("b =") << Proxy<Binary>(b) << _T("\n");
    stk_cout << _T("isNA(b) =")
              << STK::Arithmetic<Binary>::isNA(b) << _T("\n");
    stk_cout << _T("isInfinite(b) =")
              << STK::Arithmetic<Binary>::isInfinite(b) << _T("\n");

    stk_cout << _T("\n");
    stk_cout << _T("Sign s;\n");
    stk_cout << _T("stringToType(s, pi) = ")
    << stringToType(s, pi)<< _T("\n");
    stk_cout << _T("s =") << Proxy<Sign>(s) << _T("\n");
    stk_cout << _T("isNA(s) =")
              << STK::Arithmetic<Sign>::isNA(s) << _T("\n");
    stk_cout << _T("isInfinite(s) =")
              << STK::Arithmetic<Sign>::isInfinite(s) << _T("\n");

    // fourth test
    stk_cout << _T("\n\n");
    stk_cout << _T("Testing Real:\n");
    stk_cout << _T("Real pireal = 3.14159;\n");
    Real pireal = 3.14159;
    stk_cout << _T("typeToString(pireal) = ")
    << typeToString(pireal)<< _T("\n");

    // fourth test
    stk_cout << _T("\n\n");
    stk_cout << _T("Testing Range:\n");
    Range I;
    String ranges = "2:5";
    stk_cout << _T("Test with string =") << ranges << _T("\n");
    stringToType(I, ranges);
    stk_cout << _T("Range = ")  << typeToString(I)<< _T("\n");
    ranges = " 1 : 8 ";
    stk_cout << _T("Test with string =") << ranges << _T("\n");
    stringToType(I, ranges);
    stk_cout << _T("Range = ")  << typeToString(I)<< _T("\n");
    ranges = " 12 ";
    stk_cout << _T("Test with string =") << ranges << _T("\n");
    stringToType(I, ranges);
    stk_cout << _T("Range = ")  << typeToString(I)<< _T("\n");
    ranges = " >2 ";
    stk_cout << _T("Test with string =") << ranges << _T("\n");
    stringToType(I, ranges);
    stk_cout << _T("Range = ")  << typeToString(I)<< _T("\n");
    ranges = " 3:     >2 ";
    stk_cout << _T("Test with string =") << ranges << _T("\n");
    stringToType(I, ranges);
    stk_cout << _T("Range = ")  << typeToString(I)<< _T("\n");
    ranges = " 5:     2>";
    stk_cout << _T("Test with string =") << ranges << _T("\n");
    stringToType(I, ranges);
    stk_cout << _T("Range = ")  << typeToString(I)<< _T("\n");

    stk_cout << _T("\n\n");
    stk_cout << _T("+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    stk_cout << _T("+ Successful completion of testing for STK::Base      +\n");
    stk_cout << _T("+ No errors detected.                                 +\n");
    stk_cout << _T("+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    stk_cout << _T("\n\n");
  }
  catch (Exception & error)
  {
    std::cerr << "An error occured : " << error.error() << _T("\n";);
  }
  return 0;
}