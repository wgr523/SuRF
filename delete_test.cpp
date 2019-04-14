#include <iostream>
#include <vector>

#include "dynamic_include/surf.hpp"

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
    SuRF* surf = new SuRF(keys, true, 16, surf::kNone, 0, 0);//change 16 to smaller e.g. 0 will make it use dense louds encoding.

    std::cout << "Serialized Size: " <<surf->serializedSize()<< std::endl;
    std::cout << "Mem Size: " <<surf->getMemoryUsage()<< std::endl;
    //----------------------------------------
    // point queries
    //----------------------------------------
    for (auto key = keys.begin(); key!=keys.end(); ++key) {
        std::cout << "Point Query Example: " <<*key<< std::endl;
        if (!surf->lookupKey(*key))
            std::cout << "False Negative: "<< *key << " NOT found in basic SuRF" << std::endl;
        else
            std::cout << "Correct: " << *key << " found in basic SuRF" << std::endl;

        if (!surf->remove(*key))
            std::cout << "False Negative: "<< *key << " NOT removed in basic SuRF" << std::endl;
        else
            std::cout << "Correct: " << *key << " removed in basic SuRF" << std::endl;

        if (!surf->lookupKey(*key))
            std::cout << ""<< *key << " NOT found in basic SuRF" << std::endl;
        else
            std::cout << "" << *key << " found in basic SuRF" << std::endl;
        if (!surf->remove(*key))
            std::cout << ""<< *key << " NOT found in basic SuRF" << std::endl;
        else
            std::cout << "" << *key << " found in basic SuRF" << std::endl;
    }
    // basic surf
    surf = new SuRF(keys, true, 0, surf::kNone, 0, 0);

    std::cout << std::endl;
    //----------------------------------------
    // range queries
    //----------------------------------------
    for (auto key = keys.begin(); key!=keys.end(); ++key) {
        std::cout << "Range Query Example: " <<*key<< std::endl;
        if (!surf->lookupRange(*key, true, "z", false))
            std::cout << "False Negative: "<< *key << " NOT found in basic SuRF" << std::endl;
        else
            std::cout << "Correct: " << *key << " found in basic SuRF" << std::endl;

        if (!surf->remove(*key))
            std::cout << "False Negative: "<< *key << " NOT removed in basic SuRF" << std::endl;
        else
            std::cout << "Correct: " << *key << " removed in basic SuRF" << std::endl;

        if (!surf->lookupRange(*key, true, "z", false))
            std::cout << ""<< *key << " NOT found in basic SuRF" << std::endl;
        else
            std::cout << "Correct (expect the last one), although " << *key << " removed, but range still in basic SuRF" << std::endl;
    }
    return 0;
}

