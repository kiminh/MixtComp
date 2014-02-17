/*--------------------------------------------------------------------*/
/*  Copyright (C) Inria 2013-2014

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
 *  Created on: Dec 13, 2013
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

/** @file mixt_MixtureComposer.h
 *  @brief In this file 
 **/

#ifndef MIXT_MIXTURECOMPOSER_H_
#define MIXT_MIXTURECOMPOSER_H_

#include "stkpp/projects/Clustering/include/STK_MixtureComposer.h"
#include "mixt_AugmentedData.h"
#include "mixt_DataHandlerR.h"
#include "mixt_Clust_Util.h"

namespace mixt
{

class MixtureComposer : public STK::MixtureComposer
{
  public:    
    /** Constructor.
     * @param nbCluster number of cluster
     */
    inline MixtureComposer(int nbCluster)
                                   : STK::MixtureComposer(nbCluster) {}
                                   
    /** Constructor.
     * @param nbCluster number of cluster
     * @param nbSample number of sample
     */
    inline MixtureComposer(int nbCluster, int nbSample)
                                   : STK::MixtureComposer(nbCluster, nbSample) {}
                                   
    /** copy constructor.
     *  @param model the model to copy
     */
    inline MixtureComposer(STK::MixtureComposer const& model)
                                   : STK::MixtureComposer(model) {}
                                   
    /** The individual mixture will be deleted there.*/
    virtual ~MixtureComposer() {}
    
    /** Create a composer, but reinitialize the mixtures parameters. */
    virtual MixtureComposer* create() const;
    
    /** Create a clone of the current model, with mixtures parameters preserved. */
    virtual MixtureComposer* clone() const;

    /** create mixtures using info from p_dataHandler */
    void createMixtCompMixtures();

    template<typename Data>
    inline void getData(std::string const& id, Data& data, int& nbVariable) const
    {
      p_DataHandlerR()->getData(id, data, nbVariable);
    }
    
    void setDataHandler(DataHandlerR const* p_handler);
    
    void registerMixture(IMixture* mixture);
    
  private:
    inline DataHandlerR const* p_DataHandlerR() const
    {
      return static_cast<DataHandlerR const*>(this->p_handler());
    };
};

} /* namespace mixt */

#endif /* MIXT_MIXTURECOMPOSER_H_ */