#ifndef DYNAMICSURF_H_
#define DYNAMICSURF_H_

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

class DynamicSurf{

public:
    //members
    std::map<std::string, bool> hashBuffer;
    SuRF* originSurf;
    int bufferLimit;
    std::map<std::string, bool>* mainMemory;

    //ctor/dctor
    DynamicSurf(){}
    
    DynamicSurf(const std::vector<std::string>& keys, int bufferSize, std::map<std::string, bool>* memory ) {
        originSurf = new SuRF(keys);
        bufferLimit = bufferSize;
        mainMemory = memory;
    }

    DynamicSurf(const std::vector<std::string>& keys, const SuffixType suffix_type,
	 const level_t hash_suffix_len, const level_t real_suffix_len, int bufferSize
     , std::map<std::string, bool>* memory ) {
        originSurf = new SuRF(keys,suffix_type,hash_suffix_len,real_suffix_len);
        bufferLimit = bufferSize;
        mainMemory = memory;

    }
    
    DynamicSurf(const std::vector<std::string>& keys,
	 const bool include_dense, const uint32_t sparse_dense_ratio,
	 const SuffixType suffix_type, const level_t hash_suffix_len, const level_t real_suffix_len, int bufferSize
     , std::map<std::string, bool>* memory ) {
	    originSurf = new SuRF(keys,include_dense,sparse_dense_ratio,suffix_type,hash_suffix_len,real_suffix_len);
        bufferLimit = bufferSize;
        mainMemory = memory;

    }

    ~DynamicSurf(){}

    //functions
    void insertKey(const std::string& key);
    void deleteKey(const std::string& key);
    bool lookupKey(const std::string& key);
    bool lookupRange(const std::string& left_key, const bool left_inclusive, 
		     const std::string& right_key, const bool right_inclusive);

private:
    void merge();
};


void DynamicSurf::merge(){
    std::vector<std::string> keys = {};
    int size = 0;
    for (std::map<std::string, bool>::iterator i = mainMemory->begin(); i != mainMemory->end(); i++){
        keys.push_back(i->first);       
        size++;
    }
    originSurf = new SuRF(keys);
    hashBuffer.clear();
    
    //std::cout << std::endl << "Merged: New Surf of size " << size << " created."  << std::endl;
}


void DynamicSurf::insertKey(const std::string& key){
    hashBuffer.insert({key,true});
    mainMemory->insert({key,true});
    if(hashBuffer.size() == bufferLimit){
        merge();
    }
}

void DynamicSurf::deleteKey(const std::string& key){
    //erase return 0 if not found in buffer
    if( ! hashBuffer.erase(key))
    {
        originSurf->remove(key);
    }
    mainMemory->erase(key);
}

bool DynamicSurf::lookupKey(const std::string& key){
    return originSurf -> lookupKey(key) || (hashBuffer.count(key) > 0);
}


bool hashBufferRangeHelper(std::map<std::string, bool> map,
             const std::string& left_key, const bool left_inclusive, 
		     const std::string& right_key, const bool right_inclusive){
    
    if(left_key.compare(right_key) > 0)
        return false;
    bool leftFlag = false;
    bool rightFlag = false;
    for (std::map<std::string, bool>::iterator i = map.begin(); i != map.end(); i++)
    {
        //leftkey is less than the left boundary in map
        int leftBoundary = i->first.compare(left_key);
        int rightBoundary = i->first.compare(right_key);
        if((leftBoundary >= 0 && left_inclusive) || (leftBoundary > 0 && !left_inclusive ))
            leftFlag = true;
        if(leftFlag &&((rightBoundary <=0 && right_inclusive)||(rightBoundary < 0 && !right_inclusive)))
            rightFlag = true;
        
    }
    return leftFlag && rightFlag;
}

bool DynamicSurf::lookupRange(const std::string& left_key, const bool left_inclusive, 
		     const std::string& right_key, const bool right_inclusive){
   
    return originSurf -> lookupRange(left_key,left_inclusive,right_key,right_inclusive) 
    || (hashBufferRangeHelper(hashBuffer,left_key,left_inclusive,right_key,right_inclusive));
}



} // namespace surf

#endif // DYNAMICSURF_H_
