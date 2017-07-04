//
// Created by Yaser Alkayale on 2017-07-04.
//

#ifndef KMEANSII_EXPERIMENTSREADER_HH
#define KMEANSII_EXPERIMENTSREADER_HH

#include <istream>
#include <sstream>
#include "../handlers/data.hh"
#include "experiments.hh"

using namespace std;
namespace ExperimentReaderHelpers{
 inline Dataset readCentres(std::istream &file){
   Dataset result;
   while(file.good()){
     string line;
     std::getline(file, line);
     std::cout << "===" << line.substr(0, 3) << endl;
     if(line.substr(0, 3) == "End"){
       std::cout << "Returning result." << endl;
       return result;
     }
     std::stringstream lineStream(line);
     std::string item;
     Instance i;
     while(std::getline(lineStream, item, ' ')){
       std::cout << item << endl;
       try{
         double k = stod(item);
         std::cout << k << endl;
         i.push_back(stod(item));
       }
       catch(std::invalid_argument e){

         std::cout << item << "---Invalid entry in the centres." << std::endl;
       }
     }
     if(!i.empty())
       result.push_back(i);
   }
   result.clear();
   return result;
 };

 inline ExperimentResult readExperimentBody(std::istream &file){
   string line;
   ExperimentResult result;
   while(file.good()){
     string delimed;
     getline(file, line, ':');
     std::cout << line << endl;
     if(line == "Algorithm"){
       std::getline(file, line);
       std::cout << "--" << line.substr(1) << "--" << endl;
       result.algorithm = line.substr(1);
     } else if(line == "Sum of distance squared to centre"){
       std::getline(file, line);
       std::cout << "--" << line.substr(1) << "--" << endl;
       try{
         result.distanceSquared = stod(line.substr(1));
       }
       catch(std::invalid_argument e){
         std::cout << "Invalid File Input for Distance Squared." << endl;
       }
     } else if(line == "Time to pick the seeds"){
       std::getline(file, line);
       std::cout << "--" << line.substr(1) << "--" << endl;
       try{
         result.seedPickerTime = stoull(line.substr(1));
       }
       catch(std::invalid_argument e){
         std::cout << "Invalid File Input for Time to pick the seeds." << endl;
       }
     } else if(line == "Number of iterations run"){
       std::getline(file, line);
       std::cout << "--" << line.substr(1) << "--" << endl;
       try{
         result.numIterations = stoull(line.substr(1));
       }
       catch(std::invalid_argument e){
         std::cout << "Invalid File Input for number of iterations run." << endl;
       }
     } else if(line == "Time to run the iterations"){
       std::getline(file, line);
       std::cout << "--" << line.substr(1) << "--" << endl;
       try{
         result.iterationTime = stoull(line.substr(1));
       }
       catch(std::invalid_argument e){
         std::cout << "Invalid File Input for time to run iterations." << endl;
       }
     } else if(line == "Start Centres"){
       std::getline(file, line);
       std::cout << "--" << line << "--" << endl;
       result.centres = readCentres(file);
     } else if(line.substr(0, 3) == "End"){
       return result;
     }
   }
   result.distanceSquared = -1;
   result.centres.clear();
   result.iterationTime = -1;
   result.numIterations = 0;
   result.algorithm = "NOTHING";
   result.seedPickerTime = 0;
   return result;
 }
}
using namespace ExperimentReaderHelpers;

inline vector<ExperimentResult> readExperiments(std::istream &file){
  vector<ExperimentResult> result;
  while(file.good()){
    string line;
    std::getline(file, line);
    std::cout << line << endl;
    if(line.substr(0, 3) == ">>>"){
      result.push_back(readExperimentBody(file));
    }
  }
  return result;
}

#endif //KMEANSII_EXPERIMENTSREADER_HH
