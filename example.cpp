#include <iostream>
#include <vector>

#include "include/surf.hpp"

using namespace surf;

int main() {
    std::vector<std::string> keys = {
	"f",
	"far",
    "farther",
	"fas",
	"fast",
	"s",
	"top",
	"toy",
	"trie",
    "tripper",
    "trying",
    };

    SuRF* surf = new SuRF(keys, true, 64, surf::kNone, 0, 0);

    //----------------------------------------
    // point queries
    //----------------------------------------
    surf->iterAll("f");
    std::cout<<std::endl;
    for (auto key = keys.begin(); key!=keys.end(); ++key) {
        surf->remove(*key);
        surf->iterAll("f");
    }
    std::cout<<std::endl;
    //surf->iterAll("f");
    return 0;
}

