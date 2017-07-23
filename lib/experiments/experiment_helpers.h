//
// Created by Yaser Alkayale on 2017-07-14.
//

#ifndef KMEANSII_EXPERIMENT_HELPERS_H
#define KMEANSII_EXPERIMENT_HELPERS_H

#include "../algorithm/kmeans.h"

namespace kmeans{
namespace experiments{
namespace helpers{

void heapSort(std::vector<size_t> &arr);
ull lastNumberedFile(const std::string directory, std::string prefix);

}//namespace helpers
}//namespace experiments
}//namespace kmean


#endif //KMEANSII_EXPERIMENT_HELPERS_H
