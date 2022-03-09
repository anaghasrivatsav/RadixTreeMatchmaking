//
//  AttributeTranslator.cpp
//  Project4
//
//  Created by Anagha Srivatsav on 3/3/22.
//

#include <stdio.h>
#include "AttributeTranslator.h"
#include <fstream>


bool AttributeTranslator::Load(std::string filename)
{
    std::ifstream file(filename);
    std::string line;

    while (getline(file,line))
    {

        int comma = 0;
        int i = 0;
        while( comma !=2)
        {
            
            if(line[i] ==',')
            {
                comma++;
            }
           
           
            i++;
         
           
        }
        //std::cout<<line.substr(0,i-1)<< std::endl;
        std::string second = line.substr(i);
        comma = 0;
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
        
       // std::cout<<line.substr(i).substr(0,k-1)<< std::endl;
      // std::cout<<line.substr(i).substr(k)<< std::endl;
        
        
        
        AttValPair a =  AttValPair( attribute, value);
       if( m_tree.search(line.substr(0,i-1)) == nullptr)
       {
           std::vector<AttValPair> *v= new std::vector<AttValPair>(); // this new is ok because it is inserted into the radix tree-- must delete from the radix tree
           (*v).push_back(AttValPair(attribute, value));
           m_vector_tree.insert( line.substr(0,i-1), v);
           m_keys.insert(line.substr(0,i-1)+attribute+","+value);// add pair into set
       }
       else
       {
           if(m_keys.find(line.substr(0,i-1)+attribute+","+value) == m_keys.end())// if pair is not already in the vector
           {
               std::vector<AttValPair> *v=  *( m_vector_tree.search(line.substr(0,i-1)));
               (*v).push_back(AttValPair(attribute, value));
               m_keys.insert(line.substr(0,i-1)+attribute+","+value);
           }
           
          
       }
        m_tree.insert( line.substr(0,i-1), &a);
        std::cerr << a.attribute<< std::endl;
        
        std::string attr = (*m_tree.search(line.substr(0,i-1)))->attribute;
        std::cerr << attr<< std::endl;
        
        std::vector<AttValPair> *attr1=  *( m_vector_tree.search(line.substr(0,i-1)));
        
        ///std::cerr << << std::endl;
        
       
        
       
    }
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
    
    
    std::string sourceString= source.attribute + "," + source.value;
    if(m_vector_tree.search(sourceString)== nullptr)
    {
        std::vector<AttValPair> v;
        return (v);
    }
   
    std::vector<AttValPair> *v1=  *(m_vector_tree.search(sourceString));
    std::cerr<< "first" << (*v1)[0].attribute << "c"<< std::endl;
    return (*v1);
    
}


// vector of vectors where each sub vector is a vector of AttVal Pairs that are compatible to the source attribute
// vector of just keys and the index of the key corresponds to the index of the vector
// set to determine whether too insert into vectors or not ( all 4 attributes)


// Radix tree from string of source attribute to a vector of attval pairs for that specific string
// u can return the vector at search


