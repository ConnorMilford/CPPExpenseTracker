#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <functional>



#include "expensetracker.h"
#include "category.h"

#include "lib_json.hpp" 

#define INSERT_UNSUCCESSFUL "Failed to insert or overwrite Category "
#define NO_SUCH_CATEGORY "No such category exists "
#define JSON_PARSE_ERROR "Error when parsing json "
#define FILE_OPEN_ERROR "Error opening file "

using json = nlohmann::json;

// An ExpenseTracker constructor that takes no parameters and constructs an
//  an ExpenseTracker object
//
// Example:
//  ExpenseTracker etObj{};

// A function, size, that takes no parameters and returns an unsigned
//  int of the number of categories the ExpenseTracker contains.
//
// Example:
//  ExpenseTracker etObj{};
//  auto size = etObj.size();

unsigned int ExpenseTracker::size() {
    return categories.size();
}

// A function, newCategory, that takes one parameter, a category
//  identifier, and returns the Category object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Category object cannot be
//  inserted into the container.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");

Category& ExpenseTracker::newCategory(const std::string &ident) {
    auto it = categories.find(Category(ident));

    if (it != categories.end()) {
        return const_cast<Category&>(*it);
    }

    auto result = categories.emplace(Category(ident));

    // result is std::pair<iterator, bool>
    if (!result.second) {  
        throw std::runtime_error(INSERT_UNSUCCESSFUL);
    }

    return const_cast<Category&>(*result.first);
}



// A function, addCategory, that takes one parameter, a Category
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged (see also Category::addItem) and then returns false. Throw a
//  std::runtime_error if the Category object cannot be inserted into the container for whatever reason.
//
// Example:
//  ExpenseTracker etObj{};
//  Category cObj{"categoryIdent"};
//  etObj.addCategory(cObj);

bool ExpenseTracker::addCategory(Category cat) {
    auto iterator = categories.find(cat);

    if (iterator == categories.end()) {
        auto result = categories.emplace(cat);
        auto it = result.first;
        bool inserted = result.second;
        
        if (!inserted) {
            throw std::runtime_error(INSERT_UNSUCCESSFUL);
        }
        return true;   
    }
    return false;
}


// A function, getCategory, that takes one parameter, a Category
//  identifier and returns the Category with that identifier. If no Category
//  exists, throw an appropriate exception.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");
//  auto cObj = etObj.getCategory("categoryIdent");

Category& ExpenseTracker::getCategory(const std::string& ident) {
    for (auto it = categories.begin(); it != categories.end(); ++it) {
        if (it->getIdent() == ident) {
            return const_cast<Category&>(*it);
        }
    }

    // If no matching category is found, throw an exception
    throw std::out_of_range(NO_SUCH_CATEGORY);
}


// A function, deleteCategory, that takes one parameter, a Category
//  identifier, and deletes that category from the container, and returns true
//  if the Category was deleted. If no Category exists, throw an appropriate
//  exception.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");
//  etObj.deleteCategory("categoryIdent");

bool ExpenseTracker::deleteCategory(std::string ident) {
    auto iterator = categories.find(Category(ident));

    if (iterator == categories.end()) {
        throw std::out_of_range(NO_SUCH_CATEGORY);
    } 
    categories.erase(iterator);
    return true;
}

// A function, getSum, that returns the sum of all Category expense
// sums. This consists of the sum of all individual item amounts across all categories.
// If no categories or no items exist return 0.
//
// Example:
//  ExpenseTracker etObj{};
//  Category cObj = etObj.newCategory("categoryIdent");
//  Category cObj2 = etObj.newCategory("categoryIdent2");
//  cObj.newItem("newItemName", "Description", "1.0", Date(2024,12,25));
//  cObj.newItem("newItemName2", "Description", "2.0", Date(2024,12,25));
//  cObj2.newItem("newItemName3", "Description", "3.0", Date(2024,12,25));
//  cObj2.newItem("newItemName4", "Description", "4.0", Date(2024,12,25));
//  auto sum = ejObj.getSum() // 10.0


double ExpenseTracker::getSum() const {
    double totalSum = 0.0;

    for (const auto& category : categories) {
        totalSum += category.getSum();
    }

    return totalSum;
}

