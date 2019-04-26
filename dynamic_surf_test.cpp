#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "dynamic_include/surf.hpp"
#include "dynamic_include/dynamic_surf.hpp"

using namespace surf;

void LookUpKeyTest(DynamicSurf* surf, const std::string& key, bool ans){
    std::cout << std::endl << "Begin Test for SuRF Point look up, the key is "<< key << ", expected " << ans << std::endl;
   bool real = surf->lookupKey(key);
    if (ans == real)
        std::cout << "Correct "<< std::endl;
    else if(real == true)
        std::cout << "False Positive " << std::endl; 
    else
        std::cout << "Fatal !!!! False Negative " << std::endl; 
}

void LookUpRangeTest(DynamicSurf* surf, const std::string& left_key, const bool left_inclusive, 
		     const std::string& right_key, const bool right_inclusive, bool ans){
    std::cout << std::endl << "Begin Test for SuRF Range look up "<< " " <<
        "left key "<< left_key << " inclusive? " << left_inclusive << " " <<
        "right key "<< right_key << " inclusive? " << right_inclusive << " " <<
        "expected " << ans << std::endl;
    bool real = surf->lookupRange(left_key, left_inclusive,right_key, right_inclusive);
    if (ans == real)
        std::cout << "Correct "<< std::endl;
    else if(real == true)
        std::cout << "False Positive " << std::endl; 
    else
        std::cout << "Fatal !!!! False Negative " << std::endl; 

}

int readFile( std::vector<std::string> * array)
{
    short loop=0; //short for loop for input
    std::string line; //this will contain the data read from the file
    std::ifstream myfile ("words.txt"); //opening the file.
    if (myfile.is_open()) //if the file is open
    {
        while (! myfile.eof() ) //while the end of file is NOT reached
        {
            getline (myfile,line); //get one line from the file
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
	"f",
	"far",
	"fast",
	"s",
	"top",
	"toy",
	"trie",
    };

    std::map<std::string, bool> mainMemory = {};
    for(auto const& value: keys) {
            mainMemory[value] = true;
        }

    std::vector<std::string> dataSet = { };
    readFile(&dataSet);
   



    
    


    DynamicSurf* surf = new DynamicSurf(keys,4,&mainMemory);

    LookUpRangeTest(surf,"h",true,"happy",true,false);

    surf->insertKey("apple");
    surf->insertKey("z");
    surf->insertKey("hello");
    surf->insertKey("ha");
    
    //check all original keys
     for(auto const& value: keys) {
        LookUpKeyTest(surf,value,true);
    }


    LookUpRangeTest(surf,"h",true,"happy",false,true);

    surf->deleteKey("ha");
    surf->deleteKey("f");
    LookUpKeyTest(surf,"ha",false);
    LookUpKeyTest(surf,"f",false);

 
    LookUpRangeTest(surf,"h",true,"happy",false,false);

   
   
    return 0;
}
