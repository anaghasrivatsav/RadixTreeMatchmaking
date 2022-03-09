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
   // TO DO Check if person profile is nullptr and return an empty vector
    
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
    std::cerr<< compatibleAttVal.size()<< "SIZE" << std::endl;
    
    RadixTree<int> compatibleCount=  RadixTree<int>();
    std::set<std::string> allPeople = std::set<std::string>();
    std::string person;
    int countPeople= 0;
    
        for( int i = 0; i<compatibleAttVal.size(); i++)
        {
            std::vector<std::string> people = memberDatabase.FindMatchingMembers(compatibleAttVal[i]);
            std::cerr << compatibleAttVal[i].attribute;
            std::cerr << compatibleAttVal[i].value<< std::endl;
            std::cerr << people.size() << "number of emails for attval"<< std::endl;
            countPeople+= people.size();
            
            for( int j =0; j<people.size(); j++ )
            {
                 person = (people)[j];
            
                if ( compatibleCount.search(person)== nullptr)
                {
                    compatibleCount.insert(person, 1);
                    
                }
                else
                {
                    int *x= compatibleCount.search(person);
                    //std::cerr << *x << "number of traits"<< std::endl;
               
                    int y = (*x)+1;
                    int* z= compatibleCount.search(person);
                    (*z)= y;
                    std::cerr<< people[j]<< std::endl;
                    std::cerr << *x << "number of traits"<< std::endl;
                    
                  
                }
                if(*compatibleCount.search(person) >= threshold)
                {
                    allPeople.insert(person);
                    std::cerr<< *compatibleCount.search(person)<< "please work count"<< std::endl;
                }
               
                
            }
           
            
        }
    std::cerr << allPeople.size() <<"number of emails"<< std::endl;
    std::cerr << countPeople <<"number of ppl from radix"<< std::endl;
  
    
    std::vector<EmailCount> matches = std::vector<EmailCount>();
    for (std::set<std::string>::iterator it=allPeople.begin(); it!=allPeople.end(); ++it)
    {
        std::string input = *it;
        std::cerr<< input;
        int* count = compatibleCount.search(input);
        if(*(count) >= threshold)
        {
            std::cerr << *count<< " int of count" << std::endl;
            EmailCount current =  EmailCount((*it), *(count));
            matches.push_back(current);
          // insert it into a vector
    }
    }
    
    //sort( matches.begin(), matches.end(), &MatchMaker::customCompare);
    //sort vector
    std::cerr <<matches.size()<< std::endl;
    return matches;
    
    
}


