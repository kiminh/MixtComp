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
 *  Created on: Nov 21, 2013
 *  Author:     Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

/** @file mixt_DataHandlerR.h
 *  @brief In this file 
 **/

#ifndef MIXT_DATAHANDLERR_H_
#define MIXT_DATAHANDLERR_H_

#include <vector>
#include <map>
#include <Rcpp.h>
#include "boost/regex.hpp"
#include "MixtComp/src/LinAlg/mixt_LinAlg.h"
#include "MixtComp/src/Data/mixt_AugmentedData.h"
#include "MixtComp/src/Various/mixt_Def.h"
#include "MixtComp/src/IO/mixt_IO.h"

namespace mixt
{

class DataHandlerR
{
  public:
    /** map: idData -> model */
    typedef std::map<std::string, std::string> InfoMap;

    /** map: id -> indice in rList_ */
    typedef std::map<std::string, int> DataMap;

    /** default constructor */
    DataHandlerR(Rcpp::List rList);

    /** destructor */
    virtual ~DataHandlerR();

    /** @return the number of samples (the number of rows of the data) */
    int nbSample() const {return nbSample_;}
        /** @return the number of variables (the number of columns of the data) */
    int nbVariable() const {return nbVariables_;};

    /** read a data file and its companion description file,
      and fill the infoMap_ (id -> model) and dataMap_ (id -> vector of positions)
      members */
    std::string listData();
    
    /** @return the map with the idDatas and idModel of the models */
    InfoMap const& info() const{return info_;};
    void writeInfo(std::ostream& os) const;
    /** write information on the localization of data in the rList */
    void writeDataMap() const;

