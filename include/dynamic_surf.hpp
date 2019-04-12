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
    std::vector<SuRF*> surfCollection;
    int bufferLimit;
    int surfCollectionSizeLimit;

    //ctor/dctor
    DynamicSurf(){}
    
    DynamicSurf(const std::vector<std::string>& keys, int bufferSize, int surfCollectionSize ) {
        SuRF* surf = new SuRF(keys);
        surfCollection.push_back(surf);
        bufferLimit = bufferSize;
        surfCollectionSizeLimit = surfCollectionSize;
    }

    DynamicSurf(const std::vector<std::string>& keys, const SuffixType suffix_type,
	 const level_t hash_suffix_len, const level_t real_suffix_len, int bufferSize, int surfCollectionSize) {
        SuRF* surf = new SuRF(keys,suffix_type,hash_suffix_len,real_suffix_len);
        surfCollection.push_back(surf);
        bufferLimit = bufferSize;
        surfCollectionSizeLimit = surfCollectionSize;
    }
    
    DynamicSurf(const std::vector<std::string>& keys,
	 const bool include_dense, const uint32_t sparse_dense_ratio,
	 const SuffixType suffix_type, const level_t hash_suffix_len, const level_t real_suffix_len, int bufferSize, int surfCollectionSize) {
	    SuRF* surf = new SuRF(keys,include_dense,sparse_dense_ratio,suffix_type,hash_suffix_len,real_suffix_len);
        surfCollection.push_back(surf);
        bufferLimit = bufferSize;
        surfCollectionSizeLimit = surfCollectionSize;
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
    std::cout << "Not Implemented" << std::endl;
}


void DynamicSurf::insertKey(const std::string& key){
    hashBuffer[key] = true;
    std::cout << hashBuffer.size() << std::endl;
    if(hashBuffer.size() == bufferLimit){
        std::vector<std::string> v;
        for(std::map<std::string, bool>::iterator it = hashBuffer.begin(); it != hashBuffer.end(); ++it) {
            v.push_back(it->first);
        }
        SuRF* surf = new SuRF(v);
        surfCollection.push_back(surf);
        std::cout <<" a "<< surfCollection.size() << std::endl;
        if(surfCollection.size() == surfCollectionSizeLimit){
            merge();
        }
    }
}

bool DynamicSurf::lookupKey(const std::string& key){

    bool retVal = false;
    for(int i =0; i<surfCollection.size(); i++){
        SuRF* surf = surfCollection[i];
        retVal = surf -> lookupKey(key) || retVal;
    }
    return retVal || (hashBuffer.count(key) > 0);
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
        std::cout << i->first << leftBoundary << rightBoundary <<std::endl;
        
    }
    return leftFlag && rightFlag;
}

bool DynamicSurf::lookupRange(const std::string& left_key, const bool left_inclusive, 
		     const std::string& right_key, const bool right_inclusive){
    bool retVal = false;
    for(int i =0; i<surfCollection.size(); i++){
        SuRF* surf = surfCollection[i];
        retVal = surf -> lookupRange(left_key,left_inclusive,right_key,right_inclusive) || retVal;
    }
    return retVal || (hashBufferRangeHelper(hashBuffer,left_key,left_inclusive,right_key,right_inclusive));
}



} // namespace surf

#endif // DYNAMICSURF_H_