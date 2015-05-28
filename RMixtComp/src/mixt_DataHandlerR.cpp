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

/** @file mixt_DataHandlerR.cpp
 *  @brief In this file 
 **/

#include "mixt_DataHandlerR.h"

namespace mixt
{

DataHandlerR::DataHandlerR(Rcpp::List rList) :
    nbSample_(-1),
    nbVariables_(0),
    rList_(rList)
{}

DataHandlerR::~DataHandlerR()
{}

void DataHandlerR::writeInfo(std::ostream& os) const
{
  // show content
   for (InfoMap::const_iterator it = info_.begin(); it != info_.end(); ++it)
     os << "name: " << it->first << ", model: " << it->second << std::endl;
}

std::string DataHandlerR::listData()
{
#ifdef MC_DEBUG
  std::cout << "DataHandlerR::listData()" << std::endl;
  std::cout << "rList_.size(): " << rList_.size() << std::endl;
#endif
  std::string warnLog;
  for (int i = 0; i < rList_.size(); ++i)
  {
    Rcpp::List currList = rList_[i];

    std::string model = currList["model"];
    std::string id = currList["id"];
    Rcpp::CharacterVector data = currList["data"];

    // add to info_, and perform various checks
    std::pair<InfoMap::iterator, bool> ret; // parse descriptor file
    ret = info_.insert(std::pair<std::string, std::string>(id, model)); // check if identifier is already present
    if (ret.second == false) // if name already exists, return a warning
    {
      warnLog += std::string("Several variables bear the same name: ") + id + std::string(", while only a variable per name is allowed.\n");
    }
    if (data.size() == 0)
    {
      warnLog += std::string("Variable: ") + id + std::string(" has 0 samples.");
    }
    if (nbSample_ > 0 && nbSample_ != data.size())
    {
      warnLog +=   std::string("Variable: ") + id + std::string(" has ")
                 + type2str(data.size()) + std::string(" samples, while the previous variable had ")
                 + type2str(nbSample_) + std::string(" samples.\n");
    }

    nbSample_ = data.size(); // overwritten, because check has already been performed on the R side
    dataMap_[id] = i; // dataMap_[id] created if not already existing
    ++nbVariables_;
#ifdef MC_DEBUG
    std::cout << "DataHandlerR::readDataFromRListHelper()" << std::endl;
    std::cout << "\tid: " << id << std::endl;
    std::cout << "\tmodel: " << model << std::endl;
    std::cout << "\trList pos: " << i << std::endl;
#endif
  }
  return warnLog;
}

void DataHandlerR::writeDataMap() const
{
  std::cout << "Position of data in input: \n";
  for (DataMap::const_iterator it_id = dataMap_.begin(); it_id != dataMap_.end(); ++it_id)
  {
    std::cout << "\tname: " << (*it_id).first << "\n";
    std::cout << "\t\trList_ position: " << (*it_id).second << std::endl;
  }
}

} /* namespace mixt */
