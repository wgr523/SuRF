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
    SuRF* surf = new SuRF(keys);

    // use default dense-to-sparse ratio; specify suffix type and length
    SuRF* surf_hash = new SuRF(keys, surf::kHash, 8, 0);
    SuRF* surf_real = new SuRF(keys, surf::kReal, 0, 8);

    // customize dense-to-sparse ratio; specify suffix type and length
    SuRF* surf_mixed = new SuRF(keys, true, 16,  surf::kMixed, 4, 4);

    //----------------------------------------
    // point queries
    //----------------------------------------
    std::cout << "Point Query Example: fase" << std::endl;
    
    std::string key = "fase";
    
    if (surf->lookupKey(key))
	std::cout << "False Positive: "<< key << " found in basic SuRF" << std::endl;
    else
	std::cout << "Correct: " << key << " NOT found in basic SuRF" << std::endl;

    if (surf_hash->lookupKey(key))
	std::cout << "False Positive: " << key << " found in SuRF hash" << std::endl;
    else
	std::cout << "Correct: " << key << " NOT found in SuRF hash" << std::endl;

    if (surf_real->lookupKey(key))
	std::cout << "False Positive: " << key << " found in SuRF real" << std::endl;
    else
	std::cout << "Correct: " << key << " NOT found in SuRF real" << std::endl;

    if (surf_mixed->lookupKey(key))
	std::cout << "False Positive: " << key << " found in SuRF mixed" << std::endl;
    else
	std::cout << "Correct: " << key << " NOT found in SuRF mixed" << std::endl;

    //----------------------------------------
    // point queries
    //----------------------------------------
    std::cout << "Point Query Example: fast" << std::endl;
    
    key = "fast";
    
    if (!surf->lookupKey(key))
	std::cout << "False Negative: "<< key << "NOT found in basic SuRF" << std::endl;
    else
	std::cout << "Correct: " << key << " found in basic SuRF" << std::endl;

    if (!surf_hash->lookupKey(key))
	std::cout << "False Negative: "<< key << "NOT found in hash SuRF" << std::endl;
    else
	std::cout << "Correct: " << key << " found in hash SuRF" << std::endl;

    if (!surf_real->lookupKey(key))
	std::cout << "False Negative: "<< key << "NOT found in real SuRF" << std::endl;
    else
	std::cout << "Correct: " << key << " found in real SuRF" << std::endl;

    if (!surf_mixed->lookupKey(key))
	std::cout << "False Negative: "<< key << "NOT found in mixed SuRF" << std::endl;
    else
	std::cout << "Correct: " << key << " found in mixed SuRF" << std::endl;

    return 0;
}

