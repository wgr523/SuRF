#include <iostream>
#include <vector>

#include "include/surf.hpp"
#include "include/dynamic_surf.hpp"

using namespace surf;

void LookUpKeyTest(DynamicSurf* surf, const std::string& key, bool ans){
    std::cout << "Begin Test for SuRF Point look up, the key is "<< key << ", expected " << ans << std::endl;
    if (ans == surf->lookupKey(key))
        std::cout << "Correct: "<< std::endl;
    else
        std::cout << "Wrong: " << std::endl; 
}

void LookUpRangeTest(DynamicSurf* surf, const std::string& left_key, const bool left_inclusive, 
		     const std::string& right_key, const bool right_inclusive, bool ans){
    std::cout << "Begin Test for SuRF Range look up "<< std::endl <<
        "left key "<< left_key << " inclusive? " << left_inclusive << std::endl <<
        "right key "<< right_key << " inclusive? " << right_inclusive << std::endl <<
        "expected " << ans << std::endl;
    if (ans == surf->lookupRange(left_key, left_inclusive,right_key, right_inclusive))
        std::cout << "Correct: "<< std::endl;
    else
        std::cout << "Wrong: " << std::endl; 
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


    // basic surf
    DynamicSurf* surf = new DynamicSurf(keys,3,5);

    surf->insertKey("apple");
    surf->insertKey("z");
    surf->insertKey("hello");
    surf->insertKey("happy");

    std::cout << "Testing creating new surf " <<surf->surfCollection.size()  << std::endl;

    //test
    LookUpKeyTest(surf,"fase",false);
    LookUpKeyTest(surf,"happy",true);
    LookUpKeyTest(surf,"far",true);
    LookUpRangeTest(surf,"h",true,"happy",true,true);
   
    return 0;
}
