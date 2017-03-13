/* MixtComp version 2.0  - 13 march 2017
 * Copyright (C) Inria - Lille 1 */

/*
 *  Project:    MixtComp
 *  Created on: January 20, 2015
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#ifndef MIXT_MULTINOMIALSTATISTIC_H
#define MIXT_MULTINOMIALSTATISTIC_H

#include <iostream>
#include <ctime>
#include <boost/random.hpp>
#include "../LinAlg/mixt_LinAlg.h"
#include "../IO/mixt_IO.h"
#include "../Various/mixt_Constants.h"

namespace mixt
{

class MultinomialStatistic
{
  public:

    MultinomialStatistic();

    /** Sample a value from a binomial law with  */
    int sampleBinomial(Real proportion)
    {
      if (generator_() < proportion)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }

    /** Sample a value from a multinomial law with coefficient of modalities provided */
    template<typename T>
    int sample(const T& proportion)
    {
      Real x = generator_();

      Real cumProb = 0.; // cumulative probability
      int index = 0;

      for (int i = 0, ie = proportion.size();
           i < ie;
           ++i)
      {
        cumProb += proportion(i);
        if (x < cumProb)
        {
          return index;
        }
        ++index;
      }
      return -1;
    }

    template <typename T>
    void shuffle(T& data)
    {
      std::random_shuffle(data.begin(),
                          data.end(),
                          g_);
    }

    template <typename T>
    Real entropy(const T& data)
    {
      Real h = 0.;
      for(typename T::const_iterator it = data.begin();
          it != data.end();
          ++it)
      {
        h += *it * std::log(*it);
      }
      return h;
    }

    /**
     * Uniform int sample
     * @param low lower bound of the support
     * @param high higher bound of the support
     * @return integer uniformly sampled from [low:high]
     */
    int sampleInt(int low, int high);

  private:
    /** Random number generator */
    boost::random::mt19937 rng_;

    boost::random::uniform_real_distribution<> uni_;

    boost::random_number_generator<boost::mt19937> g_;

    boost::variate_generator<boost::random::mt19937&,
                             boost::random::uniform_real_distribution<> > generator_;

};

} // namespace mixt

#endif // MIXT_EXPONENTIALSTATISTIC_H
