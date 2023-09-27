#include "UserDatabase.h"
#include "User.h"
#include "treemm.h"
#include <iostream>
#include <fstream>

#include <string>
#include <vector>
using namespace std;

UserDatabase::UserDatabase(){}

UserDatabase::~UserDatabase(){
    for (User* m: totalU)
        delete m;
}



bool UserDatabase::load(const string& filename)
{
    
    
    ifstream infile(filename);
    
    if (infile){
        string name;
        string email;
        vector<string> movieIDs;
        int num = 0;
        
        string line;
        
        int count = 1;
        int end = 0;
        
        
        while (getline(infile, line)){
            
            if (line.empty()){
                count = 1;
                movieIDs.clear();
                continue;
            }
            
            else if (count == 1){
                name = line;
            }
            
            else if (count == 2){
                email = line;
            }
            
            else if (count == 3){
                num = stoi(line);
            }
            
            else{
                movieIDs.push_back(line);
                
                if (count == num + 3){
                    User* user = new User(name, email, movieIDs);
                    userD.insert(email, user);
                    totalU.push_back(user);
                }
            }
            
            count++;
            end++;
            
        }
        
    }
    
    else
        return false;
    return true;
            
          
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<string, User*>::Iterator j =  userD.find(email);
    
    if (j.is_valid())
        return j.get_value();
    
    else return nullptr;
}

