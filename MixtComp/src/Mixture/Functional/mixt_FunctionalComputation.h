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

#ifndef MIXT_FUNCTIONALCOMPUTATION
#define MIXT_FUNCTIONALCOMPUTATION

#include <list>
#include <set>
#include "LinAlg/mixt_LinAlg.h"

namespace mixt {

typedef struct {
    Vector<Real>* t_;
    Vector<std::list<Index> >* w_;
    Index nParam_;
} CostData;

void VandermondeMatrix(const Vector<Real>& timeStep,
                       Index nCoeff,
                       Matrix<Real>& mat);

template<typename betaType>
void estimateSD(const Matrix<Real>& subDesign,
                const Vector<Real>& subY,
                betaType& subBeta) {
  Index nI = subDesign.rows();
  Index nCoeff = subBeta.size() - 1; // last element is the standard deviation

  Vector<Real> error(nI);

  for (Index i = 0; i < nI; ++i) {
    error(i) = 0;
    for (Index c = 0; c < nCoeff; ++c) {
      error(i) += subDesign.row(i)(c) * subBeta(c);
    }
    error(i) -= subY(i);
  }

  Real mean;
  meanSD(error,
         mean,
         subBeta(nCoeff)); // standard deviation stored at the end of beta
}

template<typename betaType>
void regression(const Matrix<Real>& design,
                const Vector<Real>& y,
                const betaType& betaIn) {
  betaType& beta = const_cast<betaType&>(betaIn); // without the const_cast it is impossible to access a row which is a temporary object requiring a const in the argument
  Index nCoeff = design.cols();
  beta.resize(nCoeff + 1);

  Vector<Real> betaCoeff = (design.transpose() * design).inverse() * design.transpose() * y;

  for (Index c = 0; c < nCoeff; ++c) {
    beta(c) = betaCoeff(c);
  }

  estimateSD(design,
             y,
             beta); // standard deviation is stored in the last coefficient of vector beta
}

void subRegression(const Matrix<Real>& design,
                   const Vector<Real>& y,
                   const Vector<std::list<Index> >& w,
                   Matrix<Real>& beta);

void timeValue(const Vector<Real>& t,
               int nParam,
               const double* alpha,
               Matrix<Real>& logValue,
               Vector<Real>& logSumExpValue);

void costFunction(const Vector<Real>& t,
                  const Matrix<Real>& logValue,
                  const Vector<Real>& logSumExpValue,
                  const Vector<std::list<Index> >& w,
                  Real& cost);

Real costFunctionDebug(const Vector<Real>& t,
                       const Vector<Real>& alpha,
                       const Vector<std::list<Index> >& w);

Real deriv1Var(Index subReg,
               Index subRegInd,
               Index j,
               const Vector<Real>& t,
               const Matrix<Real>& value);

Real deriv2Var(Index subReg0,
               Index subRegInd0,
               Index subReg1,
               Index subRegInd1,
               Index j,
               const Vector<Real>& t,
               const Matrix<Real>& value);

void gradCostFunction(const Vector<Real>& t,
                      const Matrix<Real>& value,
                      const Vector<Real>& logSumExpValue,
                      const Vector<std::list<Index> >& w,
                      double* gradCost);

void hessianCostFunction(const Vector<Real>& t,
                         const Matrix<Real>& value,
                         const Vector<Real>& logSumExpValue,
                         const Vector<std::list<Index> >& w,
                         Matrix<Real>& hessianCost);

void hessianCostFunctionNoSym(const Vector<Real>& t,
                              const Matrix<Real>& value,
                              const Vector<Real>& logSumExpValue,
                              const Vector<std::list<Index> >& w,
                              Matrix<Real>& hessianCost);

void initAlpha(Index nParam,
               const Vector<Real>& t,
               Vector<Real>& alpha);

//void updateAlpha(Index nParam,
//                 const Vector<Real>& t,
//                 const Vector<std::list<Index> >& w,
//                 Vector<Real>& alpha,
//                 Real& alpha_k,
//                 Real& costCurr,
//                 Vector<Real>& gradCurr);

void computeLambda(const Vector<Real>& t,
                   const Vector<Real>& y,
                   int nParam,
                   const double* alpha,
                   const Matrix<Real>& beta,
                   Matrix<Real>& lambda);

double optiFunc(unsigned nParam,
                const double* alpha,
                double* grad,
                void* my_func_data);

} // namespace mixt

#endif // MIXT_FUNCTIONALCOMPUTATION
