#ifndef DummySURF_H_
#define DummySURF_H_

#include <string>
#include <map>
#include <vector>
#include <algorithm>    
#include <iostream>
#include "config.hpp"
#include "louds_dense.hpp"
#include "louds_sparse.hpp"
#include "surf_builder.hpp"
#include "surf.hpp"


namespace surf{

class DummySurf{

public:
    //members
    SuRF* originSurf;
    std::map<std::string, bool>* mainMemory;

    //ctor/dctor
    DummySurf(){}
    
    DummySurf(const std::vector<std::string>& keys, int bufferSize, std::map<std::string, bool>* memory ) {
        originSurf = new SuRF(keys);
        mainMemory = memory;
    }

    DummySurf(const std::vector<std::string>& keys, const SuffixType suffix_type,
	 const level_t hash_suffix_len, const level_t real_suffix_len, int bufferSize
     , std::map<std::string, bool>* memory ) {
        originSurf = new SuRF(keys,suffix_type,hash_suffix_len,real_suffix_len);
        mainMemory = memory;

    }
    
    DummySurf(const std::vector<std::string>& keys,
	 const bool include_dense, const uint32_t sparse_dense_ratio,
	 const SuffixType suffix_type, const level_t hash_suffix_len, const level_t real_suffix_len, int bufferSize
     , std::map<std::string, bool>* memory ) {
	    originSurf = new SuRF(keys,include_dense,sparse_dense_ratio,suffix_type,hash_suffix_len,real_suffix_len);
        mainMemory = memory;

    }

    ~DummySurf(){}

    //functions
    void insertKey(const std::string& key);
    void deleteKey(const std::string& key);
    bool lookupKey(const std::string& key);
    bool lookupRange(const std::string& left_key, const bool left_inclusive, 
		     const std::string& right_key, const bool right_inclusive);

private:
    void merge();
};


void DummySurf::merge(){
    std::vector<std::string> keys = {};
    int size = 0;
    for (std::map<std::string, bool>::iterator i = mainMemory->begin(); i != mainMemory->end(); i++){
        keys.push_back(i->first);       
        size++;
    }
    originSurf = new SuRF(keys);
    
    std::cout << std::endl << "Merged: New Surf of size " << size << " created."  << std::endl;
}


void DummySurf::insertKey(const std::string& key){
    mainMemory->insert_or_assign(key,true);
    merge();
}

void DummySurf::deleteKey(const std::string& key){
    //erase return 0 if not found in buffer
    mainMemory->erase(key);
    merge();
}

bool DummySurf::lookupKey(const std::string& key){
    return originSurf -> lookupKey(key);
}


bool DummySurf::lookupRange(const std::string& left_key, const bool left_inclusive, 
		     const std::string& right_key, const bool right_inclusive){
   
    return originSurf -> lookupRange(left_key,left_inclusive,right_key,right_inclusive);
}



} // namespace surf

#endif // DummySURF_H_