#include <iostream>
#include <vector>

#include "include/surf.hpp"

using namespace surf;

int main() {
    std::vector<std::string> keys = {
	"f",
	"far",
	"fas",
	"fast",
	"s",
	"top",
	"toy",
	"trie",
    };

    SuRF* surf = new SuRF(keys, true, 64, surf::kNone, 0, 0);

    //----------------------------------------
    // point queries
    //----------------------------------------
    std::cout << surf->lookupKey("shit")<<std::endl;
    std::cout << "Sparse. All output should be first 1 then 0" << std::endl;
    for (auto key = keys.begin(); key!=keys.end(); ++key) {
        std::cout << "Range Query Example: " <<*key<< std::endl;
        std::cout << surf->lookupKey(*key)<<std::endl;
        //std::cout << surf->lookupRange(*key, true, *key, true)<<std::endl;
        std::cout << "Remove " <<*key<<", Result "<< surf->remove(*key) << std::endl;
        std::cout << surf->lookupKey(*key)<<std::endl;
        //std::cout << surf->lookupRange(*key, true, *key, true)<<std::endl;
    }
    return 0;
}

