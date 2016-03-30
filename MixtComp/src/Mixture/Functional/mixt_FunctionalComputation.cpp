/*--------------------------------------------------------------------*/
/*  Copyright (C) Inria 2016

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
 *  Created on: March 21, 2016
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#include <iostream>
#include "IO/mixt_IO.h"
#include "mixt_FunctionalComputation.h"

namespace mixt {

void VandermondeMatrix(const Vector<Real>& timeStep,
                       int degree,
                       Matrix<Real>& mat) {
  int nStep = timeStep.size();
  mat.resize(nStep, degree + 1);
  for (int k = 0; k < degree + 1; ++k) {
    for (int i = 0; i < nStep; ++i) {
      mat(i, k) = pow(timeStep(i), k);
    }
  }
}

void subRegression(const Matrix<Real>& design,
                   const Vector<Real>& y,
                   const Vector<std::list<int> >& w,
                   Matrix<Real>& beta) {
  int nCoeff = design.cols(); // degree + 1
  int nSub = w.size();
  beta.resize(nSub, nCoeff);
  Matrix<Real> subDesign; // design matrix reconstituted for each particular subregression
  Vector<Real> subY; // y vector for each particular subregression
  RowVector<Real> subBeta;
  for (int p = 0; p < nSub; p++) {
    int nbIndSubReg = w(p).size();
    subDesign.resize(nbIndSubReg, nCoeff);
    subY.resize(nbIndSubReg);

    int i = 0;
    for (std::list<int>::const_iterator it  = w(p).begin(),
                                        itE = w(p).end();
         it != itE;
         ++it, ++i) {
      subDesign.row(i) = design.row(*it);
      subY(i) = y(*it);
    }

    regression(subDesign,
               subY,
               subBeta);

    beta.row(p) = subBeta;
  }
}

void timeValue(const Vector<Real>& t,
               const Vector<Real>& alpha,
               Matrix<Real>& value,
               Vector<Real>& logSumExpValue) {
  int nT = t.size();
  int nSub = alpha.size() / 2;

  value.resize(nT, nSub);
  logSumExpValue.resize(nT);

  for (int s = 0; s < nSub; ++s) {
    for (int j = 0; j < nT; ++j) {
      int regFirstInd = 2 * s;
      value(j, s) = alpha(regFirstInd) + alpha(regFirstInd + 1) * t(j);
    }
  }

  Vector<Real> dummy;
  for (int j = 0; j < nT; ++j) {
    logSumExpValue(j) = dummy.logToMulti(value.row(j));
  }
}

void costFunction(const Vector<Real>& t,
                  const Matrix<Real>& value,
                  const Vector<Real>& logSumExpValue,
                  const Vector<std::list<int> >& w,
                  Real& cost) {
  cost = 0.;
  int nSub = w.size(); // number of subregressions

  for (int s = 0; s < nSub; ++s) {
    for (std::list<int>::const_iterator it  = w(s).begin(),
                                        ite = w(s).end();
         it != ite;
         ++it) {
      cost += value(*it, s);
      cost += - logSumExpValue(*it);
    }
  }
}

Real deriv1Var(int subReg,
               int subRegInd,
               int j,
               const Vector<Real>& t,
               const Matrix<Real>& value) {
  return (subRegInd ? t(j) : 1.) * std::exp(value(j, subReg));
}

Real deriv2Var(int subReg0,
               int subRegInd0,
               int subReg1,
               int subRegInd1,
               int j,
               const Vector<Real>& t,
               const Matrix<Real>& value) {
  Real res = 0;

  if (subReg0 == subReg1) {
    res = std::exp(value(j, subReg0));
    if (subRegInd0 == 1) {
      res *= t(j);
    }
    if (subRegInd1 == 1) {
      res *= t(j);
    }
  }

  return res;
}

void gradCostFunction(const Vector<Real>& t,
                      const Matrix<Real>& value,
                      const Vector<Real>& logSumExpValue,
                      const Vector<std::list<int> >& w,
                      Vector<Real>& gradCost) {
  int nT = t.size();
  int nParam = 2 * value.cols();
  gradCost.resize(nParam);
  gradCost = 0.;

  for (int p = 0; p < nParam; ++p) { // currently computed coefficient in the gradient
    int subReg = p / 2; // current alpha index
    int subRegInd = p % 2; // 0 or 1, indicating which alpha among the pair in varDeriv

    for (std::list<int>::const_iterator it  = w(subReg).begin(),
                                        ite = w(subReg).end();
         it != ite;
         ++it) {
        gradCost(p) += subRegInd ? t(*it) : 1.;
    }

    for (int j = 0; j < nT; ++j) { // denominator term does not depend on lambda, and there is one term per timestep
      gradCost(p) += - deriv1Var(subReg, subRegInd, j, t, value) / std::exp(logSumExpValue(j));
    }
  }
}

void hessianCostFunction(const Vector<Real>& t,
                         const Matrix<Real>& value,
                         const Vector<Real>& logSumExpValue,
                         const Vector<std::list<int> >& w,
                         Matrix<Real>& hessianCost) {
  int nT = t.size();
  int nParam = 2 * value.cols();
  hessianCost.resize(nParam, nParam);
  hessianCost = 0.;

  for (int pRow = 0; pRow < nParam; ++pRow) { // currently computed row
    for (int pCol = pRow; pCol < nParam; ++pCol) { // upper triangular part of the symmetric hessian matrix
      int subReg0 = pRow / 2; // current alpha index
      int subRegInd0 = pRow % 2; // 0 or 1, indicating which alpha among the pair in varDeriv
      int subReg1 = pCol / 2;
      int subRegInd1 = pCol % 2;

      for (int j = 0; j < nT; ++j) { // denominator term does not depend on lambda, and there is one term per timestep
        hessianCost(pRow, pCol) += deriv2Var(subReg0,
                                             subRegInd0,
                                             subReg1,
                                             subRegInd1,
                                             j,
                                             t,
                                             value);
        Real deriv0 = deriv1Var(subReg0,
                                subRegInd0,
                                j,
                                t,
                                value);
        Real deriv1 = deriv1Var(subReg1,
                                subRegInd1,
                                j,
                                t,
                                value);;
        hessianCost(pRow, pCol) = deriv0 * deriv1;

        hessianCost(pRow, pCol) /= - pow(std::exp(logSumExpValue(j)), 2);
      }
    }
  }

  for (int pRow = 0; pRow < nParam; ++pRow) {
    for (int pCol = 0; pCol < pRow; ++pCol) {
      hessianCost(pRow, pCol) = hessianCost(pCol, pRow);
    }
  }
}

} // namespace mixt
