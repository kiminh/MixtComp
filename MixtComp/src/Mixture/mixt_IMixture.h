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
 *  Created on: July 2, 2014
 *  Authors:    Serge IOVLEFF <serge.iovleff@inria.fr>
 *              Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/


#ifndef MIXT_IMIXTURE_H
#define MIXT_IMIXTURE_H

#include <iostream>
#include "../LinAlg/mixt_LinAlg.h"
#include "../Various/mixt_Def.h"

namespace mixt
{

class IMixture
{
  public:
    /**
     * Constructor with identification character
     *
     * @param idName Identification string of the mixture provided by the framework
     */
    IMixture(std::string const& idName) :
      idName_(idName)
    {};

    /** Virtual destructor. Needed as IMixture will only be used as a base class. */
    virtual ~IMixture()
    {};

    /**
     * Return the Id of the mixture
     * @return Id of the mixture*/
    std::string const& idName() const
    {
      return idName_;
    }

    /**
     * Simulation of latent variables and partially observed data with values that
     * verify checkSampleCondition.
     *
     * @param ind index of the individual which data must be sampled
     */
    virtual void samplingStepCheck(int ind)
    = 0;

    /**
     * Simulation of latent variables and partially observed data without verifying
     * checkSampleCondition to speed-up the process.
     *
     * @param ind index of the individual which data must be sampled
     */
    virtual void samplingStepNoCheck(int ind)
    = 0;

    /**
     * Check if conditions on data are verified. For example, for a categorical model one must check that each modality
     * is present at least one time in each class. This is invoked to avoid degeneracy.
     * @return 0 if condition not verified and 1 if condition verified
     * */
    virtual int checkSampleCondition(std::string* warnLog = NULL) const
    = 0;

    /**
     * Maximum-Likelihood estimation of the mixture parameters
     *
     * @return empty string if mStep successful, or a detailed description of the eventual error
     */
    virtual std::string mStep()
    = 0;

    /**
     * Storage / display of intermediate results during the SEM burn-in phase
     *
     * @param iteration SEM burn-in iteration number in the burn-in
     * @param iterationMax maximum number of iterations
     */
    virtual void storeSEMBurnIn(int iteration,
                                int iterationMax)
    = 0;

    /**
     * Storage of mixture parameters during SEM run phase
     *
     * @param iteration SEM run iteration number
     * @param iterationMax maximum number of iterations
     * period.
     */
    virtual void storeSEMRun(int iteration,
                             int iterationMax)
    = 0;

    /**
     * Storage of mixture parameters during SEM run phase
     *
     * @param i individual
     * @param iteration Gibbs iteration
     * @param iterationMax maximum number of iterations
     */
    virtual void storeGibbsRun(int i,
                               int iteration,
                               int iterationMax)
    = 0;

    /**
     * Computation of completed likelihood
     *
     * @param i individual
     * @param k class
     * @return value of the completed likelihood in log scale
     */
    virtual Real lnCompletedProbability(int i, int k)
    = 0;

    /**
     * Computation of observed likelihood
     *
     * @param i individual
     * @param k class
     * @return value of the observed likelihood in log scale
     */
    virtual Real lnObservedProbability(int i, int k)
    = 0;

    /**
     * Computation of the number of free parameters.
     *
     *  @return Number of free parameters
     */
    virtual int nbFreeParameter() const
    = 0;

    /**
     * This function can be used to write summary of parameters on to the output stream.
     *
     *  @param[out] stream to write the summary of parameters to
     */
    virtual void writeParameters() const
    = 0;

    /**
     * Initialization of the data and parameters
     *
     * @param mode run mode, for example learning or prediction
     * @return empty string if no errors, otherwise errors description
     */
    virtual std::string setDataParam(RunMode mode)
    = 0;

    /**
     * Export of parameters and data
     */
    virtual void exportDataParam() const
    = 0;

    /**
     * Is it possible to have null probability individuals ?
     * @return true only if the model has null value for certain individuals
     */
    virtual bool possibleNullProbability() const
    = 0;

    /**
     * Crude removal of missing data by random sampling, prior to any parameter estimation. Used in
     * learning. In prediction parameters are known at initialization, and a samplingStep can be used.
     */
    virtual void removeMissing()
    = 0;

  protected:
    /** Id name of the mixture */
    std::string idName_;
};

} // namespace mixt

#endif /* MIXT_IMIXTURE_H */
