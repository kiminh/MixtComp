/*--------------------------------------------------------------------*/
/*  Copyright (C) Inria 2015

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
 *  Created on: August 20, 2015
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#ifndef MIXT_RANK_H
#define MIXT_RANK_H

#include "../Various/mixt_Def.h"
#include "../LinAlg/mixt_LinAlg.h"
#include "../Statistic/mixt_Statistic.h"

namespace mixt
{

/**
 * A rank is an object that contains everything needed to describe a particular individual. It contains both the observed and completed
 * values, as well as methods to compute the likelihood or to perform samplings.
 */
class Rank
{
  public:
    /* Each element of the vector is a position in a rank. The MisType describe the type of observation (or lack of)
     * while the Vector<int> describes the possible values, when needed. */
    typedef std::pair<MisType, Vector<int> > MisVal;

    Rank();

    /** Get the observed x value, for example for debugging purposes */
    void getX(Vector<int>& x) const {x = x_;}

    /** Get the presentation order, for example for debugging purposes */
    void getY(Vector<int>& y) const {y = y_;}

    /** Set the number of positions in the rank, used to resize storage */
    void setNbPos(int nbPos);

    /**
     * Set the observed values for the individual
     * @param pos position to be set
     * @param type observed / partially observed / unobserved value
     * @param val list of possible values for the partially observed data
     * */
    void setObserved(int pos,
                     MisType type,
                     const Vector<int> val);

    /**
     * Perform one round of Gibbs sampling for the partially observed data
     * @param mu central rank
     * @param pi precision */
    void samplingX(const Vector<int>& mu,
                   Real pi);

    /**
     * Perform one round of Gibbs sampling for the presentation order
     * @param mu central rank
     * @param pi precision */
    void samplingY(const Vector<int>& mu,
                   Real pi);

    /**
     * Completed log-probability of the individual
     * @param mu central rank
     * @param pi precision */
    Real lnCompletedProbability(const Vector<int>& mu,
                                Real pi) const;

    /** Uniform sample for partially observed valued and presentation order */
    void removeMissing();

    /**
     * Sample an individual from parameters, a presentation order
     * @param mu central rank, expressed in modality -> position representation
     * @param pi precision
     * @return log-probability of the sampled value
     * */
    Real xGen(const Vector<int>& muP,
              Real pi);

    /**
     * Switch a rank representation from
     * position -> modality
     * to
     * modality -> position
     * and vice-versa
     * */
    void switchRepresentation(const Vector<int>& mu ,
                                    Vector<int>& muP) const;

    void AG(const Vector<int>& mu,
            int& a,
            int& g) const;

    int positionRank(const Vector<int> x,
                     int i) const;

  private:
    /** Number of positions in the rank */
    int nbPos_;

    /** log(1 / n!) to normalize completed probability */
    Real lnFacNbPos_;

    /** Description of the observed data, one MisVal per position in the rank */
    Vector<MisVal> obsData_;

    /** Completed individual */
    Vector<int> x_;

    /** Presentation order */
    Vector<int> y_;

    /** Sampler for int */
    MultinomialStatistic multi_;
};

} // namespace mixt

#endif // MIXT_RANK_H
