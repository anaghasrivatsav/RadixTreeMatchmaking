//
//  RadixTree.h
//  Project4
//
//  Created by Anagha Srivatsav on 3/3/22.
//

#include <iostream>
#include <map>
#include <unordered_set>


#ifndef RadixTree_h
#define RadixTree_h
template <typename ValueType>
class RadixTree {
public:
 RadixTree()
    {
    // m = new std::map<std::string, std::unordered_set<ValueType>>();
     
 }
 ~RadixTree()
    {
     
 }
 void insert(std::string key, const ValueType& value)
    {
      
     
     (m)[key].insert(value);
     
    }
 ValueType* search(std::string key) const
    {
       
        typename std::map<std::string, std::unordered_set<ValueType>>::const_iterator it = m.begin();
        it= m.find(key);
       
        if ( it == m.end())
        {
            return nullptr;
        }
        else
        {
            typename std::unordered_set<ValueType>::const_iterator it1= (&it->second)->begin();
           // std::cerr << (*it1);
           // return &(*it1);
            
           return const_cast<ValueType*>(&(*it1));
            
            
            
            
            
            
       
        }
    }
private:
    std::map< std::string, std::unordered_set<ValueType>> m;
};

#endif /* RadixTree_h */