// A function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this ExpenseTracker. If the file does not open throw
//  an appropriate exception (either std::runtime_error or a derived class).
//
// A note on clashes:
//  If you encounter two categories with the same identifier, or two expense items with the same
//  identifier within the same category, you may choose whichever category/item is parsed
//  by the nlohmann json library. The json spec on duplicate keys is undefined, so
//  you can default to the behaviour of the nlohmann json library.
// JSON formatting:
//  The JSON file has the following format (see the sample database.json file
//  also provided with the coursework framework):
// {
//   "Studies": {
//     "1": {
//       "amount": 999.99,
//       "date": "2024-12-25",
//       "description": "Laptop",
//       "tags": [
//         "computer",
//         "programming",
//         "uni"
//       ]
//     },
//     ...
//   },
//   "Travel": {
//     "3": {
//       "amount": 164.0,
//       "date": "2024-12-30",
//       "description": "Bus Pass",
//       "tags": [
//         "bus",
//         "uni"
//       ]
//     }
//   },
//   ...
// }
//
// More help:
//  To help you with this function, I've selected the nlohmann::json
//  library that you must use for your coursework. Read up on how to use it
//  here: https://github.com/nlohmann/json. You may not use any other external
//  library other than the one I have provided. You may choose to process the
//  JSON yourself without the help of the library but I guarantee this will be
//  more work.
//
//  Understanding how to use external libraries is part of this coursework! You
//  will need to use this file to deserialize the JSON from string
//  to the JSON object provided by this library. Don't just look at the code
//  provided below, or in the README on the GitHub and despair. Google search,
//  look around, try code out in a separate file to all figure out how to use
//  this library.
//
//  Once you have deserialized the JSON string into an object, you will need to
//  loop through this object, constructing Category and Item objects according
//  to the JSON data in the file.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.load("database.json");

// APPROACH 
// Iterate over json 
// Each key is a category name
// Nested values are items
//
//

void ExpenseTracker::load(const std::string& filePath) {
    try {
       
        // check file exists
        std::ifstream f(filePath);
        if (!f.is_open()) { 
            throw std::runtime_error(FILE_OPEN_ERROR + filePath);
        }

        // parse json
        json data;
        try {
            f >> data;  
        } catch (const json::parse_error& e) {
            throw std::runtime_error(JSON_PARSE_ERROR + std::string(": ") + e.what());
        }

        
        for (auto it = data.begin(); it != data.end(); ++it) {
            // parse category
            const std::string& catIdent = it.key();
            Category& cat = newCategory(catIdent);

            for (auto itemsIt = it.value().begin(); itemsIt != it.value().end(); ++itemsIt) {
                const std::string& itemIdent = itemsIt.key();
                const auto& itemDetails = itemsIt.value();

                // parse item 
                double amount = itemDetails["amount"].get<double>();
                std::string dateStr = itemDetails["date"].get<std::string>();
                std::string description = itemDetails["description"].get<std::string>();

                Item& item = cat.newItem(itemIdent, description, amount, Date(dateStr));

                // add tags 
                const auto& tags = itemDetails["tags"];
                for (const auto& tag : tags) {
                    item.addTag(tag.get<std::string>());
                }
            }
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("ERROR: " + std::string(e.what()));
    }
}



// TODO: Write a function, save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the ExpenseTracker object
//  as JSON.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.load("database.json");
//  ...
//  etObj.save("database.json");

// use ofstream instead of
// nlohmann json since it gives better control, and json lib was returning errors. 

void ExpenseTracker::save(const std::string& filePath) const {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    try {
            // append the string representation of this object to the outfile
            outFile << this->str();     
            outFile.close();   
        if (!outFile) {
            throw std::runtime_error("Failed to write data to file: " + filePath);
        }
    } catch (std::exception &e) {
        if (outFile.is_open()) {
            outFile.close();  // close file if open and error occurs
        }
        throw std::runtime_error("Error when parsing file");  
    }
}




// TODO: Write an == operator overload for the ExpenseTracker class, such that two
//  ExpenseTracker objects are equal only if they have the exact same data.
//
// Example:
//  ExpenseTracker etObj1{};
//  ExpenseTracker etObj2{};
//  if(etObj1 == etObj2) {
//    ...
//  }

// TODO: Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the ExpenseTracker.
//
// Hint:
//  See the coursework specification for how this JSON should look.
//
// Example:
//  ExpenseTracker etObj{};
//  std::string s = etObj.str();

std::string ExpenseTracker::str() const {
    json j;
    for (const Category& category : categories) {
        json categoryJson;
        for (const auto& itemPair : category.getItems()) {
            const std::string itemId = itemPair.first;
            const Item& item = itemPair.second;
            
            json itemJson;
            itemJson["amount"] = item.getAmount();
            itemJson["date"] = item.getDate().str();
            itemJson["description"] = item.getDescription();
            
            // add reverse alphabetical
            json tagsJson = json::array();
            for (const std::string &tag : item.getTags()) {
                tagsJson.push_back(tag);
            }
            
            itemJson["tags"] = tagsJson;
            
            categoryJson[itemId] = itemJson;
        }
        
        j[category.getIdent()] = categoryJson;
    }
    
    return j.dump(-1, ' ', false) + "\n";
}



