#include <iostream>
#include "../src/framework/mixt_Facade.h"
#include "../src/framework/mixt_Data.h"
#include "../src/stkpp/projects/Clustering/include/GammaMixtureModels/STK_Gamma_ajk_bjk.h"
#include "../src/mixtures/StkppMixtures/mixt_GammaMixture.h"

int main(){
  int nbClusters = 2;

  // create object of framework facade
  mixt::Facade myFacade;

  // create the composer, indicating the number of clusters
  myFacade.createComposerModel(nbClusters);

  // register mixtures
  int nbVar;
  mixt::Data<double> data;
  mixt::DataHandler dataHandler;
  dataHandler.readDataFromFile(std::string("./data/gaussiandata.csv"),',');
  data.getData(dataHandler,'G',nbVar);
  IMixture* gamma = new mixt::Gamma_pk_ajk_bjk(nbClusters);
  myFacade.registerMixture(*gamma);

  // create the strategy
  myFacade.createSemStrategy( STK::Clust::randomInit_ // init type
                            , 2 // number of initialization trials
                            , 20 // number of burn-in iterations
                            , 100 ); // number of iterations

  //run the facade
  myFacade.run();

  gamma->writeParameters(std::cout);

  delete gamma;

  return 0;
}
