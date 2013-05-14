#ifndef IDeveloper_H_
#define IDeveloper_H_
/**@file IDeveloper.h
 * @brief
 */
#include <fstream>
#include <vector>
#include "framework/DataHandling/DataHandler.h"
class Model;
class IDeveloper
{
  public:
    IDeveloper();
    IDeveloper(char id);
    virtual void setModel(Model*);
    virtual void initializeStep() = 0;
    virtual IDeveloper* clone() = 0;
    virtual void imputationStep() {/**Do nothing by default*/}
    virtual void samplingStep() = 0;
    virtual void paramUpdateStep() = 0;
    virtual void storeIntermediateResults(int iteration) {/**Do nothing by default*/}
    virtual void finalizeStep() {/**Do nothing by default*/}
    virtual double posteriorProbability(int sample_num,int Cluster_num) = 0;
    virtual double logLikelihood() = 0;
    virtual int freeParameters() const = 0;
    virtual void setData() = 0;
    virtual void writeParameters(std::ostream&) const {};

    void setID(char id);
    virtual ~IDeveloper(){};
  protected:
    Model * p_model_;
    int nbVariable_;
    char id_;

    //protected functions
    int nbCluster() const;
    int nbSample() const;
    double** conditionalProbabilities() const;
    int* classLabels() const;
    double* proportions() const;

};

inline void IDeveloper::setID(char id){
  id_ = id;
}

inline void IDeveloper::setModel(Model* model){
  p_model_ = model;
}

#endif /* IDeveloper_H_ */
