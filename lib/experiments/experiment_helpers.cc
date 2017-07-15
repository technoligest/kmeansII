//
// Created by Yaser Alkayale on 2017-07-14.
//

#include <dirent.h>
#include "experiment_helpers.h"

namespace kmeans{
namespace experiments{
namespace helpers{

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
