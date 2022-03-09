//
//  MemberDatabase.h
//  Project4
//
//  Created by Anagha Srivatsav on 3/3/22.
//
#include "provided.h"
#include "PersonProfile.h"

#ifndef MemberDatabase_h
#define MemberDatabase_h
class MemberDatabase
{
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
private:
    RadixTree<std::vector<std::string>> m_pairs;
    RadixTree<PersonProfile> m_profiles;
    std::set<std::string> m_added;
    
};


#endif /* MemberDatabase_h */
