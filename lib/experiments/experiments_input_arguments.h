//
// Created by Yaser Alkayale on 2017-08-31.
//

#ifndef KMEANSII_EXPERIMENTS_INPUT_ARGUMENTS_H
#define KMEANSII_EXPERIMENTS_INPUT_ARGUMENTS_H


#include "../pkgs/cmdArgsReader/macro-argparse-plain.hh"

namespace kmeans{
namespace experiments{

DEF_ARGUMENT_CLASS(
    KmeansExperimentsArgs,
    std::string, inputFileName, "", REQUIRED, OPT_SLH(-i, --input, "What is the input file?"),
    std::string, outputFileName, "none", OPTIONAL, OPT_SLH(-o, --output, "What is the output file name?"),
    int, k, 1, REQUIRED, OPT_SH(-k, "Number of clusters"),
    double, l, 2, REQUIRED, OPT_SH(-l, "oversampling factor (for kmeansII)"),
    int ,r,5,REQUIRED, OPT_SH(-r, "number of rounds (for kmeansII)"),
    int , numExperiments,1, REQUIRED, OPT_LH(-numExperiments, "How many experiments?")
);

}// namespace experiments
}// namespace kmeans


#endif //KMEANSII_EXPERIMENTS_INPUT_ARGUMENTS_H
