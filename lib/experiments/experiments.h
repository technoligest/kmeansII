/*
 * This file is th einterface for the outside world.
 * Another class would only need to import this file to
 * use all of the functionalities in the experiments namespace
 */
// Created by Yaser Alkayale on 2017-06-26.
#include <unordered_map>
#include "experiment_analyzer.h"
#include "experiments_reader.h"
#include "experiment_runner.h"
#include "experiment_result.h"


#ifndef KMEANSII_EXPERIMENTS_HH
#define KMEANSII_EXPERIMENTS_HH
namespace kmeans{
namespace experiments{

std::unordered_map<ull, Instance> pointsMap;

}//experiments
}//kmeans




#endif //KMEANSII_EXPERIMENTS_HH