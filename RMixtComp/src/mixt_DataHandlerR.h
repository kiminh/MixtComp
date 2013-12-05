/*--------------------------------------------------------------------*/
/*     Copyright (C) 2004-2013 Vincent KUBICKI

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

 */

/*
 * Project:  MixtComp
 * created on: Nov 21, 2013
 * Author:   Vincent KUBICKI
 **/

/** @file mixt_DataHandlerR.h
 *  @brief In this file 
 **/

#ifndef MIXT_DATAHANDLERR_H_
#define MIXT_DATAHANDLERR_H_

#include <vector>
#include <Rcpp.h>
#include "stkpp/projects/DManager/include/STK_IDataHandler.h"

namespace mixt
{

class DataHandlerR: public STK::IDataHandler
{
  public:
    /** first: list index, second: matrix column number */
    typedef std::pair<int, int> DataPos;
    /** map: id -> vector of positions */
    typedef std::map<std::string, std::vector<DataPos> > DataMap;

    /** default constructor */
    DataHandlerR();
    /** destructor */
    virtual ~DataHandlerR();

    /** @return the number of samples (the number of rows of the data) */
    inline virtual int nbSample() const { return nbSamples_;}
        /** @return the number of variables (the number of columns of the data) */
    inline virtual int nbVariable() const {return nbVariables_;};

    /** read a data file and its companion description file. */
    bool readDataFromRList(Rcpp::List);

    /** return in an Array2D<int> the data with the given idData */
    virtual void getData(std::string const& idData, STK::Array2D<int>& data, int& nbVariable) const;
    /** return in an Array2D<Real> the data with the given idData */
    virtual void getData(std::string const& idData, STK::Array2D<STK::Real>& data, int& nbVariable) const;
    /** return in an Array2D<std::string> the data with the given idData */
    virtual void getData(std::string const& idData, STK::Array2D<std::string>& data, int& nbVariable) const;
    
    /** write information on the localization of data in the rList */
    void writeDataMap() const;
  private:
    int nbSamples_;
    int nbVariables_;
    DataMap dataMap_;
    Rcpp::List rList_;
    
    /** read data structure independently of the type (integer, numeric, character) */
    template<class RcppClass>
    void readDataFromRListHelper(int i, int& k, Rcpp::S4 s4);
};

template<class RcppClass>
void DataHandlerR::readDataFromRListHelper(int i, int& k, Rcpp::S4 s4)
{
  std::string modelname = s4.slot("model");
  RcppClass nm = s4.slot("data");
  nbSamples_ = nm.nrow(); // overwritten, because check has already been performed on the R side
  for (int j = 0; j < nm.ncol(); ++j, ++k) // each column is assigned to a model (temporary)
  {
    std::string id(STK::typeToString(k));
    addInfo(id, modelname);
    std::vector<DataPos>& v_pos = dataMap_[id]; // dataMap_[id] created if not already existing
    v_pos.push_back(DataPos(i, j));
    ++nbVariables_;
  }
}

} /* namespace mixt */
#endif /* MIXT_DATAHANDLERR_H_ */
