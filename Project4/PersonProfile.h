//
//  PersonProfile.h
//  Project4
//
//  Created by Anagha Srivatsav on 3/3/22.
//
#include <iostream>
#include <vector>
#include "RadixTree.h"
#include "provided.h"
#include <set>


#ifndef PersonProfile_h
#define PersonProfile_h

class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email);
    ~PersonProfile();
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string m_name;
    std::string m_email;
    RadixTree<std::string> m_tree;
   
    std::vector<AttValPair*> m_valpairs;
    std::set<std::string> m_keys;
    int size;
    
    
    
};



#endif /* PersonProfile_h */
