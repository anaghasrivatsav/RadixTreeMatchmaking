//
//  main.cpp
//  Project4
//
//  Created by Anagha Srivatsav on 3/3/22.
//

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include "RadixTree.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    AttributeTranslator a;
  a.Load("/Users/anaghasrivatsav/Downloads/Unhinged/translator.txt");
    RadixTree<std::string> b;
    b.insert( "hello", "1");
    assert( *(b.search("hello"))== "1");

    b.insert("hell", "2");
    assert( (*b.search("hell"))== "2");
    b.insert( "cat", "3");
    assert( *(b.search("cat"))== "3");
    b.insert( "cats", "4");
    assert( *(b.search("cats"))== "4");
    b.insert( "bash", "5");
    assert( *(b.search("bash"))== "5");
    b.insert( "cash", "6");
    assert( *(b.search("cash"))== "6");
    b.insert( "tangerine", "7");
    assert( *(b.search("tangerine"))== "7");
    b.insert( "tang", "8");
    assert( *(b.search("tang"))== "8");
    b.insert( "tang", "9");
    assert( *(b.search("tang"))== "9");
    assert( *(b.search("hello"))== "1");
     assert( (*b.search("hell"))== "2");
     assert( *(b.search("cat"))== "3");
     assert( *(b.search("cats"))== "4");
     assert( *(b.search("bash"))== "5");
     assert( *(b.search("cash"))== "6");
     assert( *(b.search("tangerine"))== "7");
     assert( *(b.search("tang"))== "9");
     b.insert( "tang", "9");
     assert( *(b.search("tang"))== "9");

 
    
    PersonProfile pp ("Albedo", "kriedenprinze@monstadt.com");
    pp.AddAttValPair(AttValPair("hello", "hi"));
    pp.AddAttValPair(AttValPair("hello", "hi"));
    assert( pp.GetNumAttValPairs()== 1);
    pp.AddAttValPair(AttValPair("hell", "hi"));
    assert( pp.GetNumAttValPairs()== 2);
    assert(pp.GetName()=="Albedo");
    assert(pp.GetEmail()== "kriedenprinze@monstadt.com");
    pp.AddAttValPair(AttValPair("CS", "isannoying"));
    pp.AddAttValPair(AttValPair("math", "isannoying"));
    pp.AddAttValPair(AttValPair("CS", "isfun"));
    assert( pp.GetNumAttValPairs()== 5);

    AttValPair* attval1 = new AttValPair("attribuet1", "value1");
    for( int i = 0; i< 5; i++)
    {
        pp.GetAttVal(i,*attval1);
        
        std::cerr << attval1->attribute;
        std::cerr << attval1->value << std::endl;
        
    }
     
     
   AttValPair pair1= AttValPair("trait", "transparent");
    std::vector<AttValPair> trans1= a.FindCompatibleAttValPairs(pair1);
    for ( int i = 0; i<trans1.size(); i++)
    {
        std::cerr << i<< std::endl;
        std::cerr<< trans1[i].attribute;
        std::cerr<< trans1[i].value<< std::endl;
    }
    std::cerr << ""<< std::endl;
    std::cerr << ""<< std::endl;
    
    AttValPair pair3= AttValPair("trait", "unlovable");
    std::vector<AttValPair> trans3= a.FindCompatibleAttValPairs(pair3);
    for ( int i = 0; i<trans3.size(); i++)
    {
        std::cerr<< trans3[i].attribute;
        std::cerr<< trans3[i].value<< std::endl;
    }
    
    //eloquent
    //cosplaying
    
    std::cerr << ""<< std::endl;
    std::cerr << ""<< std::endl;
    
    AttValPair pair2= AttValPair("hobby", "eating");
    std::vector<AttValPair> trans2= a.FindCompatibleAttValPairs(pair2);
    assert(trans2.size()== 0);
    
    std::cerr << ""<< std::endl;
    std::cerr << ""<< std::endl;
    std::cerr << ""<< std::endl;
    MemberDatabase m;
    m.LoadDatabase("/Users/anaghasrivatsav/Downloads/Unhinged/members.txt");
    
    
    const PersonProfile* pp1= m.GetMemberByEmail("klee@gmail.com");
    if(pp1!= nullptr)
    {
    for( int i = 0; i< 5; i++)
    {
        pp1->GetAttVal(i,*attval1);
        
        std::cerr << attval1->attribute;
        std::cerr << attval1->value << std::endl;
        
    }
    }
    
    
    const PersonProfile*pp2= m.GetMemberByEmail("ZairDale6049@icloud.com");
    
    int cycle = pp2->GetNumAttValPairs();
    for( int i = 0; i< cycle; i++)
    {
        pp2->GetAttVal(i,*attval1);
        
        std::cerr << attval1->attribute;
        std::cerr << attval1->value << std::endl;
        
    }
    
    
    std::cerr << pp2->GetName();
    assert(pp2->GetName()=="Zaire Dale");
    assert(pp2->GetEmail()== "ZairDale6049@icloud.com" );
    
    std::vector< std::string> match1= m.FindMatchingMembers(pair3);
    sort( match1.begin(), match1.end());
    std::set< std::string> match2;
    
    for( int i = 0; i< match1.size(); i++)
    {
        //std::cerr<< match1[i]<<"matching for pair3" << std::endl;
        match2.insert( match1[i]);
    }
    std::cerr<< match1.size()<< std::endl;
    std::cerr<< match2.size()<< std::endl;
    
    MatchMaker matcher= MatchMaker(m, a);
    std::vector<EmailCount> emailCount = std::vector<EmailCount>();
   ;
    std::cerr<< matcher.IdentifyRankedMatches("ZairDale6049@icloud.com", 5).size() << std::endl;
    
    
    
    
    
    
    
    
    
}
 
 

/*

const std::string MEMBERS_FILE    = "/Users/anaghasrivatsav/Downloads/Unhinged/members.txt";
const std::string TRANSLATOR_FILE = "/Users/anaghasrivatsav/Downloads/Unhinged/translator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

int main() {
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
        ;

    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
      // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

      // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}

*/
