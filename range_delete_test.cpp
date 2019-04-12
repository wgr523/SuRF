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

    // basic surf, all dense
    SuRF* surf = new SuRF(keys, true, 0, surf::kNone, 0, 0);

    //----------------------------------------
    // point queries
    //----------------------------------------
    std::cout << "Dense. All output should be first 1 then 0" << std::endl;
    for (auto key = keys.begin(); key!=keys.end(); ++key) {
        std::cout << "Range Query Example: " <<*key<< std::endl;
        std::cout << surf->lookupKey(*key)<<std::endl;
        std::cout << surf->lookupRange(*key, true, *key, true)<<std::endl;
        surf->remove(*key);
        std::cout << surf->lookupKey(*key)<<std::endl;
        std::cout << surf->lookupRange(*key, true, *key, true)<<std::endl;
    }
    // basic surf, all sparse
    surf = new SuRF(keys, false, 0, surf::kNone, 0, 0);

    //----------------------------------------
    // point queries
    //----------------------------------------
    std::cout << "Sparse. All output should be first 1 then 0" << std::endl;
    for (auto key = keys.begin(); key!=keys.end(); ++key) {
        std::cout << "Range Query Example: " <<*key<< std::endl;
        std::cout << surf->lookupKey(*key)<<std::endl;
        std::cout << surf->lookupRange(*key, true, *key, true)<<std::endl;
        surf->remove(*key);
        std::cout << surf->lookupKey(*key)<<std::endl;
        std::cout << surf->lookupRange(*key, true, *key, true)<<std::endl;
    }
    return 0;
}

