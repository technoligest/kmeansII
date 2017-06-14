#include "../pkgs/macro-argparse-plain.hh"

#pragma once

DEF_ARGUMENT_CLASS(
        KmeansArgs,
        std::string,	inputFileName,		"",	            REQUIRED, OPT_SLH(-i, --input, "What is the input file?"),
        std::string,    outputFileName,	    "output.txt",	OPTIONAL, OPT_SLH(-o,--output, "What is the output file name?"),
        std::string,    algorithm,          "kmeans",		REQUIRED, OPT_SLH(-a,--algorithm, "What algorithm to use? (Kmeans, Kmeans++, KmeansII)"),
        int,            k,   1,              REQUIRED, OPT_SH(-k, "Number of clusters"),
        double,          l, 2,              OPTIONAL, OPT_SH(-l, "oversampling factor (only for kmeansII)")
//bool,			decorate,	false,		OPTIONAL, OPT_SLWH(-d, --decorate, true, "decoreate the output")
);