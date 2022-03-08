//
//  PersonProfile.cpp
//  Project4
//
//  Created by Anagha Srivatsav on 3/3/22.
//

#include <stdio.h>
#include "PersonProfile.h"


PersonProfile::PersonProfile(std::string name, std::string email)
{
    m_name= name;
    m_email= email;
    m_tree= RadixTree<std::string>();

    m_valpairs= std::vector<AttValPair*>();
   
    m_keys= std::set<std::string>();
    size = 0;
}
PersonProfile::~PersonProfile()
{
    for (std::vector<AttValPair*>::iterator it = m_valpairs.begin() ; it != m_valpairs.end(); ++it)
    {
        delete *it;
    }
}
std::string PersonProfile::GetName() const
{
    return m_name;
}
std::string PersonProfile::GetEmail() const
{
    return m_email;
}
void PersonProfile::AddAttValPair(const AttValPair& attval)
{

    if (m_keys.find(attval.attribute + "," + attval.value) == m_keys.end())
    {
        AttValPair* a = new AttValPair( attval.attribute, attval.value); // pushed into radix tree so its ok if its new
        m_valpairs.push_back(a);
        size++;
    }
   
    
    m_keys.insert(attval.attribute + "," + attval.value);
  
    
  
    
      m_tree.insert(attval.attribute, attval.value);
    
    
       
    
    
    
}
int PersonProfile::GetNumAttValPairs() const
{
    
    return size;
}
bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if( attribute_num >= GetNumAttValPairs()|| attribute_num<0)
    {
        return false;
    }
   
   
        attval.attribute =   m_valpairs[attribute_num]->attribute;
        attval.value= (m_valpairs[attribute_num]->value);
   
    return true;
}
