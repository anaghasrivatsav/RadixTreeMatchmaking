//
//  MatchMaker.h
//  Project4
//
//  Created by Anagha Srivatsav on 3/3/22.
//


#include "MemberDatabase.h"
#include "AttributeTranslator.h"

#ifndef MatchMaker_h
#define MatchMaker_h
class MatchMaker
{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email,int threshold) const;
private:
    MemberDatabase memberDatabase;
    AttributeTranslator attributeTranslator;
    bool customCompare( const EmailCount &a, const EmailCount &b);
    
    
};

#endif /* MatchMaker_h */
