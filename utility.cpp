//
//  utility.cpp
//  PnetPhlix
//
//  Created by Bulent  Yesilyurt on 3/14/23.
//

#include "utility.h"
#include <string>


std::string strToLower(std::string input){
    if (input.size() == 0)
        return " ";
    
    for (int i = 0; i < input.size(); i++)
        input[i] = tolower(input[i]);
    
    return input;
    
}
