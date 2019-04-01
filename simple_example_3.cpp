#include <iostream>
#include <vector>

#include "include/surf.hpp"

using namespace surf;

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
    SuRF* surf = new SuRF(keys, true, 0, surf::kNone, 0, 0);

    //----------------------------------------
    // point queries
    //----------------------------------------
    for (auto key = keys.begin(); key!=keys.end(); ++key) {
        std::cout << "Point Query Example: " <<*key<< std::endl;
        if (!surf->lookupKey(*key))
            std::cout << "False Negative: "<< *key << "NOT found in basic SuRF" << std::endl;
        else
            std::cout << "Correct: " << *key << " found in basic SuRF" << std::endl;

        if (!surf->remove(*key))
            std::cout << "False Negative: "<< *key << "NOT removed in basic SuRF" << std::endl;
        else
            std::cout << "Correct: " << *key << " removed in basic SuRF" << std::endl;

        if (!surf->lookupKey(*key))
            std::cout << ""<< *key << "NOT found in basic SuRF" << std::endl;
        else
            std::cout << "" << *key << " found in basic SuRF" << std::endl;
        if (!surf->remove(*key))
            std::cout << ""<< *key << "NOT found in basic SuRF" << std::endl;
        else
            std::cout << "" << *key << " found in basic SuRF" << std::endl;
    }
    return 0;
}

