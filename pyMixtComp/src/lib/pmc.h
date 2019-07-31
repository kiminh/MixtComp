/* MixtComp version 4  - july 2019
 * Copyright (C) Inria - Université de Lille - CNRS*/

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 **/

/*
 *  Project:    MixtComp
 *  Created on: June 13, 2019
 *  Author:    Quentin Grimonprez
 **/

#ifndef SRC_PMC_H_
#define SRC_PMC_H_

#include <boost/python.hpp>

boost::python::dict pmc(boost::python::dict algoPy, boost::python::dict dataPy, boost::python::dict descPy, boost::python::dict resLearnPy);

#endif /* SRC_PMC_H_ */
