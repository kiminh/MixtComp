# MixtComp version 4.0  - july 2019
# Copyright (C) Inria - Université de Lille - CNRS

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
# 
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>

# @author Quentin Grimonprez
context("Write input JSON files for MixtComp")

test_that("Creation of algo file", {
  
  nClass <- 2
  nInd <- 15
  mcStrategy <- list(nbBurnInIter = 100,
                     nbIter = 100,
                     nbGibbsBurnInIter = 100,
                     nbGibbsIter = 100, 
                     nInitPerClass = 2,
                     nSemTry = 10,
                     confidenceLevel = 0.95,
                     notes = "You can add any note if you wish in unrequired fields like this one. They will be copied to the output also.")
  
  mode <- "learn"
  
  
  
  expectedJson <- '{
  "nClass": 2,
  "nInd": 15,
  "nbBurnInIter": 100,
  "nbIter": 100,
  "nbGibbsBurnInIter": 100,
  "nbGibbsIter": 100,
  "nInitPerClass": 2,
  "nSemTry": 10,
  "confidenceLevel": 0.95,
  "ratioStableCriterion": 0.99,
  "nStableCriterion": 20,
  "mode": "learn",
  "notes": "You can add any note if you wish in unrequired fields like this one. They will be copied to the output also."
}'
  
  algoJson <- createAlgoJson(nClass, nInd, mcStrategy, mode)
  expect_true(algoJson == expectedJson)
})


test_that("Creation of model file", {
  
  model <- list(varGaussian = list(type = "Gaussian", paramStr = "dummyStrTestGaussian"),
                varPoisson = list(type = "Poisson"),
                varCategorical = "Multinomial")
  
  
  expectedJson <- '{
  "varGaussian": {
    "type": "Gaussian",
    "paramStr": "dummyStrTestGaussian"
  },
  "varPoisson": {
    "type": "Poisson",
    "paramStr": ""
  },
  "varCategorical": {
    "type": "Multinomial",
    "paramStr": ""
  }
}'
  
  descriptorJson <- createModelJson(model)
  expect_true(descriptorJson == expectedJson)
})


test_that("Creation of data file: character version", {
  
  data <- data.frame(varGaussian = c("3", "?", "2.7", "3.4", "1.7", "2.99", "12.5", "3.1", "12.8", "?", "11", "4", "12.7", "3.05", "12.01"),
                     varPoisson = c("3", "13", "2", "4", "2", "?", "13", "3", "11", "2", "12", "4", "11", "?", "12"),
                     varCategorical = c("1", "2", "1", "1", "1", "1", "?", "{1, 2}", "2", "1", "2", "1", "2", "?", "2"))
  
  
  expectedJson <- '{
  "varGaussian": ["3", "?", "2.7", "3.4", "1.7", "2.99", "12.5", "3.1", "12.8", "?", "11", "4", "12.7", "3.05", "12.01"],
  "varPoisson": ["3", "13", "2", "4", "2", "?", "13", "3", "11", "2", "12", "4", "11", "?", "12"],
  "varCategorical": ["1", "2", "1", "1", "1", "1", "?", "{1, 2}", "2", "1", "2", "1", "2", "?", "2"]
}'
  
  dataJson <- createDataJson(data)
  expect_true(dataJson == expectedJson)
})

test_that("Creation of data file: numeric version", {
  
  data <- data.frame(varGaussian = c(3, 2.7, 3.4, 1.7, 2.99, 12.5, 3.1),
                     varPoisson = c(3, 13, 2, 4, 2, 1, 3),
                     varCategorical = c(1, 2, 1, 1, 1, 1, 2))
  
  
  expectedJson <- '{
  "varGaussian": ["3", "2.7", "3.4", "1.7", "2.99", "12.5", "3.1"],
  "varPoisson": ["3", "13", "2", "4", "2", "1", "3"],
  "varCategorical": ["1", "2", "1", "1", "1", "1", "2"]
}'
  
  dataJson <- createDataJson(data)
  expect_true(dataJson == expectedJson)
})

test_that("Creation of data file: case with one individuals", {
  
  data <- data.frame(varGaussian = "3",
                     varPoisson = "3",
                     varCategorical = "1")
  
  
  expectedJson <- '{
  "varGaussian": ["3"],
  "varPoisson": ["3"],
  "varCategorical": ["1"]
}'
  
  dataJson <- createDataJson(data)
  expect_true(dataJson == expectedJson)
})


