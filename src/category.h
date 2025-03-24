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
#include <unordered_map>


#include "item.h"
 

class Category {

    private:
    std::string identifier;
    std::unordered_map<std::string, Item> items;

    public:
    Category(std::string categoryIdent);
    ~Category();

    unsigned int size();
    std::string getIdent() const;
    void setIdent(const std::string &ident);

    Item& newItem(const std::string &ident, const std::string &description,
                              double amount, const Date &date);
    bool addItem(const Item &item);
    Item& getItem(const std::string &ident);
    bool deleteItem(const std::string &ident);

    double getSum() const;
    
    bool operator==(const Category &cat) const;
};

namespace std {
    template <>
    struct hash<Category> {
        size_t operator()(const Category& cat) const {
            return hash<std::string>()(cat.getIdent()); 
        }
    };
}

#endif // CATEGORY_H
