// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2214497 - Connor Milford
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// An Item class contains multiple 'tags' (e.g., a tag might be 'home' and
// another tag could be 'uni'). An Item also has a description (e.g. 'Costa
// Coffee'), a double amount (e.g. 2.55), and date associated with it. 
// -----------------------------------------------------

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <set>


#include "date.h"


class Item {
    private:
        std::string ident;
        std::string description;
        double amount;
        Date date;
        std::set<std::string> tags;

    public:
        Item(std::string ident, std::string description, double amount, Date date);
        ~Item();

        
        std::string getIdent() const;
        std::string getDescription() const ;
        double getAmount() const; 
        Date getDate() const;
        std::set<std::string> getTags() const;

        void setDescription(const std::string &description);
        void setDate(Date date);
        void setAmount(double amount);

        bool addTag(std::string tag);
        bool containsTag(std::string tag) const;
        void mergeTags(const std::set<std::string> tags);
        bool deleteTag(std::string tag);
        unsigned int numTags() const;

        bool operator!=(const Item &other) const;
        bool operator==(const Item &other) const;
};

#endif // ITEM_H

