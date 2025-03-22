// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2214497 - Connor Milford>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// A Category contains one or more Expense Items, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>

#include "item.h"
 

class Category {

    private:
    std::string identifier;
    std::vector<Item> items;

    public:
    Category(std::string categoryIdent);
    ~Category();

    unsigned int size();
    std::string getIdent() const;
    void setIdent(const std::string &ident);

    
};

#endif // CATEGORY_H
