//
//  MemberDatabase.cpp
//  Project4
//
//  Created by Anagha Srivatsav on 3/3/22.
//

#include <stdio.h>
#include "MemberDatabase.h"
#include <fstream>
MemberDatabase::MemberDatabase()
{
    
}
MemberDatabase::~MemberDatabase()
{
    
}
bool MemberDatabase::LoadDatabase(std::string filename)
{
    std::ifstream file(filename);
    std::string line;
    std::string email = "";
    std::string name = "";
    int linenum = 0;
    int attributeNum = 0;

    while (getline(file,line))
    {
        if( line== "")
        {
            linenum= 0;
        }
        else
        {
              if( linenum==0)
              {
                  name = line;
                
              }
              else if ( linenum==1)
              {
                  email = line;
           
                
                  if(m_profiles.search(email)!= nullptr)
                  {
                      return false;
                  }
                  PersonProfile *p= new PersonProfile ( name, email);// good needs this to be dynamically allocated--- inserted into the radix tree
                  m_profiles.insert(email, p);
                
                
                  
              }
            else if( linenum== 2)
            {
                attributeNum= std::stoi(line);
               
            }
            else if( attributeNum> 0)
            {
                PersonProfile *p1= *(m_profiles.search(email));
                
                std::string second = line;
                int comma = 0;
                int k = 0;
                while( comma !=1)
                {
                    
                    if(second[k] ==',')
                    {
                        comma++;
                    }
                   
                   
                    k++;
                 
                   
                }
                std::string attribute=  second.substr(0,k-1);
                std::string value = second.substr(k);
                
                if( m_pairs.search(attribute+","+value)== nullptr)// if this attribute value pair is not already in the tree
                {
                    std::vector<std::string> *v= new std::vector<std::string>(); // create a new vector
                    // ok if this is dynamically allocated bc it is pushed into the radix tree
                    (*v).push_back(email); // push back first email
                    m_added.insert(email+attribute+value); // insert the attribute,value,email into set to prevent duplication
                    m_pairs.insert(attribute+","+value, v); // insert key + email vector into tree
                }
               
                else if ( m_added.find(email+attribute+value)== m_added.end())// if this email, attribute and value are not already in the tree
                {
                    std::vector<std::string> *v = *m_pairs.search(attribute+","+value); // return a pointer to the vector
                    (*v).push_back(email); // insert new email into the vector in the tree
                    m_added.insert(email+attribute+value); // insert into set to prevent future duplication
                }
              
                p1->AddAttValPair(AttValPair(attribute, value));
                
                
                
                
            }
              linenum++;
            
             
          
            
        }

      
    }
    return false;
}


// member data base things that I need to do
// implement a set to check duplicates!!!
std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    std::string attribute= input.attribute;
    std::string value= input.value;
    
    if( m_pairs.search(attribute+","+value)== nullptr)
    {
        std::vector<std::string> v =  std::vector<std::string>();
        return (v);
        
    }
    else
    {
        std::vector<std::string> *v = *m_pairs.search(attribute+","+value);
        return *(v);
    }
    
    
    // if the database has the attval pair return the vector
    // if the database does not have the attval pair return an empty vvector ;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    if( m_profiles.search(email)== nullptr)
    {
        
        return nullptr;
    }

    return *(m_profiles.search(email));
}
