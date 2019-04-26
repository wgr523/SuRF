#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include "dynamic_include/surf.hpp"
#include "dynamic_include/dynamic_surf.hpp"

using namespace surf;
using namespace std::chrono;

int LookUpKeyTest(DynamicSurf* surf, const std::string& key, bool ans){
   bool real = surf->lookupKey(key);
    if (ans == real)
	return 0;
        //std::cout << "Correct "<< std::endl;
    else if(real == true)
        return 1;
        //std::cout << "False Positive " << std::endl; 
    else
        std::cout << "Fatal !!!! False Negative " << std::endl; 
	
}

int LookUpRangeTest(DynamicSurf* surf, const std::string& left_key, const bool left_inclusive, 
		     const std::string& right_key, const bool right_inclusive, bool ans){
    bool real = surf->lookupRange(left_key, left_inclusive,right_key, right_inclusive);
    if (ans == real)
        //std::cout << "Correct "<< std::endl;
	return 0;
    else if(real == true)
        //std::cout << "False Positive " << std::endl; 
	return 1;
    else{
        std::cout << "left key: "<< left_key << std::endl;
        std::cout  << "right key: "<< right_key<< std::endl;
        std::cout << "Fatal !!!! False Negative " << std::endl; 
    }
	

}

int readFile( std::vector<std::string> * array)
{
    short loop=0; //short for loop for input
    std::string line; //this will contain the data read from the file
    std::ifstream myfile ("words_small.txt"); //opening the file.
    if (myfile.is_open()) //if the file is open
    {
        while (! myfile.eof() ) //while the end of file is NOT reached
        {
            getline (myfile,line); //get one line from the file
            if(line != "")
                array ->push_back(line);
            // std::cout << array->at(loop) << std::endl; //and output it
            loop++;
        }
        myfile.close(); //closing the file
    }
    else std::cout << "Unable to open file"; //if the file is not open output
    system("PAUSE");
    return 0;
}

int readRef( std::vector<std::string> * array)
{
    short loop=0; //short for loop for input
    std::string line; //this will contain the data read from the file
    std::ifstream myfile ("words_large.txt"); //opening the file.
    if (myfile.is_open()) //if the file is open
    {
        while (! myfile.eof() ) //while the end of file is NOT reached
        {
            getline (myfile,line); //get one line from the file
            if(line != "")
                array ->push_back(line);
            // std::cout << array->at(loop) << std::endl; //and output it
            loop++;
        }
        myfile.close(); //closing the file
    }
    else std::cout << "Unable to open file"; //if the file is not open output
    system("PAUSE");
    return 0;
}

int main() {
    std::vector<std::string> keys = {
	"a"
    };

    std::map<std::string, bool> mainMemory = {};
    for(auto const& value: keys) {
            mainMemory[value] = true;
        }

    std::vector<std::string> dataSet = { };
    std::vector<std::string> dataSetRef = { };
    readFile(&dataSet);
    readRef(&dataSetRef);
   

    
    

    //initialize dynamic surf
    DynamicSurf* surf = new DynamicSurf(keys,50,&mainMemory);

   
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    //insert all datasets
     for(auto const& value: dataSet) {
       surf->insertKey(value);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>( t2 - t1 ).count();

    std::cout<< "insert all " << dataSet.size() << " datasets " << duration << " s" << std::endl;



    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    //random point lookup
    int i = 0;
    int FP= 0;
    while(i < 1000) {
       int RandIndex = rand() % dataSet.size();
       FP += LookUpKeyTest(surf,dataSet[RandIndex],true);
       i++;
    }
    while(i < 2000) {
       int RandIndex = rand() % dataSetRef.size();
       FP += LookUpKeyTest(surf,dataSetRef[RandIndex],false);
       i++;
    }
    high_resolution_clock::time_point t4 = high_resolution_clock::now();

    duration = duration_cast<microseconds>( t4 - t3 ).count();

    std::cout<< "random 2000 point lookup " << duration << " s " << "FP rate " << FP*100/2000 <<"%" <<std::endl;
     

    high_resolution_clock::time_point t5 = high_resolution_clock::now();
    //random range lookup
    i = 0;
    FP = 0;
    while(i < 1000) {
       int RandIndex = rand() % (dataSet.size()-1);
       FP += LookUpRangeTest(surf,dataSet[RandIndex],true,dataSet[dataSet.size()-1],true,true);
       i++;
    }
    while(i < 2000) {
       int RandIndex = rand() % dataSetRef.size();
       FP += LookUpRangeTest(surf,dataSetRef[RandIndex],true,dataSetRef[dataSetRef.size()-1],true,false);
       i++;
    }
    high_resolution_clock::time_point t6 = high_resolution_clock::now();

    duration = duration_cast<microseconds>( t6 - t5 ).count();

    std::cout<< "random 2000 range lookup " << duration << " s " << "FP rate " << FP*100/2000 << "%" <<std::endl;
    
    high_resolution_clock::time_point t7 = high_resolution_clock::now();
    //delate all datasets
     for(auto const& value: dataSet) {
       surf->deleteKey(value);
    }
    high_resolution_clock::time_point t8 = high_resolution_clock::now();

    duration = duration_cast<microseconds>( t8 - t7 ).count();

    std::cout<< "delate all datasets " << duration << " s" << std::endl;
    




    
   
   
    return 0;
}
