/* MixtComp version 4  - july 2019
 * Copyright (C) Inria - Université de Lille - CNRS*/

/*
 *  Project:    MixtComp
 *  Created on: August 7, 2018
 *  Authors:    Vincent KUBICKI <vincent.kubicki@inria.fr>
 **/

#ifndef LIB_RUN_LEARN_H
#define LIB_RUN_LEARN_H

#include <Composer/MixtureComposer.h>
#include <Statistic/RNG.h>
#include <Strategy/GibbsStrategy.h>
#include <Strategy/SEMStrategy.h>
#include <Various/Timer.h>

namespace mixt {

/**
 * The learn algorithm is encapsulated in this function.
 */
template<typename Graph>
void learn(const Graph& algo, const Graph& data, const Graph& desc, Graph& out) {
	Graph param; // dummy Graph to be provided as unused argument in setDataParam in learning

#ifdef MC_VERBOSE
	std::cout << "MixtComp, learn, version: " << version << std::endl;
	std::cout << "Deterministic mode: " << deterministicMode() << std::endl;
//	std::cout<< "Number of threads: " << omp_get_num_threads() << std::endl;
#endif

	Timer totalTimer("Total Run");

	std::string warnLog; // string to log warnings

	// Create the composer and read the data
	MixtureComposer composer(algo);

	Timer readTimer("Read Data");
	warnLog += createAllMixtures(algo, desc, data, param, out, composer);
	warnLog += composer.setDataParam(learning_, data, param);
	readTimer.finish();

	if (0 < warnLog.size()) {
		out.add_payload( { }, "warnLog", warnLog);
		return;
	}

	// Run the SEM strategy

	std::pair<Real, Real> timeSEM;

	SemStrategy<Graph> semStrategy(composer, algo);
	Timer semStratTimer("SEM Strategy Run");
	warnLog += semStrategy.run(timeSEM);
	semStratTimer.finish();

	if (0 < warnLog.size()) {
		out.add_payload( { }, "warnLog", warnLog);
		return;
	}

	// Run the Gibbs strategy

	std::pair<Real, Real> timeGibbs;

	GibbsStrategy<Graph> gibbsStrategy(composer, algo, 2);
	Timer gibbsStratTimer("Gibbs Strategy Run");
	warnLog += gibbsStrategy.run(timeGibbs);
	gibbsStratTimer.finish();

	if (0 < warnLog.size()) {
		out.add_payload( { }, "warnLog", warnLog);
		return;
	}

	composer.computeObservedProba(); // whether the Gibbs comes after a SEM or is used in prediction, parameters are known at that point
	composer.setObservedProbaCache();

	// Run has been successful, export everything

#ifdef MC_VERBOSE
	composer.writeParameters();
#endif

	if (0 < warnLog.size()) {
		out.add_payload({}, "warnLog", warnLog);
		return;
	}

	Real runTime = totalTimer.finish();

	out.add_payload( { "mixture", "runTime" }, "total", runTime);
	out.add_payload( { "mixture", "runTime" }, "SEMBurnIn", timeSEM.first);
	out.add_payload( { "mixture", "runTime" }, "SEMRun", timeSEM.second);
	out.add_payload( { "mixture", "runTime" }, "GibbsBurnIn", timeGibbs.first);
	out.add_payload( { "mixture", "runTime" }, "GibbsRun", timeGibbs.second);

	composer.exportMixture(out);
	composer.exportDataParam(out);
	out.addSubGraph( { }, "algo", algo);
}

}

#endif