    template<typename DataType>
    void getData(std::string const& idData,
                 AugmentedData<DataType>& augData,
                 int& nbSample,
                 std::string& param,
                 typename AugmentedData<DataType>::Type offset,
                 std::string& warnLog) const;
  private:
    int nbSample_;
    int nbVariables_;
    /** Store the informations  of the mixtures in the form (idData, idModel) with
     * - idData: an arbitrary idData for a model
     * - model: a string which can be converted in an existing model
     * @sa stringToMixture */
    InfoMap info_;
    /** map: id -> vector of positions in rList_, as typedef-ed above */
    DataMap dataMap_;
    /** A list of the mixtures transmitted by R, as named lists */
    Rcpp::List rList_;
};

template<typename DataType>
void DataHandlerR::getData(std::string const& idData,
                           AugmentedData<DataType>& augData,
                           int& nbSample,
                           std::string& param,
                           typename AugmentedData<DataType>::Type offset,
                           std::string& warnLog) const
{
  typedef typename AugmentedData<DataType>::Type Type;
  typedef typename AugmentedData<Matrix<Type> >::MisVal MisVal;
#ifdef MC_DEBUG
  std::cout << "DataHandlerR::getDataHelper()" << std::endl;
  std::cout << "\tidData: " << idData << std::endl;
//  std::cout << augData.data_ << std::endl;
#endif

  if (dataMap_.find(idData) != dataMap_.end()) // check if the data requested is present in the input data
  {
    int pos = dataMap_.at(idData); // get the index of the element of the rList_ corresponding to idData
    nbSample = nbSample_;
    augData.resizeArrays(nbSample_); // R has already enforced that all data has the same number of rows, and now all mixture ane univariate

    // definitions of regular expressions to capture / reject numbers
    std::string strNumber("((?:-|\\+)?(?:\\d+(?:\\.\\d*)?)|(?:\\.\\d+))");
    std::string strBlank(" *");
    std::string strLeftPar(" *\\[ *");
    std::string strRightPar(" *\\] *");
    std::string centralColon(" *: *");
    std::string minusInf("-inf");
    std::string plusInf("\\+inf");

    boost::regex reNumber(strNumber);
    boost::regex reValue(strBlank + // " *(-*[0-9.]+) *"
                         strNumber +
                         strBlank);
    boost::regex reFiniteValues(" *\\{.*\\} *");
    boost::regex reIntervals(strLeftPar + // " *\\[ *(-*[0-9.]+) *: *(-*[0-9.]+) *\\] *"
                             strNumber +
                             centralColon +
                             strNumber +
                             strRightPar);
    boost::regex reLuIntervals(strLeftPar +  // " *\\[ *-inf *: *(-*[0-9.]+) *\\] *"
                               minusInf +
                               centralColon +
                               strNumber +
                               strRightPar);
    boost::regex reRuIntervals(strLeftPar + // " *\\[ *(-*[0-9.]+) *: *\\+inf *\\] *"
                               strNumber +
                               centralColon +
                               plusInf +
                               strRightPar);

    boost::smatch matches;

#ifdef MC_DEBUG
    std::cout << "DataHandlerR::getData" << std::endl;
#endif
    Rcpp::List currVar = rList_[pos]; // get current named list
    Rcpp::CharacterVector data = currVar("data");
    for (int i = 0; i < nbSample_; ++i)
    {
#ifdef MC_DEBUG
      std::cout << "DataHandlerR::getData" << std::endl;
      std::cout << "\ti: " << i << std::endl;
#endif
      std::string currStr(data[i]);

      if (boost::regex_match(currStr, matches, reValue)) // value is present
      {
        augData.setPresent(i, str2type<Type>(matches[1].str()) + offset);
#ifdef MC_DEBUG
        std::cout << "\tpresent value" << std::endl;
        std::cout << str2type<Type>(matches[1].str()) << std::endl;
#endif
        continue;
      }

      if (boost::regex_match(currStr, matches, reFiniteValues)) // only a finite number of values are acceptable
      {
        std::string::const_iterator start = currStr.begin();
        std::string::const_iterator end   = currStr.end();
        boost::smatch m;
        MisVal misVal;
        misVal.first = missingFiniteValues_;
        while (boost::regex_search(start, end, m, reNumber ))
        {
          misVal.second.push_back(str2type<Type>(m[0].str()) + offset);
          start = m[0].second;
#ifdef MC_DEBUG
          std::cout << "\tmissingFiniteValues_" << std::endl;
          std::cout << m[0].str() << std::endl;
#endif
        }
        augData.setMissing(i, misVal);
        continue;
      }

      if (boost::regex_match(currStr, matches, reIntervals)) // acceptable values provided by intervals
      {
        MisVal misVal;
        misVal.first = missingIntervals_;
        misVal.second.resize(2);
        misVal.second[0] = str2type<Type>(matches[1].str()) + offset;
        misVal.second[1] = str2type<Type>(matches[2].str()) + offset;
        augData.setMissing(i, misVal);
#ifdef MC_DEBUG
        std::cout << "\tmissingIntervals_" << std::endl;
        std::cout << misVal.second[0] << std::endl;
        std::cout << misVal.second[1] << std::endl;
#endif
        continue;
      }

      if (boost::regex_match(currStr, matches, reLuIntervals)) // data is lower bounded
      {
        MisVal misVal;
        misVal.first = missingLUIntervals_;
        misVal.second.push_back(str2type<Type>(matches[1].str()) + offset);
        augData.setMissing(i, misVal);
#ifdef MC_DEBUG
        std::cout << "\tmissingLUIntervals_" << std::endl;
        std::cout << matches[1].str() << std::endl;
#endif
        continue;
      }

      if (boost::regex_match(currStr, matches, reRuIntervals)) // data is upper bounded
      {
        MisVal misVal;
        misVal.first = missingRUIntervals_;
        misVal.second.push_back(str2type<Type>(matches[1].str()) + offset);
        augData.setMissing(i, misVal);
#ifdef MC_DEBUG
        std::cout << "\tmissingRUIntervals_" << std::endl;
        std::cout << matches[1].str() << std::endl;
#endif
        continue;
      }

      MisVal misVal; // in all other cases data is considered completely missing
      misVal.first = missing_;
      augData.setMissing(i, misVal);
#ifdef MC_DEBUG
      std::cout << "\tmissing_" << std::endl;
#endif
    }
  }
  else
  {
    std::stringstream sstm;
    sstm << "Data from the variable: " << idData << " has been requested but is absent from the provided data."
         << " Please check that all the necessary data is provided." << std::endl;
    warnLog += sstm.str();
  }
}

} /* namespace mixt */
#endif /* MIXT_DATAHANDLERR_H_ */
