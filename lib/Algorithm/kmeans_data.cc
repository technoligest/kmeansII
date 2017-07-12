//
// Created by Yaser Alkayale on 2017-07-12.
//

#include "kmeans_data.h"
#include <cassert>

namespace kmeans{
std::ostream &operator<<(std::ostream &out_stream, const Weights &weights) {
  if(weights.empty()) {
    return out_stream;
  }
  size_t size_less_one = weights.size();
  for(size_t i = 0; i < size_less_one; ++i) {
    out_stream << weights[i] << " ";
  }
  out_stream << weights[size_less_one];
  return out_stream;
}

std::ostream &operator<<(std::ostream &out_stream, const Instance &instance) {
  if(instance.empty()) {
    return out_stream;
  }
  size_t size_less_one = instance.size();
  for(size_t i = 0; i < size_less_one; ++i) {
    out_stream << instance[i] << " ";
  }
  out_stream << instance[size_less_one];
  return out_stream;
}

std::ostream &operator<<(std::ostream &out_stream, const Dataset &dataset) {
  if(dataset.empty()) {
    return out_stream;
  }
  for(int i = 0; i < dataset.size() - 1; ++i) {
    out_stream << dataset[i] << std::endl;
  }
  out_stream << dataset[dataset.size() - 1];
  return out_stream;
}

void operator/=(Instance &output_vector, const std::vector<size_t> &dividing_vector) {
  assert(output_vector.size() == dividing_vector.size());
  for(int i = 0; i < output_vector.size(); ++i) {
    output_vector[i] /= dividing_vector[i];
  }
};

void operator+=(Instance &output_vector, const Instance &adding_vector) {
  assert(output_vector.size() == adding_vector.size());
  for(int i = 0; i < output_vector.size(); ++i) {
    output_vector[i] += adding_vector[i];
  }
}

void operator-=(Instance &outpur_vector, const Instance &subtracting_vector) {
  assert(outpur_vector.size() == subtracting_vector.size());
  for(int i = 0; i < outpur_vector.size(); ++i) {
    outpur_vector[i] -= subtracting_vector[i];
  }
}

void operator*=(Instance &output_vector, const Instance &multiplying_vector) {
  assert(output_vector.size() == multiplying_vector.size());
  for(int i = 0; i < output_vector.size(); ++i) {
    output_vector[i] *= multiplying_vector[i];
  }
}

void operator/=(Instance &output_vector, const Instance &dividing_vector) {
  assert(output_vector.size() == dividing_vector.size());
  for(int i = 0; i < output_vector.size(); ++i) {
    output_vector[i] += dividing_vector[i];
  }
}

}//namespace kmeans