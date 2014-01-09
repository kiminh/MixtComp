/*--------------------------------------------------------------------*/
/*     Copyright (C) 2004-2013  Serge Iovleff

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
 * Project:  stkpp::
 * created on: 15 nov. 2013
 * Author:   iovleff, S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
 **/

/** @file STK_DataHandler.h
 *  @brief In this file we define the data handler.
 **/


#ifndef STK_DATAHANDLER_H
#define STK_DATAHANDLER_H

#include <vector>

#include "STK_IDataHandler.h"
#include "STK_ReadWriteCsv.h"

namespace STK
{
/** @ingroup DManager
 *  The DataHandler class allow to read various csv files with their description
 *  files and to get the column by using an id.
 *  All files are stored in memory in a ReadWriteCsv structure.
 */
class DataHandler : public IDataHandler
{
  public:
    typedef IDataHandler::InfoMap InfoMap;
    /** default constructor */
    inline DataHandler() : IDataHandler()
    { data_.setWithNames(false); descriptor_.setWithNames(false);}
    /** destructor */
    inline virtual ~DataHandler() {}

    /** @return the number of sample (the number of rows of the data) */
    inline virtual int nbSample() const { return data_.rows().size();}
    /** @return the number of sample (the number of rows of the data) */
    inline virtual int nbVariable() const { return data_.size();}
    /** get the whole data set */
    inline ReadWriteCsv const& data() const { return data_;}
    /** get the whole descriptor set */
    inline ReadWriteCsv const& descriptor() const { return descriptor_;}

    /** read a data file and its companion description file. */
    bool readDataFromCsvFile(std::string const& datafile, std::string descriptorfile);

    /** return in an Array2D<int> the data with the given idData */
    virtual void getData(std::string const& idData, Array2D<int>& data, int& nbVariable) const;
    /** return in an Array2D<Real> the data with the given idModel */
    virtual void getData(std::string const& idData, Array2D<Real>& data, int& nbVariable) const;
    /** return in an Array2D<std::string> the data with the given idModel */
    virtual void getData(std::string const& idData, Array2D<std::string>& data, int& nbVariable) const;


  protected:
    /** lookup on the descriptors in order to get the columns with correct id
     *  @param idData id of the data to get
     **/
    std::vector<int> colIndex(std::string const& idData) const;

  private:
    /** data files */
    ReadWriteCsv data_;
    /** descriptor files */
    ReadWriteCsv descriptor_;
};


} // namespace STK

#endif /* STK_DATAHANDLER_H */
