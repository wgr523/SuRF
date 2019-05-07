#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include "dynamic_include/dynamic_surf.hpp"

using namespace surf;
using namespace std::chrono;

int LookUpKeyTest(DynamicSurf* surf, const std::string& key, bool ans){
    bool real = surf->lookupKey(key);
    if (ans == real)
        return 0;
    else if(real == true)
        return 1;
    else {
        std::cout << "Fatal !!!! False Negative " << std::endl;
        exit(1);
    }
}

int LookUpRangeTest(DynamicSurf* surf, const std::string& left_key, const bool left_inclusive, 
        const std::string& right_key, const bool right_inclusive, bool ans){
    bool real = surf->lookupRange(left_key, left_inclusive,right_key, right_inclusive);
    if (ans == real)
        return 0;
    else if(real == true)
        return 1;
    else{
        std::cout << "left key: "<< left_key << std::endl;
        std::cout  << "right key: "<< right_key<< std::endl;
        std::cout << "Fatal !!!! False Negative " << std::endl; 
        exit(1);
    }


}

int readFile( std::vector<std::string> * array, char* filename)
{
    short loop=0; //short for loop for input
    int total_size = 0;
    std::string line; //this will contain the data read from the file
    std::ifstream myfile (filename); //opening the file.
    if (myfile.is_open()) //if the file is open
    {
        while (! myfile.eof() ) //while the end of file is NOT reached
        {
            getline (myfile,line); //get one line from the file
            if(line != "") {
                array ->push_back(line);
                total_size += line.size();
            }
            // std::cout << array->at(loop) << std::endl; //and output it
            loop++;
        }
        myfile.close(); //closing the file
    }
    else std::cout << "Unable to open file"; //if the file is not open output
    return total_size;
}

void eval(DynamicSurf* surf, const std::vector<std::string>& dataSet, const std::vector<std::string>& dataSetRef) {
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    //insert all datasets
    for(auto const& key: dataSet) {
        surf->insertKey(key);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();

    std::cout<< "Insert " << dataSet.size() << " keys, " << duration << " micro sec" << std::endl;
    //std::cout << "Serialized Size: " <<surf->serializedSize()<< std::endl;
    //std::cout << "Mem Size: " <<surf->getMemoryUsage()<< std::endl;


    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    //random point lookup
    int i = 0;
    int FP= 0;
    for (int j=0;j<dataSet.size(); j++) {
        FP += LookUpKeyTest(surf,dataSet[j],true);
        i++;
    }
    for (int j=0;j<dataSetRef.size(); j++) {
        FP += LookUpKeyTest(surf,dataSetRef[j],false);
        i++;
    }
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    duration = duration_cast<microseconds>( t4 - t3 ).count();

    std::cout<< ""<< i<<" point lookup " << duration << " micro sec " << "FP and FP rate " << FP<<", "<<FP*100/2000 <<"%" <<std::endl;


    high_resolution_clock::time_point t5 = high_resolution_clock::now();
    //random range lookup
    i = 0;
    FP = 0;
    for (int j=0;j<dataSet.size(); j++) {
        FP += LookUpRangeTest(surf,dataSet[j],true,dataSet[dataSet.size()-1],true,true);
        i++;
    }
    for (int j=0;j<dataSetRef.size(); j++) {
        FP += LookUpRangeTest(surf,dataSetRef[j],true,dataSetRef[dataSetRef.size()-1],true,false);
        i++;
    }
    high_resolution_clock::time_point t6 = high_resolution_clock::now();

    duration = duration_cast<microseconds>( t6 - t5 ).count();

    std::cout<< ""<< i<<" range lookup " << duration << " micro sec " << "FP and FP rate " << FP<<", "<<FP*100/2000 <<"%" <<std::endl;

    high_resolution_clock::time_point t7 = high_resolution_clock::now();
    //delate all datasets
    for(auto const& key: dataSet) {
        surf->deleteKey(key);
    }
    high_resolution_clock::time_point t8 = high_resolution_clock::now();

    duration = duration_cast<microseconds>( t8 - t7 ).count();

    std::cout<< "Delate all keys (that are just inserted) " << duration << " micro sec" << std::endl;
    //std::cout << "Serialized Size: " <<surf->serializedSize()<< std::endl;
    //std::cout << "Mem Size: " <<surf->getMemoryUsage()<< std::endl;
}
int main(int argc, char *argv[]) {
    if (argc<4) {
        std::cout<<"Please add 3 file names.";
        return 0;
    }
    std::vector<std::string> keys = { };
    std::vector<std::string> dataSet = { };
    std::vector<std::string> dataSetRef = { };
    //std::vector<std::string> keys = {
    //    "a"
    //};


    int size0 = readFile(&keys, argv[1]);//size of keys of init
    int size1 = readFile(&dataSet, argv[2]);
    int size2 = readFile(&dataSetRef, argv[3]);

    std::map<std::string, bool> mainMemory = {};
    for(auto const& key: keys) {
        mainMemory[key] = true;
    }

    int bufferSize;
    //initialize dynamic surf
    bufferSize = 15000;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    DynamicSurf* surf = new DynamicSurf(keys,bufferSize,&mainMemory);//this may be changed

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();

    std::cout << "Buffer Size: " << bufferSize<< std::endl;
    std::cout << "Estimated Buffer Mem Size: " <<(double)(size0+size1+size2)/(keys.size()+dataSet.size()+dataSetRef.size()) * bufferSize<< std::endl;
    std::cout<< "Init with " << keys.size() << " keys, " << duration << " micro sec" << std::endl;
    std::cout << "Serialized Size: " <<surf->serializedSize()<< std::endl;
    std::cout << "Mem Size: " <<surf->getMemoryUsage()<< std::endl;

    eval(surf, dataSet, dataSetRef);
    return 0;
}
