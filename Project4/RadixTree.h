//
//  RadixTree.h
//  Project4
//
//  Created by Anagha Srivatsav on 3/3/22.
//

#include <iostream>
#include <map>
#include <unordered_set>


#ifndef RadixTree_h
#define RadixTree_h
template <typename ValueType>
class RadixTree {
public:
 RadixTree()
    {
    // m = new std::map<std::string, std::unordered_set<ValueType>>();
     
 }
 ~RadixTree()
    {
     
    }
    
    
  
 void insert(std::string key, const ValueType& value1)
    {
     
     // covered the case that there is nothing in the radixtree
     if( root== nullptr)
     {
         Node* n = new Node;
         n->word=  key;
         n->value= const_cast<ValueType*>(&value1);
         n->endOfWord = true;
     }
     
     else
     {
         helpInsert(key, value1, root);
     }
      
     
     //(m)[key].insert(value);
     
    }
 ValueType* search(std::string key) const
    {
       
        typename std::map<std::string, std::unordered_set<ValueType>>::const_iterator it = m.begin();
        it= m.find(key);
       
        if ( it == m.end())
        {
            return nullptr;
        }
        else
        {
            typename std::unordered_set<ValueType>::const_iterator it1= (&it->second)->begin();
           // std::cerr << (*it1);
           // return &(*it1);
            
           return const_cast<ValueType*>(&(*it1));
            
            
            
            
            
            
       
        }
    }
private:
    std::map< std::string, std::unordered_set<ValueType>> m;
   
    struct Node{
        std::string word;
        bool endOfWord;
        Node* edges[128];
        ValueType* value;
    };
    
    Node* root;
    void helpInsert( std::string rest, const ValueType &val, Node* current);

};


template<typename ValueType>
void RadixTree<ValueType>::helpInsert( std::string rest, const ValueType &val, Node* current)
{
    if( current->word == rest)
    {
        current->value = const_cast<ValueType*>(&val);
        return;
    }
    if( current->word != "")
    {
        if( current->word.size() >1)
        {
        Node *n = new Node;
        n->word= current->word.substr(1);
        n->value= current->value;
        n->endOfWord= true;
        current->edges[current->word[0]] = n;
        current->word = "";
        current->endOfWord= false;
        current->value= nullptr;
        
     
        helpInsert(rest, &val, current);
        }
        
        else
        {
            Node *n= new Node;
            n->word= "";
            n->value= current->value;
            n->endOfWord= true;
            current->edges[current->word[0]] = n;
            current->word = "";
            current->endOfWord= false;
            current->value= nullptr;
            
            helpInsert(rest, &val, current);
            
        }
        
        
        
    }
    if( rest.size() !=0 && current->edges[rest[0]] == nullptr)
    {
        if( rest.size() >1)
        {
            Node *n = new Node;
            n->word= rest.substr(1);
            n->value= const_cast<ValueType*>(&val);
            n->endOfWord= true;
            current->edges[rest[0]] = n;
            
            return;
        }
        else
        {
            Node *n = new Node;
            n->word= "";
            n->value= const_cast<ValueType*>(&val);
            n->endOfWord= true;
            current->edges[rest[0]] = n;
            
            return;
        }
       
    }
    else
    {
        if( rest.size() > 1)
        {
            helpInsert(rest.substr(1), &val, current->edges[rest[0]] );

        }
        else if ( rest.size()==1)
        {
            helpInsert("", &val, current->edges[rest[0]] );
        }
        else
        {
            current->value = const_cast<ValueType*>(&val);
            current->endOfWord= true;
        }
    }
}


#endif /* RadixTree_h */

