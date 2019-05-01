#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "dynamic_include/dynamic_surf.hpp"

using namespace surf;

void LookUpKeyTest(DynamicSurf* surf, const std::string& key, bool ans){
    std::cout << std::endl << "Begin Test for SuRF Point look up, the key is "<< key << ", expected " << ans << std::endl;
    bool real = surf->lookupKey(key);
    if (ans == real)
        std::cout << "Correct "<< std::endl;
    else if(real == true)
        std::cout << "False Positive " << std::endl;
    else {
        std::cout << "Fatal !!!! False Negative " << std::endl;
        exit(1);
    }
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
    else {
        std::cout << "Fatal !!!! False Negative " << std::endl;
        exit(1);
    }
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
    for(auto const& key: keys) {
        mainMemory[key] = true;
    }

    DynamicSurf* surf = new DynamicSurf(keys,4,&mainMemory);

    LookUpRangeTest(surf,"h",true,"happy",true,false);

    surf->insertKey("apple");
    surf->insertKey("z");
    surf->insertKey("hello");
    surf->insertKey("ha");

    //check all original keys
    for(auto const& key: keys) {
        LookUpKeyTest(surf,key,true);
        LookUpRangeTest(surf,key,true,key,true,true);
    }


    LookUpRangeTest(surf,"h",true,"happy",false,true);

    surf->deleteKey("ha");
    LookUpKeyTest(surf,"ha",false);

    LookUpRangeTest(surf,"h",true,"happy",false,false);

    for(auto const& key: keys) {
        surf->deleteKey(key);
        LookUpKeyTest(surf,key,false);
        LookUpRangeTest(surf,key,true,key,true,false);
    }

    return 0;
}
