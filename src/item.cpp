// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2214497 - Connor Milford>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include <vector>

#include "item.h"
#include "date.h"

#define NO_ITEM_MSG "Item not found."

// a constructor that takes four parameters, a string identifier,
// a description, an amount, and a date and initialises the object and member data.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};

Item::Item(std::string ident, std::string description, double amount, Date date) :
    ident(ident), description(description), amount(amount), date(date) {}


Item::~Item(){}

// function getIdent, that returns the identifier for the Item.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  auto ident = iObj.getIdent(); = 1

std::string Item::getIdent() {
    return this->ident;
}

// function getDescription, that returns the description for the Item.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  auto ident = iObj.getDescription();

std::string Item::getDescription() {
    return this->description;
}


// Function, setDescription, that takes one parameter, a string for a new
//  Item description, and updates the member variable. It returns nothing.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  auto ident = iObj.setDescription("New Item Description");

void Item::setDescription(std::string description) {
    this->description = description;
}

// Function, addTag, that takes one parameters, a tag
//  string and returns true if the entry was inserted into the
//  container or false if the tag already existed.

bool Item::addTag(std::string tag) {
    auto iterator = find(tags.begin(), tags.end(), tag);

    if (iterator != tags.end()) {
        tags.push_back(tag);
        return true;
    }
    return false;
}





// function deleteTag, that takes one parameter, a tag
// string, deletes it from the container, and returns true if the tag
// string was deleted. If no tag exists with that name, throw an appropriate
// exception.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  iObj.addTag("tag");
//  iObj.deleteTag("tag");

bool Item::deleteTag(std::string tag) {
    auto iterator = find(tags.begin(), tags.end(), tag);

    if (iterator != tags.end()) {
        tags.erase(iterator);
        return true;
    }
    
    throw std::out_of_range(NO_ITEM_MSG);
}










// function, numTags, that takes no parameters and returns an
// unsigned int of the number of tags in the Item contains.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  iObj.numTags(); // 0

unsigned int Item::numTags() {
    return tags.size();
}



// function, containsTag, that takes one parameter, a tag string.
// If the tag exists, return true. Otherwise return false.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  iObj.addTag("tag");
//  iObj.containsTag("tag"); // true

bool Item::containsTag(std::string tag) {
    auto iterator = find(tags.begin(), tags.end(), tag);

    if (iterator != tags.end()) {
        return true;
    }
    return false;
}





// Function, getAmount, that returns the amount for the Item.
double Item::getAmount() {
    return amount;
}

// TODO: Write a function setAmount, that takes one parameter, a double for
// a new amount, and updates the member variable. It returns nothing.

void Item::setAmount(double amount) {
    this->amount = amount;
}

// TODO: Write a function, getDate, that returns the date for the Item.

// TODO: Write a function setDate, that takes one parameter, a date, and updates
// the member variable. It returns nothing.

// TODO: Write an == operator overload for the Item class, such that two
// Item objects are equal only if they have the same identifier, date,
// amount, description, and tags.
// Example:
//  Item iObj1{"Item Name"};
//  Item iObj2{"Item Name"};
//  if(iObj1 == iObj2) {
//   ...
//  }

// TODO: Write a function, str, that takes no parameters and returns a
// std::string of the JSON representation of the data in the Item.
// See the coursework specification for how this JSON should look.
// Example:
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();
