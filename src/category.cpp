// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2214497 - Connor Milford>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
#include <string>
#include <numeric>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>


#include "category.h"
#include "item.h"

#define INSERT_UNSUCCESSFUL "Failed to insert or overwrite Item: "
#define NO_SUCH_ITEM "No item such found: " 

// A constructor that takes one parameter, a string identifier and
// initialises the object and member data.
//
// Example:
//  Category c{"categoryIdent"};

Category::Category(std::string ident) : identifier(ident) {

}


Category::~Category(){
    
}

// TODO: Write a function, size, that takes no parameters and returns an unsigned
// int of the number of Items in the Category contains.
//
// Example:
//  Category c{"categoryIdent"};
//  unsigned int size = c.size();

unsigned int Category::size(){
    return this->items.size();
}





// A Function, getIdent, that returns the identifier for the Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string ident = cObj.getIdent();

std::string Category::getIdent() const {
    return this->identifier;
}

// A function, setIdent, that takes one parameter, a string for a new
// Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");

void Category::setIdent(const std::string &ident) {
    this->identifier = ident;
}


// A function, newItem, that takes four parameters, an Item
// identifier (string), description (string), amount (double), and date (Date)
// and returns the Item object as a reference.  If an object with the same
// identifier already exists, then the existing object should be overwritten by
// the new Item. Throw a std::runtime_error if the Item object cannot be
// inserted into the container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");

Item& Category::newItem(const std::string& ident, const std::string& description, 
                double amount, const Date& date) {
    try {
        auto it = items.find(ident);
        if (it != items.end()) {
            it->second = Item(ident, description, amount, date);
            return it->second;
        } else {
            auto ret = items.emplace(ident, Item(ident, description, amount, date));
            return ret.first->second;
        }
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string(INSERT_UNSUCCESSFUL) + std::string(e.what()));
    }
}



// A function, addItem, that takes one parameter, an Item object, and
// returns true if the object was successfully inserted. If an object with the
// same identifier already exists, then:
//  - the tags should be merged
//  - description should be overwritten by the item being added
//  - amount should be overwritten by the item being added
//  - date overwritten by the item being added
//  - false should be returned.
//
// Example:
//  Category cObj{"categoryIdent"};
//  Item iObj{"itemIdent"};
//  cObj.addItem(iObj);


bool Category::addItem(const Item &item) {
    try {
        // find item by identifier
        auto iterator = items.find(item.getIdent());

        //  add if doesnt exist
        if (iterator == items.end()) {
            items.emplace(item.getIdent(), item); 
            return true;
        } else {
            // if doesnt exist 

            iterator->second.mergeTags(item.getTags());
            iterator->second.setDescription(item.getDescription());
            iterator->second.setAmount(item.getAmount());
            iterator->second.setDate(item.getDate());
            
            return false;
        }
    } catch (const std::exception &e) {
        // catch any exception and throw runtime_error 
        throw std::runtime_error(std::string(INSERT_UNSUCCESSFUL) + std::string(e.what()));
    }
}


// A function, getItem, that takes one parameter, an Item identifier
// (a string) and returns the Item as a reference. If no Item exists, throw an
// appropriate exception.
//
// Hint: See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
//  auto iObj = cObj.getItem("newItemName");

Item& Category::getItem(const std::string &ident) {

     auto iterator = items.find(ident);

        
        if (iterator == items.end()) {
            throw std::out_of_range(std::string(NO_SUCH_ITEM));
        } else {
            return iterator->second;
        }

}






// A function, getSum, that returns the sum of all Item amounts in
// the category. If no Item exists return 0.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName", "Description", "1.0", Date(2024,12,25));
//  cObj.newItem("newItemName2", "Description", "2.0", Date(2024,12,25));
//  auto sum = cObj.getSum() // 3.0

double Category::getSum() {
    
    double totalAmount = std::accumulate(
        items.begin(), items.end(), 0.0,  
        [](double sum, const std::pair<const std::string, Item>& pair) {
            return sum + pair.second.getAmount();  
        }
    );
    
    return totalAmount;
}


// A function, deleteItem, that takes one parameter, an Item
// identifier (a string), deletes the item with that identifier from the
// container, and returns true if the Item was deleted. If no Item exists, throw
// an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
//  bool result = cObj.deleteItem("newItemName");

bool Category::deleteItem(const std::string &ident) {
    auto iterator = items.find(ident);

    if (iterator == items.end()) {
        throw std::out_of_range(std::string(NO_SUCH_ITEM));
    } else {
        items.erase(ident);
        return true;
    }
}






// An == operator overload for the Category class, such that two
// Category objects are equal only if they have the same identifier and same
// Items.
//
// Example:
//  Category cObj1{"categoryIdent1"};
//  cObj.newItem("newItemName");
//  Category cObj2{"categoryIdent2"};
//  if(cObj1 == cObj2) {
//    ...
//  }

bool Category::operator==(const Category& cat) const {
    if (this->identifier != cat.identifier) {
        return false;
    }
    
    if (this->items.size() != cat.items.size()) {
        return false;
    }

    for (const auto& pair : this->items) {
        auto it = cat.items.find(pair.first);
        if (it == cat.items.end() || pair.second != it->second) {
            return false;
        }
    }

    return true;
}


// TODO: Write a function, str, that takes no parameters and returns a
// std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();



