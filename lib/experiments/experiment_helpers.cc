//
// Created by Yaser Alkayale on 2017-07-14.
//

#include <dirent.h>
#include "experiment_helpers.h"

namespace kmeans{
namespace experiments{
namespace helpers{

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(std::vector<size_t> &arr, size_t n, size_t i) {
  size_t largest = i;  // Initialize largest as root
  size_t l = 2 * i + 1;  // left = 2*i + 1
  size_t r = 2 * i + 2;  // right = 2*i + 2

  if(l < n && arr[l] > arr[largest])
    largest = l;

  if(r < n && arr[r] > arr[largest])
    largest = r;

  if(largest != i) {
    std::swap(arr[i], arr[largest]);

    // Recursively heapify the affected sub-tree
    heapify(arr, n, largest);
  }
}


void heapSort(std::vector<size_t > &arr) {
  size_t n = arr.size();
  for(size_t i = n / 2 - 1;; --i){
    heapify(arr, n, i);
    if(i==0){
      break;
    }
  }

  for(size_t i = n - 1; ; --i) {
    std::swap(arr[0], arr[i]);
    heapify(arr, i, 0);
    if(i==0){
      break;
    }
  }
}


/*
 * Given the prefix and the directory return the last numbered file in this directory.
 */
ull lastNumberedFile(const std::string directory, std::string prefix) {
  std::cout << "prefix" << prefix << std::endl;
  DIR *dir;
  struct dirent *ent;
  ull nextNum = 0;
  if((dir = opendir(directory.c_str())) != NULL) {
    /* print all the files and directories within directory */
    while((ent = readdir(dir)) != NULL) {
      std::string temp = ent->d_name;
      std::cout << temp << std::endl;
      ull tempNextNum = 0;
      if(temp.substr(0, prefix.size()) == prefix) {
        if(nextNum == 0) {
          nextNum = 1;
        }
        std::string nextNumstring = "";
        for(int i = prefix.size(); i < temp.size(); ++i) {
          try {
            stoi(std::string(1, ent->d_name[i]));
            nextNumstring += std::string(1, ent->d_name[i]);
          }
          catch(std::invalid_argument e) {
            break;
          }
        }
        try {
          tempNextNum = stoull(nextNumstring) + 1;
        }
        catch(std::invalid_argument e) {
          std::cout << "Something went out in finding the right number of the new file. (Parsing the final num)"
                    << std::endl;
        }
      }
      if(tempNextNum > nextNum) {
        nextNum = tempNextNum;
      }
    }
    closedir(dir);
  } else {
    /* could not open directory */
    perror("");
    return EXIT_FAILURE;
  }
  return nextNum;
}




}//namespace helpers
}//namespace experiments
}//namespace kmeans
