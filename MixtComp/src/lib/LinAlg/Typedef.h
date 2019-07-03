/* MixtComp version 4  - july 2019
 * Copyright (C) Inria - Université de Lille - CNRS*/

/*
 *  Project:    MixtComp
 *  Created on: February 24, 2016
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <cstdlib>
#include <string>

namespace mixt {

/** Eigen storage is column-major by default, which suits the main way of accessing data,
 * by looping over individuals instead of variables */
typedef double Real;
// typedef std::size_t Index;
// typedef int Index;
typedef unsigned long Index;

typedef long Integer;

Real toReal(const std::string& s);

Index toIndex(const std::string& s);

}

#endif // TYPEDEF_H
