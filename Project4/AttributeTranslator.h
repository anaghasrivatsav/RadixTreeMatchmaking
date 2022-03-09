//
//  AttributeTranslator.h
//  Project4
//
//  Created by Anagha Srivatsav on 3/3/22.
//

#include <iostream>
#include "provided.h"
#include "RadixTree.h"
#include <vector>
#include <set>
#ifndef AttributeTranslator_h
#define AttributeTranslator_h
class AttributeTranslator
{
public:
    AttributeTranslator()
    {
        
    }
   
    ~AttributeTranslator()
    {
        
    }
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    RadixTree<AttValPair> m_tree;
    RadixTree<std::vector<AttValPair>> m_vector_tree;
    std::set<std::string> m_keys;
    
};



#endif /* AttributeTranslator_h */
