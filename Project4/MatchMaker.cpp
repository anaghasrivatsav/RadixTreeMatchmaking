//
//  MatchMaker.cpp
//  Project4
//
//  Created by Anagha Srivatsav on 3/3/22.
//

#include <stdio.h>
#include "MatchMaker.h"

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    memberDatabase= mdb;
    attributeTranslator = at;
    
}
MatchMaker::~MatchMaker()
{
    
}

bool MatchMaker::customCompare( EmailCount &a,  EmailCount &b)
{
    std::cerr <<"comparing" <<std::endl;
    if(a.count > b.count)
    {
        return true;
    }
    if( a.count < b.count)
    {
        return false;
    }

    
    return (a.email > b.email);
        
}
std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email,int threshold) const
{
    const PersonProfile* pp = memberDatabase.GetMemberByEmail(email);
    std::vector<AttValPair> sourceAttVal=  std::vector<AttValPair>();
    int cycle = pp->GetNumAttValPairs();
   
    // creates a vector of all the attValPairs of this person
    for( int i = 0; i< cycle; i++)
    {
        AttValPair a = AttValPair();
        pp->GetAttVal(i, a);
        (sourceAttVal).push_back(a);
    }
    
    // creates a vector of all the compatible attValPairs of this person
    // uses a set to make sure that there is no repition
    
    std::set<std::string> duplicationPreventioncCompatible= std::set<std::string>();
    std::vector<AttValPair> compatibleAttVal=  std::vector<AttValPair>();
    for( int i = 0; i<sourceAttVal.size(); i++)// for all the attributes of the person
    {
        
        
            std::vector<AttValPair>  specificCompatible= std::vector<AttValPair>();
            specificCompatible= attributeTranslator.FindCompatibleAttValPairs(sourceAttVal[i]); // find all the attributes compatible to this an attribute
            for( int j = 0; j<specificCompatible.size(); j++)
            {
                std::string attribute = specificCompatible[j].attribute;
                //std::cerr <<specificCompatible[j].value<< std::endl;
                std::string value= specificCompatible[j].value;
                
                if( duplicationPreventioncCompatible.find(attribute+value) == duplicationPreventioncCompatible.end())// only if this compatible attval pair is not in the vector alr add it to the vector
                {
                    compatibleAttVal.push_back(specificCompatible[j]);
                }
                duplicationPreventioncCompatible.insert(attribute+value);
            }
           
           
        
    }
    
    RadixTree<int> compatibleCount= RadixTree<int>();
    std::set<std::string> allPeople = std::set<std::string>();
    
        for( int i = 0; i<compatibleAttVal.size(); i++)
        {
            std::vector<std::string> people = std::vector<std::string>();
            people= memberDatabase.FindMatchingMembers(compatibleAttVal[i]);
            
            for( int j =0; j<people.size(); j++ )
            {
                int* x= (compatibleCount.search(people[j]));
                if (x== nullptr)
                {
                    compatibleCount.insert(people[j], 1);
                }
                else
                {
               
                    int y = (*x)+1;
                    int* z= compatibleCount.search(people[j]);
                    (*z)= y;
                    
                  
                }
                allPeople.insert(people[j]);
                
            }
        }
    std::vector<EmailCount> matches = std::vector<EmailCount>();
    for (std::set<std::string>::iterator it=allPeople.begin(); it!=allPeople.end(); ++it)
    {
        int* count = compatibleCount.search((*it));
        if(*(count) >= threshold)
        {
            EmailCount current = EmailCount((*it), *(count));
            matches.push_back(current);
          // insert it into a vector
        }
    }
    
    //sort( matches.begin(), matches.end(), &MatchMaker::customCompare);
    //sort vector
    
    return matches;
    
    
}


