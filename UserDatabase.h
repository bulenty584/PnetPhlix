#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class User;

class UserDatabase
{
    public:
        UserDatabase();
        ~UserDatabase();
        bool load(const std::string& filename);
        User* get_user_from_email(const std::string& email) const;
    
    
    private:
        TreeMultimap<std::string, User*> userD;
        std::vector<User*> totalU;
    
};

#endif // USERDATABASE_INCLUDED

