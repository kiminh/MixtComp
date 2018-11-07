#! /usr/local/bin/python3

import glob
import subprocess
import sys

if sys.version_info[0] < 3 and sys.version_info[1] < 5:
    raise Exception("Python 3.5 or a more recent version is required.")

print("Note that updateLib.py updates the src/lib subdirectory. To update the optim directory, get the sources from https://github.com/PatWie/CppNumericalSolvers and directly commit a new version.")

libSource = "../MixtComp/src/lib"

subprocess.call(["rsync", "-a", "--delete", libSource, "src"])

cppList = glob.iglob("src/lib/**/*.cpp", recursive=True)
oList = [filename[4:-3] + 'o' for filename in cppList]
oListStr = ' '.join(oList)
fileContent = "LIB_OFILES = " + oListStr

makevarsStr = r'''# MixtComp version 2.0  - 13 march 2017
# Copyright (C) Inria - Lille 1 */
#
#
# Project:    MixtComp
# Created on: October 10, 2018
# Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>

%s

PKG_CXXFLAGS = -Ilib -Ilib/LinAlg -DEIGEN_MATRIXBASE_PLUGIN=\"mixt_EigenMatrixBaseAddons.h\" -Ioptim/include
CXX_STD = CXX11

PKG_LIBS = $(LIB_OFILES)

.PHONY: all # a phony target is a target that is always considered out of date

all: $(SHLIB) # $(SHLIB) is RMixtComp.so or RMixtComp.dll

$(SHLIB): $(LIB_OFILES)
'''%(fileContent)

text_file = open("src/Makevars", "w")
text_file.write(makevarsStr)
text_file.close()